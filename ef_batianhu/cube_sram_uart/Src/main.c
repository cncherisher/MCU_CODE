
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usart.h"
#include "gpio.h"
#include "fsmc.h"

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define Bank1_SRAM4_ADDR ((uint32_t)0x6C000000)
#define SRAM_SIZE 0x100000
/* USER CODE END PD */

void SystemClock_Config(void);
uint8_t SRAM_Test2(void);

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
	MX_FSMC_Init();
	led_init();
	key_init();
	SRAM_Test2();
  /* Infinite loop */
  while (1)
  {
		printf("hello!\r\n");
		HAL_Delay(1000);
		LED1_TOGGLE();
  }
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}


/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

uint8_t SRAM_Test2()
{
	uint32_t temp;
	printf("pointer method test!\r\n");
	*( uint8_t*) (Bank1_SRAM4_ADDR ) = (uint8_t)0xAA;
	temp = *( uint8_t*) (Bank1_SRAM4_ADDR );
	printf("write = 0xAA, read = 0x%X\r\n", temp);
	if(temp != 0xAA)
	{
		printf("test 8bit failed!\r\n");
		return 1;
	}
	//----------------------------------------------------------//
	*( uint16_t*) (Bank1_SRAM4_ADDR+10 ) = (uint16_t)0xBBBB;
	temp = *( uint16_t*) (Bank1_SRAM4_ADDR+10 );
	printf("write = 0xBBBB, read = 0x%X\r\n", temp);
	if(temp != 0xBBBB)
	{
		printf("test 16bit failed!\r\n");
		return 1;
	}
	//----------------------------------------------------------//
	*( uint32_t*) (Bank1_SRAM4_ADDR+20 ) = (uint32_t)0xCCCCCCCC;
	temp = *( uint32_t*) (Bank1_SRAM4_ADDR+20 );
	printf("write = 0xCCCCCCCC, read = 0x%X\r\n", temp);
		if(temp != 0xCCCCCCCC)
	{
		printf("test 31bit failed!\r\n");
		return 1;
	}
	return 0;
}

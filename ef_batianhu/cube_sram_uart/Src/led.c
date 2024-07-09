#include "led.h"

/**
 * @brief       初始化LED相关IO口, 并使能时钟
 * @param       无
 * @retval      无
 */
void led_init(void)
{
    GPIO_InitTypeDef gpio_init_struct;
    
    LED0_GPIO_CLK_ENABLE();                                 /* LED0 clock enable */
    LED1_GPIO_CLK_ENABLE();                                 /* LED1 clock enable */

    gpio_init_struct.Pin = LED0_GPIO_PIN;                   /* LED0 pin */
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;            /* push pull output */
    gpio_init_struct.Pull = GPIO_PULLUP;                    /* pull up */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;          /* high speed */
    HAL_GPIO_Init(LED0_GPIO_PORT, &gpio_init_struct);      

    gpio_init_struct.Pin = LED1_GPIO_PIN;                   /* LED1 pin */
    HAL_GPIO_Init(LED1_GPIO_PORT, &gpio_init_struct);       
	
    gpio_init_struct.Pin = LED2_GPIO_PIN;                   /* LED1 pin */
    HAL_GPIO_Init(LED2_GPIO_PORT, &gpio_init_struct);      
	
    LED0(1);                                                /* disable LED0 */
    LED1(1);                                                /* disable LED1 */
		LED2(1);                                                /* disable LED1 */
}
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_exti.h"
#include "CH430.h"
#include "button.h"

/*******************************************************************************
* Definitions
*******************************************************************************/
#define BUTTON_1_CMD        "button_1 pressed"
#define BUTTON_2_CMD        "button_2_pressed"
#define CMD_1_SIZE           16
#define CMD_2_SIZE           16
/*******************************************************************************
* API
*******************************************************************************/
void BUTTON_Init(void)
{
    /* open clock gate */
    RCC_APB2PeriphClockCmd(BUTTON_CLK,ENABLE);
    /* config */
    GPIO_InitTypeDef buttonInitStrucre;
    EXTI_InitTypeDef buttonInterruptInitStruce;

    buttonInitStrucre.GPIO_Pin   = BUTTON_1_PIN | BUTTON_2_PIN;
    buttonInitStrucre.GPIO_Mode  = GPIO_Mode_IPU;
    GPIO_Init(BUTTON_GPIO,&buttonInitStrucre);

    /* Interrupt config */
    
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource14);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource15);
    buttonInterruptInitStruce.EXTI_Line     = BUTTON_1_EXTI_LINE;
    buttonInterruptInitStruce.EXTI_Mode     = EXTI_Mode_Interrupt;
    buttonInterruptInitStruce.EXTI_LineCmd  = ENABLE;
    buttonInterruptInitStruce.EXTI_Trigger  = EXTI_Trigger_Falling;
    EXTI_Init(&buttonInterruptInitStruce);

    buttonInterruptInitStruce.EXTI_Line     = BUTTON_2_EXTI_LINE;
    buttonInterruptInitStruce.EXTI_Mode     = EXTI_Mode_Interrupt;
    buttonInterruptInitStruce.EXTI_LineCmd  = ENABLE;
    buttonInterruptInitStruce.EXTI_Trigger  = EXTI_Trigger_Falling;
    EXTI_Init(&buttonInterruptInitStruce);
    
    /* Enable NVIC */
    NVIC_EnableIRQ(BUTTON_IRQn);
}

void EXTI15_10_IRQHandler()
{
    if(EXTI_GetFlagStatus(BUTTON_1_EXTI_LINE) == SET)
    {
        EXTI_ClearFlag(BUTTON_1_EXTI_LINE);
        CH430_Send(BUTTON_1_CMD, CMD_2_SIZE);
    }
    
    if(EXTI_GetFlagStatus(BUTTON_2_EXTI_LINE) == SET)
    {
        EXTI_ClearFlag(BUTTON_2_EXTI_LINE);
        CH430_Send(BUTTON_2_CMD, CMD_2_SIZE);
    }
}
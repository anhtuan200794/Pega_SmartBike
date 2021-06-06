#ifndef __BUTTON_H__
#define __BUTTON_H__
#include "stm32f10x.h"
/*******************************************************************************
* Definitions
*******************************************************************************/
#define BUTTON_GPIO             GPIOC
#define BUTTON_CLK              RCC_APB2Periph_GPIOC
#define BUTTON_1_PIN            GPIO_Pin_14
#define BUTTON_2_PIN            GPIO_Pin_15
/* interrupt */
#define BUTTON_2_EXTI_LINE      EXTI_Line15
#define BUTTON_1_EXTI_LINE      EXTI_Line14
#define BUTTON_IRQn             EXTI15_10_IRQn
/*******************************************************************************
* API
*******************************************************************************/
void BUTTON_Init(void);
#endif    /*__BUTTON_H__*/
/*******************************************************************************
* EOF
*******************************************************************************/

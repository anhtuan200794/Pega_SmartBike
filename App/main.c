/*
 * Copyright (c) 2021
 * VitechSolutions, ltd.
 * All Rights Reserved
 *
 *
 * Description:
 *
 * Author: TuanNA
 *
 * Last Changed By:  $Author: TuanNA $
 * Revision:         $Revision: xxx $
 * Last Changed:     $Date: xxx $
 */

/******************************************************************************/
/*                              INCLUDE FILES                                 */
/******************************************************************************/
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "system_stm32f10x.h"
#include "stm32f10x_usart.h"
#include "systick.h"
#include "button.h"
#include "speaker.h"
#include "clock.h"
#include "nvic.h"
#include "BT966.h"
#include "CH430.h"


/******************************************************************************/
/*                          PRIVATE FUNCTIONS DECLERATION                     */
/******************************************************************************/

/**
 * @func   main
 * @brief  None
 * @param  
 * @retval None
 */
int main()
{
    SYSTICK_Init();
	BT966_Init();
	CH430_Init();
    BUTTON_Init();
    SPEAKER_Init();
	NVIC_Config_Init();
    CH430_Send("\r\n",2);
	while (1)
	{
        BT966_Proc();
		CH430_Proc();
//		GPIO_WriteBit(GPIOC,GPIO_Pin_13,Bit_SET);
//		SYSTICK_Delay_ms(500);
//		GPIO_WriteBit(GPIOC,GPIO_Pin_13,Bit_RESET);
//        SYSTICK_Delay_ms(500);
	}
}

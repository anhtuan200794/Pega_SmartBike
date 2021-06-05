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
#include "system_stm32f10x.h"
#include "stm32f10x_usart.h"
#include "systick.h"
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
	SystemInit();
	SYSTICK_Init();
	BT966_Init();
	CH430_Init();
	NVIC_Config_Init();
	while (1)
	{
            BT966_Proc();
            //CH430_Proc();
            //CH430_Send(&c,1);
	}
}

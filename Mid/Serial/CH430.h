/*
 *  CH430.h
 *
 *  Created on: Dec 25, 2020
 *      Author: TuanNA
 */

#ifndef _CH430_H_
#define _CH430_H_

/******************************************************************************/
/*                              INCLUDE FILES                                 */
/******************************************************************************/
#include "stm32f10x.h"

/******************************************************************************/
/*                              DEFINE                                        */
/******************************************************************************/

#define CH430_COM               USART1
#define CH430_BAUDRATE          115200
#define CH430_COMMAND_MAX_SIZE  1
#define CH430_QUEUE_SIZE        2


void CH430_Init(void);
void CH430_CallBackHandle(USART_TypeDef* USARTx);
void CH430_Proc(void);
void CH430_Send(u8* buff, u8 length);

#endif /*_CH430_H_*/
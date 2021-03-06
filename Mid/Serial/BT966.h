/*
 *  BT966.h
 *
 *  Created on: Dec 25, 2020
 *      Author: TuanNA
 */

#ifndef _BT966_H_
#define _BT966_H_

/******************************************************************************/
/*                              INCLUDE FILES                                 */
/******************************************************************************/
#include "stm32f10x.h"

/******************************************************************************/
/*                              DEFINE                                        */
/******************************************************************************/

#define BT966_COM               USART2
#define BT966_BAUDRATE          115200
#define BT966_COMMAND_MAX_SIZE  50
#define BT966_QUEUE_SIZE        10

void BT966_Init(void);
void BT966_CallBackHandle(USART_TypeDef* USARTx);
void BT966_Proc(void);
void BT966_Send(u8* buff, u8 length);

#endif /*_BT966_H_*/
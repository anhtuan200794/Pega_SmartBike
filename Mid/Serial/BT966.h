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
#define BT966_MAX_BUFF          100
#define INCOMING_CALL           "+HFPSTAT=5"
#define INCOMING_CALL_CMD_SIZE  21
#define BT966_COM               USART2
#define BT966_BAUDRATE          115200
#define BT966_COMMAND_MAX_SIZE  1
#define BT966_QUEUE_SIZE        100


void BT966_Init(void);
void BT966_CallBackHandle(USART_TypeDef* USARTx);
void BT966_Proc(void);
void BT966_Send(u8* buff, u8 length);

#endif /*_BT966_H_*/
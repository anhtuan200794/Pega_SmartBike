/*
 *  GPS.h
 *
 *  Created on: Dec 25, 2020
 *      Author: TuanNA
 */

#ifndef _GPS_H_
#define _GPS_H_

/******************************************************************************/
/*                              INCLUDE FILES                                 */
/******************************************************************************/
#include "stm32f10x.h"

/******************************************************************************/
/*                              DEFINE                                        */
/******************************************************************************/

#define GPS_COM               USART3
#define GPS_BAUDRATE          115200
#define GPS_COMMAND_MAX_SIZE  50
#define GPS_QUEUE_SIZE        5


void GPS_Init(void);
void GPS_CallBackHandle(USART_TypeDef* USARTx);
void GPS_Proc(void);
void GPS_Send(u8* buff, u8 length);

#endif /*_GPS_H_*/
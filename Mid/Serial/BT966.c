/*
 *  BT966.c
 *
 *  Created on: Dec 25, 2020
 *      Author: TuanNA
 */

#include "BT966.h"
#include "uart.h"
#include "stm32f10x_usart.h"
#include "xor.h"
#include "queue.h"
#include "CH430.h"
#include "string.h"

QUEUEx_t BT966CommandQueue;
u8 BT966CommandBuff[BT966_COMMAND_MAX_SIZE];

/******************************************************************************/
/*                              FUNCTION                                      */
/******************************************************************************/

/*!
 * @brief functions BT966_Init.
 *
 */
void BT966_Init(void)
{
    UART_Init(BT966_COM, BT966_BAUDRATE, USART_Mode_Tx|USART_Mode_Rx);
    UART_CallBackInit(BT966_COM, BT966_CallBackHandle);
    QUEUE_Init(&BT966CommandQueue, (u8*)BT966CommandBuff,\
                BT966_QUEUE_SIZE, BT966_COMMAND_MAX_SIZE);
    USART_Cmd(BT966_COM, ENABLE);
}

/*!
 * @brief functions UART_CallBackHandle.
 *
 */
void BT966_CallBackHandle(USART_TypeDef* USARTx)
{
    static u8 revByteCount = 0;
    static u8 revBuff[BT966_COMMAND_MAX_SIZE];
    u8 revByte = 0;
    
    revByte = UART_GetData(USARTx);
    revBuff[revByteCount++] = revByte;
    if(revByteCount >= BT966_COMMAND_MAX_SIZE)
    {
        QUEUE_Push(&BT966CommandQueue, revBuff);
        revByteCount = 0;
    }
}

/*!
 * @brief functions BT966_Proc.
 *
 */
void BT966_Proc(void)
{
    u8* BT966_command;
    if(!QUEUE_Empty(&BT966CommandQueue))
    {
        QUEUE_Get(&BT966CommandQueue, (u8*)&BT966_command);
        CH430_Send(BT966CommandBuff , BT966_COMMAND_MAX_SIZE);
    }
}

/*!
 * @brief functions BT966_Send.
 *
 */
void BT966_Send(u8* buff, u8 length)
{
    UART_SendData(BT966_COM, buff, length);
}
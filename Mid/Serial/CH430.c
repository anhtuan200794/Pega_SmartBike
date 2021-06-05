/*
 *  CH430.c
 *
 *  Created on: Dec 25, 2020
 *      Author: TuanNA
 */

#include "CH430.h"
#include "uart.h"
#include "stm32f10x_usart.h"
#include "xor.h"
#include "queue.h"

QUEUEx_t CH430CommandQueue;
u8 CH430CommandBuff[CH430_QUEUE_SIZE];

/******************************************************************************/
/*                              FUNCTION                                      */
/******************************************************************************/

/*!
 * @brief functions CH430_Init.
 *
 */
void CH430_Init(void)
{
    UART_Init(CH430_COM, CH430_BAUDRATE, USART_Mode_Tx|USART_Mode_Rx);
    UART_CallBackInit(CH430_COM, CH430_CallBackHandle);
    QUEUE_Init(&CH430CommandQueue, (u8*)CH430CommandBuff,\
                CH430_QUEUE_SIZE, CH430_COMMAND_MAX_SIZE);
    USART_Cmd(CH430_COM, ENABLE);
}

/*!
 * @brief functions UART_CallBackHandle.
 *
 */
void CH430_CallBackHandle(USART_TypeDef* USARTx)
{
    static u8 revByteCount = 0;
    static u8 revBuff[CH430_COMMAND_MAX_SIZE];
    u8 revByte = 0;
    
    revByte = UART_GetData(USART1);
    revBuff[revByteCount++] = revByte;
    if(revByteCount >= CH430_COMMAND_MAX_SIZE)
    {
        QUEUE_Push(&CH430CommandQueue, revBuff);
        revByteCount = 0;
    }
}

/*!
 * @brief functions CH430_Proc.
 *
 */
void CH430_Proc(void)
{
    static char CH430_command;
    if(!QUEUE_Empty(&CH430CommandQueue))
    {
        QUEUE_Get(&CH430CommandQueue, (u8*)&CH430_command);
        CH430_Send((u8*)&CH430_command,1);
    }
}

/*!
 * @brief functions CH430_Send.
 *
 */
void CH430_Send(u8* buff, u8 length)
{
    UART_SendData(CH430_COM, buff, length);
}
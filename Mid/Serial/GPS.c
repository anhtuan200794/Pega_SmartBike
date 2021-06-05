/*
 *  GPS.c
 *
 *  Created on: Dec 25, 2020
 *      Author: TuanNA
 */

#include "GPS.h"
#include "uart.h"
#include "stm32f10x_usart.h"
#include "xor.h"
#include "queue.h"

QUEUEx_t GPSCommandQueue;
u8 GPSCommandBuff[GPS_COMMAND_MAX_SIZE];

/******************************************************************************/
/*                              FUNCTION                                      */
/******************************************************************************/

/*!
 * @brief functions GPS_Init.
 *
 */
void GPS_Init(void)
{
    UART_Init(GPS_COM, GPS_BAUDRATE, USART_Mode_Tx|USART_Mode_Rx);
    UART_CallBackInit(GPS_COM, GPS_CallBackHandle);
    QUEUE_Init(&GPSCommandQueue, (u8*)GPSCommandBuff,\
                GPS_QUEUE_SIZE, GPS_COMMAND_MAX_SIZE);
    USART_Cmd(GPS_COM, ENABLE);
}

/*!
 * @brief functions UART_CallBackHandle.
 *
 */
void GPS_CallBackHandle(USART_TypeDef* USARTx)
{
    static u8 revByteCount = 0;
    static u8 revBuff[GPS_COMMAND_MAX_SIZE];
    u8 revByte = 0;
    
    revByte = UART_GetData(USARTx);
    revBuff[revByteCount++] = revByte;
        if(revByteCount >= GPS_COMMAND_MAX_SIZE)
    {
        QUEUE_Push(&GPSCommandQueue, revBuff);
        revByteCount = 0;
    }
}

/*!
 * @brief functions GPS_Proc.
 *
 */
void GPS_Proc(void)
{
    u8* GPS_command;
    if(!QUEUE_Empty(&GPSCommandQueue))
    {
        QUEUE_Get(&GPSCommandQueue, (u8*)&GPS_command);
    }

}

/*!
 * @brief functions GPS_Send.
 *
 */
void GPS_Send(u8* buff, u8 length)
{
    UART_SendData(GPS_COM, buff, length);
}
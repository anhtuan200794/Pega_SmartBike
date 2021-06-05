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
uint8_t BT966CommandBuff[BT966_COMMAND_MAX_SIZE] = {'\0'};
uint8_t BT966BuffIndex = 0;
/******************************************************************************/
/*                              FUNCTION                                      */
/******************************************************************************/

static void BT966_ClearCmdBuff()
{
    int i = 0;
    while(BT966CommandBuff[i]!= '\0')
    {
        BT966CommandBuff[i]='\0';
        i++;
    }
}
/*!
 * @brief functions BT966_Init.
 *
 */
void BT966_Init(void)
{
    UART_Init(BT966_COM, BT966_BAUDRATE, USART_Mode_Tx|USART_Mode_Rx);
    UART_CallBackInit(BT966_COM, BT966_CallBackHandle);
    /* QUEUE_Init(&BT966CommandQueue, (u8*)BT966CommandBuff,\
                BT966_QUEUE_SIZE, BT966_COMMAND_MAX_SIZE); */
    USART_Cmd(BT966_COM, ENABLE);
}

/*!
 * @brief functions UART_CallBackHandle.
 *
 */
void BT966_CallBackHandle(USART_TypeDef* USARTx)
{
    BT966CommandBuff[BT966BuffIndex] = UART_GetData(BT966_COM);
    CH430_Send(&BT966CommandBuff[BT966BuffIndex],1);
    BT966BuffIndex++;
    if(BT966CommandBuff[BT966BuffIndex] == '\n')
    {
        //if(strstr((char*)BT966CommandBuff, INCOMING_CALL))
        //    CH430_Send(BT966CommandBuff,INCOMING_CALL_CMD_SIZE);
        /* clear command buffer */
        //BT966_ClearCmdBuff();
        BT966BuffIndex = 0;
    }
}

/*!
 * @brief functions BT966_Proc.
 *
 */
void BT966_Proc(void)
{
  ;
}

/*!
 * @brief functions BT966_Send.
 *
 */
void BT966_Send(u8* buff, u8 length)
{
    UART_SendData(BT966_COM, buff, length);
}
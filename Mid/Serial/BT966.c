/*
 *  BT966.c
 *
 *  Created on: Dec 25, 2020
 *      Author: TuanNA
 */

#include "BT966.h"
#include "uart.h"
#include "stm32f10x_usart.h"
#include "CH430.h"
#include "string.h"

uint8_t BT966CommandBuff[BT966_MAX_BUFF];
volatile uint8_t BT966CommanIndex;
/******************************************************************************/
/*                              FUNCTION                                      */
/******************************************************************************/
static void ClearCommandBuff()
{
    int i;
    for(i = 0; (i< BT966_MAX_BUFF)&&(BT966CommandBuff[i+3]); i++)
    {
        BT966CommandBuff[i] = '\0';
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
    USART_Cmd(BT966_COM, ENABLE);
}

/*!
 * @brief functions UART_CallBackHandle.
 *
 */
void BT966_CallBackHandle(USART_TypeDef* USARTx)
{
    /* static u8 revByteCount =0;
    static u8 revBuff[BT966_COMMAND_MAX_SIZE];
    u8 revByte = 0;
    
    revByte = UART_GetData(USART2);
    revBuff[revByteCount++] = revByte;
    if(revByteCount >= BT966_COMMAND_MAX_SIZE)
    {
        QUEUE_Push(&BT966CommandQueue, revBuff);
        revByteCount = 0;
    } */
    BT966CommandBuff[BT966CommanIndex] = UART_GetData(BT966_COM);
    BT966CommanIndex++;
    if((BT966CommanIndex >= BT966_PREDICT_SIZE_BUFF)&&(BT966CommandBuff[BT966CommanIndex-1] == '\n'))
        BT966CommanIndex = 0;
}

/*!
 * @brief functions BT966_Proc.
 *
 */
void BT966_Proc(void)
{
    /* static char BT966_command[BT966_QUEUE_SIZE*BT966_COMMAND_MAX_SIZE];
    static u8 count =0;
    u8 *p = NULL;
    if(!QUEUE_Empty(&BT966CommandQueue))
    {
        QUEUE_Get(&BT966CommandQueue, (u8*)&BT966_command[count]);
        count++;
        if((count >= BT966_QUEUE_SIZE) || (BT966_command[count] == '\n'))
        {
            p = strstr(BT966_command,INCOMING_CALL);
            if(*p)
            {
                CH430_Send(p,21);
            }
            CH430_Send((u8*)BT966_command,(count));
            count = 0;
        }
    } */
    char *IncomingCallEvent = NULL;
    IncomingCallEvent = strstr((char *)BT966CommandBuff,INCOMING_CALL);
    if(IncomingCallEvent!=NULL)
    {
        CH430_Send((uint8_t*)IncomingCallEvent,INCOMING_CALL_EVENT_SIZE);
        ClearCommandBuff();
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
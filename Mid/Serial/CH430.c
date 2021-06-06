/*
 *  CH430.c
 *
 *  Created on: Dec 25, 2020
 *      Author: TuanNA
 */

#include "CH430.h"
#include "uart.h"
#include "timer3.h"
#include "speaker.h"
#include "stm32f10x_usart.h"
#include "xor.h"
#include "systick.h"
#include "queue.h"

/*******************************************************************************
* Definitions
*******************************************************************************/
#define SET_SPEAK     0
#define RESET_SPEAK   1
/*******************************************************************************
* Variable
*******************************************************************************/
volatile uint8_t IS_SPEAKER_ON_FLAG = RESET_SPEAK;
volatile uint8_t IsSpeak;
QUEUEx_t CH430CommandQueue;
u8 CH430CommandBuff[CH430_QUEUE_SIZE];

/******************************************************************************/
/*                              FUNCTION                                      */
/******************************************************************************/
void CH430_Speak()
{
    IsSpeak = !IsSpeak;
}
/*!
 * @brief functions CH430_Init.
 *
 */
void CH430_Init(void)
{
    UART_Init(CH430_COM, CH430_BAUDRATE, USART_Mode_Tx|USART_Mode_Rx);
    UART_CallBackInit(CH430_COM, CH430_CallBackHandle);
    TIMER3_Init();
    TIMER3_CallbackInit(CH430_Speak);
    USART_Cmd(CH430_COM, ENABLE);
}

/*!
 * @brief functions UART_CallBackHandle.
 *
 */
void CH430_CallBackHandle(USART_TypeDef* USARTx)
{
    uint8_t revbyte;
    revbyte = UART_GetData(CH430_COM);
    if(revbyte == '1')
    {
        IS_SPEAKER_ON_FLAG = SET_SPEAK;
        TIMER3_Start();
    }
    else
    {
        TIMER3_Stop();
        IsSpeak = 0;
        IS_SPEAKER_ON_FLAG = RESET_SPEAK;
    }
}

/*!
 * @brief functions CH430_Proc.
 *
 */
void CH430_Proc(void)
{
    static uint8_t speakCountTime = 0;
    if(IS_SPEAKER_ON_FLAG == SET_SPEAK)
    {
        if(IsSpeak)
        {
            speakCountTime++;
            SPEAKER_ON();
            SYSTICK_Delay_ms(60);
            SPEAKER_OFF();
            IsSpeak = !IsSpeak;
        }
        if(speakCountTime == 5)
        {
            IS_SPEAKER_ON_FLAG = RESET_SPEAK;
            TIMER3_Stop();
        }
    }
    else
        speakCountTime = 0;
}


/*!
 * @brief functions CH430_Send.
 *
 */
void CH430_Send(u8* buff, u8 length)
{
    UART_SendData(CH430_COM, buff, length);
}
/*
 *  uart.c
 *
 *  Created on: Dec 25, 2020
 *      Author: Truong VV
 */

#include "uart.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "CH430.h"
#include "GPS.h"
#include "BT966.h"

/******************************************************************************/
/*                              DECLARE VARIABLE                              */
/******************************************************************************/

type_UartCallBackInit type_Uart1CallBackFunc = NULL;
type_UartCallBackInit type_Uart2CallBackFunc = NULL;
type_UartCallBackInit type_Uart3CallBackFunc = NULL;

/******************************************************************************/
/*                              FUNCTION                                      */
/******************************************************************************/

void UART_PinInit(USART_TypeDef *USARTx)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    if (USARTx == CH430_COM)
    {
        /* Remap pin A9 A10 -> B6 B7 */
        GPIO_PinRemapConfig(GPIO_Remap_USART1,ENABLE);
        /*Config USART1 Rx as input floating */
        GPIO_InitStructure.GPIO_Pin = UART1_RxPin;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_Init(UART1_GPIO, &GPIO_InitStructure);
        /*Config USART1 Tx as alternate function pp*/
        GPIO_InitStructure.GPIO_Pin = UART1_TxPin;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_Init(UART1_GPIO, &GPIO_InitStructure);
    }
    else if (USARTx == BT966_COM)
    {
        /*Config USART2 Rx as input floating */
        GPIO_InitStructure.GPIO_Pin = UART2_RxPin;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_Init(UART2_GPIO, &GPIO_InitStructure);
        /*Config USART2 Tx as alternate function pp*/
        GPIO_InitStructure.GPIO_Pin = UART2_TxPin;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_Init(UART2_GPIO, &GPIO_InitStructure);
    }
    else if (USARTx == GPS_COM)
    {
        /*Config USART3 Rx as input floating */
        GPIO_InitStructure.GPIO_Pin = UART3_RxPin;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_Init(UART3_GPIO, &GPIO_InitStructure);
        /*Config USART3 Tx as alternate function pp*/
        GPIO_InitStructure.GPIO_Pin = UART3_TxPin;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_Init(UART3_GPIO, &GPIO_InitStructure);
    }
}

void UART_ClockInit(USART_TypeDef *USARTx)
{
    if (USARTx == CH430_COM)
    {
        /*Enable GPIO clock*/
        RCC_APB2PeriphClockCmd(UART1_GPIO_CLK, ENABLE);
        /*Enable AFIO clock*/
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
        /*Enable UART clock*/
        RCC_APB2PeriphClockCmd(UART1_CLK, ENABLE);
    }
    else if (USARTx == BT966_COM)
    {
        /*Enable GPIO clock*/
        RCC_APB2PeriphClockCmd(UART2_GPIO_CLK, ENABLE);
        /*Enable AFIO clock*/
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
        /*Enable UART clock*/
        RCC_APB1PeriphClockCmd(UART2_CLK, ENABLE);
    }
    else if (USARTx == GPS_COM)
    {
        /*Enable GPIO clock*/
        RCC_APB2PeriphClockCmd(UART3_GPIO_CLK, ENABLE);
        /*Enable AFIO clock*/
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
        /*Enable UART clock*/
        RCC_APB2PeriphClockCmd(UART3_CLK, ENABLE);
    }
}

void UART_Init(USART_TypeDef *USARTx, u32 baudrate, u16 mode)
{
    USART_InitTypeDef USART_InitStructure;
    UART_ClockInit(USARTx);
    UART_PinInit(USARTx);

    /*UARTx Config*/
    USART_InitStructure.USART_BaudRate = baudrate;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = mode;

    /*USART Config Init*/
    USART_Init(USARTx, &USART_InitStructure);

    /* Enable USARTx Receive interrupts */
    USART_ITConfig(USARTx, USART_IT_RXNE, ENABLE);

    /*Enable UARTx*/
    USART_Cmd(USARTx, DISABLE);
}

void UART_CallBackInit(USART_TypeDef *USARTx, type_UartCallBackInit pHandle)
{
    if (USARTx == CH430_COM)
    {
        type_Uart1CallBackFunc = pHandle;
    }
    else if (USARTx == BT966_COM)
    {
        type_Uart2CallBackFunc = pHandle;
    }
    else if (USARTx == GPS_COM)
    {
        type_Uart3CallBackFunc = pHandle;
    }
}

void USART1_IRQHandler(void)
{
    if ((USART1->SR & USART_FLAG_RXNE) != (u16)RESET)
    {
        type_Uart1CallBackFunc(USART1);
    }
}
void USART2_IRQHandler(void)
{
    USART_GetITStatus(USART2,USART_IT_ORE);
    type_Uart2CallBackFunc(USART2);
}

void USART3_IRQHandler(void)
{
    if ((USART3->SR & USART_FLAG_RXNE) != (u16)RESET)
    {
        type_Uart1CallBackFunc(USART3);
    }
}

void UART_SendData(USART_TypeDef *USARTx, u8 *buff, u8 len)
{
    for (u8 i = 0; i < len; i++)
    {
      
        USART_SendData(USARTx, buff[i]);
        while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);
        
    }
}

u8 UART_GetData(USART_TypeDef *USARTx)
{
    u8 datarx;
    //while (USART_GetFlagStatus(USARTx, USART_FLAG_RXNE) == RESET)
        ;
    datarx = (u8)USART_ReceiveData(USARTx);
    return datarx;
}
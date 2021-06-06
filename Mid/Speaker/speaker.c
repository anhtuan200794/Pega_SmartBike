#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "speaker.h"

/*******************************************************************************
* API
*******************************************************************************/
void SPEAKER_Init()
{
    /* open clock gate */
    RCC_APB2PeriphClockCmd(SPEAKER_CLK,ENABLE);
    GPIO_InitTypeDef speakerInitPinStruce;
    speakerInitPinStruce.GPIO_Pin   = SPEAKER_PIN;
    speakerInitPinStruce.GPIO_Mode  = GPIO_Mode_Out_PP;
    speakerInitPinStruce.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(SPEAKER_GPIO, &speakerInitPinStruce);
}

void SPEAKER_ON()
{
    GPIO_SetBits(SPEAKER_GPIO, SPEAKER_PIN);
}

void SPEAKER_OFF()
{
    GPIO_ResetBits(SPEAKER_GPIO, SPEAKER_PIN);
}
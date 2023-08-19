/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2021/06/06
 * Description        : Main program body.
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/

/*
 *@Note
 Timer DMA routines:
 TIM1_CH1(PA8)
 This example demonstrates using DMA to output PWM through TIM1_CH1(PA8) pin.

*/

#include "debug.h"
#include "util.h"
#include "ws2812.h"
#include "led.h"

void GPIO_INIT(void) {
	GPIO_InitTypeDef GPIO_InitStructure = {0};

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main(void) {
    USART_Printf_Init(115200);
    SystemCoreClockUpdate();
    printf("SystemClk:%d\r\n", SystemCoreClock);
    printf("ChipID:%08x\r\n", DBGMCU_GetCHIPID());
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    SysTickInit();
	GPIO_INIT();
    initLed();


	ws2812SetLed(0, 0xFF0000);
	ws2812SetLed(1, 0x00FF00);
	ws2812SetLed(2, 0x0000FF);
	ws2812SetLed(3, 0xFFFFFF);
	ws2812SetLed(4, 0xFF0000);

	GPIO_SetBits(GPIOA, GPIO_Pin_6);

    while (1) {
        // ws2812SetLed(0, 0);
        // delay(500);
        // ws2812SetLed(0, 0xFF0000);
        // delay(500);
        loopLed();
    }

}
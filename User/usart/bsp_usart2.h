#ifndef __USART2DMA_H
#define	__USART2DMA_H


#include "stm32f10x.h"
#include <stdio.h>

#define  USART2_RX_BUFF_SIZE            255 
#define  DEBUG_USART2_IRQ                USART2_IRQn
#define  DEBUG_USART2_IRQHandler         USART2_IRQHandler

extern uint8_t Usart2_Rx_Buf[USART2_RX_BUFF_SIZE];


// 串口工作参数宏定义
#define  DEBUG_USART2                   USART2
#define  DEBUG_USART2_CLK                RCC_APB1Periph_USART2
#define  DEBUG_USART2_APBxClkCmd         RCC_APB1PeriphClockCmd
#define  DEBUG_USART2_BAUDRATE           115200

// USART GPIO 引脚宏定义
#define  DEBUG_USART2_GPIO_CLK           (RCC_APB2Periph_GPIOA)
#define  DEBUG_USART2_GPIO_APBxClkCmd    RCC_APB2PeriphClockCmd
    
#define  DEBUG_USART2_TX_GPIO_PORT       GPIOA   
#define  DEBUG_USART2_TX_GPIO_PIN        GPIO_Pin_2
#define  DEBUG_USART2_RX_GPIO_PORT       GPIOA
#define  DEBUG_USART2_RX_GPIO_PIN        GPIO_Pin_3

// 串口对应的DMA请求通道
#define  USART2_TX_DMA_CHANNEL     DMA1_Channel7
#define  USART2_RX_DMA_CHANNEL     DMA1_Channel6
// 外设寄存器地址
#define  USART2_DR_ADDRESS        (USART2_BASE+0x04)
// 一次发送的数据量
#define  SENDBUFF2_SIZE            20

void USART2_Config(void);
void HMISends(char *str);
void HMISendb(uint8_t k);

#endif /* __USART2DMA_H */


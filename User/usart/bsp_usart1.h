#ifndef __USART1DMA_H
#define	__USART1DMA_H


#include "stm32f10x.h"
#include <stdio.h>

#define  USART1_RX_BUFF_SIZE            255 
#define  DEBUG_USART1_IRQ                USART1_IRQn
#define  DEBUG_USART1_IRQHandler         USART1_IRQHandler

extern uint8_t Usart1_Rx_Buf[USART1_RX_BUFF_SIZE];


// 串口工作参数宏定义
#define  DEBUG_USART1                   USART1
#define  DEBUG_USART1_CLK                RCC_APB2Periph_USART1
#define  DEBUG_USART1_APBxClkCmd         RCC_APB2PeriphClockCmd
#define  DEBUG_USART1_BAUDRATE           115200

// USART GPIO 引脚宏定义
#define  DEBUG_USART1_GPIO_CLK           (RCC_APB2Periph_GPIOA)
#define  DEBUG_USART1_GPIO_APBxClkCmd    RCC_APB2PeriphClockCmd
    
#define  DEBUG_USART1_TX_GPIO_PORT       GPIOA   
#define  DEBUG_USART1_TX_GPIO_PIN        GPIO_Pin_9
#define  DEBUG_USART1_RX_GPIO_PORT       GPIOA
#define  DEBUG_USART1_RX_GPIO_PIN        GPIO_Pin_10

// 串口对应的DMA请求通道
#define  USART1_TX_DMA_CHANNEL     DMA1_Channel4
#define  USART1_RX_DMA_CHANNEL     DMA1_Channel5
// 外设寄存器地址
#define  USART1_DR_ADDRESS        (USART1_BASE+0x04)
// 一次发送的数据量
#define  SENDBUFF1_SIZE            20

void USART1_Config(void);
void USART1_DMA_Config(void);
void Usart_SendString( USART_TypeDef * pUSARTx, char *str);

#endif /* __USART1DMA_H */

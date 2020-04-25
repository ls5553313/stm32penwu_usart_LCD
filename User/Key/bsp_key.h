#ifndef __KEY_H
#define	__KEY_H


#include "stm32f10x.h"

//  引脚定义
#define    KEY1_GPIO_CLK     RCC_APB2Periph_GPIOA
#define    KEY1_GPIO_PORT    GPIOA			   
#define    KEY1_GPIO_PIN		 GPIO_Pin_1

#define    KEY2_GPIO_CLK     RCC_APB2Periph_GPIOA
#define    KEY2_GPIO_PORT    GPIOA		   
#define    KEY2_GPIO_PIN		 GPIO_Pin_4

#define    KEY3_GPIO_CLK     RCC_APB2Periph_GPIOA
#define    KEY3_GPIO_PORT    GPIOA		   
#define    KEY3_GPIO_PIN		 GPIO_Pin_5

#define    KEY4_GPIO_CLK     RCC_APB2Periph_GPIOA
#define    KEY4_GPIO_PORT    GPIOA		   
#define    KEY4_GPIO_PIN		 GPIO_Pin_6

#define    KEY5_GPIO_CLK     RCC_APB2Periph_GPIOA
#define    KEY5_GPIO_PORT    GPIOA		   
#define    KEY5_GPIO_PIN		 GPIO_Pin_7

#define    KEY6_GPIO_CLK     RCC_APB2Periph_GPIOB
#define    KEY6_GPIO_PORT    GPIOB		   
#define    KEY6_GPIO_PIN		 GPIO_Pin_5

#define    KEY7_GPIO_CLK     RCC_APB2Periph_GPIOB
#define    KEY7_GPIO_PORT    GPIOB		   
#define    KEY7_GPIO_PIN		 GPIO_Pin_10

#define    KEY8_GPIO_CLK     RCC_APB2Periph_GPIOB
#define    KEY8_GPIO_PORT    GPIOB		   
#define    KEY8_GPIO_PIN		 GPIO_Pin_8

#define    KEY9_GPIO_CLK     RCC_APB2Periph_GPIOB
#define    KEY9_GPIO_PORT    GPIOB		   
#define    KEY9_GPIO_PIN		 GPIO_Pin_9

#define    KEY10_GPIO_CLK     RCC_APB2Periph_GPIOB
#define    KEY10_GPIO_PORT    GPIOB		   
#define    KEY10_GPIO_PIN		 GPIO_Pin_4

#define    KEY11_GPIO_CLK     RCC_APB2Periph_GPIOB
#define    KEY11_GPIO_PORT    GPIOB		   
#define    KEY11_GPIO_PIN		 GPIO_Pin_3

#define    KEY12_GPIO_CLK     RCC_APB2Periph_GPIOA
#define    KEY12_GPIO_PORT    GPIOA		   
#define    KEY12_GPIO_PIN		 GPIO_Pin_15

#define    KEY13_GPIO_CLK     RCC_APB2Periph_GPIOA
#define    KEY13_GPIO_PORT    GPIOA		   
#define    KEY13_GPIO_PIN		 GPIO_Pin_8

 /** 按键按下标置宏
	*  按键按下为高电平，设置 KEY_ON=1， KEY_OFF=0
	*  若按键按下为低电平，把宏设置成KEY_ON=0 ，KEY_OFF=1 即可
	*/
#define KEY_ON	0
#define KEY_OFF	1

void Key_GPIO_Config(void);
void FK_GPIO_Config(void);
uint8_t Key_Scan_Low(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin);
uint8_t Key_Scan_High(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin);
uint8_t Key_Scan_High1(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin);


#endif /* __KEY_H */


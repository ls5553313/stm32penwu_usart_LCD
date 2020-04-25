#ifndef __LED_H
#define	__LED_H


#include "stm32f10x.h"


/* 定义LED连接的GPIO端口, 用户只需要修改下面的代码即可改变控制的LED引脚 */
#define LED1_GPIO_PORT    	GPIOB		              /* GPIO端口 */
#define LED1_GPIO_CLK 	    RCC_APB2Periph_GPIOB		/* GPIO端口时钟 */
#define LED1_GPIO_PIN			GPIO_Pin_15		        

#define LED2_GPIO_PORT    	GPIOB		              /* GPIO端口 */
#define LED2_GPIO_CLK 	    RCC_APB2Periph_GPIOB		/* GPIO端口时钟 */
#define LED2_GPIO_PIN			GPIO_Pin_14		

#define LED3_GPIO_PORT    	GPIOB              /* GPIO端口 */
#define LED3_GPIO_CLK 	    RCC_APB2Periph_GPIOB		/* GPIO端口时钟 */
#define LED3_GPIO_PIN			GPIO_Pin_13		

#define LED4_GPIO_PORT    	GPIOB		              /* GPIO端口 */
#define LED4_GPIO_CLK 	    RCC_APB2Periph_GPIOB		/* GPIO端口时钟 */
#define LED4_GPIO_PIN			GPIO_Pin_12		

#define LED5_GPIO_PORT    	GPIOA		              /* GPIO端口 */
#define LED5_GPIO_CLK 	    RCC_APB2Periph_GPIOA		/* GPIO端口时钟 */
#define LED5_GPIO_PIN			GPIO_Pin_11		

#define LED6_GPIO_PORT    	GPIOA		              /* GPIO端口 */
#define LED6_GPIO_CLK 	    RCC_APB2Periph_GPIOA		/* GPIO端口时钟 */
#define LED6_GPIO_PIN			GPIO_Pin_12		





/** the macro definition to trigger the led on or off 
  * 1 - off
  *0 - on
  */
#define ON  0
#define OFF 1

/* 使用标准的固件库控制IO*/
#define LED1(a)	if (a)	\
					GPIO_SetBits(LED1_GPIO_PORT,LED1_GPIO_PIN);\
					else		\
					GPIO_ResetBits(LED1_GPIO_PORT,LED1_GPIO_PIN)

#define LED2(a)	if (a)	\
					GPIO_SetBits(LED2_GPIO_PORT,LED2_GPIO_PIN);\
					else		\
					GPIO_ResetBits(LED2_GPIO_PORT,LED2_GPIO_PIN)




/* 直接操作寄存器的方法控制IO */
#define	digitalHi(p,i)		 {p->BSRR=i;}	 //输出为高电平		
#define digitalLo(p,i)		 {p->BRR=i;}	 //输出低电平
#define digitalToggle(p,i) {p->ODR ^=i;} //输出反转状态


/* 定义控制IO的宏 */
#define LED1_TOGGLE		 digitalToggle(LED1_GPIO_PORT,LED1_GPIO_PIN)
#define ZHU_ON		   digitalHi(LED1_GPIO_PORT,LED1_GPIO_PIN)
#define ZHU_OFF			   digitalLo(LED1_GPIO_PORT,LED1_GPIO_PIN)

#define LED2_TOGGLE		 digitalToggle(LED2_GPIO_PORT,LED2_GPIO_PIN)
#define CONG_ON		   digitalHi(LED2_GPIO_PORT,LED2_GPIO_PIN)
#define CONG_OFF		   digitalLo(LED2_GPIO_PORT,LED2_GPIO_PIN)

#define LED3_TOGGLE		 digitalToggle(LED3_GPIO_PORT,LED3_GPIO_PIN)
#define ZHA_ON		   digitalHi(LED3_GPIO_PORT,LED3_GPIO_PIN)
#define ZHA_OFF			   digitalLo(LED3_GPIO_PORT,LED3_GPIO_PIN)

#define LED4_TOGGLE		 digitalToggle(LED4_GPIO_PORT,LED4_GPIO_PIN)
#define FA_ON		   digitalHi(LED4_GPIO_PORT,LED4_GPIO_PIN)
#define FA_OFF	   digitalLo(LED4_GPIO_PORT,LED4_GPIO_PIN)

#define LED5_TOGGLE		 digitalToggle(LED5_GPIO_PORT,LED5_GPIO_PIN)
#define ZHANGZENG_ON	   digitalHi(LED5_GPIO_PORT,LED5_GPIO_PIN)
#define ZHANGZENG_OFF			   digitalLo(LED5_GPIO_PORT,LED5_GPIO_PIN)

#define LED6_TOGGLE		 digitalToggle(LED6_GPIO_PORT,LED6_GPIO_PIN)
#define ZHANGJIAN_ON		   digitalHi(LED6_GPIO_PORT,LED6_GPIO_PIN)
#define ZHANGJIAN_OFF			   digitalLo(LED6_GPIO_PORT,LED6_GPIO_PIN)



void LED_GPIO_Config(void);

#endif /* __LED_H */

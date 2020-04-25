#ifndef __BSP_ADVANCETIME_H
#define __BSP_ADVANCETIME_H


#include "stm32f10x.h"


/************高级定时器TIM参数定义，只限TIM1和TIM8************/
// 当使用不同的定时器的时候，对应的GPIO是不一样的，这点要注意
// 这里我们使用高级控制定时器TIM1

#define            ADVANCE_TIM                   TIM4
#define            ADVANCE_TIM_APBxClock_FUN     RCC_APB1PeriphClockCmd
#define            ADVANCE_TIM_CLK               RCC_APB1Periph_TIM4

// 输入捕获能捕获到的最小的频率为 72M/{ (ARR+1)*(PSC+1) }
#define            ADVANCE_TIM_PERIOD            (0xFFFF-1)
#define            ADVANCE_TIM_PSC               (0xFFFF-1)

// 中断相关宏定义
#define            ADVANCE_TIM_IRQ               TIM4_IRQn
#define            ADVANCE_TIM_IRQHandler        TIM4_IRQHandler

// TIM1 输入捕获通道1
#define            ADVANCE_TIM_CH1_GPIO_CLK      RCC_APB2Periph_GPIOB
#define            ADVANCE_TIM_CH1_PORT          GPIOB
#define            ADVANCE_TIM_CH1_PIN           GPIO_Pin_6

#define            ADVANCE_TIM_IC1PWM_CHANNEL    TIM_Channel_1
#define            ADVANCE_TIM_IC2PWM_CHANNEL    TIM_Channel_2

/**************************函数声明********************************/

void ADVANCE_TIM_Init(void);


#endif	/* __BSP_ADVANCETIME_H */



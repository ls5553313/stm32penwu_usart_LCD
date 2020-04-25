/**
  *********************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2018-xx-xx
  * @brief   FreeRTOS V9.0.0  + STM32 固件库例程
  *********************************************************************
  * @attention
  *
  * 实验平台:野火 STM32 全系列开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  **********************************************************************
  */ 
 
/*
*************************************************************************
*                             包含的头文件
*************************************************************************
*/ 
#include <stdlib.h>
#include <stdio.h>
/* FreeRTOS头文件 */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "event_groups.h"
/* 开发板硬件bsp头文件 */
#include "bsp_led.h"
#include "bsp_key.h"
#include "delay.h"
#include "bsp_usart1.h"
#include "./usart/bsp_usart2.h"
#include "tasks.h"
#include "bsp_adc.h"
#include "./led/bsp_led.h" 
#include "./i2c/bsp_i2c_ee.h"
#include "bsp_GeneralTim.h" 


extern uint8_t SendBuff1[SENDBUFF1_SIZE];
extern uint8_t SendBuff2[SENDBUFF2_SIZE];
extern __IO uint16_t ADC_ConvertedValue[NOFCHANEL];  //ADC模拟转换电压
extern float ADC_ConvertedValueLocal1;     // 局部变量，用于保存转换计算后的电压值 	 
extern float ADC_ConvertedValueLocal2;     // 局部变量，用于保存转换计算后的电压值 	
extern uint8_t zhangli_qidong;
extern uint8_t yunxing_zhuangtai;

/**************************** 任务句柄 ********************************/
/* 
 * 任务句柄是一个指针，用于指向一个任务，当任务创建好之后，它就具有了一个任务句柄
 * 以后我们要想操作这个任务都需要通过这个任务句柄，如果是自身的任务操作自己，那么
 * 这个句柄可以为NULL。
 */
static TaskHandle_t AppTaskCreate_Handle = NULL;/* 创建任务句柄 */
static TaskHandle_t Jiting_Task_Handle = NULL;/* LED任务句柄 */
static TaskHandle_t Main_Task_Handle = NULL;/* KEY任务句柄 */
static TaskHandle_t ADC_Task_Handle = NULL;/* KEY任务句柄 */
static TaskHandle_t Diandong_Task_Handle = NULL;/* KEY任务句柄 */
static TaskHandle_t Kaiguan_Task_Handle = NULL;/* KEY任务句柄 */
static TaskHandle_t Zhuangtai_Task_Handle = NULL;/* KEY任务句柄 */
extern TimerHandle_t Swtmr1_Handle;   /* 软件定时器句柄 */

/********************************** 内核对象句柄 *********************************/
/*
 * 信号量，消息队列，事件标志组，软件定时器这些都属于内核的对象，要想使用这些内核
 * 对象，必须先创建，创建成功之后会返回一个相应的句柄。实际上就是一个指针，后续我
 * 们就可以通过这个句柄操作这些内核对象。
 *
 * 内核对象说白了就是一种全局的数据结构，通过这些数据结构我们可以实现任务间的通信，
 * 任务间的事件同步等各种功能。至于这些功能的实现我们是通过调用这些内核对象的函数
 * 来完成的
 * 
 */
QueueHandle_t Test_Queue =NULL;

/******************************* 全局变量声明 ************************************/
/*
 * 当我们在写应用程序的时候，可能需要用到一些全局变量。
 */

/******************************* 宏定义 ************************************/
/*
 * 当我们在写应用程序的时候，可能需要用到一些宏定义。
 */
#define  QUEUE_LEN    4   /* 队列的长度，最大可包含多少个消息 */
#define  QUEUE_SIZE   4   /* 队列中每个消息大小（字节） */


/*
*************************************************************************
*                             函数声明
*************************************************************************
*/
static void AppTaskCreate(void);/* 用于创建任务 */

static void Jiting_Task(void* pvParameters);/* Test_Task任务实现 */
static void Main_Task(void* pvParameters);/* KEY_Task任务实现 */
static void ADC_Task(void* pvParameters);/* KEY_Task任务实现 */
static void Diandong_Task(void* pvParameters);/* KEY_Task任务实现 */
static void Kaiguan_Task(void* pvParameters);/* KEY_Task任务实现 */
static void Zhuangtai_Task(void* pvParameters);/* KEY_Task任务实现 */
static void Swtmr1_Callback(void* parameter);

static void BSP_Init(void);/* 用于初始化板载相关资源 */

/*****************************************************************
  * @brief  主函数
  * @param  无
  * @retval 无
  * @note   第一步：开发板硬件初始化 
            第二步：创建APP应用任务
            第三步：启动FreeRTOS，开始多任务调度
  ****************************************************************/
int main(void)
{	
  BaseType_t xReturn = pdPASS;/* 定义一个创建信息返回值，默认为pdPASS */
	
	SystemInit();           //系统初始化
	
  /* 开发板硬件初始化 */
  BSP_Init();  
 
  /* 创建Test_Queue */
  Test_Queue = xQueueCreate((UBaseType_t ) QUEUE_LEN,/* 消息队列的长度 */
                            (UBaseType_t ) QUEUE_SIZE);/* 消息的大小 */
  
  
   /* 创建AppTaskCreate任务 */
  xReturn = xTaskCreate((TaskFunction_t )AppTaskCreate,  /* 任务入口函数 */
                        (const char*    )"AppTaskCreate",/* 任务名字 */
                        (uint16_t       )512,  /* 任务栈大小 */
                        (void*          )NULL,/* 任务入口函数参数 */
                        (UBaseType_t    )1, /* 任务的优先级 */
                        (TaskHandle_t*  )&AppTaskCreate_Handle);/* 任务控制块指针 */ 
  /* 启动任务调度 */           
  if(pdPASS == xReturn)
    vTaskStartScheduler();   /* 启动任务，开启调度 */
  else
			NVIC_SysReset();
    return -1;  
  
  while(1);   /* 正常不会执行到这里 */    
}


/***********************************************************************
  * @ 函数名  ： AppTaskCreate
  * @ 功能说明： 为了方便管理，所有的任务创建函数都放在这个函数里面
  * @ 参数    ： 无  
  * @ 返回值  ： 无
  **********************************************************************/
static void AppTaskCreate(void)
{
  BaseType_t xReturn = pdPASS;/* 定义一个创建信息返回值，默认为pdPASS */
  
  taskENTER_CRITICAL();           //进入临界区
  

  xReturn = xTaskCreate((TaskFunction_t )Main_Task,  /* 任务入口函数 */
                        (const char*    )"Main_Task",/* 任务名字 */
                        (uint16_t       )512,  /* 任务栈大小 */
                        (void*          )NULL,/* 任务入口函数参数 */
                        (UBaseType_t    )4, /* 任务的优先级 */
                        (TaskHandle_t*  )&Main_Task_Handle);/* 任务控制块指针 */ 
												
									
	xReturn = xTaskCreate((TaskFunction_t )Jiting_Task,  /* 任务入口函数 */
                        (const char*    )"Jiting_Task",/* 任务名字 */
                        (uint16_t       )512,  /* 任务栈大小 */
                        (void*          )NULL,/* 任务入口函数参数 */
                        (UBaseType_t    )5, /* 任务的优先级 */
                        (TaskHandle_t*  )&Jiting_Task_Handle);/* 任务控制块指针 */ 
												
	xReturn = xTaskCreate((TaskFunction_t )ADC_Task,  /* 任务入口函数 */
                        (const char*    )"ADC_Task",/* 任务名字 */
                        (uint16_t       )512,  /* 任务栈大小 */
                        (void*          )NULL,/* 任务入口函数参数 */
                        (UBaseType_t    )2, /* 任务的优先级 */
                        (TaskHandle_t*  )&ADC_Task_Handle);/* 任务控制块指针 */ 
												
	xReturn = xTaskCreate((TaskFunction_t )Diandong_Task,  /* 任务入口函数 */
                        (const char*    )"Diandong_Task",/* 任务名字 */
                        (uint16_t       )512,  /* 任务栈大小 */
                        (void*          )NULL,/* 任务入口函数参数 */
                        (UBaseType_t    )2, /* 任务的优先级 */
                        (TaskHandle_t*  )&Diandong_Task_Handle);/* 任务控制块指针 */ 
	
	xReturn = xTaskCreate((TaskFunction_t )Zhuangtai_Task,  /* 任务入口函数 */
                        (const char*    )"Zhuangtai_Task",/* 任务名字 */
                        (uint16_t       )256,  /* 任务栈大小 */
                        (void*          )NULL,/* 任务入口函数参数 */
                        (UBaseType_t    )2, /* 任务的优先级 */
                        (TaskHandle_t*  )&Zhuangtai_Task_Handle);/* 任务控制块指针 */ 
	
	xReturn = xTaskCreate((TaskFunction_t )Kaiguan_Task,  /* 任务入口函数 */
                        (const char*    )"Kaiguan_Task",/* 任务名字 */
                        (uint16_t       )256,  /* 任务栈大小 */
                        (void*          )NULL,/* 任务入口函数参数 */
                        (UBaseType_t    )2, /* 任务的优先级 */
                        (TaskHandle_t*  )&Kaiguan_Task_Handle);/* 任务控制块指针 */ 
												
												
	
	Swtmr1_Handle=xTimerCreate((const char*			)"OneShotTimer",
                             (TickType_t			)120000,/* 定时器周期 1s */
                             (UBaseType_t			)pdFALSE,/* 单次模式 */
                             (void*					  )1,/* 为每个计时器分配一个索引的唯一ID */
                             (TimerCallbackFunction_t)Swtmr1_Callback); 
 
  vTaskDelete(AppTaskCreate_Handle); //删除AppTaskCreate任务
  
  taskEXIT_CRITICAL();            //退出临界区
}



static void Jiting_Task(void* parameter)
{
  while(1)						//循环
	{
		jiting_task();
		vTaskDelay(50);			//延时20个tic
	}
}



static void ADC_Task(void* parameter) //模拟量
{
   while(1)
	 {
		wendu_task();
		if(zhangli_qidong ==1)
		{
			zhangli_task();
		}
		vTaskDelay(1000);
	 }
}

static void Kaiguan_Task(void* parameter) //模拟量
{
   while(1)
	 {
		kaiguan_task();
		vTaskDelay(50);
	 }
}

static void Diandong_Task(void* parameter) //模拟量
{
   while(1)
	 {
		diandong_renwu();
		vTaskDelay(50);
	 }
}

static void Main_Task(void* parameter) //主任务
{
   while(1)
	 {
		 zhu_renwu();
		 vTaskDelay(50);
	 }
}

static void Zhuangtai_Task(void* parameter)
{
  while(1)						//循环
	{
		zhuangtai_renwu();
		vTaskDelay(50);			//延时20个tic
	}
}


/***********************************************************************
  * @ 函数名  ： Swtmr2_Callback
  * @ 功能说明： 软件定时器2 回调函数，打印回调函数信息&当前系统时间
  *              软件定时器请不要调用阻塞函数，也不要进行死循环，应快进快出
  * @ 参数    ： 无  
  * @ 返回值  ： 无
  **********************************************************************/
static void Swtmr1_Callback(void* parameter)
{	
	yunxing_zhuangtai=1;
}

/***********************************************************************
  * @ 函数名  ： BSP_Init
  * @ 功能说明： 板级外设初始化，所有板子上的初始化均可放在这个函数里面
  * @ 参数    ：   
  * @ 返回值  ： 无
  *********************************************************************/
static void BSP_Init(void)
{
	/*
	 * STM32中断优先级分组为4，即4bit都用来表示抢占优先级，范围为：0~15
	 * 优先级分组只需要分组一次即可，以后如果有其他的任务需要用到中断，
	 * 都统一用这个优先级分组，千万不要再分组，切忌。
	 */
	NVIC_PriorityGroupConfig( NVIC_PriorityGroup_4 );
	
	
	delay_init(72);	     //延时初始化
	
	/* LED 即输出 初始化 */
	LED_GPIO_Config();
  
  /* 按键初即输入初始化	*/
 Key_GPIO_Config();
	FK_GPIO_Config();
	
	/* 串口初始化,此程序不用	*/
	USART1_Config(); 
	  /* 配置使用DMA模式 */
		/* 串口初始化,此程序不用	*/
   USART2_Config(); 
	  /* 配置使用DMA模式 */
	//printf("//////////////////////////////// \r\n");
	
	ADVANCE_TIM_Init();
	
	/* 模拟量初始化	*/
	ADCx_Init();

}

/********************************END OF FILE****************************/

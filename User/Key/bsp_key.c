/**
  ******************************************************************************
  * @file    bsp_key.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   按键应用bsp（扫描模式）
  ******************************************************************************
  * @attention
  *
  * 实验平台:秉火 F103-MINI STM32 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 
  
#include "bsp_key.h"  
#include "FreeRTOS.h"
#include "task.h"


/**
  * @brief  配置按键用到的I/O口
  * @param  无
  * @retval 无
  */
void Key_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
  
  RCC_APB2PeriphClockCmd(KEY1_GPIO_CLK,ENABLE); //开启按键端口PB的时钟
	GPIO_InitStructure.GPIO_Pin = KEY1_GPIO_PIN; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //端口配置为X拉输入
	GPIO_Init(KEY1_GPIO_PORT, &GPIO_InitStructure);	//初始化端口

	GPIO_InitStructure.GPIO_Pin = KEY2_GPIO_PIN; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //端口配置为x拉输入
	GPIO_Init(KEY2_GPIO_PORT, &GPIO_InitStructure);	//初始化端口
	
	GPIO_InitStructure.GPIO_Pin = KEY3_GPIO_PIN; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //端口配置为x拉输入
	GPIO_Init(KEY2_GPIO_PORT, &GPIO_InitStructure);	//初始化端口
	
	GPIO_InitStructure.GPIO_Pin = KEY4_GPIO_PIN; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //端口配置为x拉输入
	GPIO_Init(KEY2_GPIO_PORT, &GPIO_InitStructure);	//初始化端口

	GPIO_InitStructure.GPIO_Pin = KEY5_GPIO_PIN; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //端口配置为x拉输入
	GPIO_Init(KEY2_GPIO_PORT, &GPIO_InitStructure);	//初始化端口
	
	GPIO_InitStructure.GPIO_Pin = KEY13_GPIO_PIN; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //端口配置为x拉输入
	GPIO_Init(KEY13_GPIO_PORT, &GPIO_InitStructure);	//初始化端口
	
	RCC_APB2PeriphClockCmd(KEY6_GPIO_CLK,ENABLE); 
	GPIO_InitStructure.GPIO_Pin = KEY6_GPIO_PIN |KEY7_GPIO_PIN|KEY8_GPIO_PIN|KEY9_GPIO_PIN; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //端口配置为x拉输入
	GPIO_Init(KEY6_GPIO_PORT, &GPIO_InitStructure);	//初始化端口
	
	/*GPIO_InitStructure.GPIO_Pin = KEY7_GPIO_PIN; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //端口配置为x拉输入
	GPIO_Init(KEY7_GPIO_PORT, &GPIO_InitStructure);	//初始化端口
	
	GPIO_InitStructure.GPIO_Pin = KEY8_GPIO_PIN; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //端口配置为x拉输入
	GPIO_Init(KEY8_GPIO_PORT, &GPIO_InitStructure);	//初始化端口
	
	GPIO_InitStructure.GPIO_Pin = KEY9_GPIO_PIN; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //端口配置为x拉输入
	GPIO_Init(KEY9_GPIO_PORT, &GPIO_InitStructure);	//初始化端口
	
	
	GPIO_InitStructure.GPIO_Pin = KEY13_GPIO_PIN; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //端口配置为x拉输入
	GPIO_Init(KEY13_GPIO_PORT, &GPIO_InitStructure);	//初始化端口*/

}

void FK_GPIO_Config(void)
{
	  GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);    
    /* Disable JLink, enable SW */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE); 
	  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);   
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4; 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;   
    /* Push-pill output, it can be other output types */
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;   
    /* Push-pill output, it can be other output types */
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
    GPIO_Init(GPIOA, &GPIO_InitStructure);

}
	


 /*
 * 函数名：Key_Scan
 * 描述  ：检测是否有按键按下
 * 输入  ：GPIOx：x 可以是 A，B，C，D或者 E
 *		     GPIO_Pin：待读取的端口位 	
 * 输出  ：KEY_OFF(没按下按键)、KEY_ON（按下按键）
 */
uint8_t Key_Scan_Low(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin)
{			
	/*检测是否有按键按下 */
	if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON )  
	{	 
		/*等待按键释放 */
		vTaskDelay(100);
		if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON )
		{
			while(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON);   
			return 	KEY_ON;
		}
		else{
		return KEY_OFF;}
	}
	else{
		return KEY_OFF;}
}

uint8_t Key_Scan_High(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin)
{			
	/*检测是否有按键按下 */
	if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == 1 )  
	{	 
		/*等待按键释放 */
		vTaskDelay(100);
		if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == 1 )
		{
			//while(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == 1);   
			return 	1;
		}
		else{
		return 0;}
	}
	else{
		return 0;}
}

uint8_t Key_Scan_High1(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin)
{			
	/*检测是否有按键按下 */
	if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == 1 )  
	{	 
		/*等待按键释放 */
		vTaskDelay(100);
		if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == 1 )
		{
			while(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == 1);   
			return 	1;
		}
		else{
		return 0;}
	}
	else{
		return 0;}
}


/*********************************************END OF FILE**********************/

/**
  ******************************************************************************
  * @file    bsp_key.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   ����Ӧ��bsp��ɨ��ģʽ��
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:���� F103-MINI STM32 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 
  
#include "bsp_key.h"  
#include "FreeRTOS.h"
#include "task.h"


/**
  * @brief  ���ð����õ���I/O��
  * @param  ��
  * @retval ��
  */
void Key_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	


  
  RCC_APB2PeriphClockCmd(KEY1_GPIO_CLK|KEY2_GPIO_CLK,ENABLE); //���������˿�PB��ʱ��
	GPIO_InitStructure.GPIO_Pin = KEY1_GPIO_PIN; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //�˿�����Ϊ��������
	GPIO_Init(KEY1_GPIO_PORT, &GPIO_InitStructure);	//��ʼ���˿�

	GPIO_InitStructure.GPIO_Pin = KEY2_GPIO_PIN; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //�˿�����Ϊx������
	GPIO_Init(KEY2_GPIO_PORT, &GPIO_InitStructure);	//��ʼ���˿�
	
	RCC_APB2PeriphClockCmd(KEY4_GPIO_CLK,ENABLE); //���������˿�PB��ʱ��
	GPIO_InitStructure.GPIO_Pin = KEY4_GPIO_PIN; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //�˿�����Ϊx������
	GPIO_Init(KEY4_GPIO_PORT, &GPIO_InitStructure);	//��ʼ���˿�*/

}
	


 /*
 * ��������Key_Scan
 * ����  ������Ƿ��а�������
 * ����  ��GPIOx��x ������ A��B��C��D���� E
 *		     GPIO_Pin������ȡ�Ķ˿�λ 	
 * ���  ��KEY_OFF(û���°���)��KEY_ON�����°�����
 */
uint8_t Key_Scan_Low(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin)
{			
	/*����Ƿ��а������� */
	if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON )  
	{	 
		/*�ȴ������ͷ� */
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
	/*����Ƿ��а������� */
	if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == 1 )  
	{	 
		/*�ȴ������ͷ� */
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
	/*����Ƿ��а������� */
	if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == 1 )  
	{	 
		/*�ȴ������ͷ� */
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

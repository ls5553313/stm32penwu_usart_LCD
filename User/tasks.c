#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "delay.h"
#include "tasks.h"
#include "bsp_key.h"
#include "FreeRTOS.h"
#include "task.h"
#include "bsp_adc.h"
#include "bsp_i2c_ee.h"
#include "bsp_i2c_gpio.h"
#include "bsp_led.h"
#include "./usart/bsp_usart1.h"
#include "./usart/bsp_usart2.h"

int delay_time=5000;
int sec;
char string[20];
uint8_t key;
uint8_t maxNum=100;
uint8_t minNum=0;
uint8_t setNum=80;
uint8_t curNum=0;
uint8_t page=0;
uint8_t va0val;
uint8_t fasong;


extern __IO uint16_t ADC_ConvertedValue;//ģ�����ڲɼ�ֵ

// �ֲ����������ڱ���ת�������ĵ�ѹֵ 	 
float ADC_ConvertedValueLocal;   

uint8_t ADC_task(void);

void NVIC_SysReset(void) //ϵͳ��λ
{
  __DSB();

  SCB->AIRCR  = ((0x5FA << SCB_AIRCR_VECTKEY_Pos)      | 
                 (SCB->AIRCR & SCB_AIRCR_PRIGROUP_Msk) | 
                 SCB_AIRCR_SYSRESETREQ_Msk);     //��λ SYSRESETREQ
  __DSB();
  while(1);
}

uint8_t main_task1(uint8_t mode_num)
{
switch(mode_num)
      {
        case 0://Ƥ��ģʽ
						if( Key_Scan_High(KEY2_GPIO_PORT,KEY2_GPIO_PIN) == 1 ) //���������
						{
							return 1;  //����1
						}
						if( Key_Scan_High(KEY4_GPIO_PORT,KEY4_GPIO_PIN) == 1 )
						{
							return 1;
						}
						if(setNum!=0)
						{
							if( ADC_task() == 1 )
							{
								return 1;
							}
						}
						return 0;
        
        case 1://����ģʽ
						if( Key_Scan_High(KEY4_GPIO_PORT,KEY4_GPIO_PIN) == 1 )
						{
							return 1;
						}
						return 0;
				
				case 2://����ģʽ
						if( Key_Scan_High(KEY4_GPIO_PORT,KEY4_GPIO_PIN) == 1 )
						{
							return 1;
						}
						return 0;
        
        
        default://����ģʽ
						if( Key_Scan_High(KEY4_GPIO_PORT,KEY4_GPIO_PIN) == 1 )
						{
							return 1;
						}
						return 0;						
      }
};

uint8_t ADC_task(void)
{
	uint8_t wenduzhi;
	wenduzhi=ADC_ConvertedValueLocal/3.3*100;
	fasong++;
	if(fasong==10)
	{
		printf("page0.n0.val=%d",wenduzhi);
		HMISendb(0xff);	
		fasong=0;
	}
	if(ADC_ConvertedValueLocal>((float) setNum/(maxNum-minNum)*3.3)) //ת��ֵ���ں���
	{
		return 1;
	}
	else return 0;
}

uint8_t i2c_saving(void) //�洢�趨ֵ
{
	uint8_t write_buf[EEPROM_SIZE]; //��������

  
/*-----------------------------------------------------------------------------------*/  
  if (ee_CheckDevice(EEPROM_DEV_ADDR) == 1)
	{
		/* û�м�⵽EEPROM */
		//printf("û�м�⵽����EEPROM!\r\n");
				
		return 0;
	}
/*------------------------------------------------------------------------------------*/  
	write_buf[0] = delay_time/1000;
	write_buf[1] = maxNum;
	write_buf[2] = minNum;
	write_buf[3] = setNum;

/*------------------------------------------------------------------------------------*/  
  if (ee_WriteBytes(write_buf, 0, EEPROM_SIZE) == 0)
	{
		//printf("дeeprom����\r\n");
		return 0;
	}
	else
	{		
		//printf("дeeprom�ɹ���\r\n");
		return 1;
	}
}  

uint8_t i2c_reading(void) //��ȡ�趨ֵ
{
	  uint8_t read_buf[EEPROM_SIZE];
	if (ee_CheckDevice(EEPROM_DEV_ADDR) == 1)
	{
		/* û�м�⵽EEPROM */
		//printf("û�м�⵽����EEPROM!\r\n");
				
		return 0;
	}

  if (ee_ReadBytes(read_buf, 0, EEPROM_SIZE) == 0)
	{
		//printf("��eeprom����\r\n");
		return 0;
	}
	else
	{	
		delay_time = read_buf[0]*1000;
		maxNum = read_buf[1];
		minNum = read_buf[2];
		setNum = read_buf[3];
		//printf("��eeprom�ɹ�  \r\n");
		printf("page1.n0.val=%d",delay_time/1000);
		HMISendb(0xff);	
		printf("page2.n0.val=%d",setNum);
		HMISendb(0xff);	
		printf("page2.n1.val=%d",maxNum);
		HMISendb(0xff);	
		printf("page2.n2.val=%d",minNum);
		HMISendb(0xff);	
		return 1;
	}

	
}

void LCD_renwu(void)//��ҳ
{
	
	if(page==0)
	{
		if(key==SETTING)
		{
			HMISends("page 1");
			while(key==SETTING){vTaskDelay(20);};
		}
	}
	
	if(page==1)
	{
		if(key==ADD)
		{
			sec++;
			if(sec>99){sec=99;}
			printf("page1.n0.val=%d",sec);
			HMISendb(0xff);	
			while(key==ADD){vTaskDelay(20);};
		}
		if(key==LESS)
		{
			sec--;
			if(sec<=0){sec=0;}		
			printf("page1.n0.val=%d",sec);
			HMISendb(0xff);	
			while(key==LESS){vTaskDelay(20);};
		}
		if(key==RETURN)
		{
			HMISends("page 0");
			while(key==RETURN){vTaskDelay(20);};
		}
		if(key==NEXT)
		{
			HMISends("page 2");
			while(key==NEXT){vTaskDelay(20);};
		}
		if(key==SETTING)
		{
			HMISends("page 0");
			delay_time=sec*1000;
			i2c_saving();
			while(key==SETTING){vTaskDelay(20);};
		}
		
	}
	
	if(page==2)
	{
		if(key==ONE)
		{
			HMISends("page2.va0.val=1");
			va0val=1;
			while(key==ONE){vTaskDelay(20);};
		}
		if(key==TWO)
		{
			HMISends("page2.va0.val=2");
			va0val=2;
			while(key==TWO){vTaskDelay(20);};
		}
		if(key==THREE)
		{
			HMISends("page2.va0.val=3");
			va0val=3;
			while(key==THREE){vTaskDelay(20);};
		}

		
		if(va0val==1)
		{
			if(key==ADD)
			{
				setNum++;
				if(setNum>99){setNum=99;}
				printf("page2.n0.val=%d",setNum);
				HMISendb(0xff);	
				while(key==ADD){vTaskDelay(20);};					
			}
			if(key==LESS)
			{
				setNum--;
				if(setNum<=0){setNum=0;}
				printf("page2.n0.val=%d",setNum);
				HMISendb(0xff);	
				while(key==LESS){vTaskDelay(20);};
			}		
		}
		if(va0val==2)
		{
			if(key==ADD)
			{
				maxNum++;
				if(maxNum>99){maxNum=99;}
				printf("page2.n1.val=%d",maxNum);
				HMISendb(0xff);	
				while(key==ADD){vTaskDelay(20);};
			}
			if(key==LESS)
			{
				maxNum--;
				if(maxNum<=0){maxNum=0;}
				printf("page2.n1.val=%d",maxNum);
				HMISendb(0xff);	
				while(key==LESS){vTaskDelay(20);};
			}	
		}
		if(va0val==3)
		{
			if(key==ADD)
			{
				minNum++;
				if(minNum>99){minNum=99;}
				printf("page2.n2.val=%d",minNum);
				HMISendb(0xff);
				while(key==ADD){vTaskDelay(20);};				
			}
			if(key==LESS)
			{
				minNum--;
				if(minNum<=0){minNum=0;}
				printf("page2.n2.val=%d",minNum);
				HMISendb(0xff);	
				while(key==LESS){vTaskDelay(20);};
			}	
		}
		
		if(key==SETTING)
		{
			va0val=0;
			HMISends("page2.va0.val=0");
			i2c_saving();
			HMISends("page 0");
			while(key==SETTING){vTaskDelay(20);};
		}
		if(key==RETURN)
		{
			va0val=0;
			HMISends("page2.va0.val=0");
			HMISends("page 0");
			while(key==RETURN){vTaskDelay(20);};
		}
	}
}

/*void first_page(void)//��ҳ
{
	LCD_Clear(BLACK); //����
	Show_Str(32,5,BLUE,YELLOW,"ɽ������",16,0);
	Show_Str(16,30,RED,YELLOW,"����ϵͳ",24,1);
	Show_Str(5,50,RED,YELLOW,"��ǰ:    ",16,1);
	curNum=(ADC_ConvertedValueLocal/3.3*(maxNum-minNum) + minNum);
	sprintf(string, "%d", curNum);
	Show_Str(5+48+16,50,RED,YELLOW,string,16,1);
	Show_Str(48,100,BLUE,YELLOW,"�趨",16,0);
	//printf("diyiye");
}

void second_page(void)
{
	LCD_Clear(BLACK); //����
	Show_Str(15,5,RED,YELLOW,"1.��ʱ�趨",16,1);
	Show_Str(15,25,RED,YELLOW,"2.��ʱ�趨",16,1);
	Show_Str(15,45,RED,YELLOW,"3.ģ�����趨",16,1);
	//printf("dierye");
}

void third_page_1(void)
{
	LCD_Clear(BLACK); //����
  Show_Str(32,5,BLUE,YELLOW,"��ʱ�趨",16,0);
	Show_Str(53,25,RED,YELLOW,"+",16,1);
	Show_Str(16,50,RED,YELLOW,"��ʱ:    ��",16,1);
	Show_Str(5+48,50,RED,YELLOW,string,16,1);
	Show_Str(53,75,RED,YELLOW,"-",16,1);
	Show_Str(15,100,RED,YELLOW,"ȷ�ϲ�����",16,1);
}

void third_page_3(void)
{
	LCD_Clear(BLACK); //����
	Show_Str(15,25,RED,YELLOW,"1.���ֵ�趨",16,1);
	Show_Str(15,50,RED,YELLOW,"2.��Сֵ�趨",16,1);
	Show_Str(15,75,RED,YELLOW,"3.�趨ֵ�趨",16,1);
}

void third_page_3_1(void)
{
	LCD_Clear(BLACK); //����
  Show_Str(32,5,BLUE,YELLOW,"���ֵ�趨",16,0);
	Show_Str(5+48+16,25,RED,YELLOW,"+",16,1);
	Show_Str(5,50,RED,YELLOW,"���ֵ:    ",16,1);
	Show_Str(5+48+16,50,RED,YELLOW,string,16,1);
	Show_Str(5+48+16,75,RED,YELLOW,"-",16,1);
	Show_Str(5,100,RED,YELLOW,"ȷ�ϲ�����",16,1);
}

void third_page_3_2(void)
{
	LCD_Clear(BLACK); //����
  Show_Str(32,5,BLUE,YELLOW,"��Сֵ�趨",16,0);
	Show_Str(5+48+16,25,RED,YELLOW,"+",16,1);
	Show_Str(5,50,RED,YELLOW,"��Сֵ:    ",16,1);
	Show_Str(5+48+16,50,RED,YELLOW,string,16,1);
	Show_Str(5+48+16,75,RED,YELLOW,"-",16,1);
	Show_Str(5,100,RED,YELLOW,"ȷ�ϲ�����",16,1);
}

void third_page_3_3(void)
{
	LCD_Clear(BLACK); //����
  Show_Str(32,5,BLUE,YELLOW,"�趨ֵ�趨",16,0);
	Show_Str(5+48+16,25,RED,YELLOW,"+",16,1);
	Show_Str(5,50,RED,YELLOW,"�趨ֵ:    ",16,1);
	Show_Str(5+48+16,50,RED,YELLOW,string,16,1);
	Show_Str(5+48+16,75,RED,YELLOW,"-",16,1);
	Show_Str(5,100,RED,YELLOW,"ȷ�ϲ�����",16,1);
}


void lcd_task1()  //��ʾ����
{
	//first_page();
	vTaskDelay(100);
		if( key==SETTING )                           //���key����176��������
    {
			second_page();												//��ʾ�ڶ�ҳ
			while(1)															//����ѭ��
			{
				vTaskDelay(100);
				if( key==RETURN )                       //�˳�����
				{
					first_page();											
					break;
				}
				if( key==ONE )                        //������ʱ�趨
				{
					sec=delay_time/1000;								//����ʱʱ����븳��sec��
					sprintf(string, "%d", sec);
					third_page_1();											//������ʱ�趨ҳ��
					while(1)														//����ѭ��
					{
						vTaskDelay(20);
						if( key==RETURN )                     //��������ҳ��
						{
							delay_time=sec*1000;						
							i2c_saving();										//�洢�¸ĵ�ֵ
							second_page();									//��ʾ�ڶ�ҳ
							while(key==RETURN){vTaskDelay(20);};
							break;
						}
						if( key==ADD )
						{
							sec++;
							if(sec>99){sec=99;};
							sprintf(string, "%d", sec);
							third_page_1();
							while(key==ADD){vTaskDelay(20);};
						}
						if( key ==LESS )
						{
							sec--;
							if(sec<0){sec=0;};
							sprintf(string, "%d", sec);
							third_page_1();
							while(key==LESS){vTaskDelay(20);};
						}
					}
				}
				if( key==THREE )                        //����ģ�����趨
				{			
					third_page_3();
					while(key==THREE){vTaskDelay(20);};
					while(1)
					{
						vTaskDelay(20);
						if( key==RETURN )                  //��������ҳ��
						{
							second_page();
							while(key==RETURN){vTaskDelay(20);};
							break;
						}
						if( key==ONE )                        //�������ֵ�趨
						{
							uint8_t maxNum1=maxNum;
							sprintf(string, "%d", maxNum1);
							third_page_3_1();
							while(1)
							{
								vTaskDelay(20);
								if( key==RETURN )                  //��������ҳ��
								{
									maxNum=maxNum1;
									i2c_saving();
									third_page_3();
									while(key==RETURN){vTaskDelay(20);};
									break;
								}
								if( key==ADD )
								{
									maxNum1++;
									if(maxNum1>100){maxNum1=100;};
									sprintf(string, "%d", maxNum1);
									third_page_3_1();
									while(key==ADD){vTaskDelay(20);};
								}
								if( key ==LESS )
								{
									maxNum1--;
									if(maxNum1<=0){maxNum1=0;};
									sprintf(string, "%d", maxNum1);
									third_page_3_1();
									while(key==LESS){vTaskDelay(20);};
								}
							}
						}
						if( key==TWO )                        //������Сֵ�趨
						{
							uint8_t minNum1=minNum;
							sprintf(string, "%d", minNum1);
							third_page_3_2();
							while(1)
							{
								vTaskDelay(20);
								if( key==RETURN )                  //��������ҳ��
								{
									minNum=minNum1;
									i2c_saving();
									third_page_3();
									while(key==RETURN){vTaskDelay(20);};
									break;
								}
								if( key==ADD )
								{
									minNum1++;
									if(minNum1>100){minNum1=100;};
									sprintf(string, "%d", minNum1);
									third_page_3_2();
									while(key==ADD){vTaskDelay(20);};
								}
								if( key ==LESS )
								{
									minNum1--;
									if(minNum1<=0){minNum1=0;};
									sprintf(string, "%d", minNum1);
									third_page_3_2();
									while(key==LESS){vTaskDelay(20);};
								}
							}
						}
						if( key==THREE )                        //�����趨ֵ�趨
						{
							uint8_t setNum1=setNum;
							sprintf(string, "%d", setNum1);
							third_page_3_3();
							while(1)
							{
								vTaskDelay(20);
								if( key==RETURN )                  //��������ҳ��
								{
									setNum=setNum1;
									i2c_saving();
									third_page_3();
									while(key==RETURN){vTaskDelay(20);};
									break;
								}
								if( key==ADD )
								{
									setNum1++;
									if(setNum1>100){setNum1=100;};
									sprintf(string, "%d", setNum1);
									third_page_3_1();
									while(key==ADD){vTaskDelay(20);};
								}
								if( key ==LESS )
								{
									setNum1--;
									if(setNum1<=0){setNum1=0;};
									sprintf(string, "%d", setNum1);
									third_page_3_3();
									while(key==LESS){vTaskDelay(20);};
								}
							}
						}
						
						
						
					}
				}				
			}
		}
	
}*/


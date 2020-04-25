#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "event_groups.h"

#include "delay.h"
#include "tasks.h"
#include "bsp_key.h"
#include "bsp_led.h"
#include "bsp_adc.h"
#include "bsp_i2c_ee.h"
#include "bsp_i2c_gpio.h"
#include "bsp_led.h"
#include "bsp_usart2.h"
#include "./data_process/data_process.h"

uint8_t wendu_shangxian=100;
uint8_t wendu_xiaxian=0;
uint8_t wendu_sheding=80;

uint8_t qiche_yanshi = 0;
uint8_t tingche_yanshi = 0;

uint8_t duimei_yanshi = 2;
uint8_t silie_yanshi = 2;
uint8_t paopian_yanshi = 2;
uint8_t jiting_yanshi = 0;
uint8_t wendu_yanshi = 2;
uint8_t yanwu_yanshi = 2;
uint8_t sashui_yanshi = 0;

uint8_t kaichesashui = 0;

uint8_t zhangli_baojing = 0;

uint8_t zhangli_shangxian = 60;
uint8_t zhangli_xiaxian = 40;
uint8_t zhangli_liangcheng_shangxian = 100;
uint8_t zhangli_liangcheng_xiaxian = 0;

uint8_t sudu_yanshi = 0;
uint8_t sudu_sheding;
uint8_t sudu_m_s=40;
uint16_t sudu_dangqian;

uint8_t zhudianji_zhuangtai;
uint8_t congdianji_zhuangtai;
uint8_t zhadianji_zhuangtai;
uint8_t zhanglidianji_zhuangtai;
uint8_t zhangzeng_zhuangtai;
uint8_t zhangjian_zhuangtai;
uint8_t fa_zhuangtai;

uint16_t baojing_zhuangtai=0;
uint8_t yunxing_zhuangtai=0;

uint8_t zhudianji_diandong;
uint8_t congdianji_diandong;
uint8_t zhadianji_diandong;
uint8_t fa_diandong;
uint8_t zhanglijia_diandong;
uint8_t zhanglijian_diandong;
uint8_t diandong_shineng;

uint8_t qidong_qidong;
uint8_t qidong_tingche;
uint8_t qidong_jiting;
uint8_t qidong_fuwei;

uint8_t zhangli_qidong;

uint8_t kaiting_yuyin=0;

TimerHandle_t Swtmr1_Handle;


extern __IO uint16_t ADC_ConvertedValue[NOFCHANEL];//模拟量口采集值

// 局部变量，用于保存转换计算后的电压值 	 
float ADC_ConvertedValueLocal1;   
float ADC_ConvertedValueLocal2;  

void sashui(uint8_t yanshi);
void zhangli_task(void);

void zhangli_guan(uint8_t yanshi);


/*********************************************************/
/*********************************************************/
/*********************************************************/

uint8_t warning_paopian(void)
{
	if( Key_Scan_High(KEY1_GPIO_PORT,KEY1_GPIO_PIN) == 1 ) //如果有输入
	{
		return 1;  //返回1
	}
	return 0;
}

uint8_t warning_jiting(void)
{
	if( Key_Scan_High(KEY2_GPIO_PORT,KEY2_GPIO_PIN) == 1 ) //如果有输入
	{
		return 1;  //返回1
	}
	return 0;
}

uint8_t warning_duimei(void)
{
		if( Key_Scan_High(KEY3_GPIO_PORT,KEY3_GPIO_PIN) == 1 ) //如果有输入
	{
		return 1;  //返回1
	}
	return 0;
	
}

uint8_t warning_silie(void)
{
		if( Key_Scan_High(KEY4_GPIO_PORT,KEY4_GPIO_PIN) == 1 ) //如果有输入
	{
		return 1;  //返回1
	}
	return 0;
	
}

uint8_t warning_yanwu(void)
{
		if( Key_Scan_High(KEY5_GPIO_PORT,KEY5_GPIO_PIN) == 1 ) //如果有输入
	{
		return 1;  //返回1
	}
	return 0;
}

/*********************************************************/
/*********************************************************/
/*********************************************************/
void baojingyuyin(uint8_t baojing_shineng,uint8_t baojing_ma) //报警使能
{
	if( baojing_shineng == 1 ) //如果有输入
	{
		switch(baojing_ma)
		{
			case 1 :
				HMISends("play 0,0,0");
				break;
			case 2 :
				HMISends("play 0,1,0");
				break;
			default :
				HMISends("*********************");
				break;
		}
	}
}
void baojingjilu(uint8_t baojing_shineng,uint16_t baojing_ma) //报警使能
{
	if( baojing_shineng == 1 ) //如果有输入
	{
	 if((baojing_zhuangtai | baojing_ma) == baojing_zhuangtai){return;} 
	 baojing_zhuangtai = (baojing_zhuangtai | baojing_ma);
	 switch(baojing_ma)
   {
   case 0x0002 :
      HMISends("page0.va1.txt=\"张力少于下限**\"");
      break;
   case 0x0004 :
			HMISends("page0.va1.txt=\"张力大于上限**\"");
      break;
   case 0x0008 :
			HMISends("page0.va1.txt=\"主电机反馈有误\"");
      break;
	 case 0x0010 :
			HMISends("page0.va1.txt=\"从电机反馈有误\"");
      break;
	 case 0x0020 :
			HMISends("page0.va1.txt=\"张力反馈有误**\"");
      break;
	 case 0x0040 :
      HMISends("page0.va1.txt=\"闸电机反馈有误\"");
      break;
   case 0x0080 :
			HMISends("page0.va1.txt=\"起车请消除警报\"");
      break;
   case 0x0100 :
			HMISends("page0.va1.txt=\"出现跑偏故障**\"");
      break;
	 case 0x0200 :
			HMISends("page0.va1.txt=\"出现撕裂故障**\"");
      break;
	 case 0x0400 :
			HMISends("page0.va1.txt=\"出现堆煤故障**\"");
      break;
	 case 0x0800 :
      HMISends("page0.va1.txt=\"出现温度故障**\"");
      break;
   case 0x1000 :
			HMISends("page0.va1.txt=\"出现速度故障**\"");
      break;
   case 0x2000 :
			HMISends("page0.va1.txt=\"出现烟雾故障**\"");
      break;
	 case 0x4000 :
			HMISends("page0.va1.txt=\"设备已急停****\"");
      break;	
   default :
		 HMISends("*********************");
      break;
   }
	}
}

/*********************************************************/
/*********************************************************/
/*********************************************************/

void tingche(uint8_t yanshi)
{
	if(kaiting_yuyin==1)
	{
		baojingyuyin(1,2);
	};
	kaiting_yuyin=0;
	xTimerStop(Swtmr1_Handle,0);
	vTaskDelay(yanshi*1000);
	zhangli_qidong=0;
	ZHU_OFF;
	CONG_OFF;
	vTaskDelay(500);
	if( zhudianji_zhuangtai != 0 ) //如果有输入
	{
		baojingjilu(1,0x0008);
	}
	if( congdianji_zhuangtai != 0 ) //如果有输入
	{
		baojingjilu(1,0x0010);
	}	
  zhangli_guan(0);
	ZHA_OFF;
	vTaskDelay(500);
	if( zhadianji_zhuangtai != 0 ) //如果有输入
	{
		baojingjilu(1,0x0040);
	}
	yunxing_zhuangtai=0;
}

void kaiche(uint8_t yanshi)
{
	if(baojing_zhuangtai >>3 != 0)
	{
		baojingjilu(1,0x0080);
		return;
	}
	ZHA_ON; 
	vTaskDelay(500);
	if( zhadianji_zhuangtai != 1 ) //如果有输入
	{
		baojingjilu(1,0x0040);
		return;
	}
	if(kaiting_yuyin==0)
	{
		baojingyuyin(1,2);
	};
	kaiting_yuyin=1;
	baojingyuyin(1,1);
	vTaskDelay(yanshi*1000);
	if(baojing_zhuangtai >>3 != 0)
	{
		baojingjilu(1,0x0080);
		return;
	}
	zhangli_qidong=1;
	ZHU_ON;
	CONG_ON;
	vTaskDelay(500);
	if( zhudianji_zhuangtai != 1 ) //如果有输入
	{
		baojingjilu(1,0x0008);
	}
	if( congdianji_zhuangtai != 1 ) //如果有输入
	{
		baojingjilu(1,0x0010);
	}	
	if(kaichesashui==1)
	{
		sashui(0);
	}
	if(Swtmr1_Handle != NULL)
	{
	 xTimerReset(Swtmr1_Handle,0);	//开启定时器
	}
}



void sashui(uint8_t yanshi)
{
	vTaskDelay(yanshi*1000);
	FA_ON;
}

void tingshui(uint8_t yanshi)
{
	vTaskDelay(yanshi*1000);
	FA_OFF;
}

void zhangli_jia(uint8_t yanshi)
{
	vTaskDelay(yanshi*1000);
	ZHANGJIAN_OFF;
	ZHANGZENG_ON;
	vTaskDelay(500);
	if( zhanglidianji_zhuangtai != 1 ) //如果有输入
	{
		baojingjilu(1,0x0020);
	}
}

void zhangli_jian(uint8_t yanshi)
{
	vTaskDelay(yanshi*1000);
	ZHANGZENG_OFF;
	ZHANGJIAN_ON;
	vTaskDelay(500);
	if( zhanglidianji_zhuangtai != 1 ) //如果有输入
	{
		baojingjilu(1,0x0020);
	}	
}

void zhangli_guan(uint8_t yanshi)
{
	vTaskDelay(yanshi*1000);
	ZHANGJIAN_OFF;
	ZHANGZENG_OFF;
	vTaskDelay(500);
	if( zhanglidianji_zhuangtai != 0 ) //如果有输入
	{
		baojingjilu(1,0x0020);
	}
}


/*********************************************************/
/*********************************************************/
/*********************************************************/

void kaiguan_task(void)
{
	if( warning_paopian() == 1 ) 
	{
		baojingjilu(1,0x0100);
		tingche(paopian_yanshi);
	}
	if( warning_duimei() == 1 ) 
	{
		baojingjilu(1,0x0400);
		tingche(duimei_yanshi);
	}
	if( warning_silie() == 1 ) 
	{
		baojingjilu(1,0x0200);
		tingche(silie_yanshi);
	}
	if( warning_yanwu() == 1 ) 
	{
		baojingjilu(1,0x2000);
		sashui(sashui_yanshi);
		tingche(yanwu_yanshi);
	}	
}

void jiting_task(void)
{
	if( warning_jiting() == 1 ) 
	{
		baojingjilu(1,0x4000);
		tingche(0);
	}
	if( Key_Scan_High(KEY8_GPIO_PORT,KEY8_GPIO_PIN) == 1|| qidong_jiting) //如果有输入
	{
		qidong_jiting=0;
		tingche(0);
		baojingjilu(1,0x4000);
		qidong_jiting=0;
	}
}

void sudu_task(void)
{
		if( sudu_dangqian != 0 ) 
	{
		uint8_t sudu;
		sudu = sudu_m_s *(sudu_sheding/sudu_dangqian);
		if(sudu>99){sudu=99;};
	  char ptr[2];
		char ptr_send[15] = "page0.x0.val=";
		sprintf(ptr,"%d",sudu);
		strcat (ptr_send,ptr);
		Usart_SendString(DEBUG_USART2,ptr_send);
		HMISendb(0xff);
		if((sudu_sheding/sudu_dangqian)>1.2)
		{
			baojingjilu(1,0x1000);
			tingche(sudu_yanshi);
		}
		if((sudu_sheding/sudu_dangqian)<0.7)
		{
			baojingjilu(1,0x1000);
			tingche(sudu_yanshi);
		}
	}
}

void wendu_task(void)
{
	ADC_ConvertedValueLocal1 =(float) ADC_ConvertedValue[0]/4096*3.3;
	uint8_t wendu;
	wendu = ADC_ConvertedValueLocal1/2*100;
	char ptr[2];
	char ptr_send[15] = "page0.n0.val=";
	sprintf(ptr,"%d",wendu);
	strcat (ptr_send,ptr);
	Usart_SendString(DEBUG_USART2,ptr_send);
	HMISendb(0xff);
	if(wendu > wendu_sheding) //转化值大于后面
	{
		baojingjilu(1,0x0800);
		sashui(0);
		tingche(wendu_yanshi);
	}
	if(wendu <= wendu_sheding) 
	{
		if(kaichesashui==0)
		{
		 tingshui(0);
		}
	}
}

void zhangli_task(void)
{
	ADC_ConvertedValueLocal2 =(float) ADC_ConvertedValue[1]/4096*3.3; 
	uint8_t zhangli;
	zhangli = ADC_ConvertedValueLocal2/3.3*100;
	char ptr[2];
	char ptr_send[15] = "page0.x1.val=";
	sprintf(ptr,"%d",zhangli);
	strcat (ptr_send,ptr);
	Usart_SendString(DEBUG_USART2,ptr_send);
	HMISendb(0xff);
	if(zhangli > zhangli_shangxian) //转化值大于后面
	{
		baojingjilu(1,0x0004);
		zhangli_jian(0);
	}
	if(zhangli < zhangli_xiaxian) //转化值大于后面
	{
		baojingjilu(1,0x0002);
		zhangli_jia(0);
	}
	if( (zhangli >= zhangli_xiaxian) && (zhangli <= zhangli_shangxian)) //转化值大于后面
	{
		zhangli_guan(0);
	}
}

/*********************************************************/
/*********************************************************/
/*********************************************************/
void zhu_renwu(void)
{
	if( Key_Scan_High(KEY6_GPIO_PORT,KEY6_GPIO_PIN) == 1 || qidong_qidong) //如果有输入
	{
		qidong_qidong=0;
		kaiche(qiche_yanshi);
		qidong_qidong=0;
	}
	if( Key_Scan_High(KEY7_GPIO_PORT,KEY7_GPIO_PIN) == 1 || qidong_tingche) //如果有输入
	{
		qidong_tingche=0;
		tingche(tingche_yanshi);
		qidong_tingche=0;
	}
	if( Key_Scan_High(KEY9_GPIO_PORT,KEY9_GPIO_PIN) == 1 || qidong_fuwei) //如果有输入
	{
		baojing_zhuangtai=0;
		qidong_fuwei=0;
		tingshui(0);
		HMISends("page0.t9.txt=\"\"");
	}
	if(yunxing_zhuangtai==1)
	{
		sudu_task();
	}	
}


void diandong_renwu(void)
{
	if(diandong_shineng == 0)
	{
		zhudianji_diandong=0;
		congdianji_diandong=0;
		zhadianji_diandong=0;
		fa_diandong=0;
		zhanglijia_diandong=0;
		zhanglijian_diandong=0;
		return;
	}
	
	if( zhudianji_diandong == 1 ) //如果有输入
	{
		ZHU_ON;
	}
	else
	{
		ZHU_OFF;
	}
	
	if( congdianji_diandong == 1 ) //如果有输入
	{
		CONG_ON;
	}
	else
	{
		CONG_OFF;
	}
	
	if( zhadianji_diandong == 1 ) //如果有输入
	{
		ZHA_ON;
	}
	else
	{
		ZHA_OFF;
	}
	
	if( fa_diandong == 1 ) //如果有输入
	{
		sashui(0);
	}
	else
	{
		tingshui(0);
	}
	
	if( zhanglijia_diandong == 1 ) //如果有输入
	{
		ZHANGZENG_ON;
	}
	else
	{
		ZHANGZENG_OFF;
	}
	
	if( zhanglijian_diandong == 1 ) //如果有输入
	{
		ZHANGJIAN_ON;
	}
	else
	{
		ZHANGJIAN_OFF;
	}
}


/*********************************************************/
/*********************************************************/
/*********************************************************/

void zhuangtai_renwu(void)
{
	if( Key_Scan_High(KEY10_GPIO_PORT,KEY10_GPIO_PIN) == 1) //如果有输入
	{
		if(zhudianji_zhuangtai!=1)
		{
		HMISends("page0.t13.txt=\"开\"");
		}
		zhudianji_zhuangtai=1;
	}
	else
	{
		if(zhudianji_zhuangtai!=0)
		{
		HMISends("page0.t13.txt=\"关\"");
		}
		zhudianji_zhuangtai=0;
	}
	
	if( Key_Scan_High(KEY11_GPIO_PORT,KEY11_GPIO_PIN) == 1) //如果有输入
	{
		if(congdianji_zhuangtai!=1)
		{
		HMISends("page0.t14.txt=\"开\"");
		}
		congdianji_zhuangtai=1;
	}
	else
	{
		if(congdianji_zhuangtai!=0)
		{
		HMISends("page0.t14.txt=\"关\"");
		}
		congdianji_zhuangtai=0;
	}
	
	if( Key_Scan_High(KEY12_GPIO_PORT,KEY12_GPIO_PIN) == 1) //如果有输入
	{
		if(zhadianji_zhuangtai!=1)
		{
		HMISends("page0.t20.txt=\"开\"");
		}
		zhadianji_zhuangtai=1;
	}
	else
	{
		if(zhadianji_zhuangtai!=0)
		{
		HMISends("page0.t20.txt=\"关\"");
		}
		zhadianji_zhuangtai=0;
	}
	
	if( Key_Scan_High(KEY10_GPIO_PORT,KEY10_GPIO_PIN) == 1) //如果有输入
	{
		zhanglidianji_zhuangtai=1;
	}
	else
	{
		zhanglidianji_zhuangtai=0;
	}

	if(GPIO_ReadOutputDataBit(LED4_GPIO_PORT,LED4_GPIO_PIN) == 1)
	{
		if(fa_zhuangtai!=1)
		{
			HMISends("page0.t15.txt=\"开\"");
		}
			fa_zhuangtai=1;
	}
	if(GPIO_ReadOutputDataBit(LED4_GPIO_PORT,LED4_GPIO_PIN) == 0)
	{
		if(fa_zhuangtai!=0)
		{
			HMISends("page0.t15.txt=\"关\"");
		}
		fa_zhuangtai=0;
	}
	
	if(GPIO_ReadOutputDataBit(LED5_GPIO_PORT,LED5_GPIO_PIN) == 1)
	{
		if(zhangzeng_zhuangtai!=1)
		{
			HMISends("page0.t16.txt=\"开\"");
		}
			zhangzeng_zhuangtai=1;
	}
	if(GPIO_ReadOutputDataBit(LED5_GPIO_PORT,LED5_GPIO_PIN) == 0)
	{
		if(zhangzeng_zhuangtai!=0)
		{
			HMISends("page0.t16.txt=\"关\"");
		}
		zhangzeng_zhuangtai=0;
	}
	
	if(GPIO_ReadOutputDataBit(LED6_GPIO_PORT,LED6_GPIO_PIN) == 1)
	{
		if(zhangjian_zhuangtai!=1)
		{
			HMISends("page0.t17.txt=\"开\"");
		}
			zhangjian_zhuangtai=1;
	}
	if(GPIO_ReadOutputDataBit(LED6_GPIO_PORT,LED6_GPIO_PIN) == 0)
	{
		if(zhangjian_zhuangtai!=0)
		{
			HMISends("page0.t17.txt=\"关\"");
		}
		zhangjian_zhuangtai=0;
	}
	
}


/*********************************************************/
/*********************************************************/
/*********************************************************/


void NVIC_SysReset(void) //系统复位
{
  __DSB();

  SCB->AIRCR  = ((0x5FA << SCB_AIRCR_VECTKEY_Pos)      | 
                 (SCB->AIRCR & SCB_AIRCR_PRIGROUP_Msk) | 
                 SCB_AIRCR_SYSRESETREQ_Msk);     //置位 SYSRESETREQ
  __DSB();
  while(1);
}






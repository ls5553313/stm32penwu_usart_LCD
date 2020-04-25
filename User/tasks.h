#ifndef __TASKS_H
#define	__TASKS_H

#include "stm32f10x.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "event_groups.h"

//uint8_t wendu_shangxian=100;
//uint8_t wendu_xiaxian=0;
extern uint8_t wendu_sheding;

extern uint8_t qiche_yanshi;
extern uint8_t tingche_yanshi;

extern uint8_t duimei_yanshi;
extern uint8_t silie_yanshi;
extern uint8_t paopian_yanshi;
extern uint8_t jiting_yanshi;
extern uint8_t wendu_yanshi;
extern uint8_t yanwu_yanshi;
extern uint8_t sashui_yanshi;

extern uint8_t sudu_yanshi;
extern uint8_t sudu_sheding;
extern uint16_t sudu_dangqian;
extern uint8_t sudu_m_s;

extern uint8_t zhudianji_zhuangtai;
extern uint8_t congdianji_zhuangtai;
extern uint8_t zhadianji_zhuangtai;
extern uint8_t zhanglidianji_zhuangtai;

extern uint8_t kaichesashui;
extern uint8_t zhangli_baojing;

extern uint8_t zhangli_shangxian;
extern uint8_t zhangli_xiaxian;

extern uint8_t zhudianji_diandong;
extern uint8_t congdianji_diandong;
extern uint8_t zhadianji_diandong;
extern uint8_t fa_diandong;
extern uint8_t zhanglijia_diandong;
extern uint8_t zhanglijian_diandong;
extern uint8_t diandong_shineng;

extern uint8_t qidong_qidong;
extern uint8_t qidong_tingche;
extern uint8_t qidong_jiting;
extern uint8_t qidong_fuwei;

extern uint8_t zhangli_qidong;

extern TimerHandle_t Swtmr1_Handle;

//uint8_t zhangli_liangcheng_shangxian = 100;
//uint8_t zhangli_liangcheng_xiaxian = 0;

void NVIC_SysReset(void);

void kaiguan_task(void);

void wendu_task(void);
void zhangli_task(void);
void jiting_task(void);
void zhu_renwu(void);
void diandong_renwu(void);
void zhuangtai_renwu(void);

#endif


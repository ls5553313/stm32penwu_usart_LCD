#ifndef __TASKS_H
#define	__TASKS_H

#include "stm32f10x.h"

#define SETTING	226
#define RETURN	194
#define ADD	    2
#define LESS	  152
#define ONE			48
#define TWO	    24
#define THREE	  122
#define NEXT	  144

uint8_t main_task1(uint8_t mode_num);
uint8_t ADC_task(void);
void NVIC_SysReset(void);
uint8_t i2c_saving(void);
uint8_t i2c_reading(void);
void LCD_renwu(void);

extern int delay_time;
extern int sec;
extern char string[20];
extern uint8_t key;
extern uint8_t page;

extern float ADC_ConvertedValueLocal;   


#endif


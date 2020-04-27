
/* 头文件 */
#include "stm32f10x.h"
#include <stdio.h>
#include "./data_process/data_process.h"

extern uint8_t page;


void Usart2_data_process(uint8_t *pbuff)
{
	switch(pbuff[0])
   {
   case '0' :
      page=0;
      break;
   case '1' :
			page=1;
			break;
   case '2' :
			page=2;
			break;
   default :
      break;
   }
}





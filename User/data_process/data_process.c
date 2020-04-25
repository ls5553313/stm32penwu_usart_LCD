
/* 头文件 */
#include "stm32f10x.h"
#include <stdio.h>
#include "./data_process/data_process.h"


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
extern uint8_t sudu_m_s;
extern uint16_t sudu_dangqian;

extern uint8_t kaichesashui;
extern uint8_t zhangli_baojing;

extern uint8_t zhangli_shangxian;
extern uint8_t zhangli_xiaxian;

extern uint8_t zhudianji_zhuangtai;
extern uint8_t congdianji_zhuangtai;
extern uint8_t zhadianji_zhuangtai;
extern uint8_t zhanglidianji_zhuangtai;

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



static int32_t isspace(int32_t x);
static int32_t isdigit(int32_t x);
int32_t Str2Int(const char *nptr);
void Int2Str(int32_t num,char *ptr);
char *StrnCopy(char *dst, const char *src, uint32_t n);
void shezhi_fuzhi(uint8_t *pbuff);
void diandong_fuzhi(uint8_t *pbuff);
void zhuangtai_fuzhi(uint8_t *pbuff);
void qidong_fuzhi(uint8_t *pbuff);

void Usart2_data_process(uint8_t *pbuff)
{
	switch(pbuff[0])
   {
   case '0' :
      shezhi_fuzhi(pbuff);
      break;
   case '1' :
			diandong_fuzhi(pbuff);
			break;
   case '2' :
			zhuangtai_fuzhi(pbuff);
			break;
	 case '3' :
			qidong_fuzhi(pbuff);
			break;
   default :
      break;
   }
}

void shezhi_fuzhi(uint8_t *pbuff)
{
	char str[3];
	uint8_t shuruzhi;
	str[0]=pbuff[2];
	str[1]=pbuff[3];
	str[2]=pbuff[4];
	shuruzhi = Str2Int(str);
	switch(pbuff[1])
   {
   case '0' :
		  qiche_yanshi=shuruzhi;
      printf("qiche_yanshi=%d \n",qiche_yanshi);
      break;
   case '1' :
		 	tingche_yanshi=shuruzhi;
      printf("tingche_yanshi=%d \n",tingche_yanshi);
      break;		 
   case '2' :		  
		  paopian_yanshi=shuruzhi;
      printf("tingche_yanshi=%d \n",tingche_yanshi);
      break;
	 case '3' :		  
		  silie_yanshi=shuruzhi;
      printf("silie_yanshi=%d \n",silie_yanshi);
      break;
	 case '4' :		  
		  duimei_yanshi=shuruzhi;
      printf("duimei_yanshi=%d \n",duimei_yanshi);
      break;
	 case '5' :		  
		  wendu_yanshi=shuruzhi;
      printf("wendu_yanshi=%d \n",wendu_yanshi);
      break;
	 case '6' :		  
		  sudu_yanshi=shuruzhi;
      printf("sudu_yanshi=%d \n",sudu_yanshi);
      break;
	 case '7' :		  
		  yanwu_yanshi=shuruzhi;
      printf("yanwu_yanshi=%d \n",yanwu_yanshi);
      break;
	 case '8' :		  
		  sashui_yanshi=shuruzhi;
      printf("sashui_yanshi=%d \n",sashui_yanshi);
      break;
	 case '9' :		  
		  zhangli_shangxian=shuruzhi;
      printf("zhangli_shangxian=%d \n",zhangli_shangxian);
      break;
	 case 'a' :		  
		  zhangli_xiaxian=shuruzhi;
      printf("zhangli_xiaxian=%d \n",zhangli_xiaxian);
      break;
	 case 'b' :		  
		  wendu_sheding=shuruzhi;
      printf("wendu_sheding=%d \n",wendu_sheding);
      break;
	 case 'c' :		  
		  sudu_m_s=shuruzhi;
      printf("sudu_m_s=%d \n",sudu_sheding);
      break;
	 case 'd' :		  
		  kaichesashui=shuruzhi;
      printf("kaichesashui=%d \n",kaichesashui);
      break;
	 case 'e' :		  
		  zhangli_baojing=shuruzhi;
      printf("zhangli_baojing=%d \n",zhangli_baojing);
      break;
	 case 'f' :		  
		  sudu_sheding=sudu_dangqian;
      printf("sudu_sheding=%d \n",sudu_dangqian);
      break;
	 /*case 'g' :		  
		  qiche_yanshi=shuruzhi;
      printf("qiche_yanshi=%d \n",qiche_yanshi);
      break;*/
   default :
      break;
   }
}

void diandong_fuzhi(uint8_t *pbuff)
{
	char str[1];
	uint8_t shuruzhi;
	str[0]=pbuff[2];
	shuruzhi = Str2Int(str);
	switch(pbuff[1])
   {
   case '0' :
		  zhudianji_diandong=shuruzhi;
      printf("zhudianji_diandong=%d \n",zhudianji_diandong);
      break;
   case '1' :
		 	congdianji_diandong=shuruzhi;
      printf("congdianji_diandong=%d \n",congdianji_diandong);
      break;		 
   case '2' :		  
		  zhadianji_diandong=shuruzhi;
      printf("zhadianji_diandong=%d \n",zhadianji_diandong);
      break;
	 case '3' :		  
		  fa_diandong=shuruzhi;
      printf("fa_diandong=%d \n",fa_diandong);
      break;
	 case '4' :		  
		  zhanglijia_diandong=shuruzhi;
      printf("zhanglijia_diandong=%d \n",zhanglijia_diandong);
      break;
	 case '5' :		  
		  zhanglijian_diandong=shuruzhi;
      printf("zhanglijian_diandong=%d \n",zhanglijian_diandong);
      break;
	 case 'z' :		  
		  diandong_shineng=shuruzhi;
      printf("diandong_shineng=%d \n",diandong_shineng);
      break;

   default :
      break;
   }
}


void zhuangtai_fuzhi(uint8_t *pbuff)
{
	char str[1];
	uint8_t shuruzhi;
	str[0]=pbuff[2];
	shuruzhi = Str2Int(str);
	switch(pbuff[1])
   {
   case '0' :
		  zhudianji_zhuangtai=shuruzhi;
      printf("zhudianji_zhuangtai=%d \n",zhudianji_zhuangtai);
      break;
   case '1' :
		 	congdianji_zhuangtai=shuruzhi;
      printf("congdianji_zhuangtai=%d \n",congdianji_zhuangtai);
      break;		 
   case '2' :		  
		  zhadianji_zhuangtai=shuruzhi;
      printf("zhadianji_zhuangtai=%d \n",zhadianji_zhuangtai);
      break;
	 case '3' :		  
		  fa_diandong=shuruzhi;
      printf("zhanglidianji_zhuangtai=%d \n",zhanglidianji_zhuangtai);
      break;

   default :
      break;
   }
}

void qidong_fuzhi(uint8_t *pbuff)
{
	char str[1];
	uint8_t shuruzhi;
	str[0]=pbuff[2];
	shuruzhi = Str2Int(str);
	switch(pbuff[1])
   {
   case '0' :
		  qidong_qidong=shuruzhi;
      printf("qidong_qidong=%d \n",qidong_qidong);
      break;
   case '1' :
		 	qidong_tingche=shuruzhi;
      printf("qidong_tingche=%d \n",qidong_tingche);
      break;		 
   case '2' :		  
		  qidong_jiting=shuruzhi;
      printf("qidong_jiting=%d \n",qidong_jiting);
      break;
	 case '3' :		  
		  qidong_fuwei=shuruzhi;
      printf("qidong_fuwei=%d \n",qidong_fuwei);
      break;

   default :
      break;
   }
}




/************************************************************
  * @brief   Str2Int
  * @param   nptr:输入的字符串
  * @return  int32_t:返回一个整形数（int32）
  * @author  jiejie
  * @github  https://github.com/jiejieTop
  * @date    2018-xx-xx
  * @version v1.0
  * @note    将字符串转换为整形数
  ***********************************************************/
int32_t Str2Int(const char *nptr)
{
    int32_t c;             /* 当前字符 */
    int32_t total;         /* 目前的总和 */
    int32_t sign;          /* 如果'-'，则为负数，否则为正数 */

    /* 跳过空白 */
    while ( isspace((int32_t)(unsigned char)*nptr) )
        ++nptr;

    c = (int32_t)(unsigned char)*nptr++;
    sign = c;          			 /* 保存标志指示 */
    if (c == '-' || c == '+')
        c = (int32_t)(unsigned char)*nptr++;    /* 跳过符号 */

    total = 0;

    while (isdigit(c)) /* 字符串在数字范围 */
    {
        total = 10 * total + (c - '0');     /* 积累数字 */
        c = (int32_t)(unsigned char)*nptr++;   /* 获取下一个字符 */
    }

    if (sign == '-')
        return -total;
    else
        return total;   /* 返回结果 */
}
/************************************************************
  * @brief
  * @param   NULL
  * @return  NULL
  * @author  jiejie
  * @github  https://github.com/jiejieTop
  * @date    2018-xx-xx
  * @version v1.0
  * @note    将整形数转换为字符
  ***********************************************************/
void Int2Str(int32_t num,char *ptr)
{
  int i,j,sign;
  char str[7];/* uint32的数字最大为5位，加上正负号与'\0' */
  if((sign = num) < 0)    /* 记录符号 */
    num = -num;           /* 使n成为正数 */
  i=0;
  do {
      str[i++] = num%10 + '0';  /* 取下一个数字 */
  } while((num/=10) > 0);     /* 循环相除 */

  if(sign<0)
    str[i++] = '-'; /* 负数 */
  
  str[i] = '\0';  /* 添加结束'\0' */
  
  for(j=i-1; j>=0; j--) /* 生成的数字是逆序的，要逆序输出 */
    *ptr++ = str[j];
}

char *StrnCopy(char *dst, const char *src, uint32_t n)
{
  if (n != 0)
  {
    char *d = dst;
    const char *s = src;
    do
    {
        if ((*d++ = *s++) == 0)
        {
            while (--n != 0)
                *d++ = 0;
            break;
        }
    } while (--n != 0);
  }
  return (dst);
}


/************************************************************
                以下是内部调用函数
  ***********************************************************/
static int32_t isspace(int32_t x)
{
    if(x==' '||x=='\t'||x=='\n'||x=='\f'||x=='\b'||x=='\r')
        return 1;
    else
        return 0;
}

static int32_t isdigit(int32_t x)
{
    if(x<='9'&&x>='0')
        return 1;
    else
        return 0;
}



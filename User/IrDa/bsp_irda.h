#ifndef __IRDA_H
#define	__IRDA_H

#include "stm32f10x.h"
#include "sys.h"
 
#define RDATA 	PBin(9)	 	//�������������
//����ң��ʶ����(ID),ÿ��ң�����ĸ�ֵ��������һ��,��Ҳ��һ����.
//����ѡ�õ�ң����ʶ����Ϊ0
#define REMOTE_ID 0 

void Remote_Init(void);    	//���⴫��������ͷ���ų�ʼ��
uint8_t Remote_Scan(void);	    


#endif /* __IRDA_H */

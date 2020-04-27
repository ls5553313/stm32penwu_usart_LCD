
#include "bsp_usart1.h"
#include "bsp_usart2.h"
#include <string.h>

uint8_t SendBuff1[SENDBUFF1_SIZE];
uint8_t Usart1_Rx_Buf[USART1_RX_BUFF_SIZE];

static void USART1_DMA_Rx_Config(void);
static void USART1_DMA_Tx_Config(void);
void USART1_Receive_DataPack(void);

static void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* Ƕ�������жϿ�������ѡ�� */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
  
  /* ����USARTΪ�ж�Դ */
  NVIC_InitStructure.NVIC_IRQChannel = DEBUG_USART1_IRQ;
  /* �������ȼ�*/
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 6;
  /* �����ȼ� */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  /* ʹ���ж� */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  /* ��ʼ������NVIC */
  NVIC_Init(&NVIC_InitStructure);
}


/**
  * @brief  USART GPIO ����,������������
  * @param  ��
  * @retval ��
  */
void USART1_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	// �򿪴���GPIO��ʱ��
	DEBUG_USART1_GPIO_APBxClkCmd(DEBUG_USART1_GPIO_CLK, ENABLE);
	
	// �򿪴��������ʱ��
	DEBUG_USART1_APBxClkCmd(DEBUG_USART1_CLK, ENABLE);

	// ��USART Tx��GPIO����Ϊ���츴��ģʽ
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART1_TX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DEBUG_USART1_TX_GPIO_PORT, &GPIO_InitStructure);

  // ��USART Rx��GPIO����Ϊ��������ģʽ
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART1_RX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(DEBUG_USART1_RX_GPIO_PORT, &GPIO_InitStructure);
	
	// ���ô��ڵĹ�������
	// ���ò�����
	USART_InitStructure.USART_BaudRate = DEBUG_USART1_BAUDRATE;
	// ���� �������ֳ�
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	// ����ֹͣλ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	// ����У��λ
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	// ����Ӳ��������
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	// ���ù���ģʽ���շ�һ��
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	// ��ɴ��ڵĳ�ʼ������
	USART_Init(DEBUG_USART1, &USART_InitStructure);	
	// �����ж����ȼ�����
	NVIC_Configuration();
	
	
	USART_ITConfig(DEBUG_USART1, USART_IT_IDLE, ENABLE);  
	USART_DMACmd(DEBUG_USART1, USART_DMAReq_Rx, ENABLE); 
	USART1_DMA_Rx_Config();
	USART1_DMA_Tx_Config();
	// ʹ�ܴ���
	USART_Cmd(DEBUG_USART1, ENABLE);	    
}


void USART1_DMA_Tx_Config(void)
{
		DMA_InitTypeDef DMA_InitStructure;
	
		// ����DMAʱ��
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
		// ����DMAԴ��ַ���������ݼĴ�����ַ*/
    DMA_InitStructure.DMA_PeripheralBaseAddr = USART1_DR_ADDRESS;
		// �ڴ��ַ(Ҫ����ı�����ָ��)
		DMA_InitStructure.DMA_MemoryBaseAddr = (u32)SendBuff1;
		// ���򣺴��ڴ浽����	
		DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
		// �����С	
		DMA_InitStructure.DMA_BufferSize = SENDBUFF1_SIZE;
		// �����ַ����	    
		DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
		// �ڴ��ַ����
		DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
		// �������ݵ�λ	
		DMA_InitStructure.DMA_PeripheralDataSize = 
	  DMA_PeripheralDataSize_Byte;
		// �ڴ����ݵ�λ
		DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;	 
		// DMAģʽ��һ�λ���ѭ��ģʽ
		DMA_InitStructure.DMA_Mode = DMA_Mode_Normal ;
		//DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;	
		// ���ȼ�����	
		DMA_InitStructure.DMA_Priority = DMA_Priority_Medium; 
		// ��ֹ�ڴ浽�ڴ�Ĵ���
		DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
		// ����DMAͨ��		   
		DMA_Init(USART1_TX_DMA_CHANNEL, &DMA_InitStructure);		
		// ʹ��DMA
		DMA_Cmd (USART1_TX_DMA_CHANNEL,ENABLE);
}

static void USART1_DMA_Rx_Config(void)
{
	DMA_InitTypeDef DMA_InitStructure;

	// ����DMAʱ��
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	// ����DMAԴ��ַ���������ݼĴ�����ַ*/
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)USART1_DR_ADDRESS;
	// �ڴ��ַ(Ҫ����ı�����ָ��)
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)Usart1_Rx_Buf;
	// ���򣺴��ڴ浽����	
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	// �����С	
	DMA_InitStructure.DMA_BufferSize = USART1_RX_BUFF_SIZE;
	// �����ַ����	    
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	// �ڴ��ַ����
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	// �������ݵ�λ	
	DMA_InitStructure.DMA_PeripheralDataSize = 
	DMA_PeripheralDataSize_Byte;
	// �ڴ����ݵ�λ
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;	 
	// DMAģʽ��һ�λ���ѭ��ģʽ
	//DMA_InitStructure.DMA_Mode = DMA_Mode_Normal ;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;	
	// ���ȼ�����	
	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh; 
	// ��ֹ�ڴ浽�ڴ�Ĵ���
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	// ����DMAͨ��		   
	DMA_Init(USART1_RX_DMA_CHANNEL, &DMA_InitStructure);		
	// ���DMA���б�־
	DMA_ClearFlag(DMA1_FLAG_TC5);
	DMA_ITConfig(USART1_RX_DMA_CHANNEL, DMA_IT_TE, ENABLE);
	// ʹ��DMA
	DMA_Cmd (USART1_RX_DMA_CHANNEL,ENABLE);
}

void DEBUG_USART1_IRQHandler(void)
{
	/* ʹ�ô���DMA */
	if(USART_GetITStatus(DEBUG_USART1,USART_IT_IDLE)!=RESET)
	{		
		/* �������� */
		USART1_Receive_DataPack();
		// ��������жϱ�־λ
		USART_ReceiveData( DEBUG_USART1 );
	}	

}




/*****************  ����һ���ֽ� **********************/
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch)
{
	/* ����һ���ֽ����ݵ�USART */
	USART_SendData(pUSARTx,ch);
		
	/* �ȴ��������ݼĴ���Ϊ�� */
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}

/****************** ����8λ������ ************************/
void Usart_SendArray( USART_TypeDef * pUSARTx, uint8_t *array, uint16_t num)
{
  uint8_t i;
	
	for(i=0; i<num; i++)
  {
	    /* ����һ���ֽ����ݵ�USART */
	    Usart_SendByte(pUSARTx,array[i]);	
  
  }
	/* �ȴ�������� */
	while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TC)==RESET);
}

/*****************  �����ַ��� **********************/
void Usart_SendString( USART_TypeDef * pUSARTx, char *str)
{
	unsigned int k=0;
  do 
  {
      Usart_SendByte( pUSARTx, *(str + k) );
      k++;
  } while(*(str + k)!='\0');
  
  /* �ȴ�������� */
  while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TC)==RESET)
  {}
}

/*****************  ����һ��16λ�� **********************/
void Usart_SendHalfWord( USART_TypeDef * pUSARTx, uint16_t ch)
{
	uint8_t temp_h, temp_l;
	
	/* ȡ���߰�λ */
	temp_h = (ch&0XFF00)>>8;
	/* ȡ���Ͱ�λ */
	temp_l = ch&0XFF;
	
	/* ���͸߰�λ */
	USART_SendData(pUSARTx,temp_h);	
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
	
	/* ���͵Ͱ�λ */
	USART_SendData(pUSARTx,temp_l);	
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}

///�ض���c�⺯��printf�����ڣ��ض�����ʹ��printf����
int fputc(int ch, FILE *f)
{
		/* ����һ���ֽ����ݵ����� */
		USART_SendData(DEBUG_USART2, (uint8_t) ch);
		
		/* �ȴ�������� */
		while (USART_GetFlagStatus(DEBUG_USART2, USART_FLAG_TXE) == RESET);		
	
		return (ch);
}

///�ض���c�⺯��scanf�����ڣ���д����ʹ��scanf��getchar�Ⱥ���
int fgetc(FILE *f)
{
		/* �ȴ������������� */
		while (USART_GetFlagStatus(DEBUG_USART2, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(DEBUG_USART2);
}

/**
  * @brief  USARTx TX DMA ���ã��ڴ浽����(USART1->DR)
  * @param  ��
  * @retval ��
  */


void Usart1_Send_Data(uint8_t *buf, uint16_t len)
{
	uint16_t i = 0;

	/* ѭ�����ͣ�һ���ֽ� */
	for(i=0; i<len; i++)
	{
		Usart_SendByte(DEBUG_USART1,buf[i]);
	}
}


	
void USART1_Receive_DataPack(void)
{
	/* ���յ����ݳ��� */
	uint32_t buff_length;
  uint8_t *pbuff = Usart1_Rx_Buf;
	
	/* �ر�DMA ����ֹ���� */
	DMA_Cmd(USART1_RX_DMA_CHANNEL, DISABLE);  /* ��ʱ�ر�dma��������δ���� */ 
	
	/* ��ȡ���յ������ݳ��� ��λΪ�ֽ�*/
	buff_length = USART1_RX_BUFF_SIZE - DMA_GetCurrDataCounter(USART1_RX_DMA_CHANNEL);
	
	
	 printf("���յ��ַ���%s\n",pbuff);
	
	memset(Usart1_Rx_Buf,0,buff_length);
	
	/* ��DMA��־λ */
	DMA_ClearFlag( DMA1_FLAG_TC5 );          
	
	/* ���¸�ֵ����ֵ��������ڵ��������ܽ��յ�������֡��Ŀ */
	USART1_RX_DMA_CHANNEL->CNDTR = USART1_RX_BUFF_SIZE;    
  
	/* �˴�Ӧ���ڴ����������ٴ򿪣����� DataPack_Process() ��*/
	DMA_Cmd(USART1_RX_DMA_CHANNEL, ENABLE);      

}


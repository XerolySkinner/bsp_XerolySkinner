/*----------------------------------------------------------------------------------------------------
 #
 #	Copyright (c) 2022 Yuankang Liang(XerolySkinner)
 #
 #	�������ԭ���ṩ,���κ���ʾ��ʾ
 #	���κ������,���߶����е��κ����⳥����
 #
 #	ʹ�õ��������:
 #	1.	�����������������Դ,�㲻���������д��ԭʼ���.
 #	2.	����������κ�Ŀ��,ǰ���ǰ�Ȩ�������������и�����.
 #		���Ұ�Ȩ�������������ͬʱ����.
 #	3.	����ʹ��,����,�޸�,�ַ�,�����۱���������.
 #	4.	������ڲ�Ʒ��ʹ��,��Ʒ�ĵ��е����������͵ĵ����Ǳ����.
 #	5.	��֪ͨ���ô��κ���Դɾ�������.
 #
 #	Yuankang Liang(XerolySkinner)
 #		E-mail:zabbcccbbaz@163.com
 #		QQ:2715099320
 #		Mobile Phone:13005636215
 #
 #	All rights reserved.
 */

/**
 * @file		bsp_IIC.h
 * @brief		����ʵ�����IIC����
 *				�������������������IIC����
 * @mainpage	��Ҫ��Ϣ
 * @author		Yuankang Liang(XerolySkinner)
 * @email		zabbcccbbaz@163.com
 * @version		V1.0.0
 * @date		2022-11-07 00:56
 */
#ifndef _BSP_IIC_
#define _BSP_IIC_
#include "reg52.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	��������
/**
 * @todo 		����SCK�Ĺܽ�
 */
sbit	IIC_SCK_PIN=P2^1;			///< ����SCK�Ĺܽ�
/**
 * @todo 		����SDA�Ĺܽ�
 */
sbit	IIC_SDA_PIN=P2^0;			///< ����SDA�Ĺܽ�
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	ö��ͷ
/**
 * @brief 		���ƹܽŵ�����״̬(��λ,��λ,��ȡ)
 */
enum {
	IIC_RESET,			///< �ܽŸ�λ״̬
	IIC_SET,			///< �ܽ���λ״̬
	IIC_READ			///< ��ȡ�ܽ�״̬
};
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	��Ŀ
/**
 * @brief 		IIC�Ļ���ʵ�ַ���
 */
void			IIC_WriteOneByte(unsigned char id, unsigned char addr, unsigned char dat);
unsigned char	IIC_ReadOneByte(unsigned char id, unsigned char addr);
void			IIC_Write(unsigned char id,unsigned char addr,unsigned char* dat,unsigned int len);
void			IIC_Read(unsigned char id,unsigned char addr,unsigned char* dat,unsigned int len);
//----------------------------------------------------------------------------------------------------
void			IIC_Start(void);
void			IIC_Stop(void);
void			IIC_SendAck(unsigned char ackbit);
unsigned char	IIC_WaitAck(void);
void			IIC_SendByte(unsigned char byt);
unsigned char	IIC_RecByte(void);
//----------------------------------------------------------------------------------------------------
/**
 * @brief			����SCK�ܽſ�
 * 
 * @param	var		�˴�������״̬,IIC_SET��λ�ܽ�,IIC_RESET��λ�ܽ�
 * @return			��varΪIIC_READʱ���عܽ�״̬
 */ 
unsigned char IIC_SCK(unsigned char var);
/**
 * @brief			����SDA�ܽſ�
 * 
 * @param	var		�˴�������״̬,IIC_SET��λ�ܽ�,IIC_RESET��λ�ܽ�
 * @return			��varΪIIC_READʱ���عܽ�״̬
 */ 
unsigned char IIC_SDA(unsigned char var);
/**
 * @brief			ʱ���е���ʱ
 * 					�ڴ˴�������ʱ
 */ 
void IIC_Delay(void);
//////////////////////////////////////////////////////////////////////////////////////////////////////
#endif

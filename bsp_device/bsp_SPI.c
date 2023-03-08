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
  * @file		bsp_SPI.c
  * @brief		SPI�Ŀ�
  * @mainpage	��Ҫ��Ϣ
  * @author		Yuankang Liang(XerolySkinner)
  * @email		zabbcccbbaz@163.com
  * @version		V1.0.0
  * @date		Wed Mar  8 22:22:53 2023
  */
#include "bsp_SPI.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	����
/**
 * @brief			ʹ�����߷���һ���ֽ�����
 * @param	temp	���͵�����
 * @return			�޷���ֵ
 * @note			������Ϊ�����������Ӻ���,��Ҫֱ��ʹ�ñ�����
 */ 
void SPI_Byte(unsigned char temp){
	unsigned char i;
	for (i=0;i<8;i++){
		SPI_SCK_PIN = 0;
		SPI_SDA_PIN = temp&0x01;
		temp>>=1;
		SPI_SCK_PIN=1;}}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			ʹ�����߷���һ���ֽ�����
 * @param	addr	��Ҫ��д�ļĴ�����ַ
 * @param	dat 	��д������
 * @return			�޷���ֵ
 */ 
void SPI_WriteOneByte(unsigned char address,unsigned char dat){
 	SPI_RST_PIN=0;	_nop_();
 	SPI_SCK_PIN=0;	_nop_();
 	SPI_RST_PIN=1; 	_nop_();
 	SPI_Byte(address);
 	SPI_Byte(dat);
 	SPI_RST_PIN=0;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			ʹ�����߻�ȡһ���ֽ�����
 * @param	addr	��Ҫ���յļĴ�����ַ
 * @param	dat 	���ܵ�����
 * @return			�޷���ֵ
 */ 
unsigned char SPI_ReadOneByte(unsigned char address){
 	unsigned char i,temp=0x00;
 	SPI_RST_PIN=0;	_nop_();
 	SPI_SCK_PIN=0;	_nop_();
 	SPI_RST_PIN=1;	_nop_();
 	SPI_Byte(address);
 	for (i=0;i<8;i++){
		SPI_SCK_PIN=0;
		temp>>=1;
 		if(SPI_SDA_PIN)temp|=0x80;
		SPI_SCK_PIN=1;}
 	SPI_RST_PIN=0;	_nop_();
 	SPI_SCK_PIN=0;	_nop_();
	SPI_SCK_PIN=1;	_nop_();
	SPI_SDA_PIN=0;	_nop_();
	SPI_SDA_PIN=1;	_nop_();
	return temp;}
//////////////////////////////////////////////////////////////////////////////////////////////////////

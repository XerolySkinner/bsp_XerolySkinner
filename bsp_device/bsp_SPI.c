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
#include "intrins.h"
#include <stdarg.h>
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	����
/**
 * @brief			ʹ�����߷���һ���ֽ�����
 * @param	temp	���͵�����
 * @return			�޷���ֵ
 * @note			������Ϊ�����������Ӻ���,��Ҫֱ��ʹ�ñ�����
 */ 
void SPI3_Byte(u8 temp){
	u8 i;
	for (i=0;i<8;i++){
		SPI3_SCK_PIN = 0;
		SPI3_SDA_PIN = (temp&0x01!=0);
		temp>>=1;
		SPI3_SCK_PIN=1;}}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			ʹ�����߷���һ���ֽ�����
 * @param	addr	��Ҫ��д�ļĴ�����ַ
 * @param	dat 	��д������
 * @return			�޷���ֵ
 */ 
void SPI3_WriteOneByte(u8 address,u8 dat){
 	SPI3_RST_PIN=SPI_CS;		_nop_();
 	SPI3_SCK_PIN=0;				_nop_();
 	SPI3_RST_PIN=!SPI_CS;	 	_nop_();
 	SPI3_Byte(address);
 	SPI3_Byte(dat);
 	SPI3_RST_PIN=SPI_CS;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			ʹ�����߻�ȡһ���ֽ�����
 * @param	addr	��Ҫ���յļĴ�����ַ
 * @param	dat 	���ܵ�����
 * @return			�޷���ֵ
 */ u8 SPI3_ReadOneByte(u8 address){
 	u8 i,temp=0x00;
 	SPI3_RST_PIN=SPI_CS;		_nop_();
 	SPI3_SCK_PIN=0;				_nop_();
 	SPI3_RST_PIN=!SPI_CS;		_nop_();
 	SPI3_Byte(address);
 	for (i=0;i<8;i++){
		SPI3_SCK_PIN=0;
		temp>>=1;
 		if(SPI3_SDA_PIN)temp|=0x80;
		SPI3_SCK_PIN=1;}
 	SPI3_RST_PIN=SPI_CS;		_nop_();
 	SPI3_SCK_PIN=0;				_nop_();
	SPI3_SCK_PIN=1;				_nop_();
	SPI3_SDA_PIN=0;				_nop_();
	SPI3_SDA_PIN=1;				_nop_();
	return temp;}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	����
/**
 * @brief			��ʼ��4��SPI
 * @return			�޷���ֵ
 * @note			ʹ�����º���ǰ,��������ʹ��һ�θú�����ʼ��
 */ 
void SPI4_Init(void){
	SPI4_CS_PIN=SPI_CS;
	SPI4_SCK_PIN=SPI_CPOL;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			ʹ�����߽���һ���ֽ�����
 * @param	temp	���͵�����
 * @return			�����ص�����
 */ 
u8 SPI4_Byte(u8 temp){
	u8 k=0;
	u16 i=0;
	u8 res=0;
//	CPHA=1
#if SPI_CPHA														//	ǰ��������ز���
	SPI4_Delay();
	for(i=0;i<8;i++){
		SPI4_SCK_PIN=!SPI_CPOL;										//	����
		SPI4_MOSI_PIN=(_crol_(temp,i)&0x80)!=0;						//	���
		SPI4_Delay();
		SPI4_SCK_PIN=SPI_CPOL;										//	����
		res|=(SPI4_MISO_PIN!=0);									//	����
		SPI4_Delay();
		if(i!=7)res<<=1;
		}
//	CPHA=0
#else																//	ǰ�ز������ش���
	SPI4_MOSI_PIN=(_crol_(temp,0)&0x80)!=0;							//	Ԥ���
	SPI4_Delay();
	for(i=1;i<9;i++){
		SPI4_SCK_PIN=!SPI_CPOL;										//	����
		res|=(SPI4_MISO_PIN!=0);									//	����
		SPI4_Delay();
		if(i!=8)res<<=1;
		SPI4_SCK_PIN=SPI_CPOL;										//	����
		SPI4_MOSI_PIN=(_crol_(temp,i)&0x80)!=0;						//	���
		SPI4_Delay();
		}
#endif
	return res;
	}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			ʹ�����߽���һ������
 * @param	format	�����ĸ�ʽ
 * @return			�����ص�����
 * @attention		����Ϊʹ��ʾ��
 * @code
 * // д��0xAB 0xFF 0xFF��,��ȡһ���ֽڵ�dat��
 * SPI4_Data_WR("WWWR",0xAB,0xFF,0XFF,&dat);
 * @endcode
 */ 
void SPI4_Data_WR(const char* format,...){
	u8 temp=0;
	u8* member=0;
	va_list args;														//	����������
	va_start(args, format);												//	��ʼ������������
	SPI4_CS_PIN=!SPI_CS;
	while(*format=='W' || *format=='w' || *format=='R' || *format=='r'){
		if(*format=='W' || *format=='w'){
			temp=va_arg(args,u8);										//	��ȡW����
			SPI4_Byte(temp);}											//	д��
		else if(*format=='R' || *format=='r'){
			member=va_arg(args,u8*);									//	��ȡR����
			*member=SPI4_Byte(SPI_READ_DATA);}							//	��ȡ
		format++;}
	va_end(args);														//	��ʬ
	SPI4_CS_PIN=SPI_CS;
	return;}
//////////////////////////////////////////////////////////////////////////////////////////////////////

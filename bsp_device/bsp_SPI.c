/*----------------------------------------------------------------------------------------------------
 #
 #	Copyright (c) 2022 Yuankang Liang(XerolySkinner)
 #
 #	本软件按原样提供,无任何明示或暗示
 #	在任何情况下,作者都不承担任何损害赔偿责任
 #
 #	使用的许可声明:
 #	1.	不得歪曲本软件的来源,你不能声称你编写了原始软件.
 #	2.	免费授予以任何目的,前提是版权声明出现在所有副本中.
 #		并且版权声明和许可声明同时出现.
 #	3.	你有使用,复制,修改,分发,和销售本软件的许可.
 #	4.	如果你在产品中使用,产品文档中的声明是赞赏的但不是必须的.
 #	5.	本通知不得从任何来源删除或更改.
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
  * @brief		SPI的库
  * @mainpage	主要信息
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
//	函数
/**
 * @brief			使用总线发送一个字节数据
 * @param	temp	发送的数据
 * @return			无返回值
 * @note			本函数为其他函数的子函数,不要直接使用本函数
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
 * @brief			使用总线发送一个字节数据
 * @param	addr	需要改写的寄存器地址
 * @param	dat 	改写的数据
 * @return			无返回值
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
 * @brief			使用总线获取一个字节数据
 * @param	addr	需要接收的寄存器地址
 * @param	dat 	接受的数据
 * @return			无返回值
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
//	函数
/**
 * @brief			初始化4线SPI
 * @return			无返回值
 * @note			使用以下函数前,请先至少使用一次该函数初始化
 */ 
void SPI4_Init(void){
	SPI4_CS_PIN=SPI_CS;
	SPI4_SCK_PIN=SPI_CPOL;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			使用总线交换一个字节数据
 * @param	temp	发送的数据
 * @return			交换回的数据
 */ 
u8 SPI4_Byte(u8 temp){
	u8 k=0;
	u16 i=0;
	u8 res=0;
//	CPHA=1
#if SPI_CPHA														//	前沿输出后沿采样
	SPI4_Delay();
	for(i=0;i<8;i++){
		SPI4_SCK_PIN=!SPI_CPOL;										//	先沿
		SPI4_MOSI_PIN=(_crol_(temp,i)&0x80)!=0;						//	输出
		SPI4_Delay();
		SPI4_SCK_PIN=SPI_CPOL;										//	后沿
		res|=(SPI4_MISO_PIN!=0);									//	采样
		SPI4_Delay();
		if(i!=7)res<<=1;
		}
//	CPHA=0
#else																//	前沿采样后沿传输
	SPI4_MOSI_PIN=(_crol_(temp,0)&0x80)!=0;							//	预输出
	SPI4_Delay();
	for(i=1;i<9;i++){
		SPI4_SCK_PIN=!SPI_CPOL;										//	先沿
		res|=(SPI4_MISO_PIN!=0);									//	采样
		SPI4_Delay();
		if(i!=8)res<<=1;
		SPI4_SCK_PIN=SPI_CPOL;										//	后沿
		SPI4_MOSI_PIN=(_crol_(temp,i)&0x80)!=0;						//	输出
		SPI4_Delay();
		}
#endif
	return res;
	}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			使用总线交换一串数据
 * @param	format	交换的格式
 * @return			交换回的数据
 * @attention		以下为使用示例
 * @code
 * // 写入0xAB 0xFF 0xFF后,读取一个字节到dat中
 * SPI4_Data_WR("WWWR",0xAB,0xFF,0XFF,&dat);
 * @endcode
 */ 
void SPI4_Data_WR(const char* format,...){
	u8 temp=0;
	u8* member=0;
	va_list args;														//	不定长变量
	va_start(args, format);												//	初始化不定长变量
	SPI4_CS_PIN=!SPI_CS;
	while(*format=='W' || *format=='w' || *format=='R' || *format=='r'){
		if(*format=='W' || *format=='w'){
			temp=va_arg(args,u8);										//	获取W参数
			SPI4_Byte(temp);}											//	写入
		else if(*format=='R' || *format=='r'){
			member=va_arg(args,u8*);									//	获取R参数
			*member=SPI4_Byte(SPI_READ_DATA);}							//	读取
		format++;}
	va_end(args);														//	收尸
	SPI4_CS_PIN=SPI_CS;
	return;}
//////////////////////////////////////////////////////////////////////////////////////////////////////

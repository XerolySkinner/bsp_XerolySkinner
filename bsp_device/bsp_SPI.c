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
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	函数
/**
 * @brief			使用总线发送一个字节数据
 * @param	temp	发送的数据
 * @return			无返回值
 * @note			本函数为其他函数的子函数,不要直接使用本函数
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
 * @brief			使用总线发送一个字节数据
 * @param	addr	需要改写的寄存器地址
 * @param	dat 	改写的数据
 * @return			无返回值
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
 * @brief			使用总线获取一个字节数据
 * @param	addr	需要接收的寄存器地址
 * @param	dat 	接受的数据
 * @return			无返回值
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

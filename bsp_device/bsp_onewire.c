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
  * @file		bsp_onewire.c
  * @brief		onewire协议
  * @mainpage	主要信息
  * @author		Yuankang Liang(XerolySkinner)
  * @email		zabbcccbbaz@163.com
  * @version		V1.0.0
  * @date		Wed Mar 15 21:48:36 2023

  */
#include "bsp_onewire.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	函数
/**
 * @brief			title
 * @param	var 	vars
 * @return			res
 */
//单总线延时函数
void Delay_OneWire(u16 t){
	while(t--);}
//----------------------------------------------------------------------------------------------------
//	写一个字节
void OneWire_Write(u8 dat){
	u8 i;
	for(i=0;i<8;i++){
		IO = 0;
		IO = dat&0x01;
		Delay_OneWire(5);
		IO = 1;
		dat >>= 1;}
	Delay_OneWire(5);}
//----------------------------------------------------------------------------------------------------
//	读取一个字节
u8 OneWire_Read(void){
	u8 i;
	u8 dat;
	for(i=0;i<8;i++){
		IO = 0;
		dat >>= 1;
		IO = 1;
		if(IO)dat |= 0x80;
		Delay_OneWire(5);}
	return dat;}
//----------------------------------------------------------------------------------------------------
//	设备初始化
u8 OneWire_Init(void){
  	u8 initflag = 0;
  	IO = 1;
  	Delay_OneWire(12);
  	IO = 0;
  	Delay_OneWire(80);
  	IO = 1;
  	Delay_OneWire(10);
    initflag = IO;
  	Delay_OneWire(5);
  	return initflag;}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	DS18B20
u8 rd_temperature(void){
	u8 LSB,MSB,temp8;
	u16 temp16;
	OneWire_Init();
	OneWire_Write(0xcc);
	OneWire_Write(0x44);
	OneWire_Init();	
	OneWire_Write(0xcc);
	OneWire_Write(0xbe);
	LSB = OneWire_Read();
	MSB = OneWire_Read();	
	temp16 = (MSB<<8) | LSB;
	temp8 = temp16 * 0.0625;
	return temp8;}
//////////////////////////////////////////////////////////////////////////////////////////////////////

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
 * @file		varint.h
 * @brief		全局共用的标准类型表
 * @mainpage	主要信息
 * @author		Yuankang Liang(XerolySkinner)
 * @email		zabbcccbbaz@163.com
 * @version		V1.0.0
 * @date		2022-11-07 18:50
 */

#ifndef _VARINT_H_
#define _VARINT_H_
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	程序
//	
typedef unsigned char	u8;		///< 8位无符号数类型
typedef unsigned int	u16;	///< 16位无符号数类型
typedef unsigned long	u32;	///< 32位无符号数类型

typedef char			i8;		///< 8位有符号数类型
typedef int				i16;	///< 16位有符号数类型
typedef long			i32;	///< 32位有符号数类型

typedef volatile u8		vu8;	///< 8位无符号易变类型
typedef volatile u16 	vu16;	///< 16位无符号易变类型
typedef volatile u32 	vu32;	///< 32位无符号易变类型

typedef volatile i8		vi8;	///< 8位有符号易变类型
typedef volatile i16 	vi16;	///< 16位有符号易变类型
typedef volatile i32 	vi32;	///< 32位有符号易变类型
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	位宏
#define P8(x)		((u8*)(&(x)))				///< 强制转换变成u8的指针
#define Pn8(x,y)	(((u8*)(&(x)))[y])			///< 强制转换变成u8的数组
#define P16(x)		((u16*)(&(x)))				///< 强制转换变成u16的指针
#define Pn16(x,y)	(((u16*)(&(x)))[y])			///< 强制转换变成u16的数组
#define P32(x)		((u32*)(&(x)))				///< 强制转换变成u32的指针
#define Pn32(x,y)	(((u32*)(&(x)))[y])			///< 强制转换变成u32的数组

#define DelLb(x)	(x & (x - 1))				///< 移除最低位的1
#define qDelLb(x)	(x=(x & (x - 1)))			///< 移除并保存最低位的1

#define toBool(x)	(x!=0)						///< 数布尔化
#define uBit(x,y)	(x&(1<<y))					///< 挑选某一位
#define tBit(x,y)	(toBool(uBit(x,y)))			///< 挑选某一位并且布尔化

#define sBit(x,y)	(x|(1<<y))					///< 置高某一位
#define rBit(x,y)	(x&(~(1<<y)))				///< 拉低某一位
#define mBit(x,y,z)	((z)?sBit(x,y):rBit(x,y))	///< 选择性拉高拉低某一位

#define LoopAdd(var,min,step,max)	(var<max?var+step:min)
#define qLoopAdd(var,min,step,max)	(var=var<max?var+step:min)
#define LoopDec(var,min,step,max)	(var>min?var-step:max)
#define qLoopDec(var,min,step,max)	(var=var>min?var-step:max)
//////////////////////////////////////////////////////////////////////////////////////////////////////
#endif

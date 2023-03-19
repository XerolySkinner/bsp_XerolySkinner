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
 * @file		varint.h
 * @brief		ȫ�ֹ��õı�׼���ͱ�
 * @mainpage	��Ҫ��Ϣ
 * @author		Yuankang Liang(XerolySkinner)
 * @email		zabbcccbbaz@163.com
 * @version		V1.0.0
 * @date		2022-11-07 18:50
 */

#ifndef _VARINT_H_
#define _VARINT_H_
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	����
//	
typedef unsigned char	u8;		///< 8λ�޷���������
typedef unsigned int	u16;	///< 16λ�޷���������
typedef unsigned long	u32;	///< 32λ�޷���������

typedef char			i8;		///< 8λ�з���������
typedef int				i16;	///< 16λ�з���������
typedef long			i32;	///< 32λ�з���������

typedef volatile u8		vu8;	///< 8λ�޷����ױ�����
typedef volatile u16 	vu16;	///< 16λ�޷����ױ�����
typedef volatile u32 	vu32;	///< 32λ�޷����ױ�����

typedef volatile i8		vi8;	///< 8λ�з����ױ�����
typedef volatile i16 	vi16;	///< 16λ�з����ױ�����
typedef volatile i32 	vi32;	///< 32λ�з����ױ�����
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	λ��
#define P8(x)		((u8*)(&(x)))				///< ǿ��ת�����u8��ָ��
#define Pn8(x,y)	(((u8*)(&(x)))[y])			///< ǿ��ת�����u8������
#define P16(x)		((u16*)(&(x)))				///< ǿ��ת�����u16��ָ��
#define Pn16(x,y)	(((u16*)(&(x)))[y])			///< ǿ��ת�����u16������
#define P32(x)		((u32*)(&(x)))				///< ǿ��ת�����u32��ָ��
#define Pn32(x,y)	(((u32*)(&(x)))[y])			///< ǿ��ת�����u32������

#define DelLb(x)	(x & (x - 1))				///< �Ƴ����λ��1
#define qDelLb(x)	(x=(x & (x - 1)))			///< �Ƴ����������λ��1

#define toBool(x)	(x!=0)						///< ��������
#define uBit(x,y)	(x&(1<<y))					///< ��ѡĳһλ
#define tBit(x,y)	(toBool(uBit(x,y)))			///< ��ѡĳһλ���Ҳ�����

#define sBit(x,y)	(x|(1<<y))					///< �ø�ĳһλ
#define rBit(x,y)	(x&(~(1<<y)))				///< ����ĳһλ
#define mBit(x,y,z)	((z)?sBit(x,y):rBit(x,y))	///< ѡ������������ĳһλ

#define LoopAdd(var,min,step,max)	(var<max?var+step:min)
#define qLoopAdd(var,min,step,max)	(var=var<max?var+step:min)
#define LoopDec(var,min,step,max)	(var>min?var-step:max)
#define qLoopDec(var,min,step,max)	(var=var>min?var-step:max)
//////////////////////////////////////////////////////////////////////////////////////////////////////
#endif

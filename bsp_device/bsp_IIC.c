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
 * @file		bsp_IIC.c
 * @brief		����ʵ�����IIC����
 *				�������������������IIC����
 * @mainpage	��Ҫ��Ϣ
 * @author		Yuankang Liang(XerolySkinner)
 * @email		zabbcccbbaz@163.com
 * @version		V1.0.0
 * @date		2022-11-07 00:56
 *
 */

//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	ͷ�ļ�
#include "bsp_IIC.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	�ײ����
//	
/**
 * @brief			����IIC��ʼ�ź�
 */
void IIC_Start(void) {
	IIC_SDA(IIC_SET);
	IIC_SDA(IIC_SET);
	IIC_SCK(IIC_SET);
	IIC_Delay();
	IIC_SDA(IIC_RESET);
	IIC_Delay();
	IIC_SCK(IIC_RESET);}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			����IICֹͣ�ź�
 */
void IIC_Stop(void) {
	IIC_SDA(IIC_RESET);
	IIC_SCK(IIC_SET);
	IIC_Delay();
	IIC_SDA(IIC_SET);
	IIC_Delay();}
//----------------------------------------------------------------------------------------------------
//����Ӧ����Ӧ���ź�
/**
 * @brief			����IICӦ���ź�
 * @param	ackbit	0ΪӦ��,1λ��Ӧ��
 */
void IIC_SendAck(unsigned char ackbit) {
	IIC_SCK(IIC_RESET);
	IIC_SDA(ackbit);
	IIC_Delay();
	IIC_SCK(IIC_SET);
	IIC_Delay();
	IIC_SCK(IIC_RESET);
	IIC_SDA(IIC_SET);
	IIC_Delay();}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			�ȴ�Ӧ���ź�
 * @return			�����Ƿ��л�Ӧ
 */
unsigned char IIC_WaitAck(void) {
	unsigned char ackbit;
	IIC_SCK(IIC_SET);
	IIC_Delay();
	ackbit = IIC_SDA(IIC_READ);
	IIC_SCK(IIC_RESET);
	IIC_Delay();
	return ackbit;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			����IICһ���ֽ��ź�
 * @param	byt		���͵��ֽ�
 */
void IIC_SendByte(unsigned char byt) {
	unsigned char i;
	for (i = 0; i < 8; i++) {
		IIC_SCK(IIC_RESET);
		IIC_Delay();
		IIC_SDA((byt & 0x80) != 0);
		IIC_Delay();
		IIC_SCK(IIC_SET);
		byt <<= 1;
		IIC_Delay();}
	IIC_SCK(IIC_RESET);}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			����IICһ���ֽ��ź�
 * @return			���յ���һ���ֽ��ź�
 */
unsigned char IIC_RecByte(void) {
	unsigned char i=0, da=0;
	for (i = 0; i < 8; i++) {
		IIC_SCK(IIC_SET);
		IIC_Delay();
		da <<= 1;
		if (IIC_SDA(IIC_READ))da |= 1;
		IIC_SCK(IIC_RESET);
		IIC_Delay();}
	return da;}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	��װ����
//	
/**
 * @brief			ʹ�����߷���һ���ֽ�����
 * 
 * @param	id		���͵�������ַ,��0x68(MPU6050)
 * @param	addr	��Ҫ��д�ļĴ�����ַ
 * @param	dat 	��д������
 * @return			�޷���ֵ
 */ 
void IIC_WriteOneByte(unsigned char id, unsigned char addr, unsigned char dat) {
	IIC_Start();
	IIC_SendByte(id << 1);
	IIC_WaitAck();
	IIC_SendByte(addr);
	IIC_WaitAck();
	IIC_SendByte(dat);
	IIC_WaitAck();
	IIC_Stop();}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			ʹ�����߽���һ���ֽ�����
 * 
 * @param	id		���յ�������ַ,��0x68(MPU6050)
 * @param	addr	��Ҫ��ȡ���ݵļĴ�����ַ
 * @return			���ظüĴ����ڵ�����
 */
unsigned char IIC_ReadOneByte(unsigned char id, unsigned char addr) {
	unsigned char temp = 0;
	IIC_Start();
	IIC_SendByte(id << 1);
	IIC_WaitAck();
	IIC_SendByte(addr);
	IIC_SendAck(0);
	IIC_Start();
	IIC_SendByte((id << 1) | 0x01);
	IIC_SendAck(0);
	temp = IIC_RecByte();
	IIC_SendAck(1);
	IIC_Stop();
	return temp;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			ʹ�����߷��Ͷ�������
 * 
 * @param	id		���͵�������ַ,��0x68(MPU6050)
 * @param	addr	��Ҫ��д�ļĴ�����ַ��ʼ
 * @param	dat 	��д������ָ��
 * @param	len		������Ŀ
 * @return			�޷���ֵ
 */
void IIC_Write(unsigned char id,unsigned char addr,unsigned char* dat,unsigned int len){
	unsigned int i=0;
	IIC_Start();
	IIC_SendByte(id<<1);
	IIC_WaitAck();
	IIC_SendByte(addr);
	IIC_WaitAck();
	for(;i<len;i++){
		IIC_SendByte(dat[i]);
		IIC_WaitAck();}
	IIC_Stop();
	return;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			ʹ�����߽��ն�������
 * 
 * @param	id		���յ�������ַ,��0x68(MPU6050)
 * @param	addr	��Ҫ���յļĴ�����ַ��ʼ
 * @param	dat 	��д������ָ��
 * @param	len		������Ŀ
 * @return			�޷���ֵ
 */
void IIC_Read(unsigned char id,unsigned char addr,unsigned char* dat,unsigned int len){
	unsigned int i=0;
	IIC_Start();
	IIC_SendByte(id<<1);
	IIC_WaitAck();
	IIC_SendByte(addr);
	IIC_SendAck(0);
	IIC_Start();
	IIC_SendByte((id<<1)|0x01);
	IIC_SendAck(0);
	for(;i<len;i++){
		dat[i]=IIC_RecByte();
		IIC_SendAck(i==(len-1));}
	IIC_Stop();
	return;}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	�������
//	
/**
 * @brief			ʱ���е���ʱ
 *					�ڴ˴�������ʱ
 */ 
void IIC_Delay(void) {
	unsigned char i = 0;
	while (++i);}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			����SCK�ܽſ�
 * 
 * @param	var 	�˴�������״̬,IIC_SET��λ�ܽ�,IIC_RESET��λ�ܽ�
 * @return			��varΪIIC_READʱ���عܽ�״̬
 */ 
unsigned char IIC_SCK(unsigned char var) {
	if (var == IIC_RESET) {
		IIC_SCK_PIN=0;
		return 2;}
	else if (var == IIC_SET) {
		IIC_SCK_PIN=1;
		return 2;}
	else {
		return IIC_SCK_PIN;
	}}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			����SDA�ܽſ�
 * @param	var 	�˴�������״̬,IIC_SET��λ�ܽ�,IIC_RESET��λ�ܽ�
 * @return			��varΪIIC_READʱ���عܽ�״̬
 */ 
unsigned char IIC_SDA(unsigned char var){
	if (var == IIC_RESET) {
		IIC_SDA_PIN=0;
		return 2;}
	else if (var == IIC_SET) {
		IIC_SDA_PIN=1;
		return 2;}
	else {
		return IIC_SDA_PIN;
	}}
//////////////////////////////////////////////////////////////////////////////////////////////////////


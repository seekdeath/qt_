#include "motorcmd.h"
#include "includes.h"

#ifndef 	NULL
#define		NULL	(void*)0
char aRxBuff1[];
char aTxBuff1[];
unsigned char NRxBuff1;
unsigned char NTxBuff1;
unsigned char StaBao1;

unsigned short cal_crc(unsigned char *byte,unsigned char nbyte)
{
	unsigned short itemp=0xFFFF;
	unsigned char i;
	while(nbyte--)
	{
		itemp ^= *byte;
		byte++;
		for (i=0; i<8; i++)
    	{
			if (itemp & 0x1)
       	{
				itemp>>= 1;
				itemp ^= 0xA001;
			}
			else
      		{
				itemp>>= 1;         
			}
		}
	}
	return itemp;
}
char SendCommand1(char* pReceiveBuf,const char* lpszFormat,...)
{
	char* p = aTxBuff1;
	unsigned char err;
	va_list va;
	//OSMutexPend(MutexUart2,0,&err);
	if(err ==OS_NO_ERR)
	{
		va_start(va,lpszFormat);
		*p++ = '>'
		p +=vsprintf(p,lpszFormat,va);
		va_end(va);
		p += sprintf(p,"%04X\r\r\r",cal_crc((unsigned char *)aTxBuff1,p-aTxBuff1));
		UART2_SendStr(aTxBuff1,p-aTxBuff1);
		 err = wait_back(aTxBuff1[1]);
		 FRAME_RESET();
	}
	OSMutexPost(MutexUart2);
	return err;
}
//设置位置模式加减速和运行速度
char MotorSetPosAcc(unsigned short nAddr,unsigned short Acc,unsigned short Dec,unsigned short Run)
{
	return SendCommand1(NULL,"%02XA%04X%04X%04X",nAddr,Acc,Dec,Run);
}
//获取位置模式加减速和运行速度
char MotorGetPosAcc(unsigned short nAddr)
{
	return SendCommand1(NULL,"%02Xa");
}
//设置速度模式加减速和运行速度
char MotorSetSpeAcc(unsigned short nAddr,unsigned short Acc,unsigned short Dec,unsigned short Run)
{
	return SendCommand1(NULL,"%02XB%04X%04X%04X",nAddr,Acc,Dec,Run);
}
//获取速度模式加减速和运行速度
char MotorGetSpeAcc(unsigned short nAddr)
{
	return SendCommand1(NULL,"%02Xb");
}
//设置位置/速度/力矩/液位的低速，高速，空闲电流
char MotorSetCurrent(unsigned short nAddr,unsigned short LowI,unsigned short HighI,unsigned short HoldI)
{
	return SendCommand1(NULL,"%02XC%04X%04X%04X",nAddr,LowI,HighI,HoldI);
}
//读取电流
char MotorGetCurrent(unsigned short nAddr)
{
	return SendCommand1(NULL,"%02Xc",nAddr);
}
//设置回零电流和回零速度
char MotorSetZeroCurrentSpe(unsigned short nAddr,unsigned short ZeroI,unsigned short ZeroSpeed)
{
	return SendCommand1(NULL,"%02XD%04X%04X",nAddr,ZeroI,ZeroSpeed);
}
//读取回零电流和回零速度
char MotorGetZeroCurrentSpe(unsigned short nAddr)
{
	return SendCommand1(NULL,"%02Xd");
}
//设置Home模式Offset/评估距离的加减速度和运行速度
char MotorSetHomeAcc(unsigned short nAddr,unsigned short Acc,unsigned short Dec,unsigned short Run)
{
	return SendCommand1(NULL,"%02XE%04X%04X%04X",nAddr,Acc,Dec,Run);
}
//读取Home模式Offset/评估距离的加减速和运行速度
char MotorGetHomeAcc(unsigned short nAddr)
{
    return SendCommand1(NULL,"%02Xe");
}
//设置Home模式的低速、高速、空闲电流
char MotorSetHomeCurrent(unsigned short nAddr,unsigned short LowI,unsigned short HighI,unsigned short HoldI)
{
    return SendCommand1(NULL,"%02XR%04X%04X%04X",nAddr,LowI,HighI,HoldI);
}
//读取Home模式的低速、高速、空闲电流
char MotorGetHomeCurrent(unsigned short nAddr)
{
    return SendCommand1(NULL,"%02Xr%04X%04X%04X",nAddr,LowI,HighI,HoldI);
}
//设置Home offset评估距离 硬件零点
char MotorSetHomeOffset(unsigned short nAddr ,unsigned int HomeOffset,unsigned int AssDis,unsigned short HardZero)
{
    return SendCommand1(NULL,"%02XF%08X%08X%04X",nAddr,HomeOffset,AssDis,HardZero);
}
//读取Home offset 评估距离 硬件零点
char MotorGetHomeOffset(unsigned short nAddr)
{
    return SendCommand1(NULL,"%02Xf",nAddr);
}
//设置最大回原距离、液位探测最大距离、正限位坐标、负限位坐标、点击运行误差、速度比率
char MotorSetMaxDist(unsigned short nAddr,unsigned int MaxDist,unsigned int LiquidDist,unsigned int ForwardDist,unsigned int ReverseDist,unsigned short StepOffset，unsigned short SpeedRate)
{
    return SendCommand1(NULL,"%02XG%08X%08X%08X%08X%04X%04X",nAddr,MaxDist,LiquidDist,ForwardDist,ReverseDist,StepOffset，SpeedRate);
}
//读取最大回原距离，液位探测最大距离，正限位坐标，负限位坐标、点击运行误差、速度比率
char MotorGetMaxDist(unsigned short nAddr)
{
    return SendCommand1(NULL,"%02Xg",nAddr);
}
//设置参数、步距角、编码器精度、细分、每半圈步数
char MotorSetParam(unsigned short nAddr,unsigned short Param,unsigned short StepAngle,unsigned short EncoderAccuracy,unsigned short Subdivide,unsigned short StepHalfRound)
{
	return SendCommand1(NULL,"%02XH%04X%04X%04X%04X%04X",nAddr,Param,StepAngle,EncoderAccuracy,Subdivide,StepHalfRound);
}
//读取参数、步距角、编码器精度、细分、每半圈步数
char MotorGetParam(unsigned short nAddr)
{
	return SendCommand1(NULL,"%02Xh",nAddr);
}
//设置绝对位置/相对位置
char MotorSetAbsolutoPos(unsigned short nAddr,unsigned char Operate,unsigned short Pos)
{
	return SendCommand1(NULL,"%02XI%d%08X",nAddr,Operate,Pos);
}
//读取当前的绝对位置
char MotorGetAbsolutoPos(unsigned short nAddr)
{
	return SendCommand1(NULL,"%02Xi");
}
//配置管脚停止条件
char MotorSetStopPin(unsigned short nAddr,unsigned char Dir,unsigned char Pin,unsigned char Condition)
{
	return SendCommand1(NULL,"%02XI2%d%d%d",nAddr,Dir,Pin,Condition);
}
//点动速度运行/停止
char MotorSetRunStop(unsigned short nAddr,unsigned char Flag)
{
	return SendCommand1(NULL,"%02XJ%d",nAddr,Flag);
}
//读取速度模式状态
char MotorGetRunStopSta(unsigned short nAddr)
{
	return SendCommand1(NULL,"%02Xj");
}
//设置液位模式告诉空走距离+探液深度(速度？)
char MotorSetLiquidDist(unsigned short nAddr,unsigned short HighSpeedDist,unsigned short Speed)
{
	return SendCommand1(NULL,"%02XK0%08X%04")
}
//设置液位探测最大深度
char MotorSetLiquidMaxDist(unsigned short nAddr, short MaxDist)
{
	return SendCommand1(NULL,"%02XK%08X");
}
//读取液位模式运行状态
char MotorGetLiquidSta(unsigned short nAddr)
{
	return SendCommand1(NULL,"%02Xk");
}
//设置力矩模式下保护距离和速度。高速空走距离和力矩保护距离（转速）
char MotorSetMomentMode(unsigned short nAddr, long Moment,unsigned short Speed)
{
	return SendCommand1(NULL,%02XL0%08X%04X",nAddr,Moment,Speed);
}
//设置力矩模式高速空走坐标  到达该坐标后以力矩速度探测运行
char MotorSetMomentModeHighSpeed(unsigned short nAddr,long Dist)
{
	return SendCommand1(NULL,"%02XL1%08X",nAddr,Dist);
}
//读取力矩模式运行状态
char MotorGetMomentSta(unsigned short nAddr)
{
	return SendCommand1(NULL,"%02Xl",nAddr);
}
//电机复位
char MototReset(unsigned short nAddr,unsigned char Flag)
{
	return SendCommand1(NULL,"%02XM%d",nAddr,Flag);
}
//读取电机回零状态
char MotorGetResetSta(unsigned short nAddr)
{
	return SendCommand1(NULL,"%02Xm",nAddr);
}
//使能和失能电机
char MotorSetAble(unsigned short nAddr ,unsigned char Flag)
{
	return SendCommand1(NULL,"%02XN%1d");
}
//快速停止 （刹车）
char MotorStop(unsigned short nAddr)
{
	return SendCommand1(NULL,"%02XO",nAddr);
}
//读取上一次运行步数
char MotorGetlast(unsigned short nAddr)
{
	return SendCommand1(NULL,"%02Xo")
}
//电机参数保存
char MotorSaveParam(unsigned short nAddr)
{
	return SendCommand1(NULL,"%02XP",nAddr);
}
//读取位置模式的状态
char MotorGetPosSta(unsigned short nAddr)
{
	return SendCommand1(NULL,"%02Xp");
}
//设置Q程序
//char MotorQProgram(unsigned short nAddr,unsigned char SN,)

//q读取Q程序

//V设置延时时间
char MotorSetDelay(unsigned short nAddr,unsigned short Delay)
{
	return SendCommand1(NULL,"%02XV%04X",nAddr,Delay);
}
//v读取程序版本
char MotorGetversion(unsigned short nAddr)
{
	return SendCommand1(NULL,"%02Xv");
}
//S设置当前位置
char MotorSetPos(unsigned short nAddr,unsigned short Pos)
{
	return SendCommand1(NULL,"%02XS04X",nAddr,Pos);
}
//读取状态和报警
char MotorGetSta(unsigned short nAddr,unsigned char Sta)
{
	return SendCommand1(NULL,"%02Xs%1d",nAddr,Sta);
}
//T设置电机地址/波特率
char MotorSetAddr(unsigned short nAddr, unsigned short NewAddr)
{
    return SendCommand1(NULL,"%02XT0%02X",nAddr,Flag,NewAddr);
}
//T 设置波特率
char MotorSetBaud(unsigned short nAddr,unsigned short NewBaud)
{
    return SendCommand1(NULL,"%02T1%02X");
}
//t 读取地址,波特率
char MotorGetAddr(unsigned short nAddr,unsigned char Flag)
{
    return SendCommand1(NULL,"%02X%1d");
}
//W设置管脚功能
char MotorSetPin(unsigned short nAddr,unsigned short Pin,unsigned short Opr)
{
    return SendCommand1(NULL,"%02XW%02X%02X",nAddr,Pin,Opr);
}
//W设置管脚输出
char MotorSetPinOpr(unsigned short nAddr,unsigned short Pin,unsigned long PinOut)
{
    return SendCommand1(NULL,"%02XW%02X%08X",nAddr,Pin,PinOut);
}
//w获取管脚配置状态
char MotorGetPinSta(unsigned short nAddr)
{
    return SendCommand1(NULL,"%02Xw0");
}
//w获取管脚输入输出状态
char MotorGetPinOut(unsigned short nAddr)
{
    return SendCommand1(NULL,"%02Xw1",nAddr);
}
char MotorSetAllParam(unsigned short nAddr,unsigned char* param)
{
    return SendCommand1(NULL,"%02XU%148X",nAddr,param);
}
//u读取所有参数
char MotorGetAllParam(unsigned short nAddr)
{
    return SendCommand1(NULL,"%02Xu");
}
char MotorReset(unsigned short nAddr)
{
	return SendCommand1()
}







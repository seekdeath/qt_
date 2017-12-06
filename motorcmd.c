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
char MotorReset(unsigned short nAddr)
{
	return SendCommand1()
}







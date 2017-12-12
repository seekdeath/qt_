#include "motorcmd.h"
#include "includes.h"

#ifndef 	NULL
#define		NULL	(void*)0
char aRxBuff1[];
char aTxBuff1[];
unsigned char NRxBuff1;
unsigned char NTxBuff1;
unsigned char StaBao1;




//多项式8005
static unsigned short crc_table1[]={
		0x0000, 0xC0C1, 0xC181, 0x0140, 0xC301, 0x03C0, 0x0280, 0xC241,
        0xC601, 0x06C0, 0x0780, 0xC741, 0x0500, 0xC5C1, 0xC481, 0x0440,
        0xCC01, 0x0CC0, 0x0D80, 0xCD41, 0x0F00, 0xCFC1, 0xCE81, 0x0E40,
        0x0A00, 0xCAC1, 0xCB81, 0x0B40, 0xC901, 0x09C0, 0x0880, 0xC841,
        0xD801, 0x18C0, 0x1980, 0xD941, 0x1B00, 0xDBC1, 0xDA81, 0x1A40,
        0x1E00, 0xDEC1, 0xDF81, 0x1F40, 0xDD01, 0x1DC0, 0x1C80, 0xDC41,
        0x1400, 0xD4C1, 0xD581, 0x1540, 0xD701, 0x17C0, 0x1680, 0xD641,
        0xD201, 0x12C0, 0x1380, 0xD341, 0x1100, 0xD1C1, 0xD081, 0x1040,
        0xF001, 0x30C0, 0x3180, 0xF141, 0x3300, 0xF3C1, 0xF281, 0x3240,
        0x3600, 0xF6C1, 0xF781, 0x3740, 0xF501, 0x35C0, 0x3480, 0xF441,
        0x3C00, 0xFCC1, 0xFD81, 0x3D40, 0xFF01, 0x3FC0, 0x3E80, 0xFE41,
        0xFA01, 0x3AC0, 0x3B80, 0xFB41, 0x3900, 0xF9C1, 0xF881, 0x3840,
        0x2800, 0xE8C1, 0xE981, 0x2940, 0xEB01, 0x2BC0, 0x2A80, 0xEA41,
        0xEE01, 0x2EC0, 0x2F80, 0xEF41, 0x2D00, 0xEDC1, 0xEC81, 0x2C40,
        0xE401, 0x24C0, 0x2580, 0xE541, 0x2700, 0xE7C1, 0xE681, 0x2640,
        0x2200, 0xE2C1, 0xE381, 0x2340, 0xE101, 0x21C0, 0x2080, 0xE041,
        0xA001, 0x60C0, 0x6180, 0xA141, 0x6300, 0xA3C1, 0xA281, 0x6240,
        0x6600, 0xA6C1, 0xA781, 0x6740, 0xA501, 0x65C0, 0x6480, 0xA441,
        0x6C00, 0xACC1, 0xAD81, 0x6D40, 0xAF01, 0x6FC0, 0x6E80, 0xAE41,
        0xAA01, 0x6AC0, 0x6B80, 0xAB41, 0x6900, 0xA9C1, 0xA881, 0x6840,
        0x7800, 0xB8C1, 0xB981, 0x7940, 0xBB01, 0x7BC0, 0x7A80, 0xBA41,
        0xBE01, 0x7EC0, 0x7F80, 0xBF41, 0x7D00, 0xBDC1, 0xBC81, 0x7C40,
        0xB401, 0x74C0, 0x7580, 0xB541, 0x7700, 0xB7C1, 0xB681, 0x7640,
        0x7200, 0xB2C1, 0xB381, 0x7340, 0xB101, 0x71C0, 0x7080, 0xB041,
        0x5000, 0x90C1, 0x9181, 0x5140, 0x9301, 0x53C0, 0x5280, 0x9241,
        0x9601, 0x56C0, 0x5780, 0x9741, 0x5500, 0x95C1, 0x9481, 0x5440,
        0x9C01, 0x5CC0, 0x5D80, 0x9D41, 0x5F00, 0x9FC1, 0x9E81, 0x5E40,
        0x5A00, 0x9AC1, 0x9B81, 0x5B40, 0x9901, 0x59C0, 0x5880, 0x9841,
        0x8801, 0x48C0, 0x4980, 0x8941, 0x4B00, 0x8BC1, 0x8A81, 0x4A40,
        0x4E00, 0x8EC1, 0x8F81, 0x4F40, 0x8D01, 0x4DC0, 0x4C80, 0x8C41,
        0x4400, 0x84C1, 0x8581, 0x4540, 0x8701, 0x47C0, 0x4680, 0x8641,
        0x8201, 0x42C0, 0x4380, 0x8341, 0x4100, 0x81C1, 0x8081, 0x4040
};
//多项式8005查表
unsigned short GetRevCrc_16(unsigned char * pData,  unsigned char nLength)
{
  unsigned short cRc_16 = 0xFFFF;
  unsigned char temp;

  while(nLength-- > 0)
  {
    temp = cRc_16 & 0xFF;
    cRc_16 = (cRc_16 >> 8) ^ crc_table1[(temp ^ *pData++) ];
  }

  return cRc_16;
}
//校验多项式8005的计算
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
//指令发送函数
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
		p += sprintf(p,"%04X\r\r\r",GetRevCrc_16((unsigned char *)aTxBuff1,p-aTxBuff1));
		UART2_SendStr(aTxBuff1,p-aTxBuff1);
		 err = wait_back(aTxBuff1[1]);
		 FRAME_RESET();
	}
	OSMutexPost(MutexUart2);
	return err;
}
char IsFrame1Ok(void)
{
    return StBao1;
}
/**
等待下位机回复.
@retval 接收到的数据帧长度. 0: 失败.
*/
char wait_back(char nAddr)
{
	INT8U err=0;
	// 等待接收帧
	while (!IsFrame1Ok())
        {
            OSTimeDly(5);
            err=err+1;
            if (err==20)break;
        }
	if (err <20)
	{
		//校验
		if (NRxBuff1 < 8 ||	// 帧最小长度
			aRxBuff1[1] != nAddr ||
			PackWord(FRAME_CRC1) != cal_crc((INT8U*)aRxBuff1, NRxBuff1-5))
		{
//			FRAME_RESET1();
			return 0;
		}
		return NRxBuff1;
	}
	return 0;
}
//重置数据帧
void ResetFrame1(void)
{
        //int i;
        StBao1=0;
	NRxBuff1=0;
}
//****************************************************************************
//接收数据包处理，向缓冲区中写入接收到的数据
//****************************************************************************
void ReceiverData1(unsigned char sq0)
{
	if (FRAME_OK1())	// 上一次接收的包还没处理完, 拒绝接收
		return;

	if (sq0 == '>')
		NRxBuff1 = 0;
        
	aRxBuff1[NRxBuff1++] = sq0;				// 保存数据
	if((NRxBuff1==1)&&(sq0!='>'))			// 包头错误
		NRxBuff1 = 0;
	else if(NRxBuff1==FRAME_SIZE)
		NRxBuff1 = 0;
	else if ((sq0=='\r'))				// 如果检测到包尾则处理
	{
                StBao1=1;
	}
}
//A设置位置模式加减速和运行速度
char MotorSetPosAcc(unsigned short nAddr,unsigned short Acc,unsigned short Dec,unsigned short Run)
{
	return SendCommand1(NULL,"%02XA%04X%04X%04X",nAddr,Acc,Dec,Run);
}
//a获取位置模式加减速和运行速度
char MotorGetPosAcc(unsigned short nAddr)
{
	return SendCommand1(NULL,"%02Xa",nAddr);
}
//B设置速度模式加减速和运行速度
char MotorSetSpeAcc(unsigned short nAddr,unsigned short Acc,unsigned short Dec,unsigned short Run)
{
	return SendCommand1(NULL,"%02XB%04X%04X%04X",nAddr,Acc,Dec,Run);
}
//b获取速度模式加减速和运行速度
char MotorGetSpeAcc(unsigned short nAddr)
{
	return SendCommand1(NULL,"%02Xb",nAddr);
}
//C设置位置/速度/力矩/液位的低速，高速，空闲电流
char MotorSetCurrent(unsigned short nAddr,unsigned short LowI,unsigned short HighI,unsigned short HoldI)
{
	return SendCommand1(NULL,"%02XC%04X%04X%04X",nAddr,LowI,HighI,HoldI);
}
//c读取电流
char MotorGetCurrent(unsigned short nAddr)
{
	return SendCommand1(NULL,"%02Xc",nAddr);
}
//D设置回零电流和回零速度
char MotorSetZeroCurrentSpe(unsigned short nAddr,unsigned short ZeroI,unsigned short ZeroSpeed)
{
	return SendCommand1(NULL,"%02XD%04X%04X",nAddr,ZeroI,ZeroSpeed);
}
//d读取回零电流和回零速度
char MotorGetZeroCurrentSpe(unsigned short nAddr)
{
	return SendCommand1(NULL,"%02Xd",nAddr);
}
//E设置Home模式Offset/评估距离的加减速度和运行速度
char MotorSetHomeAcc(unsigned short nAddr,unsigned short Acc,unsigned short Dec,unsigned short Run)
{
	return SendCommand1(NULL,"%02XE%04X%04X%04X",nAddr,Acc,Dec,Run);
}
//e读取Home模式Offset/评估距离的加减速和运行速度
char MotorGetHomeAcc(unsigned short nAddr)
{
    return SendCommand1(NULL,"%02Xe",nAddr);
}
//R设置Home模式的低速、高速、空闲电流
char MotorSetHomeCurrent(unsigned short nAddr,unsigned short LowI,unsigned short HighI,unsigned short HoldI)
{
    return SendCommand1(NULL,"%02XR%04X%04X%04X",nAddr,LowI,HighI,HoldI);
}
//r读取Home模式的低速、高速、空闲电流
char MotorGetHomeCurrent(unsigned short nAddr)
{
    return SendCommand1(NULL,"%02Xr%04X%04X%04X",nAddr,LowI,HighI,HoldI);
}
//F设置Home offset评估距离 硬件零点
char MotorSetHomeOffset(unsigned short nAddr ,longHomeOffset,long AssDis,unsigned short HardZero)
{
    return SendCommand1(NULL,"%02XF%08X%08X%04X",nAddr,HomeOffset,AssDis,HardZero);
}
//f读取Home offset 评估距离 硬件零点
char MotorGetHomeOffset(unsigned short nAddr)
{
    return SendCommand1(NULL,"%02Xf",nAddr);
}
//G设置最大回原距离、液位探测最大距离、正限位坐标、负限位坐标、电机运行误差、速度比率
char MotorSetMaxDist(unsigned short nAddr,long MaxDist,long LiquidDist,long ForwardDist,long ReverseDist,unsigned short StepOffset，unsigned short SpeedRate)
{
    return SendCommand1(NULL,"%02XG%08X%08X%08X%08X%04X%04X",nAddr,MaxDist,LiquidDist,ForwardDist,ReverseDist,StepOffset，SpeedRate);
}
//g读取最大回原距离，液位探测最大距离，正限位坐标，负限位坐标、点击运行误差、速度比率
char MotorGetMaxDist(unsigned short nAddr)
{
    return SendCommand1(NULL,"%02Xg",nAddr);
}
//H设置参数、步距角、编码器精度、细分、每半圈步数
char MotorSetParam(unsigned short nAddr,unsigned short Param,unsigned short StepAngle,unsigned short EncoderAccuracy,unsigned short Subdivide,unsigned short StepHalfRound)
{
	return SendCommand1(NULL,"%02XH%04X%04X%04X%04X%04X",nAddr,Param,StepAngle,EncoderAccuracy,Subdivide,StepHalfRound);
}
//h读取参数、步距角、编码器精度、细分、每半圈步数
char MotorGetParam(unsigned short nAddr)
{
	return SendCommand1(NULL,"%02Xh",nAddr);
}
//I设置绝对位置/相对位置
char MotorSetAbsolutoPos(unsigned short nAddr,unsigned char Operate,long Pos)
{
	return SendCommand1(NULL,"%02XI%d%08X",nAddr,Operate,Pos);
}
//i读取当前的绝对位置
char MotorGetAbsolutoPos(unsigned short nAddr)
{
	return SendCommand1(NULL,"%02Xi",nAddr);
}
//I配置管脚停止条件
char MotorSetStopPin(unsigned short nAddr,unsigned char Dir,unsigned char Pin,unsigned char Condition)
{
	return SendCommand1(NULL,"%02XI2%d%d%d",nAddr,Dir,Pin,Condition);
}
//J点动速度运行/停止
char MotorSetRunStop(unsigned short nAddr,unsigned char Flag)
{
	return SendCommand1(NULL,"%02XJ%d",nAddr,Flag);
}
//j读取速度模式状态
char MotorGetRunStopSta(unsigned short nAddr)
{
	return SendCommand1(NULL,"%02Xj",nAddr);
}
//K设置液位模式告诉空走距离+探液深度(速度？)
char MotorSetLiquidDist(unsigned short nAddr,long HighSpeedDist,unsigned short Speed)
{
	return SendCommand1(NULL,"%02XK0%08X%04")
}
//K设置液位探测最大深度
char MotorSetLiquidMaxDist(unsigned short nAddr, long MaxDist)
{
	return SendCommand1(NULL,"%02XK%08X",nAddr,MaxDist);
}
//k读取液位模式运行状态
char MotorGetLiquidSta(unsigned short nAddr)
{
	return SendCommand1(NULL,"%02Xk",nAddr);
}
//L设置力矩模式下保护距离和速度。高速空走距离和力矩保护距离（转速）
char MotorSetMomentMode(unsigned short nAddr, long Moment,unsigned short Speed)
{
	return SendCommand1(NULL,%02XL0%08X%04X",nAddr,Moment,Speed);
}
//L设置力矩模式高速空走坐标  到达该坐标后以力矩速度探测运行
char MotorSetMomentModeHighSpeed(unsigned short nAddr,long Dist)
{
	return SendCommand1(NULL,"%02XL1%08X",nAddr,Dist);
}
//l读取力矩模式运行状态
char MotorGetMomentSta(unsigned short nAddr)
{
	return SendCommand1(NULL,"%02Xl",nAddr);
}
//M电机复位
char MototReset(unsigned short nAddr,unsigned char Flag)
{
	return SendCommand1(NULL,"%02XM%d",nAddr,Flag);
}
//m读取电机回零状态
char MotorGetResetSta(unsigned short nAddr)
{
	return SendCommand1(NULL,"%02Xm",nAddr);
}
//N使能和失能电机
char MotorSetAble(unsigned short nAddr ,unsigned char Flag)
{
	return SendCommand1(NULL,"%02XN%1d",nAddr,Flag);
}
//O快速停止 （刹车）
char MotorStop(unsigned short nAddr)
{
	return SendCommand1(NULL,"%02XO",nAddr);
}
//o读取上一次运行步数
char MotorGetlast(unsigned short nAddr)
{
	return SendCommand1(NULL,"%02Xo",nAddr)
}
//P电机参数保存
char MotorSaveParam(unsigned short nAddr)
{
	return SendCommand1(NULL,"%02XP",nAddr);
}
//p读取位置模式的状态
char MotorGetPosSta(unsigned short nAddr)
{
	return SendCommand1(NULL,"%02Xp",nAddr);
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
	return SendCommand1(NULL,"%02Xv",nAddr);
}
//S设置当前位置
char MotorSetPos(unsigned short nAddr,unsigned short Pos)
{
	return SendCommand1(NULL,"%02XS04X",nAddr,Pos);
}
//s读取状态和报警
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
    return SendCommand1(NULL,"%02T1%02X",nAddr,NewBaud);
}
//t 读取地址,波特率
char MotorGetAddr(unsigned short nAddr,unsigned char Flag)
{
    return SendCommand1(NULL,"%02X%1d",nAddr,Flag);
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
    return SendCommand1(NULL,"%02Xw0",nAddr);
}
//w获取管脚输入输出状态
char MotorGetPinOut(unsigned short nAddr)
{
    return SendCommand1(NULL,"%02Xw1",nAddr);
}
//设置所有参数
char MotorSetAllParam(unsigned short nAddr,unsigned char* param)
{
    return SendCommand1(NULL,"%02XU%148X",nAddr,param);
}
//u读取所有参数
char MotorGetAllParam(unsigned short nAddr)
{
    return SendCommand1(NULL,"%02Xu",nAddr);
}












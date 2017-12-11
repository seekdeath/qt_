#define 	FRAME_SIZE 		128
extern char aRxBuff1[];
extern char aTxBuff1[];
extern unsigned char NRxBuff1;
extern unsigned char NTxBuff1;
extern unsigned char StaBao1;
#define 	FRAME_CRC1				&(aRxBuff1)[NRxBuff1-5])	
#define 	FRAME_END1(buf,len)		(buf)[(len)-5] =  '\0'
#define 	FRAME_DATA1				(&aRxBuff1[4])
#define 	FRAME_DATA_LEN1			(NRxBuff1-4)
#define		FRAME_CMD1				((aRxBuff1)[3])
#define 	FRAME_RESET()			ResetFrame1()
#define		FRAME_OK1()				IsFrame1OK()

#define 	WAIT_BACK_TIMEOUTS		Ms2Tick(100)
#define 	TRY(expression)			{unsigned char __i;for(__i = 0; __i<10; __i++){if((expression)!=0)break;}}
unsigned short cal_crc(unsigned char *byte,unsigned char nbyte);
char SendCommand1(char* pReceiveBuf,const char* lpszFormat,...);
//A设置位置模式加减速和运行速度
char MotorSetPosAcc(unsigned short nAddr,unsigned short Acc,unsigned short Dec,unsigned short Run);
//a获取位置模式加减速和运行速度
char MotorGetPosAcc(unsigned short nAddr);
//B设置速度模式加减速和运行速度
char MotorSetSpeAcc(unsigned short nAddr,unsigned short Acc,unsigned short Dec,unsigned short Run);
//b获取速度模式加减速和运行速度
char MotorGetSpeAcc(unsigned short nAddr);
//C设置位置/速度/力矩/液位的低速，高速，空闲电流
char MotorSetCurrent(unsigned short nAddr,unsigned short LowI,unsigned short HighI,unsigned short HoldI);
//c读取电流
char MotorGetCurrent(unsigned short nAddr);
//D设置回零电流和回零速度
char MotorSetZeroCurrentSpe(unsigned short nAddr,unsigned short ZeroI,unsigned short ZeroSpeed);
//d读取回零电流和回零速度
char MotorGetZeroCurrentSpe(unsigned short nAddr);
//E设置Home模式Offset/评估距离的加减速度和运行速度
char MotorSetHomeAcc(unsigned short nAddr,unsigned short Acc,unsigned short Dec,unsigned short Run);
//e读取Home模式Offset/评估距离的加减速和运行速度
char MotorGetHomeAcc(unsigned short nAddr);
//R设置Home模式的低速、高速、空闲电流
char MotorSetHomeCurrent(unsigned short nAddr,unsigned short LowI,unsigned short HighI,unsigned short HoldI);
//r读取Home模式的低速、高速、空闲电流
char MotorGetHomeCurrent(unsigned short nAddr);
//F设置Home offset评估距离 硬件零点
char MotorSetHomeOffset(unsigned short nAddr ,longHomeOffset,long AssDis,unsigned short HardZero);
//f读取Home offset 评估距离 硬件零点
char MotorGetHomeOffset(unsigned short nAddr);
//G设置最大回原距离、液位探测最大距离、正限位坐标、负限位坐标、电机运行误差、速度比率
char MotorSetMaxDist(unsigned short nAddr,long MaxDist,long LiquidDist,long ForwardDist,long ReverseDist,unsigned short StepOffset，unsigned short SpeedRate);
//g读取最大回原距离，液位探测最大距离，正限位坐标，负限位坐标、点击运行误差、速度比率
char MotorGetMaxDist(unsigned short nAddr);
//H设置参数、步距角、编码器精度、细分、每半圈步数
char MotorSetParam(unsigned short nAddr,unsigned short Param,unsigned short StepAngle,unsigned short EncoderAccuracy,unsigned short Subdivide,unsigned short StepHalfRound);
//h读取参数、步距角、编码器精度、细分、每半圈步数
char MotorGetParam(unsigned short nAddr);
//I设置绝对位置/相对位置
char MotorSetAbsolutoPos(unsigned short nAddr,unsigned char Operate,long Pos);
//i读取当前的绝对位置
char MotorGetAbsolutoPos(unsigned short nAddr);
//I配置管脚停止条件
char MotorSetStopPin(unsigned short nAddr,unsigned char Dir,unsigned char Pin,unsigned char Condition);
//J点动速度运行/停止
char MotorSetRunStop(unsigned short nAddr,unsigned char Flag);
//j读取速度模式状态
char MotorGetRunStopSta(unsigned short nAddr);
//K设置液位模式告诉空走距离+探液深度(速度？)
char MotorSetLiquidDist(unsigned short nAddr,long HighSpeedDist,unsigned short Speed);
//K设置液位探测最大深度
char MotorSetLiquidMaxDist(unsigned short nAddr, long MaxDist);
//k读取液位模式运行状态
char MotorGetLiquidSta(unsigned short nAddr);
//L设置力矩模式下保护距离和速度。高速空走距离和力矩保护距离（转速）
char MotorSetMomentMode(unsigned short nAddr, long Moment,unsigned short Speed);
//L设置力矩模式高速空走坐标  到达该坐标后以力矩速度探测运行
char MotorSetMomentModeHighSpeed(unsigned short nAddr,long Dist);
//l读取力矩模式运行状态
char MotorGetMomentSta(unsigned short nAddr);
//M电机复位
char MototReset(unsigned short nAddr,unsigned char Flag);
//m读取电机回零状态
char MotorGetResetSta(unsigned short nAddr);
//N使能和失能电机
char MotorSetAble(unsigned short nAddr ,unsigned char Flag);
//O快速停止 （刹车）
char MotorStop(unsigned short nAddr);
//o读取上一次运行步数
char MotorGetlast(unsigned short nAddr);
//P电机参数保存
char MotorSaveParam(unsigned short nAddr);
//p读取位置模式的状态
char MotorGetPosSta(unsigned short nAddr);
//设置Q程序
//char MotorQProgram(unsigned short nAddr,unsigned char SN,)

//q读取Q程序

//V设置延时时间
char MotorSetDelay(unsigned short nAddr,unsigned short Delay);
//v读取程序版本
char MotorGetversion(unsigned short nAddr);
//S设置当前位置
char MotorSetPos(unsigned short nAddr,unsigned short Pos);
//s读取状态和报警
char MotorGetSta(unsigned short nAddr,unsigned char Sta);
//T设置电机地址/波特率
char MotorSetAddr(unsigned short nAddr, unsigned short NewAddr);
//T 设置波特率
char MotorSetBaud(unsigned short nAddr,unsigned short NewBaud);
//t 读取地址,波特率
char MotorGetAddr(unsigned short nAddr,unsigned char Flag);
//W设置管脚功能
char MotorSetPin(unsigned short nAddr,unsigned short Pin,unsigned short Opr);
//W设置管脚输出
char MotorSetPinOpr(unsigned short nAddr,unsigned short Pin,unsigned long PinOut);
//w获取管脚配置状态
char MotorGetPinSta(unsigned short nAddr);
//w获取管脚输入输出状态
char MotorGetPinOut(unsigned short nAddr);
//设置所有参数
char MotorSetAllParam(unsigned short nAddr,unsigned char* param);
//u读取所有参数
char MotorGetAllParam(unsigned short nAddr);



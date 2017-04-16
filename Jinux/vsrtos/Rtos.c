/*
*********************************************************************************************************
*                                                WenOS
*                                          The Real-Time Kernel
*
description:后	一共有4个线程，主线程TaskStart初始化消息队列，开启定时器，Tast1只是简单的运行
				Task2给Task3发消息，收到回执继续发，从A发到Z，task3则收取消息并回执

author：		JunGeGe
*********************************************************************************************************
*/

#include "includes.h"
#include <windows.h>

#define OS_TICKS_PER_SEC 		10
#define RTOS_NUMBER_OF_TASK 	2
#define Rtos_EMPTY_TASK   		RTOS_NUMBER_OF_TASK

/* task queue definition */
#define Rtos_BACK_QUEUE    0
#define Rtos_FIRST_QUEUE   1
#define Rtos_SECOND_QUEUE  2

void CALLBACK OSTickISR(unsigned int a,unsigned int b,unsigned long c,unsigned long d,unsigned long e);

void StartOS (ubyte Mode);
void Rtos_EndLessLoop(void);


//extern TASK(DISP_Task_ts);
extern TASK(KEY_Task_ts);

//任务列表 
typedef void Rtos_Task_t (void);
Rtos_Task_t *const Rtos_TasksAddressTable[RTOS_NUMBER_OF_TASK] =
{
//	&DISP_Task_ts,
	&KEY_Task_ts,
};

//任务优先级表
const ubyte Rtos_QueueNumberTable[RTOS_NUMBER_OF_TASK] =
{
	Rtos_BACK_QUEUE,
	Rtos_BACK_QUEUE,
};


//BACK优先级先入先出队列参数
//#ifdef Rtos_BACK_QUEUE_USED
#define Rtos_DIM_BUFFER_BACK 8	
static ubyte Rtos_BackQueueBuffer[Rtos_DIM_BUFFER_BACK];
static ubyte Rtos_BackQueuePointerIn;
static ubyte Rtos_BackQueuePointerOut;
//#endif



//任务定时器
static ubyte Rtos_TaskPeriod[RTOS_NUMBER_OF_TASK];
static ubyte Rtos_TaskPeriodCounter[RTOS_NUMBER_OF_TASK];

u32 Rtos_Timer ;


void StartOS (ubyte Mode)//启动前，系统硬件，系统参数初始化
{
	
	//initgraph(640, 480);	// 这里和 TC 略有区别
	//Mode = Mode;
	//timeSetEvent(1000/OS_TICKS_PER_SEC, 0, OSTickISR, 0, TIME_PERIODIC);	//开启一个100ms定时器
	
	Rtos_Timer = 1;
	Rtos_TaskPeriodCounter[0] =1;
	Rtos_TaskPeriod[0] = 1;// 1000ms
	Rtos_TaskPeriodCounter[1] =1;
	Rtos_TaskPeriod[1] = 1;	// 500ms

	Rtos_BackQueuePointerIn = 0;
	Rtos_BackQueuePointerOut = 0;

	//outtextxy(200,0,"This is a RtOS On Windows\0");
}


int main(int argc, char **argv)
{
	//GetAsyncKeyState(int   vKey); 
	StartOS (0);
	Rtos_EndLessLoop();
	return 1;
}


void Rtos_EndLessLoop(void)//无限循环
{
	ubyte TaskId = 0;
	while(1)
	{
		if (Rtos_BackQueuePointerIn != Rtos_BackQueuePointerOut)//有新的任务就绪
    	{
    		Rtos_BackQueuePointerOut++;
			if (Rtos_BackQueuePointerOut == Rtos_DIM_BUFFER_BACK)
      		{
        		Rtos_BackQueuePointerOut = 0;
      		}
			TaskId = Rtos_BackQueueBuffer[Rtos_BackQueuePointerOut];//取出新任务
			if (TaskId != Rtos_EMPTY_TASK)
			{
				(*(Rtos_TasksAddressTable[TaskId]))();//执行任务
	
			}
		}
	}
}




void CALLBACK OSTickISR(unsigned int a,unsigned int b,unsigned long c,unsigned long d,unsigned long e)//定时器中断
{
	ubyte TaskId;

	Rtos_Timer ++;
	for (TaskId = 0; TaskId <= RTOS_NUMBER_OF_TASK-1 ; TaskId++)
    {
    	if (Rtos_TaskPeriodCounter[TaskId] != 0)
      	{
        	Rtos_TaskPeriodCounter[TaskId]--;
        	if (Rtos_TaskPeriodCounter[TaskId] == 0)
        	{
		  		if (Rtos_QueueNumberTable[TaskId] == Rtos_BACK_QUEUE)
		  		{
		  			Rtos_BackQueuePointerIn++;//就绪任务先入先出
		  			if (Rtos_BackQueuePointerIn == Rtos_DIM_BUFFER_BACK)
            		{
              			Rtos_BackQueuePointerIn = 0;
            		}
					if (Rtos_BackQueuePointerIn == Rtos_BackQueuePointerOut)//任务溢出,任务队列尾部追上了头部
            		{
                		/* Back queue full */
                		//RTOS_DisableAllInterrupts();
                		//SYST_Reset();
						//outtextxy(0,100,"Sys_Err Back queue full\n");
                		//printf("Sys_Err Back queue full\n");
						//while(1);
            		}
		  			Rtos_BackQueueBuffer[Rtos_BackQueuePointerIn] = TaskId;//就绪任务输入队列
		  		}
		  		Rtos_TaskPeriodCounter[TaskId] = Rtos_TaskPeriod[TaskId];//任务定时计数器重赋值
        	}
      	}
    }
}


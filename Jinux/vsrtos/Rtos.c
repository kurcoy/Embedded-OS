/*
*********************************************************************************************************
*                                                WenOS
*                                          The Real-Time Kernel
*
description:��	һ����4���̣߳����߳�TaskStart��ʼ����Ϣ���У�������ʱ����Tast1ֻ�Ǽ򵥵�����
				Task2��Task3����Ϣ���յ���ִ����������A����Z��task3����ȡ��Ϣ����ִ

author��		JunGeGe
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

//�����б� 
typedef void Rtos_Task_t (void);
Rtos_Task_t *const Rtos_TasksAddressTable[RTOS_NUMBER_OF_TASK] =
{
//	&DISP_Task_ts,
	&KEY_Task_ts,
};

//�������ȼ���
const ubyte Rtos_QueueNumberTable[RTOS_NUMBER_OF_TASK] =
{
	Rtos_BACK_QUEUE,
	Rtos_BACK_QUEUE,
};


//BACK���ȼ������ȳ����в���
//#ifdef Rtos_BACK_QUEUE_USED
#define Rtos_DIM_BUFFER_BACK 8	
static ubyte Rtos_BackQueueBuffer[Rtos_DIM_BUFFER_BACK];
static ubyte Rtos_BackQueuePointerIn;
static ubyte Rtos_BackQueuePointerOut;
//#endif



//����ʱ��
static ubyte Rtos_TaskPeriod[RTOS_NUMBER_OF_TASK];
static ubyte Rtos_TaskPeriodCounter[RTOS_NUMBER_OF_TASK];

u32 Rtos_Timer ;


void StartOS (ubyte Mode)//����ǰ��ϵͳӲ����ϵͳ������ʼ��
{
	
	//initgraph(640, 480);	// ����� TC ��������
	//Mode = Mode;
	//timeSetEvent(1000/OS_TICKS_PER_SEC, 0, OSTickISR, 0, TIME_PERIODIC);	//����һ��100ms��ʱ��
	
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


void Rtos_EndLessLoop(void)//����ѭ��
{
	ubyte TaskId = 0;
	while(1)
	{
		if (Rtos_BackQueuePointerIn != Rtos_BackQueuePointerOut)//���µ��������
    	{
    		Rtos_BackQueuePointerOut++;
			if (Rtos_BackQueuePointerOut == Rtos_DIM_BUFFER_BACK)
      		{
        		Rtos_BackQueuePointerOut = 0;
      		}
			TaskId = Rtos_BackQueueBuffer[Rtos_BackQueuePointerOut];//ȡ��������
			if (TaskId != Rtos_EMPTY_TASK)
			{
				(*(Rtos_TasksAddressTable[TaskId]))();//ִ������
	
			}
		}
	}
}




void CALLBACK OSTickISR(unsigned int a,unsigned int b,unsigned long c,unsigned long d,unsigned long e)//��ʱ���ж�
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
		  			Rtos_BackQueuePointerIn++;//�������������ȳ�
		  			if (Rtos_BackQueuePointerIn == Rtos_DIM_BUFFER_BACK)
            		{
              			Rtos_BackQueuePointerIn = 0;
            		}
					if (Rtos_BackQueuePointerIn == Rtos_BackQueuePointerOut)//�������,�������β��׷����ͷ��
            		{
                		/* Back queue full */
                		//RTOS_DisableAllInterrupts();
                		//SYST_Reset();
						//outtextxy(0,100,"Sys_Err Back queue full\n");
                		//printf("Sys_Err Back queue full\n");
						//while(1);
            		}
		  			Rtos_BackQueueBuffer[Rtos_BackQueuePointerIn] = TaskId;//���������������
		  		}
		  		Rtos_TaskPeriodCounter[TaskId] = Rtos_TaskPeriod[TaskId];//����ʱ�������ظ�ֵ
        	}
      	}
    }
}


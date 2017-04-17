/**
 ******************************************************************************
 * @file       _win_os.c
 * @version    V1.1.4
 * @brief      API C source file of _win_os.c
 *             Created on: 2016-9-26
 *             Author: wenrenjinjun
 * @details    This file including all API functions's implement of dps.
 * @copy       Copyrigth(C), 2008-2012,Sanxing Electric Co.,Ltd.
 *
 ******************************************************************************
 */
#include "_win_os.h"
#include <stdio.h>

CRITICAL_SECTION    cs;
BOOLEAN             OSRunning;
INT8U               OSIntNesting;
INT32U              OSTime;


extern void
winos_task_init(void);


/**
 ******************************************************************************
 * @brief
 * @param[in]
 * @retval
 ******************************************************************************
 */
void
win_OSInit(void)
{
    InitializeCriticalSection(&cs);
    printf("OSInit\n");

    OSRunning = 0;
    OSIntNesting = 0;
    OSTime = 0;
    winos_task_init();
}

/**
 ******************************************************************************
 * @brief
 * @param[in]
 * @retval
 ******************************************************************************
 */
void
OS_CPU_SysTickHandler(void)
{
    EnterCriticalSection(&cs);
    OSTime ++;
    LeaveCriticalSection(&cs);
}

/**
 ******************************************************************************
 * @brief
 * @param[in]
 * @retval
 ******************************************************************************
 */
void
win_OSStart(void)
{
    printf("os_start\n");
    OSRunning = 1;

    while(1)
    {
        OS_CPU_SysTickHandler();

        Sleep(1000/OS_TICKS_PER_SEC);
    }
    printf("os_end\n");
}

/**
 ******************************************************************************
 * @brief
 * @param[in]
 * @retval
 ******************************************************************************
 */
INT32U  OSTimeGet (void)
{
    INT32U     ticks;

    EnterCriticalSection(&cs);
    ticks = OSTime;
    LeaveCriticalSection(&cs);
    return (ticks);
}



/**
 ******************************************************************************
 * @brief
 * @param[in]
 * @retval
 ******************************************************************************
 */
void
win_OSStatInit (void)
{
}

/**
 ******************************************************************************
 * @brief
 * @param[in]
 * @retval
 ******************************************************************************
 */
void
win_OSSysTickInit (
        INT32U  cnts)
{
}

/**
 ******************************************************************************
 * @brief
 * @param[in]
 * @retval
 ******************************************************************************
 */
void
wOSTimeDly (INT32U ticks)
{
    Sleep((1000 / OS_TICKS_PER_SEC));

#if 0
    INT8U      y;
#if OS_CRITICAL_METHOD == 3u                     /* Allocate storage for CPU status register           */
    OS_CPU_SR  cpu_sr = 0u;
#endif
    if (OSIntNesting > 0u) {                     /* See if trying to call from an ISR                  */
        return;
    }
    if (OSLockNesting > 0u) {                    /* See if called with scheduler locked                */
        return;
    }
    if (ticks > 0u) {                            /* 0 means no delay!                                  */
        OS_ENTER_CRITICAL();
        y            =  OSTCBCur->OSTCBY;        /* Delay current task                                 */
        OSRdyTbl[y] &= (OS_PRIO)~OSTCBCur->OSTCBBitX;
        if (OSRdyTbl[y] == 0u) {
            OSRdyGrp &= (OS_PRIO)~OSTCBCur->OSTCBBitY;
        }
        OSTCBCur->OSTCBDly = ticks;              /* Load ticks in TCB                                  */
        OS_EXIT_CRITICAL();
        OS_Sched();                              /* Find next task to run!                             */
    }
#endif
}

/**
 ******************************************************************************
 * @brief
 * @param[in]
 * @retval
 ******************************************************************************
 */
#undef FALSE
#undef TRUE

#include <shell.h>
static uint32_t
do_taskInfo(const cmd_tbl_t * cmdtp,
        uint32_t argc,
        const char *argv[])
{
//    critical_show(&cs);
    printf(" OSTimeGet = %d\n", OSTimeGet());
    return 0;
}
SHELL_CMD(task, CFG_MAXARGS, do_taskInfo, "taskInfo\r\n");

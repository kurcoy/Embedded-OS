/**
 ******************************************************************************
 * @file      osLib.c
 * @brief     C Source file of osLib.c.
 * @details   This file including all API functions's implement of osLib.c.
 * @copyright Copyright(C), 2015-2020,Sanxing Medical & Electric Co.,Ltd.
 ******************************************************************************
 */
 
/*-----------------------------------------------------------------------------
 Section: Includes
 ----------------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <types.h>
#include <mempLib.h>
#include <oscfg.h>
#include "_ucos_interface.h"

/*-----------------------------------------------------------------------------
 Section: Type Definitions
 ----------------------------------------------------------------------------*/
/* NONE */

/*-----------------------------------------------------------------------------
 Section: Constant Definitions
 ----------------------------------------------------------------------------*/
/* NONE */ 

/*-----------------------------------------------------------------------------
 Section: Global Variables
 ----------------------------------------------------------------------------*/
/* NONE */

/*-----------------------------------------------------------------------------
 Section: Local Variables
 ----------------------------------------------------------------------------*/
/* NONE */

/*-----------------------------------------------------------------------------
 Section: Local Function Prototypes
 ----------------------------------------------------------------------------*/
/* NONE */

/*-----------------------------------------------------------------------------
 Section: Global Function Prototypes
 ----------------------------------------------------------------------------*/
/* NONE */

/*-----------------------------------------------------------------------------
 Section: Function Definitions
 ----------------------------------------------------------------------------*/
/**
 ******************************************************************************
 * @brief   输出os版本
 *
 * @return  None
 ******************************************************************************
 */
void
os_print_banner(void)
{
    puts("\n  OS Version: NxOS "OS_RELEASE
         "\n  Build Time: "__DATE__" "__TIME__
         "\n  CopyRight : Sanxing Medical & Electric Co.,Ltd.");
}

/**
 ******************************************************************************
 * @brief   输出OS版本信息
 * @return  None
 ******************************************************************************
 */
void
os_show_version(void)
{
//    INT16U v = OSVersion();
    // 输出版本信息
//    printf("Micrium uC/OS-II %d.%d", (int32_t)(v / 10), (int32_t)(v % 10));

#if OS_TASK_STAT_EN > 0u
    // 输出CPU使用率
    printf(" CPU Usage %d%%\n", (uint32_t)OSCPUUsage);
#endif
}


/**
 ******************************************************************************
 * @brief   输出任务信息
 * @return  None
 ******************************************************************************
 */
void
os_show_task(void)
{
    OS_TCB *tcb;
    OS_STK_DATA stkData;
    uint8_t str[20];

    // 输出列名
    printf("%-16s %3s %-10s %8s %20s %10s\n", "NAME", "PRI", "STATUS", "SP", "USED/SIZE", "DELAY");
    printf("---------------- --- ---------- -------- -------------------- ----------\n");
    tcb = OSTCBList;
    while (NULL != tcb)
    {
        // 输出任务名
        printf("%-16s", tcb->OSTCBTaskName);
        // 输出任务优先级
        printf(" %3u", tcb->OSTCBPrio);
        // 输出任务状态
        switch (tcb->OSTCBStat) {
        case OS_STAT_RDY    : printf(" %-10s", "READY");      break;
        case OS_STAT_SUSPEND: printf(" %-10s", "SUSPEND");    break;
        case OS_STAT_SEM    : printf(" %-10s", "PEND SEM");   break;
        case OS_STAT_MBOX   : printf(" %-10s", "PEND MBOX");  break;
        case OS_STAT_Q      : printf(" %-10s", "PEND QUEUE"); break;
        case OS_STAT_MUTEX  : printf(" %-10s", "PEND MUTEX"); break;
        case OS_STAT_FLAG   : printf(" %-10s", "PEND FLAG");  break;
        case OS_STAT_MULTI  : printf(" %-10s", "PEND MULTI"); break;
        default             : printf(" %-10s", "UNKNOW");     break;
        }
        // 输出栈顶地址
        printf(" %8X", (uint32_t)tcb->OSTCBStkPtr);
        // 输出栈容量及使用情况
        if (0u != tcb->OSTCBStkSize) {
            OSTaskStkChk(tcb->OSTCBPrio, &stkData);
            memset(str, 0, sizeof(str));

            snprintf((char_t *)str, sizeof(str), "%d/%d(%3d%%)", stkData.OSUsed, tcb->OSTCBStkSize * 4, (stkData.OSUsed * 100) / (tcb->OSTCBStkSize * 4));
            printf(" %20s", str);
        }
        else printf(" %20s", "UNKNOW");
        // 输出允许等待节拍数
        printf(" %10d\n", tcb->OSTCBDly);

        tcb = tcb->OSTCBNext;
    }
}

/**
 ******************************************************************************
 * @brief   输出osecb信息
 * @return  None
 ******************************************************************************
 */
#if 0
void
os_show_ecb(void)
{
    int32_t i;
    int32_t num[6] = {0, 0, 0, 0, 0, 0};

    for (i = 0; i < OS_MAX_EVENTS; i++)
    {
        if (OSEventTbl[i].OSEventType <= OS_EVENT_TYPE_FLAG)
        {
            num[OSEventTbl[i].OSEventType]++;
        }
    }
    printf("OS EVENT control blocks info:\n");
    printf("  TOTAL          %d\n", OS_MAX_EVENTS);
    printf("  UNUSED         %d\n", num[OS_EVENT_TYPE_UNUSED]);
    printf("  MBOX           %d\n", num[OS_EVENT_TYPE_MBOX]);
    printf("  Q              %d\n", num[OS_EVENT_TYPE_Q]);
    printf("  SEM            %d\n", num[OS_EVENT_TYPE_SEM]);
    printf("  MUTEX          %d\n", num[OS_EVENT_TYPE_MUTEX]);
    printf("  FLAG           %d\n", num[OS_EVENT_TYPE_FLAG]);
}
#endif
/*--------------------------------osLib.c------------------------------------*/

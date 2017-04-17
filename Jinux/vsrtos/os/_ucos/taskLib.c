/**
 ******************************************************************************
 * @file      taskLib.c
 * @brief     内核接口模块.
 * @details   This file including all API functions's implement of taskLib.c.
 * @copyright Copyright(C), 2015-2020,Sanxing Medical & Electric Co.,Ltd.
 ******************************************************************************
 */
/*-----------------------------------------------------------------------------
 Section: Includes
 ----------------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <maths.h>
#include <types.h>
#include <taskLib.h>
//#include <clkLib.h>
#include <oscfg.h>
#include "_ucos_interface.h"

/*-----------------------------------------------------------------------------
 Section: Constant Definitions
 ----------------------------------------------------------------------------*/
#if 0
#define IS_MEM(addr)    (((((uint32_t)(addr)) & 0xFFFE0000) == 0x20000000) \
    || ((((uint32_t)(addr)) & 0xFFFE0000) == 0x10000000))
//    || ((((uint32_t)(addr)) & 0xFFFE0000) == 0xc0000000))
#endif

/*-----------------------------------------------------------------------------
 Section: Local Variables
 ----------------------------------------------------------------------------*/
static uint16_t OSTaskID = 65500;   /* task ID   */

/*-----------------------------------------------------------------------------
 Section: Function Definitions
 ----------------------------------------------------------------------------*/
/** @defgroup group_taskLib taskLib
 *   @brief  多任务内核模块
 *
*   本模块封装了所有任务、信号量、消息队列的相关操作接口
*
* @{
*/

/**
 ******************************************************************************
 * @brief   判断句柄是否有效
 * @param[in]  *pId : 句柄
 *
 * @retval
 ******************************************************************************
 */
#if 0
int
isIdValid(void *pId)
{
    return  (IS_MEM(pId) && IS_MEM(*((uint32_t *)pId))) ? 1 : 0;
}
#endif

/**
 ******************************************************************************
 * @brief   任务创建方法
 * @param[in]  name         ：任务名
 * @param[in]  priority     : 任务优先级
 * @param[in]  *pbos        : 任务栈底
 * @param[in]  stackSize    : 任务栈大小,需要4字节对齐
 * @param[in]  entryPt      : 任务执行体方法
 * @param[in]   arg         : 任务执行体参数
 *
 * @retval   <0  : 任务创建失败
 * @retval  >=0  : 任务创建成功，返回任务优先级
 ******************************************************************************
 */
TASK_ID
taskSpawn(
    char_t *    name,       /* name of new task */
    uint8_t     priority,   /* priority of new task */
    uint32_t    *pbos,      /* a pointer to the task's bottom of stack */
    uint32_t    stackSize,  /* size (bytes) of stack, need a multiple of 4 */
    OSFUNCPTR   entryPt,    /* entry point32_t of new task */
    int32_t     arg         /* task args to pass to func */
    )
{
    if ((stackSize % 4) || ((uint32_t)pbos % 4))
    {
        //fixme: 正式版无需打印
//        printf("Create task err, stack size or address is not 4 bytes alignment\n");
        return ERROR;
    }

    OS_STK *ptos;
    uint8_t err;

    ptos = (OS_STK *)pbos + ((stackSize / 4) - 1);
    err = OSTaskCreateExt(entryPt,
                       (int32_t *)arg,
                       (OS_STK *)ptos,
                       priority,
                       OSTaskID,
                       (OS_STK *)pbos,
                       stackSize / 4,
                       (void *)0,                                 /* No TCB extension                     */
                       OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);/* Enable stack checking + clear stack  */
    if (err != OS_ERR_NONE)
    {
        printf("Create task: %s error[%d]\n", name, err);
        return ERROR;
    }
    OSTaskNameSet(priority, (uint8_t *)name, (uint8_t *)&err);


    OSTaskID--;
    if (OSTaskID <= 10) return -1;
    return priority;
}

/**
 ******************************************************************************
 * @brief   获取当前任务ID
 *
 * @retval  任务ID
 ******************************************************************************
 */
TASK_ID
taskID(void)
{
    return (TASK_ID)OSPrioCur;
}

/**
 ******************************************************************************
 * @brief   获取任务名
 * @param[in]  tid  : 任务ID
 *
 * @retval  任务名
 ******************************************************************************
 */
char_t*
taskName(TASK_ID tid)
{
    INT8U *pname = NULL;
    INT8U err;
    (void)OSTaskNameGet((INT8U)tid, &pname, &err);
    return (err == OS_ERR_NONE) ? (char_t *)pname : NULL;
}

/**
 ******************************************************************************
 * @brief   设置任务名
 * @param[in]  tid   : 任务ID
 * @param[in]  *pname: 任务名
 *
 * @retval  任务名
 ******************************************************************************
 */
status_t
taskNameSet(TASK_ID tid,
        char_t *pname)
{
    INT8U err;
    (void)OSTaskNameSet((INT8U)tid, (INT8U*)pname, &err);
    return (err == OS_ERR_NONE) ? OK : ERROR;
}

/**
 ******************************************************************************
 * @brief   删除任务
 * @param[in]  tid  : 任务号
 *
 * @retval  OK   : 成功
 * @retval  ERROR: 失败
 ******************************************************************************
 */
status_t
taskDelete(TASK_ID tid)
{
    return (OSTaskDel((INT8U)tid) == OS_ERR_NONE) ? OK : ERROR;
}

/**
 ******************************************************************************
 * @brief   暂停任务
 * @param[in]  tid  : 任务号
 *
 * @retval  OK   : 成功
 * @retval  ERROR: 失败
 ******************************************************************************
 */
status_t
taskSuspend(TASK_ID tid)
{
    return (OSTaskSuspend((INT8U)tid) == OS_ERR_NONE) ? OK : ERROR;
}

/**
 ******************************************************************************
 * @brief   恢复任务
 * @param[in]  tid  : 任务号
 *
 * @retval  OK   : 成功
 * @retval  ERROR: 失败
 ******************************************************************************
 */
status_t
taskResume(TASK_ID tid)
{
    return (OSTaskResume((INT8U)tid) == OS_ERR_NONE) ? OK : ERROR;
}

/**
 ******************************************************************************
 * @brief   设置任务新优先级
 * @param[in]  tid          : 任务号
 * @param[in]  newPriority  : 新优先级
 *
 * @retval  OK   : 成功
 * @retval  ERROR: 失败
 ******************************************************************************
 */
status_t
taskPrioritySet(TASK_ID tid,
        uint8_t newPriority)
{
    return (OSTaskChangePrio((INT8U)tid, (INT8U)newPriority) == OS_ERR_NONE)
            ? OK : ERROR;
}

/**
 ******************************************************************************
 * @brief   调度器加锁
 * @return  None
 ******************************************************************************
 */
void
taskLock(void)
{
    OSSchedLock();
}

/**
 ******************************************************************************
 * @brief   调度器解锁
 * @return  None
 ******************************************************************************
 */
void
taskUnlock(void)
{
    OSSchedUnlock();
}

/**
 ******************************************************************************
 * @brief   任务延时
 * @param[in]  ticks    : 延时时间片数量
 *
 * @return  None
 ******************************************************************************
 */
void
taskDelay(uint32_t ticks)
{
    OSTimeDly((INT32U)ticks);
}

/**
 ******************************************************************************
 * @brief   创建信号量
 * @param[in]  cnt  : 初始化值
 *
 * @return  NULL    : 创建失败
 * @return  >0      : 信号量ID
 ******************************************************************************
 */
SEM_ID
semBCreate(uint16_t cnt)
{
    return OSSemCreate((INT16U)cnt);
}

/**
 ******************************************************************************
 * @brief   删除信号量
 * @param[in]  semId  : 待删除的信号量ID
 *
 * @return  OK   : 删除成功
 * @return  ERROR: 删除失败
 ******************************************************************************
 */
status_t
semDelete(SEM_ID semId)
{
    INT8U status_err;

    (void)OSSemDel((OS_EVENT *)semId, OS_DEL_ALWAYS, &status_err);
    return (OS_ERR_NONE == status_err) ? OK : ERROR;
}

/**
 ******************************************************************************
 * @brief   获取信号量
 * @param[in]  semId    : 信号量ID
 * @param[in]  timeout  : 超时时间片数量(0:永远等待)
 *
 * @retval  OK   : 获取成功
 * @retval  ERROR: 获取失败
 ******************************************************************************
 */
status_t
semTake(SEM_ID semId,
        uint32_t timeout)
{
    INT8U status_err;

    OSSemPend((OS_EVENT *)semId, (INT32U)timeout, &status_err);
    return (OS_ERR_NONE == status_err) ? OK : ERROR;
}

/**
 ******************************************************************************
 * @brief   释放信号量
 * @param[in]  semId    : 信号量ID
 *
 * @retval  OK   : 释放成功
 * @retval  ERROR: 释放失败
 ******************************************************************************
 */
status_t
semGive(SEM_ID semId)
{
    return (OSSemPost((OS_EVENT *)semId) == OS_ERR_NONE) ? OK : ERROR;
}

/**
 ******************************************************************************
 * @brief   创建消息队列
 * @param[in]  **start  : 消息队列数据存放地址
 * @param[in]  size     : 消息队列数量
 *
 * @retval  >0   : 创建成功
 * @retval  NULL : 创建失败
 ******************************************************************************
 */
MSG_Q_ID
msgQCreate(void **start,/* a pointer to the base address of the message queue storage area */
        uint16_t size  /* the number of elements in the storage area */
        )
{
    return OSQCreate(start, (INT16U)size);
}

/**
 ******************************************************************************
 * @brief   发送消息
 * @param[in]  msgQId   : 消息队列ID
 * @param[in]  *pmsg    : 指向待发送消息
 *
 * @retval  OK   : 发送成功
 * @retval  ERROR: 发送失败
 ******************************************************************************
 */
status_t
msgQSend(MSG_Q_ID msgQId,
        void *pmsg  /* a pointer to the message to send */
        )
{
    return (OSQPost((OS_EVENT *)msgQId, pmsg) == OS_ERR_NONE) ? OK : ERROR;
}

/**
 ******************************************************************************
 * @brief   接收消息队列
 * @param[in]  msgQId   : 消息队列ID
 * @param[in]  timeout  : 超时时间片数量(0:永远等待)
 * @param[out] **pmsg   : 返回接收到消息指针
 *
 * @retval  OK   : 接收成功
 * @retval  ERROR: 接收失败
 ******************************************************************************
 */
status_t
msgQReceive(MSG_Q_ID msgQId,
        int32_t timeout,  /* ticks to wait */
        void **pmsg       /* a pointer to the message to recv */
        )
{
    INT8U err;

    *pmsg = OSQPend((OS_EVENT *)msgQId, (INT32U)timeout, &err);

    return (err == OS_ERR_NONE) ? OK : ERROR;
}

/**
 ******************************************************************************
 * @brief   查询消息队列中消息个数
 * @param[in]  msgQId   : 消息队列ID
 *
 * @retval  消息队列中消息个数
 ******************************************************************************
 */
uint16_t
msgQNumMsgs(MSG_Q_ID msgQId)
{
    OS_Q_DATA msgInfo;

    if (OS_ERR_NONE == OSQQuery((OS_EVENT *)msgQId, &msgInfo))
    {
        return (uint16_t)msgInfo.OSNMsgs;
    }
    return 0u;
}

/**
 ******************************************************************************
 * @brief   清空消息队列
 * @param[in]  msgQId   : 消息队列ID
 *
 * @retval  消息队列中消息个数
 ******************************************************************************
 */
status_t
msgQFlush(MSG_Q_ID msgQId)
{
    return (OSQFlush((OS_EVENT *)msgQId) == OS_ERR_NONE) ? OK : ERROR;
}

/**
 ******************************************************************************
 * @brief   获取系统时间片
 * @retval  调度器启动后时间片的数量
 ******************************************************************************
 */
uint32_t
tickGet(void)
{
    return (uint32_t)OSTimeGet();
}

/**
 ******************************************************************************
 * @brief   获取系统每秒钟的时间片数量
 * @retval  系统每秒钟的时间片数量(一般为100)
 ******************************************************************************
 */
uint32_t
sysClkRateGet(void)
{
    return (uint32_t)OS_TICKS_PER_SEC;
}

/**
 * @}
 */

/*-------------------------------taskLib.c-----------------------------------*/

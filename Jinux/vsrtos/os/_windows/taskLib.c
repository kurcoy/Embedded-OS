/**
 ******************************************************************************
 * @file       _taskLib.c
 * @version    V1.1.4
 * @brief      API C source file of _taskLib.c
 *             Created on: 2016-9-7
 *             Author: wenrenjinjun
 * @details    This file including all API functions's implement of dps.
 * @copy       Copyrigth(C), 2008-2012,Sanxing Electric Co.,Ltd.
 *
 ******************************************************************************
 */
#include <types.h>
#include <taskLib.h>
#include <string.h>
#include <stdio.h>

#include "_win_interface.h"
#include <process.h>

#undef  ERROR
#define ERROR   -1

#undef  OK
#define OK      0

static char *   _window_task_name   [MAXNUM_OF_TASKS];
static HANDLE   _window_task_handle [MAXNUM_OF_TASKS];
static unsigned _window_task_id     [MAXNUM_OF_TASKS];
static char     _window_task_msgQ   [MAXNUM_OF_TASKS]; //每个线程一个消息队列
//static char _existed_task_num = 0;

/* ----------------------编译需要----------------------------------- */
int32_t
_time_of_now(int32_t type)
{
     return 0;
}
/* ----------------------------------------------------------------- */


/**
 ******************************************************************************
 * @brief
 * @param[in]
 * @retval
 ******************************************************************************
 */
void
winos_task_init(void)
{
    memset(_window_task_name,   0x00, sizeof(_window_task_name));
    memset(_window_task_id,     0x00, sizeof(_window_task_id));
    memset(_window_task_handle, 0x00, sizeof(_window_task_handle));
    memset(_window_task_msgQ,   0x00, sizeof(_window_task_msgQ));
}

/**
 ******************************************************************************
 * @brief
 * @param[in]
 * @retval
 ******************************************************************************
 */
int
test_tid_valid_and_existed(unsigned tid)
{
    if(tid > (MAXNUM_OF_TASKS - 1))
    {
        __PRINTF_("err priority %d err\n", tid);
        return 0;
    }

    if(_window_task_id[tid] == 0)
    {
        __PRINTF_("err priority %d task_not_existed\n", tid);
        return 0;
    }
    return 1;
}

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
    int32_t     arg)         /* task args to pass to func */
{
    unsigned tid;
    HANDLE handle;

    if(priority > (MAXNUM_OF_TASKS - 1))
    {
        __PRINTF_("err priority %d err\n", priority);
        return -1;
    }

    if(_window_task_id[priority] != 0)
    {
        __PRINTF_("err priority %d task_existed\n", priority);
        return -1;
    }

//  避免使用 CreateThread   ExitThread  TerminateThread
    handle = (void*)_beginthreadex(
            NULL,
            stackSize,
            (void *) entryPt,
            (void *)arg,
            0,
            &tid);

    if(handle == 0)
    {
        __PRINTF_("err _beginthreadex err priority %d\n", priority);
        return -1;
    }

    _window_task_id[priority] = tid;
    _window_task_name[priority] = name;
    _window_task_handle[priority] = handle;

//    __PRINTF_("\n");
//    __PRINTF_("handle = %p\n", handle ) ;
//    __PRINTF_("Thread_id = %d\n", tid ) ;
//    __PRINTF_("task_name = %s\n", name ) ;
//    __PRINTF_("task_priority = %d\n", priority) ;
//    __PRINTF_("\n");
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
    int i;
    unsigned tid;

    tid = GetCurrentThreadId();
    for(i = 0; i <MAXNUM_OF_TASKS; i++)
    {
        if(tid == _window_task_id[i])
        {
            break;
        }
    }
    if( i == MAXNUM_OF_TASKS)
    {
        printf("taskID err\n");
        i = -1;
    }

    return (TASK_ID)i;
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
    if(tid > (MAXNUM_OF_TASKS - 1))
    {
        return NULL;
    }

    if(_window_task_id[tid] == 0)
    {
        __PRINTF_("任务为创建\n");
        return NULL;
    }

    return _window_task_name[tid];
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
    if(test_tid_valid_and_existed(tid))
    {
        _window_task_name[tid] = pname;
        __PRINTF_("\ntaskNameSet = %s\n", pname ) ;
        return OK;
    }
    return ERROR;
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
    if(test_tid_valid_and_existed(tid))
    {
        _endthreadex(0);//todo 需要更改
        __PRINTF_("\taskDelete = %s\n", _window_task_name[tid] ) ;
        return OK;
    }
    return ERROR;
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
    if(test_tid_valid_and_existed(tid))
    {
        __PRINTF_("taskSuspend %d\n", tid);
        SuspendThread(_window_task_handle[tid]);
        return OK;
    }
    return ERROR;
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
    if(test_tid_valid_and_existed(tid))
    {
        __PRINTF_("taskResume %d\n", tid);
        ResumeThread(_window_task_handle[tid]);
        return OK;
    }
    return ERROR;
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
    return OK;
}

/**
 ******************************************************************************
 * @brief   调度器加锁
 *
 * @return  None
 ******************************************************************************
 */
void
taskLock(void)
{
    __OS_ENTER_CRITICAL();
//    OSSchedLock();
}

/**
 ******************************************************************************
 * @brief   调度器解锁
 *
 * @return  None
 ******************************************************************************
 */
void
taskUnlock(void)
{
    __OS_EXIT_CRITICAL();
//    OSSchedUnlock();
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
    Sleep((1000 / OS_TICKS_PER_SEC) * ticks);
//    wOSTimeDly((INT32U)ticks);
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
    SEM_ID semID;
    semID = CreateSemaphore(NULL, cnt, 1, NULL);

    if(semID == NULL)
    {
        printf("CreateSemaphore err \n");
    }
    return semID;
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
    (void)CloseHandle((HANDLE)semId);
    return OK;
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
extern void ShowErrInfo(DWORD err);
status_t
semTake(SEM_ID semId,
        uint32_t timeout)
{
    DWORD dw;
    dw = WaitForSingleObject((HANDLE)semId, INFINITE);
    switch(dw)
    {
        case WAIT_OBJECT_0:
            // The process terminated.
//            printf("The process terminated\n");
            return OK;

        case WAIT_TIMEOUT:
            // The process did not terminate within 5000 milliseconds.
            printf("The process did not terminate within 5000 milliseconds\n");
            ShowErrInfo(GetLastError());
            return ERROR;

        default:
        case WAIT_FAILED:
         // Bad call to function (invalid handle?)
            printf("Bad call to function (invalid handle?)\n");
            ShowErrInfo(GetLastError());
            return ERROR;
    }
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
    if (!ReleaseSemaphore((HANDLE)semId, 1, NULL))
    {
        printf("semGive error\n");
        return ERROR;
    }
    return OK;
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
    TASK_ID tid;

    tid = size;
    if(_window_task_msgQ[tid])
    {
        printf("msgQCreate tid ERROR = %d\n", tid);
        return NULL;
    }
    _window_task_msgQ[tid] = 1;
//    printf("msgQCreate tid = %d\n", tid);
    return (MSG_Q_ID)(tid + 100);
}

/**
 ******************************************************************************
 * @brief   发送消息
 * @param[in]  msgQId   : 消息队列ID
 * @param[in]  *pmsg    : 指向待发送消息
 *
 * @retval  OK   : 发送成功
 * @retval  ERROR: 发送失败
 * //    PostMessage();
//    SendMessage();
 ******************************************************************************
 */

#define MY_MSG WM_USER+100
extern void ShowErrInfo(DWORD err);
status_t
msgQSend(MSG_Q_ID msgQId,
        void *pmsg  /* a pointer to the message to send */
        )
{

    int id = (int)msgQId - 100;
//    SetLastError(0);
//    ShowErrInfo(GetLastError());
//    printf("msgQId = %d\n", msgQId);
//    printf("tid = %d\n", _window_task_id[id]);
//    while(1);
    if(PostThreadMessage(_window_task_id[id], WM_USER, (WPARAM)pmsg, 0))
    {
//        printf("PostThreadMessage OK\n");
        return OK;
    }
//
//    ShowErrInfo(GetLastError());
    return ERROR;
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
    if( msgQId == NULL)
    {
        return ERROR;
    }
    MSG Msg;
    if (PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE))
    //if (GetMessage(&Msg, NULL, 0, 0))
    {
        (*pmsg) = (void *)(Msg.wParam);
//        printf("*************************************msgQReceive OK\n");
//        while(1);
        return OK;
    }
    else
    {
//        printf("msgQReceive delay\n");
        Sleep(timeout);
    }

    return ERROR;
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
//    OS_Q_DATA msgInfo;
//
//    if (OS_ERR_NONE == OSQQuery((OS_EVENT *)msgQId, &msgInfo))
//    {
//        return (uint16_t)msgInfo.OSNMsgs;
//    }
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
//    return (OSQFlush((OS_EVENT *)msgQId) == OS_ERR_NONE) ? OK : ERROR;
    return ERROR;
}

/**
 ******************************************************************************
 * @brief   获取系统时间片
 *
 * @retval  调度器启动后时间片的数量
 ******************************************************************************
 */
uint32_t
tickGet(void)
{
    return OSTimeGet();
}

/**
 ******************************************************************************
 * @brief   获取系统每秒钟的时间片数量
 *
 * @retval  系统每秒钟的时间片数量(一般为100)
 ******************************************************************************
 */
uint32_t
sysClkRateGet(void)
{
    return (uint32_t)OS_TICKS_PER_SEC;
}


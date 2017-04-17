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
static char     _window_task_msgQ   [MAXNUM_OF_TASKS]; //ÿ���߳�һ����Ϣ����
//static char _existed_task_num = 0;

/* ----------------------������Ҫ----------------------------------- */
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
 * @brief   ���񴴽�����
 * @param[in]  name         ��������
 * @param[in]  priority     : �������ȼ�
 * @param[in]  *pbos        : ����ջ��
 * @param[in]  stackSize    : ����ջ��С,��Ҫ4�ֽڶ���
 * @param[in]  entryPt      : ����ִ���巽��
 * @param[in]   arg         : ����ִ�������
 *
 * @retval   <0  : ���񴴽�ʧ��
 * @retval  >=0  : ���񴴽��ɹ��������������ȼ�
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

//  ����ʹ�� CreateThread   ExitThread  TerminateThread
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
 * @brief   ��ȡ��ǰ����ID
 *
 * @retval  ����ID
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
 * @brief   ��ȡ������
 * @param[in]  tid  : ����ID
 *
 * @retval  ������
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
        __PRINTF_("����Ϊ����\n");
        return NULL;
    }

    return _window_task_name[tid];
}

/**
 ******************************************************************************
 * @brief   ����������
 * @param[in]  tid   : ����ID
 * @param[in]  *pname: ������
 *
 * @retval  ������
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
 * @brief   ɾ������
 * @param[in]  tid  : �����
 *
 * @retval  OK   : �ɹ�
 * @retval  ERROR: ʧ��
 ******************************************************************************
 */
status_t
taskDelete(TASK_ID tid)
{
    if(test_tid_valid_and_existed(tid))
    {
        _endthreadex(0);//todo ��Ҫ����
        __PRINTF_("\taskDelete = %s\n", _window_task_name[tid] ) ;
        return OK;
    }
    return ERROR;
}

/**
 ******************************************************************************
 * @brief   ��ͣ����
 * @param[in]  tid  : �����
 *
 * @retval  OK   : �ɹ�
 * @retval  ERROR: ʧ��
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
 * @brief   �ָ�����
 * @param[in]  tid  : �����
 *
 * @retval  OK   : �ɹ�
 * @retval  ERROR: ʧ��
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
 * @brief   �������������ȼ�
 * @param[in]  tid          : �����
 * @param[in]  newPriority  : �����ȼ�
 *
 * @retval  OK   : �ɹ�
 * @retval  ERROR: ʧ��
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
 * @brief   ����������
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
 * @brief   ����������
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
 * @brief   ������ʱ
 * @param[in]  ticks    : ��ʱʱ��Ƭ����
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
 * @brief   �����ź���
 * @param[in]  cnt  : ��ʼ��ֵ
 *
 * @return  NULL    : ����ʧ��
 * @return  >0      : �ź���ID
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
 * @brief   ɾ���ź���
 * @param[in]  semId  : ��ɾ�����ź���ID
 *
 * @return  OK   : ɾ���ɹ�
 * @return  ERROR: ɾ��ʧ��
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
 * @brief   ��ȡ�ź���
 * @param[in]  semId    : �ź���ID
 * @param[in]  timeout  : ��ʱʱ��Ƭ����(0:��Զ�ȴ�)
 *
 * @retval  OK   : ��ȡ�ɹ�
 * @retval  ERROR: ��ȡʧ��
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
 * @brief   �ͷ��ź���
 * @param[in]  semId    : �ź���ID
 *
 * @retval  OK   : �ͷųɹ�
 * @retval  ERROR: �ͷ�ʧ��
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
 * @brief   ������Ϣ����
 * @param[in]  **start  : ��Ϣ�������ݴ�ŵ�ַ
 * @param[in]  size     : ��Ϣ��������
 *
 * @retval  >0   : �����ɹ�
 * @retval  NULL : ����ʧ��
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
 * @brief   ������Ϣ
 * @param[in]  msgQId   : ��Ϣ����ID
 * @param[in]  *pmsg    : ָ���������Ϣ
 *
 * @retval  OK   : ���ͳɹ�
 * @retval  ERROR: ����ʧ��
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
 * @brief   ������Ϣ����
 * @param[in]  msgQId   : ��Ϣ����ID
 * @param[in]  timeout  : ��ʱʱ��Ƭ����(0:��Զ�ȴ�)
 * @param[out] **pmsg   : ���ؽ��յ���Ϣָ��
 *
 * @retval  OK   : ���ճɹ�
 * @retval  ERROR: ����ʧ��
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
 * @brief   ��ѯ��Ϣ��������Ϣ����
 * @param[in]  msgQId   : ��Ϣ����ID
 *
 * @retval  ��Ϣ��������Ϣ����
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
 * @brief   �����Ϣ����
 * @param[in]  msgQId   : ��Ϣ����ID
 *
 * @retval  ��Ϣ��������Ϣ����
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
 * @brief   ��ȡϵͳʱ��Ƭ
 *
 * @retval  ������������ʱ��Ƭ������
 ******************************************************************************
 */
uint32_t
tickGet(void)
{
    return OSTimeGet();
}

/**
 ******************************************************************************
 * @brief   ��ȡϵͳÿ���ӵ�ʱ��Ƭ����
 *
 * @retval  ϵͳÿ���ӵ�ʱ��Ƭ����(һ��Ϊ100)
 ******************************************************************************
 */
uint32_t
sysClkRateGet(void)
{
    return (uint32_t)OS_TICKS_PER_SEC;
}


/**
 ******************************************************************************
 * @file      taskLib.c
 * @brief     �ں˽ӿ�ģ��.
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
 *   @brief  �������ں�ģ��
 *
*   ��ģ���װ�����������ź�������Ϣ���е���ز����ӿ�
*
* @{
*/

/**
 ******************************************************************************
 * @brief   �жϾ���Ƿ���Ч
 * @param[in]  *pId : ���
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
    int32_t     arg         /* task args to pass to func */
    )
{
    if ((stackSize % 4) || ((uint32_t)pbos % 4))
    {
        //fixme: ��ʽ�������ӡ
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
 * @brief   ��ȡ��ǰ����ID
 *
 * @retval  ����ID
 ******************************************************************************
 */
TASK_ID
taskID(void)
{
    return (TASK_ID)OSPrioCur;
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
    INT8U *pname = NULL;
    INT8U err;
    (void)OSTaskNameGet((INT8U)tid, &pname, &err);
    return (err == OS_ERR_NONE) ? (char_t *)pname : NULL;
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
    INT8U err;
    (void)OSTaskNameSet((INT8U)tid, (INT8U*)pname, &err);
    return (err == OS_ERR_NONE) ? OK : ERROR;
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
    return (OSTaskDel((INT8U)tid) == OS_ERR_NONE) ? OK : ERROR;
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
    return (OSTaskSuspend((INT8U)tid) == OS_ERR_NONE) ? OK : ERROR;
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
    return (OSTaskResume((INT8U)tid) == OS_ERR_NONE) ? OK : ERROR;
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
    return (OSTaskChangePrio((INT8U)tid, (INT8U)newPriority) == OS_ERR_NONE)
            ? OK : ERROR;
}

/**
 ******************************************************************************
 * @brief   ����������
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
 * @brief   ����������
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
 * @brief   ������ʱ
 * @param[in]  ticks    : ��ʱʱ��Ƭ����
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
    return OSSemCreate((INT16U)cnt);
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
    INT8U status_err;

    (void)OSSemDel((OS_EVENT *)semId, OS_DEL_ALWAYS, &status_err);
    return (OS_ERR_NONE == status_err) ? OK : ERROR;
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
    return (OSSemPost((OS_EVENT *)semId) == OS_ERR_NONE) ? OK : ERROR;
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
    return OSQCreate(start, (INT16U)size);
}

/**
 ******************************************************************************
 * @brief   ������Ϣ
 * @param[in]  msgQId   : ��Ϣ����ID
 * @param[in]  *pmsg    : ָ���������Ϣ
 *
 * @retval  OK   : ���ͳɹ�
 * @retval  ERROR: ����ʧ��
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
    INT8U err;

    *pmsg = OSQPend((OS_EVENT *)msgQId, (INT32U)timeout, &err);

    return (err == OS_ERR_NONE) ? OK : ERROR;
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
    OS_Q_DATA msgInfo;

    if (OS_ERR_NONE == OSQQuery((OS_EVENT *)msgQId, &msgInfo))
    {
        return (uint16_t)msgInfo.OSNMsgs;
    }
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
    return (OSQFlush((OS_EVENT *)msgQId) == OS_ERR_NONE) ? OK : ERROR;
}

/**
 ******************************************************************************
 * @brief   ��ȡϵͳʱ��Ƭ
 * @retval  ������������ʱ��Ƭ������
 ******************************************************************************
 */
uint32_t
tickGet(void)
{
    return (uint32_t)OSTimeGet();
}

/**
 ******************************************************************************
 * @brief   ��ȡϵͳÿ���ӵ�ʱ��Ƭ����
 * @retval  ϵͳÿ���ӵ�ʱ��Ƭ����(һ��Ϊ100)
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

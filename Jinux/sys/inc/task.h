/**
 ******************************************************************************
 * @file       task.h
 * @version    V1.0.0
 * @brief      API C source file of task.h
 *             Created on: 2017年4月17日
 *             Author: JunGeGe
 * @details    This file including all API functions's implement of dps.
 * @copyright  Copyright(C)
 ******************************************************************************
 */
#ifndef INC_TASK_H_
#define INC_TASK_H_

/*-----------------------------------------------------------------------------
 Section: Includes
 ----------------------------------------------------------------------------*/
#include <types.h>

/*-----------------------------------------------------------------------------
 Section: Macro Definitions
 ----------------------------------------------------------------------------*/
#if __CORE_SELECTION_ != 1
#define OS_TICKS_PER_SECOND (1000)
#else
#define OS_TICKS_PER_SECOND (100)
#endif

#define WAIT_FOREVER    ((uint32_t)0)
#define MS2TICK(ms)     ((ms) * (OS_TICKS_PER_SECOND) / 1000)
#define S2TICK(s)       ((s) * (OS_TICKS_PER_SECOND))

/*-----------------------------------------------------------------------------
 Section: Type Definitions
 ----------------------------------------------------------------------------*/
typedef int16_t TASK_ID;
typedef void *  SEM_ID;
typedef void *  MSG_Q_ID;

/*-----------------------------------------------------------------------------
 Section: Globals
 ----------------------------------------------------------------------------*/
/* NONE */

/*-----------------------------------------------------------------------------
 Section: Function Prototypes
 ----------------------------------------------------------------------------*/
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
extern TASK_ID
taskSpawn(char_t *pname,
        uint8_t priority,
        uint32_t *pbos,
        uint32_t stackSize,
        OSFUNCPTR entryPt,
        int32_t arg);

/**
 ******************************************************************************
 * @brief   获取当前任务ID
 *
 * @retval  任务ID
 ******************************************************************************
 */
extern TASK_ID
taskID(void);

/**
 ******************************************************************************
 * @brief   获取任务名
 * @param[in]  tid  : 任务ID
 *
 * @retval  任务名
 ******************************************************************************
 */
extern char_t*
taskName(TASK_ID tid);

extern status_t
taskNameSet(TASK_ID tid,
        char_t *pname);

extern status_t
taskDelete(TASK_ID tid);

extern status_t
taskSuspend(TASK_ID tid);

extern status_t
taskResume(TASK_ID tid);

extern status_t
taskPrioritySet(TASK_ID tid,
        uint8_t newPriority);

extern void
taskLock(void);

extern void
taskUnlock(void);

extern void
taskDelay(uint32_t ticks);

extern SEM_ID
semBCreate(uint16_t cnt);

extern status_t
semDelete(SEM_ID semId);

extern status_t
semTake(SEM_ID semId,
        uint32_t timeout);

extern status_t
semGive(SEM_ID semId);

extern MSG_Q_ID
msgQCreate(void **start,
        uint16_t size);

extern status_t
msgQSend(MSG_Q_ID msgQId,
        void *pmsg);

extern status_t
msgQReceive(MSG_Q_ID msgQId,
        int32_t timeout,
        void **pmsg);

extern uint16_t
msgQNumMsgs(MSG_Q_ID msgQId);

extern status_t
msgQFlush(MSG_Q_ID msgQId);

extern uint32_t
tickGet(void);

extern uint32_t
sysClkRateGet(void);



#endif /* INC_TASK_H_ */

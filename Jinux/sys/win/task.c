/**
 ******************************************************************************
 * @file      task.c
 * @brief     C Source file of task.c.
 * @details   This file including all API functions's implement of task.c.	
 * @copyright  Copyright(C)
 ******************************************************************************
 */
 
/*-----------------------------------------------------------------------------
 Section: Includes
 ----------------------------------------------------------------------------*/
#include <types.h>

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
/*TASK_ID*/

uint8_t
taskSpawn(
    char_t *    name,       /* name of new task */
    uint8_t     priority,   /* priority of new task */
    uint32_t    *pbos,      /* a pointer to the task's bottom of stack */
    uint32_t    stackSize,  /* size (bytes) of stack, need a multiple of 4 */
    OSFUNCPTR   entryPt,    /* entry point32_t of new task */
    int32_t     arg)         /* task args to pass to func */
{
 //   unsigned tid;
 //   HANDLE handle;

//    if(priority > (MAXNUM_OF_TASKS - 1))
//    {
//        __PRINTF_("err priority %d err\n", priority);
//        return -1;
//    }

//    if(_window_task_id[priority] != 0)
//    {
//        __PRINTF_("err priority %d task_existed\n", priority);
//        return -1;
//    }

////  避免使用 CreateThread   ExitThread  TerminateThread
//    handle = (void*)_beginthreadex(
//            NULL,
//            stackSize,
//            (void *) entryPt,
//            (void *)arg,
//            0,
//            &tid);

//    if(handle == 0)
//    {
//        __PRINTF_("err _beginthreadex err priority %d\n", priority);
//        return -1;
//    }

//    _window_task_id[priority] = tid;
//    _window_task_name[priority] = name;
//    _window_task_handle[priority] = handle;

//    __PRINTF_("\n");
//    __PRINTF_("handle = %p\n", handle ) ;
//    __PRINTF_("Thread_id = %d\n", tid ) ;
//    __PRINTF_("task_name = %s\n", name ) ;
//    __PRINTF_("task_priority = %d\n", priority) ;
//    __PRINTF_("\n");
    return priority;
}


/*----------------------------task.c--------------------------------*/

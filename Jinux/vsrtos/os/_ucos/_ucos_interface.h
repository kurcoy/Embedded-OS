/**
 ******************************************************************************
 * @file       _ucos_interface.h
 * @brief      API C source file of _ucos_interface.h
 * @details    This file including all API functions's declare of
 *             _ucos_interface.h.
 * @copyright Copyright(C), 2015-2020,Sanxing Medical & Electric Co.,Ltd.
 ******************************************************************************
 */

#ifndef UCOS_INTERFACE_H_
#define UCOS_INTERFACE_H_

/*-----------------------------------------------------------------------------
 Section: Includes
 ----------------------------------------------------------------------------*/
#include "sched/ucos_ii.h"
#include "sched/cpu_os.h"

/*-----------------------------------------------------------------------------
 Section: Macro Definitions
 ----------------------------------------------------------------------------*/
#if OS_CRITICAL_METHOD == 3u
#define __OS_DECLARE_CRITICAL()  OS_CPU_SR  cpu_sr = 0u
#else
#define __OS_DECLARE_CRITICAL()
#endif

#define __OS_ENTER_CRITICAL()   OS_ENTER_CRITICAL()
#define __OS_EXIT_CRITICAL()    OS_EXIT_CRITICAL()

#define __OS_Init()             OSInit()
#define __OS_Start()            OSStart()
#define __OS_SysTickInit(n)     OS_CPU_SysTickInit(n)
#define __OS_StatInit()         OSStatInit()

#endif /* UCOS_INTERFACE_H_ */
/*-------------------------End of _ucos_interface.h--------------------------*/

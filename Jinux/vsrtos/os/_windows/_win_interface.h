/**
 ******************************************************************************
 * @file       _windows_interface.h
 * @version    V1.1.4
 * @brief      API C source file of core_windows_interface.h
 *             Created on: 2016-8-30
 *             Author: wenrenjinjun
 * @details    This file including all API functions's implement of dps.
 * @copy       Copyrigth(C), 2008-2012,Sanxing Electric Co.,Ltd.
 *
 ******************************************************************************
 */

#ifndef _WINDOWS_INTERFACE_H_
#define _WINDOWS_INTERFACE_H_

#include "sched/_win_os.h"
#include "sched/_cpu_os.h"

#define __OS_DECLARE_CRITICAL()
#define __OS_ENTER_CRITICAL()  EnterCriticalSection(&cs);
#define __OS_EXIT_CRITICAL()   LeaveCriticalSection(&cs);

#define __OS_Init()            win_OSInit()
#define __OS_Start()           win_OSStart()
#define __OS_SysTickInit(n)    win_OSSysTickInit(n)
#define __OS_StatInit()        win_OSStatInit()

#define __PRINTF_(format, ...) \
    {\
        __OS_ENTER_CRITICAL()\
        printf(format, ##__VA_ARGS__);\
        __OS_EXIT_CRITICAL();\
    }

#define OS_MAX_TASKS              16u
#define OS_MAX_QS                 8u

#endif /* CORE_WINDOWS_INTERFACE_H_ */

/**
 ******************************************************************************
 * @file       _core_sel.h
 * @brief      API C source file of _core_sel.h
 * @details    This file including all API functions's declare of _core_sel.h.
 * @copyright Copyright(C), 2015-2020,Sanxing Medical & Electric Co.,Ltd.
 ******************************************************************************
 */

#ifndef CORE_SEL_H_
#define CORE_SEL_H_

/*-----------------------------------------------------------------------------
 Section: Macro Definitions
 ----------------------------------------------------------------------------*/
#define CORE_WINDOWS    (1u)
#define CORE_UCOS       (2u)

#ifndef __CORE_SELECTION_
#define __CORE_SELECTION_   CORE_WINDOWS
#endif

#if (__CORE_SELECTION_ == CORE_WINDOWS)
#include "_windows/_win_interface.h"

#elif (__CORE_SELECTION_ == CORE_UCOS)
#include "_ucos/_ucos_interface.h"

#else
# error "__CORE_SELECTION_ define error!"
#endif

#endif /* CORE_SEL_H_ */
/*----------------------------End of _core_sel.h-----------------------------*/

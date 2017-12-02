/**
 ******************************************************************************
 * @file      config.h
 * @brief     C Source file of config.h.
 * @details   This file including all API functions's implement of config.h.
 *            选择某个板子即选择定义某个产品的宏
 *            例如  ：   #define S34S11_V1
 * @copyright   Copyright(C), 2015-2020,Sanxing Medical & Electric Co.,Ltd.
 ******************************************************************************
 */
#ifndef __BSPCFG_H__
#define __BSPCFG_H__

/*-----------------------------------------------------------------------------
 Section: Macro Definitions
 ----------------------------------------------------------------------------*/
#define BOARD_STM32F3_Wildfire      (1u)    //
#define BOARD_STM32F4_ALENTEK       (2u)    //
#define BOARD_WINDOWS               (3u)    //

#define BOARD_BUILD_VER BOARD_STM32F3_Wildfire

#if (BOARD_BUILD_VER == BOARD_STM32F3_Wildfire)
   #define BSP_VER  "Wiledfire"
   #include "board/STM32F3_Wildfire/STM32F3_Wildfire.h"
#elif (BOARD_BUILD_VER == BOARD_STM32F4_ALENTEK)
   #define BSP_VER  "ALENTEK"
   #include "board/STM32F4_ALIENTEK/STM32F4_ALIENTEK.h"
#elif (BOARD_BUILD_VER == BOARD_WINDOWS)
    #define BSP_VER  "WIN_TEST"
    #include "board/WIN_TEST/WIN_TEST.h"
#else
# error "BOARD_BUILD_VER define error!"
#endif

//#ifndef BOARD_BANNER
//# error "Please define 'BOARD_BANNER' in 'boardcfg.h'!"
//#endif
//
//#ifndef MAX_INT_COUNT
//# error "Please define 'MAX_INT_COUNT' in 'boardcfg.h'!"
//#endif
//
//#ifndef CPU_CLOCK_HZ
//# error "Please define 'CPU_CLOCK_HZ' in 'boardcfg.h'!"
//#endif
//
//#ifndef INCLUDE_TTY
//# error "Please define 'INCLUDE_TTY' in 'boardcfg.h'!"
//#endif
//
//#ifndef INCLUDE_SHELL
//# error "Please define 'INCLUDE_SHELL' in 'boardcfg.h'!"
//#endif
//
//#ifndef ROOT_STACK_SIZE
//# error "Please define 'ROOT_STACK_SIZE' in 'boardcfg.h'!"
//#endif
//
//#ifndef INCLUDE_DMN
//# error "Please define 'INCLUDE_DMN' in 'boardcfg.h'!"
//#endif
//
//#ifndef INCLUDE_LOGMSG
//# error "Please define 'INCLUDE_LOGMSG' in 'boardcfg.h'!"
//#endif

#endif /* __BSPCFG_H__ */
/*-----------------------------End of bspcfg.h-------------------------------*/

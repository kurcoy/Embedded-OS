/*
*********************************************************************************************************
*                                                uC/OS-II
*                                          The Real-Time Kernel
*
*                           (c) Copyright 1992-1999, Jean J. Labrosse, Weston, FL
*                                           All Rights Reserved
*
*                                           MASTER INCLUDE FILE
									changed by 文佳
*********************************************************************************************************
*/

#include    <stdio.h>
#include    <string.h>
#include    <ctype.h>
#include    <stdlib.h>
#include	<conio.h>
#include	<windows.h>
#include	<mmsystem.h>	//包含时钟函数的头文件，需要windows.h的支持
//#include   <graphics.h>		// 这样引用 EasyX 图形库


/*!< Signed integer types  */
typedef   signed char     int8_t;
typedef   signed short    int16_t;
typedef   signed long     int32_t;

/*!< Unsigned integer types  */
typedef unsigned char     uint8_t;
typedef unsigned short    uint16_t;
typedef unsigned long     uint32_t;

/*!< STM8 Standard Peripheral Library old types (maintained for legacy purpose) */

typedef int32_t  s32;
typedef int16_t s16;
typedef int8_t  s8;

typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t  u8;

typedef  unsigned char ubyte;

//typedef void Rtos_Task_t (void);

#define TASK(x)		void (x)(void)
#define ISR(x)		void x(void)

extern u32 Rtos_Timer ;

/**
 ******************************************************************************
 * @file       types.h
 * @brief      系统类型定义
 * @details    本文件定义系统中用到的所有使用的基本类型
 * @copyright Copyright(C)
 ******************************************************************************
 */

#ifndef _SXTYPES_H_
#define _SXTYPES_H_

/*-----------------------------------------------------------------------------
 Section: Includes
 ----------------------------------------------------------------------------*/
//#include <stdint.h>

/*-----------------------------------------------------------------------------
 Section: Macro Definitions
 ----------------------------------------------------------------------------*/
#ifndef OK
#define OK      0
#endif
#ifndef ERROR
#define ERROR   (-1)
#endif

#ifndef IMPORT
#define IMPORT  extern
#endif
#ifndef LOCAL
#define LOCAL   static
#endif
#ifndef FAST
#define FAST    register
#endif

//#ifndef BOOL
//#define BOOL  char
//#endif

//#ifndef bool
//#define bool  char
//#endif
//
#ifndef false
#define false   0
#endif

#ifndef true
#define true    1
#endif

#ifndef NULL
#define NULL ((void *)0)
#endif

#define __I     volatile const  /*!< defines 'read only' permissions      */
#define __O     volatile        /*!< defines 'write only' permissions     */
#define __IO    volatile        /*!< defines 'read / write' permissions   */

/*-----------------------------------------------------------------------------
 Section: Type Definitions
 ----------------------------------------------------------------------------*/
typedef char                    char_t;
typedef signed char             int8_t;
typedef signed short            int16_t;
typedef signed int              int32_t;
typedef signed long long        int64_t;
typedef unsigned char           uint8_t;
typedef unsigned short          uint16_t;
typedef unsigned int            uint32_t;
typedef unsigned long long      uint64_t;
typedef float                   float32_t;
typedef double                  float64_t;
typedef long double             float128_t;
typedef enum  /*boolean*/
{
   FALSE  = 0,
   TRUE   = 1
} bool_e;
typedef int                 status_t;

typedef unsigned char       byte;
typedef unsigned char       bits;
typedef unsigned char       uchar;
typedef float               float32;


typedef uint32_t     size_t;

typedef signed long time_t;

#define WAIT_FOREVER  ((uint32_t)0)

//#define FOREVER for (;;)

#define FAR

#ifdef __cplusplus
typedef void        (*OSFUNCPTR) (void *);     /* ptr to function returning int */
typedef int         (*FUNCPTR) (...);     /* ptr to function returning int */
typedef void        (*VOIDFUNCPTR) (...); /* ptr to function returning void */
typedef double      (*DBLFUNCPTR) (...);  /* ptr to function returning double*/
typedef float       (*FLTFUNCPTR) (...);  /* ptr to function returning float */
typedef void (*VOIDFUNCPTRBOOL)(boolean);

#else
typedef void        (*OSFUNCPTR) (void *);     /* ptr to function returning int */
typedef int         (*FUNCPTR) ();     /* ptr to function returning int */
typedef void        (*VOIDFUNCPTR) (); /* ptr to function returning void */
typedef double      (*DBLFUNCPTR) ();  /* ptr to function returning double*/
typedef float       (*FLTFUNCPTR) ();  /* ptr to function returning float */
typedef void (*VOIDFUNCPTRBOOL)(bool_e b);

#endif          /* _cplusplus */

#ifdef __CC_ARM                         /* ARM Compiler */
#define WEAK __weak
#elif defined (__IAR_SYSTEMS_ICC__)     /* for IAR Compiler */
#define WEAK __weak
#elif defined (__GNUC__)                /* GNU GCC Compiler */
#define WEAK __attribute__ ((weak))
#endif

#define MEM_ALIGNMENT                   4
#define MEM_ALIGN_SIZE(size) (((size) + MEM_ALIGNMENT - 1) & ~(MEM_ALIGNMENT-1))
#define MEM_ALIGN(addr) ((void *)(((uint32_t)(addr) + MEM_ALIGNMENT - 1) & ~(uint32_t)(MEM_ALIGNMENT-1)))

typedef union
{
    unsigned long longValue;
    unsigned char array[4];
    struct
    {
        unsigned short high, low;
    } shortValue;
    struct
    {
        unsigned char highest, higher, middle, low;
    } charValue;
} U_UINT32;

#endif /*_TYPES_H_ */

/*-----------------------------End of types.h--------------------------------*/

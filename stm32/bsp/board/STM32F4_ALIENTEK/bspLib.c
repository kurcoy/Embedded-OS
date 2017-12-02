/**
 ******************************************************************************
 * @file      bspLib.c
 * @brief     C Source file of bspLib.c.
 * @details   This file including all API functions's implement of bspLib.c.
 * @copyright  Copyright(C), JunGeGe
 ******************************************************************************
 */

/*-----------------------------------------------------------------------------
 Section: Includes
 ----------------------------------------------------------------------------*/
#include <bsp_config.h>
#if (BOARD_BUILD_VER == BOARD_STM32F4_ALENTEK)
#include "stm32f4xx_conf.h"

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
 * @brief   初始化bsp  //todo:使用汇编改写
 *          (a)锁住中断；
 *          (b)禁用Cache；
 *          (c)初始化处理器寄存器到一缺省值;(关闭内部看门狗,晶振设置）
 *          (d)使回溯失效；?
 *          (e)清除所有悬置中断；
 * @return  None
 ******************************************************************************
 */
void
bspHwInit(void)
{
//    CPU_IntDis();
//    bsp_close_watchdog();    //针对特殊芯片，需要关闭看门狗
    SystemInit();
}

void
Delay( volatile int nCount)     //简单的延时函数
{
    for(; nCount != 0; nCount--);
}

/*
 * 函数名：LED_GPIO_Config
 * 描述  ：配置LED用到的I/O口
 * 输入  ：无
 * 输出  ：无
 */
void
LED_GPIO_Config(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;

      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);//使能GPIOF时钟

      //GPIOF9,F10初始化设置
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;//LED0和LED1对应IO口
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
      GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
      GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
      GPIO_Init(GPIOF, &GPIO_InitStructure);//初始化GPIO

    GPIO_SetBits(GPIOF,GPIO_Pin_9 | GPIO_Pin_10);//GPIOF9,F10设置高，灯灭
}

void LED1(char a)
{
    if (a)
       {
           GPIO_SetBits(GPIOF, GPIO_Pin_9);
       }
       else
       {
           GPIO_ResetBits(GPIOF,GPIO_Pin_9);
       }

}

void LED2(char a)
{
    if (a)
       {
           GPIO_SetBits(GPIOF, GPIO_Pin_10);
       }
       else
       {
           GPIO_ResetBits(GPIOF,GPIO_Pin_10);
       }

}

void LED3(char a)
{
//    if (a)
//       {
//           GPIO_SetBits(GPIOC,GPIO_Pin_5);
//       }
//       else
//       {
//           GPIO_ResetBits(GPIOC,GPIO_Pin_5);
//       }

}
#endif
//
///*----------------------------bspLib.c--------------------------------*/

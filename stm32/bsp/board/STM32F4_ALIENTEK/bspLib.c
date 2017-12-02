///**
// ******************************************************************************
// * @file      bspLib.c
// * @brief     C Source file of bspLib.c.
// * @details   This file including all API functions's implement of bspLib.c.
// * @copyright  Copyright(C), JunGeGe
// ******************************************************************************
// */
//
///*-----------------------------------------------------------------------------
// Section: Includes
// ----------------------------------------------------------------------------*/
//#include "cpu/stm32f10x.h"
//#include "cpu/stm32f10x/system_stm32f10x.h"
//
///*-----------------------------------------------------------------------------
// Section: Type Definitions
// ----------------------------------------------------------------------------*/
///* NONE */
//
///*-----------------------------------------------------------------------------
// Section: Constant Definitions
// ----------------------------------------------------------------------------*/
///* NONE */
//
///*-----------------------------------------------------------------------------
// Section: Global Variables
// ----------------------------------------------------------------------------*/
///* NONE */
//
///*-----------------------------------------------------------------------------
// Section: Local Variables
// ----------------------------------------------------------------------------*/
///* NONE */
//
///*-----------------------------------------------------------------------------
// Section: Local Function Prototypes
// ----------------------------------------------------------------------------*/
///* NONE */
//
///*-----------------------------------------------------------------------------
// Section: Global Function Prototypes
// ----------------------------------------------------------------------------*/
///* NONE */
//
///*-----------------------------------------------------------------------------
// Section: Function Definitions
// ----------------------------------------------------------------------------*/
//
///**
// ******************************************************************************
// * @brief   初始化bsp  //todo:使用汇编改写
// *          (a)锁住中断；
// *          (b)禁用Cache；
// *          (c)初始化处理器寄存器到一缺省值;(关闭内部看门狗,晶振设置）
// *          (d)使回溯失效；?
// *          (e)清除所有悬置中断；
// * @return  None
// ******************************************************************************
// */
//void
//bspHwInit(void)
//{
////    CPU_IntDis();
////    bsp_close_watchdog();    //针对特殊芯片，需要关闭看门狗
//    SystemInit();
//}
//
//void
//Delay( volatile int nCount)     //简单的延时函数
//{
//    for(; nCount != 0; nCount--);
//}
//
///*
// * 函数名：LED_GPIO_Config
// * 描述  ：配置LED用到的I/O口
// * 输入  ：无
// * 输出  ：无
// */
//void
//LED_GPIO_Config(void)
//{
//    /*定义一个GPIO_InitTypeDef类型的结构体*/
//    GPIO_InitTypeDef GPIO_InitStructure;
//
//    /*开启GPIOC的外设时钟*/
//    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC, ENABLE);
//
//    /*选择要控制的GPIOC引脚*/
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
//
//    /*设置引脚模式为通用推挽输出*/
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//
//    /*设置引脚速率为50MHz */
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//
//    /*调用库函数，初始化GPIOC*/
//    GPIO_Init(GPIOC, &GPIO_InitStructure);
//
//    /* 关闭所有led灯 */
//    GPIO_SetBits(GPIOC, GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5);
//}
//
//void LED1(char a)
//{
//    if (a)
//    {
//        GPIO_SetBits(GPIOC,GPIO_Pin_3);
//    }
//    else
//    {
//        GPIO_ResetBits(GPIOC,GPIO_Pin_3);
//    }
//}
//
//void LED2(char a)
//{
//    if (a)
//       {
//           GPIO_SetBits(GPIOC,GPIO_Pin_4);
//       }
//       else
//       {
//           GPIO_ResetBits(GPIOC,GPIO_Pin_4);
//       }
//
//}
//
//void LED3(char a)
//{
//    if (a)
//       {
//           GPIO_SetBits(GPIOC,GPIO_Pin_5);
//       }
//       else
//       {
//           GPIO_ResetBits(GPIOC,GPIO_Pin_5);
//       }
//
//}
//
///*----------------------------bspLib.c--------------------------------*/

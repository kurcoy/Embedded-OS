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
 * @brief   ��ʼ��bsp  //todo:ʹ�û���д
 *          (a)��ס�жϣ�
 *          (b)����Cache��
 *          (c)��ʼ���������Ĵ�����һȱʡֵ;(�ر��ڲ����Ź�,�������ã�
 *          (d)ʹ����ʧЧ��?
 *          (e)������������жϣ�
 * @return  None
 ******************************************************************************
 */
void
bspHwInit(void)
{
//    CPU_IntDis();
//    bsp_close_watchdog();    //�������оƬ����Ҫ�رտ��Ź�
    SystemInit();
}

void
Delay( volatile int nCount)     //�򵥵���ʱ����
{
    for(; nCount != 0; nCount--);
}

/*
 * ��������LED_GPIO_Config
 * ����  ������LED�õ���I/O��
 * ����  ����
 * ���  ����
 */
void
LED_GPIO_Config(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;

      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);//ʹ��GPIOFʱ��

      //GPIOF9,F10��ʼ������
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;//LED0��LED1��ӦIO��
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
      GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
      GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
      GPIO_Init(GPIOF, &GPIO_InitStructure);//��ʼ��GPIO

    GPIO_SetBits(GPIOF,GPIO_Pin_9 | GPIO_Pin_10);//GPIOF9,F10���øߣ�����
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

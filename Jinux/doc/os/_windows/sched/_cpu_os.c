/**
 ******************************************************************************
 * @file       _cpu_os.c
 * @version    V1.1.4
 * @brief      API C source file of _cpu_os.c
 *             Created on: 2016-9-21
 *             Author: wenrenjinjun
 * @details    This file including all API functions's implement of dps.
 * @copy       Copyrigth(C), 2008-2012,Sanxing Electric Co.,Ltd.
 *
 ******************************************************************************
 */
#include "_cpu_os.h"

void
CPU_IntSrcPrioSet (
        CPU_INT08U  pos,
        CPU_INT08U  prio)
{

}

void
CPU_IntSrcEn (
        CPU_INT08U  pos)
{

}

void
CPU_IntSrcDis(
        CPU_INT08U  pos)
{

}


CPU_SR
CPU_SR_Save(
        void)
{
    return 0;
}

void
CPU_SR_Restore(
        CPU_SR cpu_sr)
{

}
//
void
CPU_IntDis(void)
{

}

void
CPU_IntEn(void)
{

}

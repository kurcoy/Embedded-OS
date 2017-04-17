/**
 ******************************************************************************
 * @file      startup.c
 * @brief     �ں��ж�������.
 * @details   This file including all API functions's implement of startup.c.
 * @copyright Copyright(C), 2015-2020,Sanxing Medical & Electric Co.,Ltd.
 ******************************************************************************
 */

/*-----------------------------------------------------------------------------
 Section: Includes
 ----------------------------------------------------------------------------*/
#include <types.h>
//#include <oscfg.h>
//#include <bspLib.h>
//#include <intLib.h>

/*-----------------------------------------------------------------------------
 Section: Macro Definitions
 ----------------------------------------------------------------------------*/
/*None*/

/*-----------------------------------------------------------------------------
 Section: Type Definitions
 ----------------------------------------------------------------------------*/
/*None*/

/*-----------------------------------------------------------------------------
 Section: Global Variables
 ----------------------------------------------------------------------------*/
//extern char heap_low; /* Defined by the linker */
//extern char cstack_top;

/*-----------------------------------------------------------------------------
 Section: Global Function Prototypes
 ----------------------------------------------------------------------------*/
extern void
rootTask_create(void);

/*-----------------------------------------------------------------------------
 Section: Function Definitions
 ----------------------------------------------------------------------------*/
/**
 ******************************************************************************
 * @brief   usrInit
 *          1������intLibInit
 *          ��ʼ������ϵͳ��ȱʡ�ж�������
 *
 *          2������sysHwInit
 *
 *          3�� ����__OS_Init()
 *          OS��ʼ��
 *
 *          4��  ���� rootTask_create()
 *          ����������
 *
 *          5��  __OS_Start()
 *          OS����
 *
 * @return  None
 ******************************************************************************
 */
int
#if defined (__IAR_SYSTEMS_ICC__)     /* for IAR Compiler */
main(void)
#else
usrInit(void)
#endif
{
#if 0
    memlib_init((uint32_t)&heap_low, (uint32_t)(&cstack_top - 0x200));
#endif

//    (void)intLibInit();
//
//    sysHwInit();
//
//    __OS_Init();
//
//    rootTask_create();
//
//    __OS_Start();

    return 0;
}

/**
 ******************************************************************************
 * @brief   ��λ�ж����
 *          resetRoutine()
 *
 *          1������bspHwInit
 *          (a)��ס�жϣ�
 *          (b)����Cache��
 *          (c)��ʼ���������Ĵ�����һȱʡֵ;(�ر��ڲ����Ź�,�������ã�
 *          (d)ʹ����ʧЧ��?
 *          (e)������������жϣ�
 *
 *          2����data�γ�ʼ����
 *          3����bss�����㣻
 *
 *          4������usrInit
 *
 * @return  None
 ******************************************************************************
 */
#if __CORE_SELECTION_ != CORE_WINDOWS
void
resetRoutine(void)
{
    bspHwInit();

#if defined (__IAR_SYSTEMS_ICC__)     /* for IAR Compiler */
    extern void __iar_program_start(void);
    __iar_program_start();
#elif defined (__GNUC__)                /* GNU GCC Compiler */
    // Copy the data segment initializers from flash to SRAM.
    extern unsigned long _sidata;
    extern unsigned long _data;
    extern unsigned long _edata;

    unsigned long *pulSrc, *pulDest;

    pulSrc = &_sidata;
    for (pulDest = &_data; pulDest < &_edata;)
    {
        *pulDest++ = *pulSrc++;
    }

#if 0
    // Zero fill the bss segment.
    extern unsigned long _bss;
    extern unsigned long _ebss;
    for(pulDest = &_bss; pulDest < &_ebss; )
    {
        *pulDest++ = 0;
    }
#else
    /* Zero fill the bss segment. */
    __asm(" ldr r0, =_bss\n"
            " ldr r1, =_ebss\n"
            " mov r2, #0\n"
            " .thumb_func\n"
            " zero_loop:\n"
            " cmp r0, r1\n"
            " it lt\n"
            " strlt r2, [r0], #4\n"
            " blt zero_loop");
#endif
    usrInit();
#endif /* defined (__GNUC__)*/

}
#endif

/**
 ******************************************************************************
 * @brief   ��λ�ж����
 *          resetRoutine()
 *
 *          1������bspHwInit
 *          (a)��ס�жϣ�
 *          (b)����Cache��
 *          (c)��ʼ���������Ĵ�����һȱʡֵ;(�ر��ڲ����Ź�,�������ã�
 *          (d)ʹ����ʧЧ��?
 *          (e)������������жϣ�
 *
 *          2����data�γ�ʼ����
 *          3����bss�����㣻
 *
 *          4������usrInit
 *
 * @return  None
 ******************************************************************************
 */
//#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <test.h>
#include <task.h>
#include <shell.h>
#include <windows.h>


int
main(
        int argc,
        char* argv[],
        char *envp[])
{
//    bspHwInit();
//    usrInit();

    puts("_______________start_________________________");
    // __DO_WHITEBOX_TEST();
    puts("_______________end_________________________");
    extern status_t
    shell_init(void);
    shell_init();

    while(1);
    {
       Sleep(1000);
    }
    return EXIT_SUCCESS;
}

static uint32_t
do_reboot(cmd_tbl_t * cmdtp,
        uint32_t argc,
        const uint8_t *argv[])
{
    //bsp_reboot();
    printf("reboot\n");
    return 1;
}

SHELL_CMD(
    reboot, CFG_MAXARGS, (SHELL_CMD_FUNCPTR)do_reboot,
    "reboot \n"
);


#ifdef __WHITEBOX_TEST

__INIT_SUITE(main)   {return 0;}
__CLEAN_SUITE(main)  {return 0;}

__IMPLEMENT_TEST(test)
{
    CU_PASS("just for test...");
}

__BEGIN_TESTMAP_OF_SUITE(main)
    __REG_TEST(test)
__END_TESTMAP()

#endif

/*------------------------------ startup.c ----------------------------------*/

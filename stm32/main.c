/**
 ******************************************************************************
 * @file       main.c
 * @version    V0.0.1
 * @brief      bootloader������.
 * @details    
 * @copyright   Copyright(C), 2008-2013,Sanxing Electric Co.,Ltd.
 ******************************************************************************
 */
/*-----------------------------------------------------------------------------
 Section: Includes
 ----------------------------------------------------------------------------*/
//#include <config.h>
#include <types.h>
//#include <lib.h>
//#include <bsp.h>

/*-----------------------------------------------------------------------------
 Section: Type Definitions
 ----------------------------------------------------------------------------*/
/* None */

/*-----------------------------------------------------------------------------
 Section: Private Function Prototypes
 ----------------------------------------------------------------------------*/
void reset_routine(void);
static void default_routine(void);
static void dummy(void);
static void systick_routine(void);
static void jump_to_app(void);
static void sxmain(void);
static void hd_feed(void);

/*-----------------------------------------------------------------------------
 Section: Globals
 ----------------------------------------------------------------------------*/
extern uint32_t _etext; //The end of text;
extern uint32_t _bss;   //The start of bss;
extern uint32_t _ebss;
extern uint32_t _data;
extern uint32_t _edata;

/*-----------------------------------------------------------------------------
 Section: Private Variables
 ----------------------------------------------------------------------------*/
static uint32_t the_cstack[1024 * 10];

__attribute__((section(".isr_vector")))
const VOIDFUNCPTR vector_table[] =
{
    (VOIDFUNCPTR)((uint32_t)the_cstack + sizeof(the_cstack)),/* ջ��ָ�� */
    reset_routine,      /* ��λ�ж�  */
    default_routine,    /* NMI�ж� */
    default_routine,    /* Ӳ������ */
    default_routine,    /* �洢��������� */
    default_routine,    /* ���ߴ��� */
    default_routine,    /* �÷����� */
    dummy, /* ���� */
    dummy, /* ���� */
    dummy, /* ���� */
    dummy, /* ���� */
    dummy, /* ���� */
    dummy, /* ���� */
    dummy, /* ���� */
    dummy, /* ���� */
    dummy,// systick_routine, /* 15ϵͳ��ʱ�� */
};

/*-----------------------------------------------------------------------------
 Section: Constant Definitions
 ----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Section: Global Variables
 ----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Section: Local Variables
 ----------------------------------------------------------------------------*/
static volatile uint32_t systime = 0u; /* ����ʱ��(ms) */

/*-----------------------------------------------------------------------------
 Section: Import Function Prototypes
 ----------------------------------------------------------------------------*/
extern status_t
uart_check(void);

extern bool_e
is_in_cmd_proc(void);

extern bool_e
is_in_flash_proc(void);

extern status_t
flash_check(void);

/*-----------------------------------------------------------------------------
 Section: Local Function Prototypes
 ----------------------------------------------------------------------------*/
static void
show_ver(void);

static void
light_shine(void);

/*-----------------------------------------------------------------------------
 Section: Function Definitions
 ----------------------------------------------------------------------------*/
/**
 ******************************************************************************
 * @brief   ��λ�ж����
 * @return  None
 ******************************************************************************
 */
void
reset_routine(void)
{
    uint32_t *pul_src;
    uint32_t *pul_dest;

    /* �����渴�Ƴ�ʼ�����ݶε�SRAM��. */
    for (pul_dest = &_data, pul_src = &_etext; pul_dest < &_edata;)
    {
        *pul_dest++ = *pul_src++;
    }

    /* bss������ */
    for (pul_dest = &_bss; pul_dest < &_ebss;)
    {
        *pul_dest++ = 0;
    }

    /* ��ת�������� */
    sxmain();
}

/**
 ******************************************************************************
 * @brief   �쳣�ж����
 * @return  None
 ******************************************************************************
 */
static void
default_routine(void)
{
    while (TRUE)
    {
    }
}

/**
 ******************************************************************************
 * @brief   �����ж����
 * @return  None
 ******************************************************************************
 */
static void
dummy(void)
{
    return;
}

/**
 ******************************************************************************
 * @brief   boot������
 * @return  None
 ******************************************************************************
 */
static void
sxmain(void)
{


//    hw_init();      /* Ӳ����ʼ�� */
//    show_ver();     /* ��ӡ �汾��Ϣ */
//    uart_check();   /* ��⴮�� */
//    flash_check();  /* ���flash */
//    hw_deinit();    /* �ָ�Ӳ��״̬ */

    jump_to_app();  /* ��ת��Ӧ�ó��� */
}

/**
 ******************************************************************************
 * @brief   ��ת��Ӧ��
 * @return  None
 ******************************************************************************
 */
static void
jump_to_app(void)
{
//    if (((*(__IO uint32_t*)APP_START_ADDRESS) & 0x2FFC0000) == 0x20000000)
//    {
////        print("Enter application ...\n");
//        __asm("mov r2, %0"::"r"(APP_START_ADDRESS) : "%r2");
//        __asm("ldr r2, [r2, #0]");
//        __asm("mov r0, r2");
//        __asm("msr   MSP, r0");
//
//        __asm("mov r3, %0"::"r"(APP_START_ADDRESS + 4) : "%r3");
//        __asm("ldr r3, [r3, #0]");
//        __asm("mov r0, r3");
//        __asm("bx r0");
//    }
//    print("No app\n");

    while (1);
}

/**
 ******************************************************************************
 * @brief   ��ʱ���жϴ���
 * @return  None
 * @note    ע�⣺�ж�����Ҫ��Ϊ1����
 ******************************************************************************
 */
//static void
//systick_routine(void)
//{
//    systime++;     /* ����ϵͳʱ�� */
//
//    light_shine(); /* ��˸�ƹ� */
//
//    hd_feed();     /* Ӳ��ι�� */
//}

///**
// ******************************************************************************
// * @brief   ��ӡ�汾��Ϣ
// *
// * @return  None
// ******************************************************************************
// */
//static void
//show_ver(void)
//{
//    print("\n\033[H\033[J"
//            "BootLoader Version: "VERSION"\n"
//            "MCU: "MCU_NAME"\n"
//            "APP Size: "APP_SIZE_STR"\n"
//            "Build Time: "__DATE__" "__TIME__"\n\n");
//}

///**
// ******************************************************************************
// * @brief   ����ַ�
// * @return  None
// ******************************************************************************
// */
//void
//put_char(const char_t c)
//{
//    if (c == '\n')
//    {
//        the_uart_drv.send('\r');
//    }
//    the_uart_drv.send(c);
//}

/**
 ******************************************************************************
 * @brief   ��ȡtimer
 *
 * @return  None
 ******************************************************************************
 */
//uint32
//timerGet(void)
//{
//    return systime;
//}

/**
 ******************************************************************************
 * @brief   LCD������˸
 *
 * @return  None
 ******************************************************************************
 */
//static void
//light_shine(void)
//{
//    static bool_e lit = FALSE;
//    static uint32 last_shine = 0;
//
//    if ((is_in_cmd_proc() == FALSE) && (is_in_flash_proc() == FALSE))
//    {
//        the_sys_drv.light_ctrl(FALSE);
//        return;
//    }
//    if (timerGet() - last_shine < 100)
//    {
//        return;
//    }
//
//    if (is_in_cmd_proc() == TRUE)
//    {
//        the_sys_drv.light_ctrl(lit);
//    }
//
//    if (is_in_flash_proc() == TRUE)
//    {
//        if (the_sys_drv.light_flash)
//        {
//            the_sys_drv.light_flash(lit);
//        }
//    }
//
//    last_shine = timerGet();
//    lit = !lit;
//}

/**
 ******************************************************************************
 * @brief   ιӲ����
 *
 * @return  None
 ******************************************************************************
 */
//static void
//hd_feed(void)
//{
//    static bool_e state = FALSE;
//
//    /* ����2���Ӳ���ι�� */
//    if (timerGet() > 2 * 60 * 1000)
//    {
//        //��λоƬ
//        the_sys_drv.mcu_reset();
//        return;
//    }
//    the_sys_drv.hd_feed(state);
//    state = !state;
//}

/*--------------------------------End of main.c------------------------------*/

/**
 ******************************************************************************
 * @file       main.c
 * @version    V0.0.1
 * @brief      bootloader主程序.
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
    (VOIDFUNCPTR)((uint32_t)the_cstack + sizeof(the_cstack)),/* 栈顶指针 */
    reset_routine,      /* 复位中断  */
    default_routine,    /* NMI中断 */
    default_routine,    /* 硬件错误 */
    default_routine,    /* 存储器管理错误 */
    default_routine,    /* 总线错误 */
    default_routine,    /* 用法错误 */
    dummy, /* 空闲 */
    dummy, /* 空闲 */
    dummy, /* 空闲 */
    dummy, /* 空闲 */
    dummy, /* 空闲 */
    dummy, /* 空闲 */
    dummy, /* 空闲 */
    dummy, /* 空闲 */
    dummy,// systick_routine, /* 15系统定时器 */
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
static volatile uint32_t systime = 0u; /* 运行时间(ms) */

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
 * @brief   复位中断入口
 * @return  None
 ******************************************************************************
 */
void
reset_routine(void)
{
    uint32_t *pul_src;
    uint32_t *pul_dest;

    /* 从闪存复制初始化数据段到SRAM中. */
    for (pul_dest = &_data, pul_src = &_etext; pul_dest < &_edata;)
    {
        *pul_dest++ = *pul_src++;
    }

    /* bss段清零 */
    for (pul_dest = &_bss; pul_dest < &_ebss;)
    {
        *pul_dest++ = 0;
    }

    /* 跳转到主程序 */
    sxmain();
}

/**
 ******************************************************************************
 * @brief   异常中断入口
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
 * @brief   空闲中断入口
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
 * @brief   boot主程序
 * @return  None
 ******************************************************************************
 */
static void
sxmain(void)
{


//    hw_init();      /* 硬件初始化 */
//    show_ver();     /* 打印 版本信息 */
//    uart_check();   /* 检测串口 */
//    flash_check();  /* 检查flash */
//    hw_deinit();    /* 恢复硬件状态 */

    jump_to_app();  /* 跳转到应用程序 */
}

/**
 ******************************************************************************
 * @brief   跳转到应用
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
 * @brief   定时器中断处理
 * @return  None
 * @note    注意：中断周期要求为1毫秒
 ******************************************************************************
 */
//static void
//systick_routine(void)
//{
//    systime++;     /* 更新系统时间 */
//
//    light_shine(); /* 闪烁灯光 */
//
//    hd_feed();     /* 硬件喂狗 */
//}

///**
// ******************************************************************************
// * @brief   打印版本信息
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
// * @brief   输出字符
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
 * @brief   获取timer
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
 * @brief   LCD背光闪烁
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
 * @brief   喂硬件狗
 *
 * @return  None
 ******************************************************************************
 */
//static void
//hd_feed(void)
//{
//    static bool_e state = FALSE;
//
//    /* 超过2分钟不再喂狗 */
//    if (timerGet() > 2 * 60 * 1000)
//    {
//        //复位芯片
//        the_sys_drv.mcu_reset();
//        return;
//    }
//    the_sys_drv.hd_feed(state);
//    state = !state;
//}

/*--------------------------------End of main.c------------------------------*/

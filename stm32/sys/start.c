/**
 ******************************************************************************
 * @file      start.c
 * @brief     C Source file of start.c.
 * @details   This file including all API functions's implement of start.c.	
 * @copyright  Copyright(C), JunGeGe
 ******************************************************************************
 */
 
/*-----------------------------------------------------------------------------
 Section: Includes
 ----------------------------------------------------------------------------*/
#include <types.h>

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
extern uint32_t _etext; //The end of text;
extern uint32_t _bss;   //The start of bss;
extern uint32_t _ebss;
extern uint32_t _data;
extern uint32_t _edata;


/*-----------------------------------------------------------------------------
 Section: Local Function Prototypes
 ----------------------------------------------------------------------------*/
void reset_routine(void);
static void default_routine(void);
static void dummy(void);

void __attribute__((weak))
Default_Handler(void);

// Forward declaration of the specific IRQ handlers. These are aliased
// to the Default_Handler, which is a 'forever' loop. When the application
// defines a handler (with the same name), this will automatically take
// precedence over these weak definitions

void __attribute__ ((weak, alias ("Default_Handler")))
WWDG_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
PVD_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
TAMP_STAMP_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
RTC_WKUP_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
FLASH_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
RCC_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
EXTI0_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
EXTI1_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
EXTI2_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
EXTI3_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
EXTI4_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
DMA1_Stream0_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
DMA1_Stream1_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
DMA1_Stream2_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
DMA1_Stream3_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
DMA1_Stream4_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
DMA1_Stream5_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
DMA1_Stream6_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
ADC_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
CAN1_TX_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
CAN1_RX0_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
CAN1_RX1_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
CAN1_SCE_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
EXTI9_5_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
TIM1_BRK_TIM9_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
TIM1_UP_TIM10_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
TIM1_TRG_COM_TIM11_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
TIM1_CC_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
TIM2_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
TIM3_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
TIM4_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
I2C1_EV_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
I2C1_ER_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
I2C2_EV_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
I2C2_ER_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
SPI1_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
SPI2_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
USART1_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
USART2_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
USART3_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
EXTI15_10_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
RTC_Alarm_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
OTG_FS_WKUP_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
TIM8_BRK_TIM12_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
TIM8_UP_TIM13_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
TIM8_TRG_COM_TIM14_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
TIM8_CC_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
DMA1_Stream7_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
FMC_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
SDIO_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
TIM5_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
SPI3_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
UART4_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
UART5_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
TIM6_DAC_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
TIM7_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
DMA2_Stream0_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
DMA2_Stream1_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
DMA2_Stream2_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
DMA2_Stream3_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
DMA2_Stream4_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
ETH_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
ETH_WKUP_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
CAN2_TX_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
CAN2_RX0_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
CAN2_RX1_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
CAN2_SCE_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
OTG_FS_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
DMA2_Stream5_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
DMA2_Stream6_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
DMA2_Stream7_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
USART6_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
I2C3_EV_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
I2C3_ER_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
OTG_HS_EP1_OUT_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
OTG_HS_EP1_IN_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
OTG_HS_WKUP_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
OTG_HS_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
DCMI_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
HASH_RNG_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
FPU_IRQHandler(void);


/*-----------------------------------------------------------------------------
 Section: Local Variables
 ----------------------------------------------------------------------------*/
//static uint32_t the_cstack[1024 * 10];
//
//__attribute__((section(".isr_vector")))
//const VOIDFUNCPTR vector_table[] =
//{
//    (VOIDFUNCPTR)((uint32_t)the_cstack + sizeof(the_cstack)),/* 栈顶指针 */
//    reset_routine,      /* 复位中断  */
//    default_routine,    /* NMI中断 */
//    default_routine,    /* 硬件错误 */
//    default_routine,    /* 存储器管理错误 */
//    default_routine,    /* 总线错误 */
//    default_routine,    /* 用法错误 */
//    dummy, /* 空闲 */
//    dummy, /* 空闲 */
//    dummy, /* 空闲 */
//    dummy, /* 空闲 */
//    dummy, /* 空闲 */
//    dummy, /* 空闲 */
//    dummy, /* 空闲 */
//    dummy, /* 空闲 */
//    dummy,// systick_routine, /* 15系统定时器 */
//    dummy, dummy,dummy,dummy,dummy,dummy, dummy,dummy,dummy,dummy,
//    dummy, dummy,dummy,dummy,dummy,dummy, dummy,dummy,dummy,dummy,
//    dummy, dummy,dummy,dummy,dummy,dummy, dummy,dummy,dummy,dummy,
//    dummy, dummy,dummy,dummy,dummy,dummy, dummy,dummy,dummy,dummy,
//    dummy, dummy,dummy,dummy,dummy,dummy, dummy,dummy,dummy,dummy,
//    dummy, dummy,dummy,dummy,dummy,dummy, dummy,dummy,dummy,dummy,
//    dummy, dummy,dummy,dummy,dummy,dummy, dummy,dummy,dummy,dummy,
//    dummy, dummy,dummy,dummy,dummy,dummy, dummy,dummy,dummy,dummy,
//    dummy, dummy,dummy,dummy,dummy,dummy, dummy,dummy,dummy,dummy,
//    dummy, dummy,dummy,dummy,dummy,dummy, dummy,dummy,dummy,dummy,
//};
void
Reset_Handler(void);
extern unsigned int cstack_top;//_estack;

typedef void
(* const pHandler)(void);

__attribute__ ((section(".isr_vector"),used))
pHandler __isr_vectors[] =
  {
    // Cortex-M Core Handlers
    (pHandler) &cstack_top,               // The initial stack pointer
    Reset_Handler,                     // The reset handler

    WWDG_IRQHandler,//NMI_Handler,                       // The NMI handler
    WWDG_IRQHandler,//HardFault_Handler,                 // The hard fault handler

#if defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7EM__)
    WWDG_IRQHandler,//MemManage_Handler,                 // The MPU fault handler
    WWDG_IRQHandler,//BusFault_Handler,                  // The bus fault handler
    WWDG_IRQHandler,//UsageFault_Handler,                // The usage fault handler
#else
    0,                                 // Reserved
    0,                                 // Reserved
    0,                                 // Reserved
#endif
    0,                                 // Reserved
    0,                                 // Reserved
    0,                                 // Reserved
    0,                                 // Reserved
    WWDG_IRQHandler,//SVC_Handler,                       // SVCall handler
#if defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7EM__)
    WWDG_IRQHandler,//DebugMon_Handler,                  // Debug monitor handler
#else
    0,                                 // Reserved
#endif
    0,                                 // Reserved
    WWDG_IRQHandler,//PendSV_Handler,                    // The PendSV handler
    WWDG_IRQHandler,//SysTick_Handler,                   // The SysTick handler

    // ----------------------------------------------------------------------
    // External Interrupts
    WWDG_IRQHandler,                   // Window WatchDog
    PVD_IRQHandler,                    // PVD through EXTI Line detection
    TAMP_STAMP_IRQHandler,             // Tamper and TimeStamps through the EXTI line
    RTC_WKUP_IRQHandler,               // RTC Wakeup through the EXTI line
    FLASH_IRQHandler,                  // FLASH
    RCC_IRQHandler,                    // RCC
    EXTI0_IRQHandler,                  // EXTI Line0
    EXTI1_IRQHandler,                  // EXTI Line1
    EXTI2_IRQHandler,                  // EXTI Line2
    EXTI3_IRQHandler,                  // EXTI Line3
    EXTI4_IRQHandler,                  // EXTI Line4
    DMA1_Stream0_IRQHandler,           // DMA1 Stream 0
    DMA1_Stream1_IRQHandler,           // DMA1 Stream 1
    DMA1_Stream2_IRQHandler,           // DMA1 Stream 2
    DMA1_Stream3_IRQHandler,           // DMA1 Stream 3
    DMA1_Stream4_IRQHandler,           // DMA1 Stream 4
    DMA1_Stream5_IRQHandler,           // DMA1 Stream 5
    DMA1_Stream6_IRQHandler,           // DMA1 Stream 6
    ADC_IRQHandler,                    // ADC1, ADC2 and ADC3s
    CAN1_TX_IRQHandler,                // CAN1 TX
    CAN1_RX0_IRQHandler,               // CAN1 RX0
    CAN1_RX1_IRQHandler,               // CAN1 RX1
    CAN1_SCE_IRQHandler,               // CAN1 SCE
    EXTI9_5_IRQHandler,                // External Line[9:5]s
    TIM1_BRK_TIM9_IRQHandler,          // TIM1 Break and TIM9
    TIM1_UP_TIM10_IRQHandler,          // TIM1 Update and TIM10
    TIM1_TRG_COM_TIM11_IRQHandler,     // TIM1 Trigger and Commutation and TIM11
    TIM1_CC_IRQHandler,                // TIM1 Capture Compare
    TIM2_IRQHandler,                   // TIM2
    TIM3_IRQHandler,                   // TIM3
    TIM4_IRQHandler,                   // TIM4
    I2C1_EV_IRQHandler,                // I2C1 Event
    I2C1_ER_IRQHandler,                // I2C1 Error
    I2C2_EV_IRQHandler,                // I2C2 Event
    I2C2_ER_IRQHandler,                // I2C2 Error
    SPI1_IRQHandler,                   // SPI1
    SPI2_IRQHandler,                   // SPI2
    USART1_IRQHandler,                 // USART1
    USART2_IRQHandler,                 // USART2
    USART3_IRQHandler,                 // USART3
    EXTI15_10_IRQHandler,              // External Line[15:10]s
    RTC_Alarm_IRQHandler,              // RTC Alarm (A and B) through EXTI Line
    OTG_FS_WKUP_IRQHandler,            // USB OTG FS Wakeup through EXTI line
    TIM8_BRK_TIM12_IRQHandler,         // TIM8 Break and TIM12
    TIM8_UP_TIM13_IRQHandler,          // TIM8 Update and TIM13
    TIM8_TRG_COM_TIM14_IRQHandler,     // TIM8 Trigger and Commutation and TIM14
    TIM8_CC_IRQHandler,                // TIM8 Capture Compare
    DMA1_Stream7_IRQHandler,           // DMA1 Stream7
    FMC_IRQHandler,                    // FMC
    SDIO_IRQHandler,                   // SDIO
    TIM5_IRQHandler,                   // TIM5
    SPI3_IRQHandler,                   // SPI3
    UART4_IRQHandler,                  // UART4
    UART5_IRQHandler,                  // UART5
    TIM6_DAC_IRQHandler,               // TIM6 and DAC1&2 underrun errors
    TIM7_IRQHandler,                   // TIM7
    DMA2_Stream0_IRQHandler,           // DMA2 Stream 0
    DMA2_Stream1_IRQHandler,           // DMA2 Stream 1
    DMA2_Stream2_IRQHandler,           // DMA2 Stream 2
    DMA2_Stream3_IRQHandler,           // DMA2 Stream 3
    DMA2_Stream4_IRQHandler,           // DMA2 Stream 4
    ETH_IRQHandler,                    // Ethernet
    ETH_WKUP_IRQHandler,               // Ethernet Wakeup through EXTI line
    CAN2_TX_IRQHandler,                // CAN2 TX
    CAN2_RX0_IRQHandler,               // CAN2 RX0
    CAN2_RX1_IRQHandler,               // CAN2 RX1
    CAN2_SCE_IRQHandler,               // CAN2 SCE
    OTG_FS_IRQHandler,                 // USB OTG FS
    DMA2_Stream5_IRQHandler,           // DMA2 Stream 5
    DMA2_Stream6_IRQHandler,           // DMA2 Stream 6
    DMA2_Stream7_IRQHandler,           // DMA2 Stream 7
    USART6_IRQHandler,                 // USART6
    I2C3_EV_IRQHandler,                // I2C3 event
    I2C3_ER_IRQHandler,                // I2C3 error
    OTG_HS_EP1_OUT_IRQHandler,         // USB OTG HS End Point 1 Out
    OTG_HS_EP1_IN_IRQHandler,          // USB OTG HS End Point 1 In
    OTG_HS_WKUP_IRQHandler,            // USB OTG HS Wakeup through EXTI
    OTG_HS_IRQHandler,                 // USB OTG HS
    DCMI_IRQHandler,                   // DCMI
    0,                                 // Reserved
    HASH_RNG_IRQHandler,               // Hash and Rng
    FPU_IRQHandler,                    // FPU
};




/*-----------------------------------------------------------------------------
 Section: Global Function Prototypes
 ----------------------------------------------------------------------------*/
void
main(void);

extern void
bspHwInit(void);

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
Reset_Handler(void)
{
    bspHwInit();//上电需要立刻初始化的硬件

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
    main();
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

// ----------------------------------------------------------------------------

// Processor ends up here if an unexpected interrupt occurs or a
// specific handler is not present in the application code.
// When in DEBUG, trigger a debug exception to clearly notify
// the user of the exception and help identify the cause.

void __attribute__ ((section(".after_vectors")))
Default_Handler(void)
{
#if defined(DEBUG)
__DEBUG_BKPT();
#endif
while (1)
  {
  }
}



/**
 ******************************************************************************
 * @brief   boot主程序
 * @return  None
 ******************************************************************************
 */

/*----------------------------start.c--------------------------------*/

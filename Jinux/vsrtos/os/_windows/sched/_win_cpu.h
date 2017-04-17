
#ifndef  OS_CPU_H
#define  OS_CPU_H

typedef unsigned char  BOOLEAN;
typedef unsigned char  INT8U;                    /* Unsigned  8 bit quantity                           */
typedef signed   char  INT8S;                    /* Signed    8 bit quantity                           */
typedef unsigned short INT16U;                   /* Unsigned 16 bit quantity                           */
typedef signed   short INT16S;                   /* Signed   16 bit quantity                           */
typedef unsigned int   INT32U;                   /* Unsigned 32 bit quantity                           */
typedef signed   int   INT32S;                   /* Signed   32 bit quantity                           */
typedef float          FP32;                     /* Single precision floating point                    */
typedef double         FP64;                     /* Double precision floating point                    */

typedef unsigned int   OS_STK;                   /* Each stack entry is 32-bit wide                    */
typedef unsigned int   OS_CPU_SR;                /* Define size of CPU status register (PSR = 32 bits) */


typedef enum IRQn
{
/******  Cortex-M3 Processor Exceptions Numbers ****************************************************************/
  NonMaskableInt_IRQn         = -14,    /*!< 2 Non Maskable Interrupt                                          */
  MemoryManagement_IRQn       = -12,    /*!< 4 Cortex-M3 Memory Management Interrupt                           */
  BusFault_IRQn               = -11,    /*!< 5 Cortex-M3 Bus Fault Interrupt                                   */
  UsageFault_IRQn             = -10,    /*!< 6 Cortex-M3 Usage Fault Interrupt                                 */
  SVCall_IRQn                 = -5,     /*!< 11 Cortex-M3 SV Call Interrupt                                    */
  DebugMonitor_IRQn           = -4,     /*!< 12 Cortex-M3 Debug Monitor Interrupt                              */
  PendSV_IRQn                 = -2,     /*!< 14 Cortex-M3 Pend SV Interrupt                                    */
  SysTick_IRQn                = -1,     /*!< 15 Cortex-M3 System Tick Interrupt                                */
/******  STM32 specific Interrupt Numbers **********************************************************************/
  WWDG_IRQn                   = 16,      /*!< Window WatchDog Interrupt                                         */
//  PVD_IRQn                    = 1+16,      /*!< PVD through EXTI Line detection Interrupt                         */
//  TAMP_STAMP_IRQn             = 2+16,      /*!< Tamper and TimeStamp interrupts through the EXTI line             */
//  RTC_WKUP_IRQn               = 3+16,      /*!< RTC Wakeup interrupt through the EXTI line                        */
//  FLASH_IRQn                  = 4+16,      /*!< FLASH global Interrupt                                            */
//  RCC_IRQn                    = 5+16,      /*!< RCC global Interrupt                                              */
//  EXTI0_IRQn                  = 6+16,      /*!< EXTI Line0 Interrupt                                              */
//  EXTI1_IRQn                  = 7+16,      /*!< EXTI Line1 Interrupt                                              */
//  EXTI2_IRQn                  = 8+16,      /*!< EXTI Line2 Interrupt                                              */
//  EXTI3_IRQn                  = 9+16,      /*!< EXTI Line3 Interrupt                                              */
//  EXTI4_IRQn                  = 10+16,     /*!< EXTI Line4 Interrupt                                              */
//  DMA1_Stream0_IRQn           = 11+16,     /*!< DMA1 Stream 0 global Interrupt                                    */
//  DMA1_Stream1_IRQn           = 12+16,     /*!< DMA1 Stream 1 global Interrupt                                    */
//  DMA1_Stream2_IRQn           = 13+16,     /*!< DMA1 Stream 2 global Interrupt                                    */
//  DMA1_Stream3_IRQn           = 14+16,     /*!< DMA1 Stream 3 global Interrupt                                    */
//  DMA1_Stream4_IRQn           = 15+16,     /*!< DMA1 Stream 4 global Interrupt                                    */
//  DMA1_Stream5_IRQn           = 16+16,     /*!< DMA1 Stream 5 global Interrupt                                    */
//  DMA1_Stream6_IRQn           = 17+16,     /*!< DMA1 Stream 6 global Interrupt                                    */
//  ADC_IRQn                    = 18+16,     /*!< ADC1, ADC2 and ADC3 global Interrupts                             */
//  CAN1_TX_IRQn                = 19+16,     /*!< CAN1 TX Interrupt                                                 */
//  CAN1_RX0_IRQn               = 20+16,     /*!< CAN1 RX0 Interrupt                                                */
//  CAN1_RX1_IRQn               = 21+16,     /*!< CAN1 RX1 Interrupt                                                */
//  CAN1_SCE_IRQn               = 22+16,     /*!< CAN1 SCE Interrupt                                                */
//  EXTI9_5_IRQn                = 23+16,     /*!< External Line[9:5] Interrupts                                     */
//  TIM1_BRK_TIM9_IRQn          = 24+16,     /*!< TIM1 Break interrupt and TIM9 global interrupt                    */
//  TIM1_UP_TIM10_IRQn          = 25+16,     /*!< TIM1 Update Interrupt and TIM10 global interrupt                  */
//  TIM1_TRG_COM_TIM11_IRQn     = 26+16,     /*!< TIM1 Trigger and Commutation Interrupt and TIM11 global interrupt */
//  TIM1_CC_IRQn                = 27+16,     /*!< TIM1 Capture Compare Interrupt                                    */
//  TIM2_IRQn                   = 28+16,     /*!< TIM2 global Interrupt                                             */
//  TIM3_IRQn                   = 29+16,     /*!< TIM3 global Interrupt                                             */
//  TIM4_IRQn                   = 30+16,     /*!< TIM4 global Interrupt                                             */
//  I2C1_EV_IRQn                = 31+16,     /*!< I2C1 Event Interrupt                                              */
//  I2C1_ER_IRQn                = 32+16,     /*!< I2C1 Error Interrupt                                              */
//  I2C2_EV_IRQn                = 33+16,     /*!< I2C2 Event Interrupt                                              */
//  I2C2_ER_IRQn                = 34+16,     /*!< I2C2 Error Interrupt                                              */
//  SPI1_IRQn                   = 35+16,     /*!< SPI1 global Interrupt                                             */
//  SPI2_IRQn                   = 36+16,     /*!< SPI2 global Interrupt
  CONSOLE_RX_IRQn                      ,     /*!< CONSOLE Rx                        */
  CONSOLE_TX_IRQn                      ,     /*!< CONSOLE Tx                        */
  USART1_RX_IRQn                       ,     /*!< USART1 Rx                         */
  USART1_TX_IRQn                       ,     /*!< USART1 Tx                         */
  USART2_RX_IRQn                       ,     /*!< USART2 Rx                         */
  USART2_TX_IRQn                       ,     /*!< USART2 Tx                         */
  USART3_RX_IRQn                       ,     /*!< USART3 Rx                         */
  USART3_TX_IRQn                       ,     /*!< USART3 Tx                         */
//  EXTI15_10_IRQn              = 40+16,     /*!< External Line[15:10] Interrupts                                   */
//  RTC_Alarm_IRQn              = 41+16,     /*!< RTC Alarm (A and B) through EXTI Line Interrupt                   */
//  OTG_FS_WKUP_IRQn            = 42+16,     /*!< USB OTG FS Wakeup through EXTI line interrupt                     */
//  TIM8_BRK_TIM12_IRQn         = 43+16,     /*!< TIM8 Break Interrupt and TIM12 global interrupt                   */
//  TIM8_UP_TIM13_IRQn          = 44+16,     /*!< TIM8 Update Interrupt and TIM13 global interrupt                  */
//  TIM8_TRG_COM_TIM14_IRQn     = 45+16,     /*!< TIM8 Trigger and Commutation Interrupt and TIM14 global interrupt */
//  TIM8_CC_IRQn                = 46+16,     /*!< TIM8 Capture Compare Interrupt                                    */
//  DMA1_Stream7_IRQn           = 47+16,     /*!< DMA1 Stream7 Interrupt                                            */
//  FSMC_IRQn                   = 48+16,     /*!< FSMC global Interrupt                                             */
//  SDIO_IRQn                   = 49+16,     /*!< SDIO global Interrupt                                             */
//  TIM5_IRQn                   = 50+16,     /*!< TIM5 global Interrupt                                             */
//  SPI3_IRQn                   = 51+16,     /*!< SPI3 global Interrupt                                             */
//  UART4_IRQn                  = 52+16,     /*!< UART4 global Interrupt                                            */
//  UART5_IRQn                  = 53+16,     /*!< UART5 global Interrupt                                            */
//  TIM6_DAC_IRQn               = 54+16,     /*!< TIM6 global and DAC1&2 underrun error  interrupts                 */
//  TIM7_IRQn                   = 55+16,     /*!< TIM7 global interrupt                                             */
//  DMA2_Stream0_IRQn           = 56+16,     /*!< DMA2 Stream 0 global Interrupt                                    */
//  DMA2_Stream1_IRQn           = 57+16,     /*!< DMA2 Stream 1 global Interrupt                                    */
//  DMA2_Stream2_IRQn           = 58+16,     /*!< DMA2 Stream 2 global Interrupt                                    */
//  DMA2_Stream3_IRQn           = 59+16,     /*!< DMA2 Stream 3 global Interrupt                                    */
//  DMA2_Stream4_IRQn           = 60+16,     /*!< DMA2 Stream 4 global Interrupt                                    */
//  ETH_IRQn                    = 61+16,     /*!< Ethernet global Interrupt                                         */
//  ETH_WKUP_IRQn               = 62+16,     /*!< Ethernet Wakeup through EXTI line Interrupt                       */
//  CAN2_TX_IRQn                = 63+16,     /*!< CAN2 TX Interrupt                                                 */
//  CAN2_RX0_IRQn               = 64+16,     /*!< CAN2 RX0 Interrupt                                                */
//  CAN2_RX1_IRQn               = 65+16,     /*!< CAN2 RX1 Interrupt                                                */
//  CAN2_SCE_IRQn               = 66+16,     /*!< CAN2 SCE Interrupt                                                */
//  OTG_FS_IRQn                 = 67+16,     /*!< USB OTG FS global Interrupt                                       */
//  DMA2_Stream5_IRQn           = 68+16,     /*!< DMA2 Stream 5 global interrupt                                    */
//  DMA2_Stream6_IRQn           = 69+16,     /*!< DMA2 Stream 6 global interrupt                                    */
//  DMA2_Stream7_IRQn           = 70+16,     /*!< DMA2 Stream 7 global interrupt                                    */
//  USART6_IRQn                 = 71+16,     /*!< USART6 global interrupt                                           */
//  I2C3_EV_IRQn                = 72+16,     /*!< I2C3 event interrupt                                              */
//  I2C3_ER_IRQn                = 73+16,     /*!< I2C3 error interrupt                                              */
//  OTG_HS_EP1_OUT_IRQn         = 74+16,     /*!< USB OTG HS End Point 1 Out global interrupt                       */
//  OTG_HS_EP1_IN_IRQn          = 75+16,     /*!< USB OTG HS End Point 1 In global interrupt                        */
//  OTG_HS_WKUP_IRQn            = 76+16,     /*!< USB OTG HS Wakeup through EXTI interrupt                          */
//  OTG_HS_IRQn                 = 77+16,     /*!< USB OTG HS global interrupt                                       */
//  DCMI_IRQn                   = 78+16,     /*!< DCMI global interrupt                                             */
//  CRYP_IRQn                   = 79+16,     /*!< CRYP crypto global interrupt                                      */
//  HASH_RNG_IRQn               = 80+16      /*!< Hash and Rng global interrupt                                     */
} IRQn_Type;

#endif

#if 0

#define  OS_CRITICAL_METHOD   3u

#if OS_CRITICAL_METHOD == 3u
#define  OS_ENTER_CRITICAL()  {cpu_sr = OS_CPU_SR_Save();}
#define  OS_EXIT_CRITICAL()   {OS_CPU_SR_Restore(cpu_sr);}
#endif

/*
*********************************************************************************************************
*                                        Cortex-M3 Miscellaneous
*********************************************************************************************************
*/

#define  OS_STK_GROWTH        1u                  /* Stack grows from HIGH to LOW memory on ARM        */

#define  OS_TASK_SW()         OSCtxSw()

/*
*********************************************************************************************************
*                                              PROTOTYPES
*********************************************************************************************************
*/

#if OS_CRITICAL_METHOD == 3u                      /* See OS_CPU_A.ASM                                  */
OS_CPU_SR  OS_CPU_SR_Save(void);
void       OS_CPU_SR_Restore(OS_CPU_SR cpu_sr);
#endif

void       OSCtxSw(void);
void       OSIntCtxSw(void);
void       OSStartHighRdy(void);

void       OS_CPU_PendSVHandler(void);

                                                  /* See OS_CPU_C.C                                    */
void       OS_CPU_SysTickHandler(void);
void       OS_CPU_SysTickInit(INT32U  cnts);
#endif

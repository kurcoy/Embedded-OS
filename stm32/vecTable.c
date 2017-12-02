/**
 ******************************************************************************
 * @file       vecTable.c
 * @version    V1.1.4
 * @brief      �ں��ж�������
 * @details    This file including all API functions's implement of vecTable.
 * @copyright Copyright(C), 2015-2020,Sanxing Medical & Electric Co.,Ltd.
 ******************************************************************************
 */

/*-----------------------------------------------------------------------------
 Section: Includes
 ----------------------------------------------------------------------------*/
#if __CPU_SEL_ != 1
#include <types.h>

/*-----------------------------------------------------------------------------
 Section: Macro Definitions
 ----------------------------------------------------------------------------*/
//#define ROUTINE(n) routine##n
#define ROUTINE(n) routine_comm

//#if defined (__IAR_SYSTEMS_ICC__)     /* for IAR Compiler */
//#if defined (__GNUC__)              /* GNU GCC Compiler */

/*-----------------------------------------------------------------------------
 Section: Type Definitions
 ----------------------------------------------------------------------------*/
/* �ж�����������ջ����ַ��ISR��ַ */
typedef union
{
    VOIDFUNCPTR routine;     /**< �жϴ�������ַ */
    void *msp;               /**< ջ����ַ         */
} INTVECT_ITEM;

/*-----------------------------------------------------------------------------
 Section: Global Function Prototypes
 ----------------------------------------------------------------------------*/

extern void
main(void);

void
resetRoutine(void)
{
    main();
}

//extern void
//OS_CPU_PendSVHandler(void);
//
//extern void
//OS_CPU_SysTickHandler(void);
//
//extern void
//excEnterCommon(void);
//
//extern void
//intHandler(uint32_t irq_num);
//
//extern void
//NMIRoutine(void);

void
dummy(void)
{
    ;
}

/*-----------------------------------------------------------------------------
 Section: Local Function Prototypes
 ----------------------------------------------------------------------------*/
static void
routine_comm(void);

/*-----------------------------------------------------------------------------
 Section: Global Variables
 ----------------------------------------------------------------------------*/
/* �ж������� */
#if defined (__IAR_SYSTEMS_ICC__)     /* for IAR Compiler */
#pragma language=extended
#pragma segment="CSTACK"

__root const INTVECT_ITEM __vector_table[] @ ".intvec" = {
    { .msp = (void *)__sfe( "CSTACK" )},    //ջ��ָ��

#elif defined (__GNUC__)              /* GNU GCC Compiler */
extern unsigned long cstack_top;

__attribute__((section(".isr_vector")))
const INTVECT_ITEM __vector_table[] =
{
    { (void *)&cstack_top},     // ջ��ָ��

#endif
    {resetRoutine},            // ��λ�ж�
    {dummy},               // NMI�ж�
#if 1
    {dummy},                    // Ӳ�������ж�
    {dummy},                    // �洢����������ж�
    {dummy},                    // ���ߴ����ж�
    {dummy},                    // �÷������ж�
#else
    {excEnterCommon},           // Ӳ�������ж�
    {excEnterCommon},           // �洢����������ж�
    {excEnterCommon},           // ���ߴ����ж�
    {excEnterCommon},           // �÷������ж�
#endif
    {dummy},                    // �����ж�
    {dummy},
    {dummy},
    {dummy},
    {dummy},                    // SVC�ж�
    {dummy},
    {dummy},
    {dummy},     // ��COS
    {dummy},    // ��COS

//    {ROUTINE(16 )}, {ROUTINE(17 )}, {ROUTINE(18 )}, {ROUTINE(19 )},
//    {ROUTINE(20 )}, {ROUTINE(21 )}, {ROUTINE(22 )}, {ROUTINE(23 )},
//    {ROUTINE(24 )}, {ROUTINE(25 )}, {ROUTINE(26 )}, {ROUTINE(27 )},
//    {ROUTINE(28 )}, {ROUTINE(29 )}, {ROUTINE(30 )}, {ROUTINE(31 )},
//    {ROUTINE(32 )}, {ROUTINE(33 )}, {ROUTINE(34 )}, {ROUTINE(35 )},
//    {ROUTINE(36 )}, {ROUTINE(37 )}, {ROUTINE(38 )}, {ROUTINE(39 )},
//    {ROUTINE(40 )}, {ROUTINE(41 )}, {ROUTINE(42 )}, {ROUTINE(43 )},
//    {ROUTINE(44 )}, {ROUTINE(45 )}, {ROUTINE(46 )}, {ROUTINE(47 )},
//    {ROUTINE(48 )}, {ROUTINE(49 )}, {ROUTINE(50 )}, {ROUTINE(51 )},
//    {ROUTINE(52 )}, {ROUTINE(53 )}, {ROUTINE(54 )}, {ROUTINE(55 )},
//    {ROUTINE(56 )}, {ROUTINE(57 )}, {ROUTINE(58 )}, {ROUTINE(59 )},
//
//    {ROUTINE(60 )}, {ROUTINE(61 )}, {ROUTINE(62 )}, {ROUTINE(63 )},
//    {ROUTINE(64 )}, {ROUTINE(65 )}, {ROUTINE(66 )}, {ROUTINE(67 )},
//    {ROUTINE(68 )}, {ROUTINE(69 )}, {ROUTINE(70 )}, {ROUTINE(71 )},
//    {ROUTINE(72 )}, {ROUTINE(73 )}, {ROUTINE(74 )}, {ROUTINE(75 )},
//    {ROUTINE(76 )}, {ROUTINE(77 )}, {ROUTINE(79 )}, {ROUTINE(79 )},
//    {ROUTINE(80 )}, {ROUTINE(81 )}, {ROUTINE(82 )}, {ROUTINE(83 )},
//
//    {ROUTINE(84 )}, {ROUTINE(85 )}, {ROUTINE(86 )}, {ROUTINE(87 )},
//    {ROUTINE(88 )}, {ROUTINE(89 )}, {ROUTINE(90 )}, {ROUTINE(91 )},
};

/*-----------------------------------------------------------------------------
 Section: Function Definitions
 ----------------------------------------------------------------------------*/
/**
 ******************************************************************************
 * @brief   �����ж�
 *          Interrupt Control and State Register
 *          bit[0:8]��ʾ��ǰ�жϺ�
 * @return  None
 ******************************************************************************
 */
static void
routine_comm(void)
{
    intHandler(*((volatile uint32_t *)0xE000ED04) & 0x1FF);
}

#endif

/*---------------------------End of vecTable.c-------------------------------*/

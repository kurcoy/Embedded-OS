/**
 ******************************************************************************
 * @file      shell_help.c
 * @brief     C Source file of shell_help.c.
 * @details   This file including all API functions's implement of shell_help.c.	
 * @copyright  Copyright(C)
 ******************************************************************************
 */
 
/*-----------------------------------------------------------------------------
 Section: Includes
 ----------------------------------------------------------------------------*/
#include <types.h>
#include <shell.h>

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
extern cmd_tbl_t  __shell_cmd_start;
extern cmd_tbl_t  __shell_cmd_end;

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
 * @brief   打印帮助信息help
 * @retval  None
 ******************************************************************************
 */
static uint32_t
help(void)
{
    uint8_t *usage;
    cmd_tbl_t *cmdtptemp;

    SHELL_PRINTF("\n");
    /* print short help (usage) */
    for (cmdtptemp = &__shell_cmd_start; cmdtptemp != &__shell_cmd_end;
            cmdtptemp++)
    {
        usage = (uint8_t *)cmdtptemp->name;
        if (usage == NULL)
        {
            continue;
        }
        SHELL_PRINTF((char*) usage);
        SHELL_PRINTF("\r\t\t\t\t ");
        usage = (uint8_t *)cmdtptemp->usage;
        /* allow user abort */
        if (usage == NULL)
        {
            continue;
        }
        SHELL_PRINTF((char*) usage);
    }

    return 0;
}

/**
 ******************************************************************************
 * @brief   显示帮助提示信息
 * @param[in]  *cmdtp   : shell命令信息
 * @param[in]  argc     : 命令行参数数量
 * @param[in]  *argv[]  : 命令行参数内容
 *
 * @retval  命令执行状态
 ******************************************************************************
 */
static uint32_t
do_help(const cmd_tbl_t * cmdtp,
        uint32_t argc,
        const char *argv[])
{
    return help();
}

SHELL_CMD(help, CFG_MAXARGS, do_help, "Print this list\r\n");

/*----------------------------shell_help.c--------------------------------*/

/**
 ******************************************************************************
 * @file       shell.h
 * @brief      shell模块.
 * @details    This file including all API functions's implement of shell.
 * @copyright Copyright(C), 2015-2020,Sanxing Medical & Electric Co.,Ltd.
 ******************************************************************************
 */
#ifndef __SHELL_H__
#define __SHELL_H__

/*-----------------------------------------------------------------------------
 Section: Includes
 ----------------------------------------------------------------------------*/
#include <types.h>

/*-----------------------------------------------------------------------------
 Section: Macro Definitions
 ----------------------------------------------------------------------------*/
# define CFG_MAXARGS                (8u)    /**< 命令行最大参数数量 */
# define INCLUDE_SHELL_CMD
#define SHELL_PRINTF                printf          /**< 字符串输出 */

/*-----------------------------------------------------------------------------
 Section: Type Definitions
 ----------------------------------------------------------------------------*/
#pragma pack(push, 1)

/**
 * Monitor Command Table
 */
struct cmd_tbl_s
{
	char_t      *name;		/**< Command Name			        */
	uint32_t    maxargs;	/**< maximum number of arguments	*/
	uint32_t    (*cmd)(const struct cmd_tbl_s *, uint32_t, const char *[]);
	char_t      *usage;		/**< Usage message	(short)	    */
};
typedef struct cmd_tbl_s	cmd_tbl_t;
typedef uint32_t (*SHELL_CMD_FUNCPTR) (const cmd_tbl_t *, uint32_t, const char *[]);

#pragma pack(pop)

#define Struct_Section  __attribute__ ((unused,section (".shell_cmd")))

#ifdef INCLUDE_SHELL_CMD
#define SHELL_CMD(name, maxargs, cmd, usage) \
const cmd_tbl_t __shell_cmd_##name Struct_Section = {#name, maxargs, cmd, usage}
#else
#define SHELL_CMD(name,maxargs,cmd,usage) 
#endif

/*-----------------------------------------------------------------------------
 Section: Function Prototypes
 ----------------------------------------------------------------------------*/
extern status_t
shell_init(void);

extern void
print_usage(cmd_tbl_t *pcmd);

#endif /* __SHELL_H__ */

/*------------------------------End of shell.h-------------------------------*/


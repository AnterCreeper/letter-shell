/**
 * @file shell_port.c
 * @author Letter (NevermindZZT@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2019-02-22
 * 
 * @copyright (c) 2019 Letter
 * 
 */

#include "shell.h"
#include "stdio.h"

Shell shell;
char shellBuffer[512];

/**
 * @brief 用户shell写
 * 
 * @param data 数据
 */
void userShellWrite(char data)
{
    debug_putchar(data);
}

/**
 * @brief 用户shell读
 * 
 * @param data 数据
 * @return char 状态
 */
signed char userShellRead(char *data)
{
    return debug_getchar(data);
}

/**
 * @brief 用户shell初始化
 * 
 */
void userShellInit(void)
{
    shell.write = userShellWrite;
    shell.read = userShellRead;
    shellInit(&shell, shellBuffer, 512);
}

void shellVersion(void)
{
    shellPrint(shellGetCurrent(), "letter-shell v3.0 %s %s %s\n", __VERSION__, __DATE__, __TIME__);
}
SHELL_EXPORT_CMD(
SHELL_CMD_PERMISSION(0x00)|SHELL_CMD_TYPE(SHELL_TYPE_CMD_FUNC)|SHELL_CMD_DISABLE_RETURN,
version, shellVersion, show shell version);


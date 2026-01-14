#include "shell.h"
#include "stdio.h"
#include "time.h"

Shell shell;
char shellBuffer[512];

int userShellRead(char *data) {
    return debug_getchar(data);
}

void userShellWrite(char data) {
    debug_putchar(data);
}

void userShellInit(void) {
    shell.read = userShellRead;
    shell.write = userShellWrite;
    shellInit(&shell, shellBuffer, 512);
}

void shellVersion(void)
{
    shellPrint(shellGetCurrent(), "letter-shell v3.0 %s %s\n", __DATE__, __VERSION__);
}
SHELL_EXPORT_CMD(
SHELL_CMD_PERMISSION(0x00)|SHELL_CMD_TYPE(SHELL_TYPE_CMD_FUNC)|SHELL_CMD_DISABLE_RETURN,
version, shellVersion, display shell version information.);

void shellClock(void)
{
    shellPrint(shellGetCurrent(), "%08lx\n", clock());
}
SHELL_EXPORT_CMD(
SHELL_CMD_PERMISSION(0x00)|SHELL_CMD_TYPE(SHELL_TYPE_CMD_FUNC)|SHELL_CMD_DISABLE_RETURN,
clock, shellClock, display system clock ticks.);

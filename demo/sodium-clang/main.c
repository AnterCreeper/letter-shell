#include "shell_port.h"

int main(void)
{
    userShellInit();
    while(1) {
        shellTask(&shell);
    }
    return 0;
}

/**
 * @file main.c
 * @author Letter (NevermindZZT@gmail.com)
 * @brief
 * @version 0.1
 * @date 2020-07-12
 *
 * @copyright (c) 2019 Letter
 *
 */

#include "shell_port.h"

int main(void)
{
    userShellInit();
    while(1) {
        shellTask(&shell);
    }
    return 0;
}

#include "stdio.h"
#include <stdbool.h>
#include "string.h"
#include "shell.h"
#include "engine.h"
#include "gfx.h"

#define printf(...) shellPrint(shellGetCurrent(), __VA_ARGS__)
#define puts(str)   shellWriteString(shellGetCurrent(), str)

void draw_then_sleep(struct gamestate *g)
{
    gfx_draw(g);
    /* Have a fixed time for each turn to animate (160 default) */
    gfx_sleep(160 / GRID_WIDTH);
}

int startgame()
{
    struct gamestate game;
    gamestate_init(&game);
    puts("\033[?25l"); //disable cursor

    int game_running = true;
    while (game_running) {
        gfx_draw(&game);

get_new_key:;
        int direction = dir_invalid;
        char value = gfx_getch();
        switch (value) {
            case 'A':
            case 'a':
                direction = dir_left;
                break;
            case 'D':
            case 'd':
                direction = dir_right;
                break;
            case 'S':
            case 's':
                direction = dir_down;
                break;
            case 'W':
            case 'w':
                direction = dir_up;
                break;
            case 'Q':
            case 'q':
                game_running = false;
                break;
            default:
                goto get_new_key;
        }

        /* Game will only end if 0 moves available */
        if (game_running) {
            gamestate_tick(&game, direction, draw_then_sleep);

            if (game.moved == 0)
                goto get_new_key;

            for (int spawned = 0; spawned < SPAWN_RATE; spawned++)
                gamestate_new_block(&game);

            if (gamestate_end_condition(&game)) {
                game_running = false;
            }
        }
    }

    printf("Total: %ld\n", game.score);
    puts("\033[?25h"); //enable cursor
    gamestate_clear(&game);
    return 0;
}
SHELL_EXPORT_CMD(
SHELL_CMD_PERMISSION(0x00)|SHELL_CMD_TYPE(SHELL_TYPE_CMD_FUNC)|SHELL_CMD_DISABLE_RETURN,
2048, startgame, 2048 game.);

long score2048 = 0;
SHELL_EXPORT_VAR(SHELL_CMD_PERMISSION(0)|SHELL_CMD_TYPE(SHELL_TYPE_VAR_INT), score2048, &score2048, highscore of 2048 game.);

long highscore_load() {
    return score2048;
}

void highscore_save(long score) {
    if (score < score2048)
        return;
    score2048 = score;
}

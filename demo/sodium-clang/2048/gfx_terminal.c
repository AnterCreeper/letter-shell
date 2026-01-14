#include "stdio.h"
#include "time.h"
#include "merge.h"
#include "gfx.h"
#include "shell.h"

#define printf(...) shellPrint(shellGetCurrent(), __VA_ARGS__)
#define puts(str)   shellWriteString(shellGetCurrent(), str)    //shellWriteString will not echo with additional newline character

#define iterate(n, expression)\
    do {\
        int i;\
        for (i = 0; i < n; ++i) { expression; }\
    } while (0)

#define COLOR_BLACK           0x01
#define COLOR_RED             0x02
#define COLOR_GREEN           0x03
#define COLOR_YELLOW          0x04
#define COLOR_BLUE            0x05
#define COLOR_MAGENTA         0x06
#define COLOR_CYAN            0x07
#define COLOR_WHITE           0x08
#define COLOR(fc, bc)         ((fc << 4) | (bc))

#define NUMBER_OF_COLORS      8
const unsigned char paintboard[NUMBER_OF_COLORS] = {
    COLOR(COLOR_WHITE, COLOR_BLACK),
    COLOR(COLOR_WHITE, COLOR_RED),
    COLOR(COLOR_BLACK, COLOR_GREEN),
    COLOR(COLOR_BLACK, COLOR_YELLOW),
    COLOR(COLOR_WHITE, COLOR_BLUE),
    COLOR(COLOR_BLACK, COLOR_MAGENTA),
    COLOR(COLOR_BLACK, COLOR_CYAN),
    COLOR(COLOR_BLACK, COLOR_WHITE)
};

void gfx_color_set(int number) {
    int fcolor = paintboard[number] >> 4;
    int bcolor = paintboard[number] & 0xf;
    printf("\033[0;3%c;4%cm", fcolor-1+'0', bcolor-1+'0');
}

void gfx_color_clear() {
    puts("\033[0m|");
}

void gfx_draw(struct gamestate *g)
{
    puts("\033[2J\033[H");

    if (g->score_last)
        printf("Score: %ld (+%ld)\n", g->score, g->score_last);
    else
        printf("Score: %ld\n", g->score);
    if (g->score >= g->score_high)
        g->score_high = g->score;

    printf("   Hi: %ld\n", g->score_high);
    iterate((g->print_width + 2) * GRID_WIDTH + 1, puts("-")); puts("\n");

    int x, y;
    for (y = 0; y < GRID_WIDTH; ++y) {
        puts("|");

        for (x = 0; x < GRID_WIDTH; ++x) {
            if (g->grid[x][y]) {
                gfx_color_set(g->grid[x][y] % NUMBER_OF_COLORS);
                printf("%*lu ", g->print_width, merge_value(g->grid[x][y]));
                gfx_color_clear();
            } else {
                printf("%*s |", g->print_width, "");
            }
        }
        puts("\n");
    }
    iterate((g->print_width + 2) * GRID_WIDTH + 1, puts("-")); puts("\n\n");
}

char gfx_getch()
{
    char data;
    while (debug_getchar(&data));
    return data;
}

void gfx_sleep(int ms)
{
    //TODO general sleep based on clock();
    for(int i = 0; i < ms*(CLOCKS_PER_SEC/1000/10); i++) {
        asm("nop");
        asm("nop");
    }
}

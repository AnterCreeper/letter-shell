#ifndef ENGINE_H
#define ENGINE_H

#include "stdio.h"
#include "options.h"

struct gamestate {
    /* Game state */
    int *grid_data_ptr;
    int *grid[GRID_HEIGHT];
    int moved;
    long score;
    long score_high;
    long score_last;
    int print_width;
    int blocks_in_play;
};

enum {
    dir_invalid,
    dir_down,
    dir_left,
    dir_right,
    dir_up
};

struct gfx_state;

int gamestate_end_condition(struct gamestate*);
void gamestate_new_block(struct gamestate*);
int  gamestate_tick(struct gamestate*, int, void (*callback)(struct gamestate*));
void gamestate_init(struct gamestate*);
void gamestate_clear(struct gamestate*);

long highscore_load();
void highscore_save(long score);

#endif

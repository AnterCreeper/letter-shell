#ifndef GFX_H
#define GFX_H

#include "engine.h"

/* Drawing of a game_state onto a graphics context */
void gfx_draw(struct gamestate *);

/* Blocking get character. Should not be buffered for best results */
char gfx_getch();

/* Sleep for a specifed millisecond period */
void gfx_sleep(int ms);

#endif

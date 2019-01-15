#include <curses.h>
#include "../backend/logic.h"
#include "graphics.h"

int maxy, maxx;
int change = 0;

const char emperor[] = {
    ' ', '_', '_', '_', ' ', 0,
    '|', 'E', 'E', 'E', '|', 0,
    '|', 'E', 'E', 'E', '|', 0,
    '|', ' ', 'E', ' ', '|', 0,
    '|', '_', '_', '_', '|', 0
};

const char civilian[] = {
    ' ', '_', '_', '_', ' ', 0,
    '|', ' ', 'C', ' ', '|', 0,
    '|', 'C', 'C', 'C', '|', 0,
    '|', ' ', 'C', ' ', '|', 0,
    '|', '_', '_', '_', '|', 0
};

const char slave[] = {
    ' ', '_', '_', '_', ' ', 0,
    '|', ' ', ' ', ' ', '|', 0,
    '|', ' ', 'S', 'S', '|', 0,
    '|', 'S', 'S', ' ', '|', 0,
    '|', '_', '_', '_', '|', 0
};

const char arrow[] = {
    '|', 0,
    'v', 0
};

static void draw(const char* img, int x, int y, int w, int h) {
    int end = y + h;
    const char* ptr = img;
    for (int i = y; i < end; i++, ptr += (w + 1)) {
        mvprintw(i, x, ptr);
    }
}

static void patch(int x, int y, int w, int h) {
    for (int i = x; i < x + w; i++) {
        for (int j = y; j < y + h; j++) {
            mvaddch(j, i, ' ');
        }
    }
}

void render(void) {
    int cur = (maxx - 29) >> 1;
    int row = maxy - 10;
    for (int i = 0; i < 5; i++, cur += 6) {
        if (player & (1 << i)) {
            if (i) {
                draw(civilian, cur, row, 5, 5);
            } else {
                if (turn & 0x80) {
                    draw(slave, cur, row, 5, 5);
                } else {
                    draw(emperor, cur, row, 5, 5);
                }
            }
        }
    }
    draw(arrow, ((maxx - 29) >> 1) + 2 + 6 * (sel_life_score >> 13),
         row - 2, 1, 2);
}

void update(void) {
    switch (change & 0xf0000000) {
    case CURSOR_MOVED:
        patch(((maxx - 29) >> 1) + 2 + 6 * (change & ~0xf0000000), maxy - 12,
               1, 2);
        draw(arrow, ((maxx - 29) >> 1) + 2 + 6 * (sel_life_score >> 13),
             maxy - 12, 1, 2);
        break;
    }
    return;
}
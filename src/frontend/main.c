#include <curses.h>
#include "graphics.h"
#include "../backend/logic.h"

#define START_SCREEN 0
#define APP 1
#define END_SCREEN 2

unsigned char state = START_SCREEN;

int main(void) {
    initscr();
    raw();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    clear();
    getmaxyx(stdscr, maxy, maxx);
    mvprintw((maxy - 1) >> 1, (maxx - 5) >> 1, "ECARD");
    mvprintw(((maxy - 1) >> 1) + 1, (maxx - 13) >> 1, "Press Any Key");
    init();
    int inp = 0;
    for (;;) {
        inp = getch();
        switch (state) {
        case START_SCREEN:
            state = APP;
            clear();
            render();
            break;
        case APP:
            switch (inp) {
            case KEY_LEFT:
                change = CURSOR_MOVED | (sel_life_score >> 13);
                move_sel(LEFT);
                break;
            case KEY_RIGHT:
                change = CURSOR_MOVED | (sel_life_score >> 13);
                move_sel(RIGHT);
                break;
            case 'q':
            case 'Q':
                state = END_SCREEN;
                break;
            }
            update();
            break;
        }
        if (state == END_SCREEN) break;
        
    }
    endwin();
}
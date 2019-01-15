#include "logic.h"
#include <stdio.h>
Hand player;
Hand cpu;
Turn turn;
unsigned short sel_life_score;

void init(void) {
    player = 0x1f;
    cpu = 0x1f;
    turn = 0;
    sel_life_score = 30 << 8;
}

void move_sel(char dir) {
    unsigned char sel = sel_life_score >> 13;
    switch (dir) {
    case LEFT:
        if (!sel) {
            sel = 4;
        } else {
            sel--;
        }
        break;
    case RIGHT:
        if (sel == 4) {
            sel = 0;
        } else {
            sel++;
        }
    }
    sel_life_score &= 0x1fff;
    sel_life_score |= ((unsigned short)sel) << 13;
}

void toggle_cheat(void) {
    turn ^= 0x40;
}

unsigned char play(unsigned char bet) {
    if (!player) {
        turn++;
        if (!((turn & 0x3f) % 3)) {
            turn ^= 0x80;
        }
        return 1;
    }
    if (turn == 12) return 0;
    unsigned char sel = sel_life_score >> 13;
    if (!(player & (1 << sel))) {
        return 2;
    }
    unsigned char life = (sel_life_score & 0x1f00) >> 8;
    unsigned char cpu_sel = 0;
    player &= ~(1 << sel);
    if (turn & 0x40) {
        if (sel) {
            sel = 0;
        } else {
            for (sel = 1; !(player & (1 << sel)); sel++);
        }
    }
    switch (turn & 0x80) {
    case 0:        
        switch (sel) {
        case 0:
            cpu &= 0x1e;
            if (turn & 0x40) {
                sel_life_score++;
            } else {
                sel_life_score &= ~0x1f00;
                if (bet >= life) {
                    return 0;
                } else {
                    life -= bet;
                }
                sel_life_score |= ((unsigned short)life) << 8;
            }
            player = 0x1f;
            cpu = 0x1f;
            turn++;
            if (!((turn & 0x3f) % 3)) {
                turn ^= 0x80;
            }
            break;
        default:
            for (cpu_sel = 1; !(cpu & (1 << cpu_sel)); cpu_sel++);
            cpu &= ~(1 << cpu_sel);
            break;
        }
        break;
    default:
        switch (sel) {
        case 0:
            for (cpu_sel = 1; !(cpu & (1 << cpu_sel)); cpu_sel++);
            cpu &= ~(1 << cpu_sel);
            if (turn & 0x40) {
                sel_life_score++;
            } else {
                sel_life_score &= ~0x1f00;
                if (bet >= life) {
                    return 0;
                } else {
                    life -= bet;
                }
                sel_life_score |= ((unsigned short)life) << 8;
            }
            player = 0x1f;
            cpu = 0x1f;
            turn++;
            if (!((turn & 0x3f) % 3)) {
                turn ^= 0x80;
            }
            break;
        default:
            cpu &= 0x1e;
            sel_life_score &= ~0x1f00;
            if (!(turn & 0x40)) {
                if (bet >= life) {
                    return 0;
                } else {
                    life -= bet;
                }
                sel_life_score |= ((unsigned short)life) << 8;
            }
            break;
        }
    }
    return 1;
}

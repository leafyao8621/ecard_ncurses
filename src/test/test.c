#include <stdio.h>
#include "../backend/logic.h"

#define PRINT {\
    printf("role %u turn %u\n", turn >> 7, turn & 0x3f);\
    printf("sel %u life %u score %u\n", sel_life_score >> 13, (sel_life_score & 0x1f00) >> 8, sel_life_score & 0xff);\
    printf("player hand 0x%x cpu hand 0x%x\n\n", player, cpu);\
}

int main(void) {
    init();
    PRINT;
    play(10);
    PRINT;
    move_sel(LEFT);
    play(10);
    PRINT;
    move_sel(RIGHT);
    play(10);
    PRINT;
    play(1);
    PRINT;
    move_sel(RIGHT);
    play(1);
    PRINT;
    move_sel(LEFT);
    play(1);
    PRINT;
}
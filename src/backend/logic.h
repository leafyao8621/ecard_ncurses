#ifndef _LOGIC_H_
#define _LOGIC_H_

#define LEFT 0
#define RIGHT 1
typedef unsigned char Hand;
typedef unsigned char Turn;

extern Hand player; //0b000hhhhh
extern Hand cpu; //0b000hhhhh
extern Turn turn; //0bsctttttt
extern unsigned short sel_life_score; //0bsellllllssssssss
void init(void);
void move_sel(char dir);
void toggle_cheat(void);
unsigned char play(unsigned char bet);
#endif


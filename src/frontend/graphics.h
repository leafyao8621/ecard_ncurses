#ifndef GRAPHICS_H
#define GRAPHICS_H

#define CURSOR_MOVED (1 << 28)
#define CARD_SELECTED (2 << 28)
#define CARD_UNSELECTED (3 << 28)
#define CARD_REVEALED (4 << 28)

extern int maxy, maxx;
extern int change;

void render(void);
void update(void);
#endif

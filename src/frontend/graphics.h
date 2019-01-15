#ifndef GRAPHICS_H
#define GRAPHICS_H

#define CURSOR_MOVED (1 << 28)

extern int maxy, maxx;
extern int change;

void render(void);
void update(void);
#endif
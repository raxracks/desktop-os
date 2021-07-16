#ifndef FONT_H
#define FONT_H

#include "util.h"
#include "screen.h"

#define font_width(_s) (strlen((_s)) * 8)
#define font_height() (8)

void font_char(char c, size_t x, size_t y, u8 color);
void font_str(const char *s, size_t x, size_t y, u8 color);

#endif

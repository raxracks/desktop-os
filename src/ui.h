#ifndef UI_H
#define UI_H

#include "util.h"
#include "screen.h"

struct UIElement {
    const char* s;
    size_t x;
    size_t y;
    size_t textX;
    size_t textY;
    size_t width;
    size_t height;
    u8 foreground;
    u8 background;
    int (*callback)(void);
};

void UIButton(const char *s, size_t x, size_t y, size_t textX, size_t textY, size_t width, size_t height, u8 foreground, u8 background, int (*callback)(void));
void UIRect(size_t x, size_t y, size_t width, size_t height, u8 color, int (*callback)(void));
void CheckMouse(int mouse_x, int mouse_y);

void DrawUI();
void ClearUI();

#endif

#include "screen.h"
#include "system.h"
#include "font.h"
#include "ui.h"
#define n 100

int currentIndex = 0;

struct UIElement UIElements[n];

void UIButton(const char *s, size_t x, size_t y, size_t textX, size_t textY, size_t width, size_t height, u8 foreground, u8 background, int (*callback)(void)) {
    UIElements[currentIndex].s = s;
    UIElements[currentIndex].x = x;
    UIElements[currentIndex].y = y;
    UIElements[currentIndex].textX = textX;
    UIElements[currentIndex].textY = textY;
    UIElements[currentIndex].width = width;
    UIElements[currentIndex].height = height;
    UIElements[currentIndex].foreground = foreground;
    UIElements[currentIndex].background = background;
    UIElements[currentIndex].callback = callback;

    currentIndex++;
}

void UIRect(size_t x, size_t y, size_t width, size_t height, u8 color, int (*callback)(void)) {
    UIElements[currentIndex].s = NULL;
    UIElements[currentIndex].x = x;
    UIElements[currentIndex].y = y;
    UIElements[currentIndex].textX = NULL;
    UIElements[currentIndex].textY = NULL;
    UIElements[currentIndex].width = width;
    UIElements[currentIndex].height = height;
    UIElements[currentIndex].foreground = NULL;
    UIElements[currentIndex].background = color;
    UIElements[currentIndex].callback = callback;

    currentIndex++;
}

bool Intersect(int aX, int aY, int aWidth, int aHeight, int bX, int bY, int bWidth, int bHeight) {
    return (bX > aX && bX < aX + aWidth && bY > aY && bY < aY + aHeight);
}

void CheckMouse(int mouse_x, int mouse_y) {
    for(int i = 0; i < n; i++) {
        if(UIElements[i].background != NULL) {
            if(Intersect(UIElements[i].x, UIElements[i].y, UIElements[i].width, UIElements[i].height, mouse_x, mouse_y, 1, 1)) {
                UIElements[i].callback();
            }
        }
    }
}

void DrawUI() {
    for(int i = 0; i < n; i++) {
        if(UIElements[i].background != NULL) {
            screen_fill(
                UIElements[i].background,
                UIElements[i].x,
                UIElements[i].y,
                UIElements[i].width,
                UIElements[i].height
            );
        }

        if(UIElements[i].s != NULL) { 
            font_str(UIElements[i].s,
                UIElements[i].x + UIElements[i].textX,
                UIElements[i].y + UIElements[i].textY,
                UIElements[i].foreground
            );
        }
    }
}

void ClearUI() {
    currentIndex = 0;
}
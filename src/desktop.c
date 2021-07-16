#include "screen.h"
#include "system.h"
#include "font.h"
#include "ui.h"
#include "mouse.h"

void DisplayDesktop() {
    InitializeMouse(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 4);

    while (true) {
        ClearUI();
        InitializeUI();
        UpdateMouse();

        screen_clear(COLOR(0, 0, 0));

        Render();

        screen_swap();
    }
}

void InitializeUI() {
    UIRect(0, SCREEN_HEIGHT - 15, SCREEN_WIDTH, 15, COLOR(0, 19, 19));
    UIButton("Start", 0, SCREEN_HEIGHT - 15, (50 / 2) - (font_width("Start") / 2), (15 / 2) - 3, 50, 15, COLOR(255, 255, 255), COLOR(0, 17, 17));
}

void Render() {
    DrawWallpaper();
    DrawUI();

    screen_fill(COLOR(0, 0, 0), mouse_x, mouse_y, 10, 10);
}

void DrawWallpaper() {
    screen_fill(COLOR(0, 18, 18), 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
}
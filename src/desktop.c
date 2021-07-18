#include "screen.h"
#include "system.h"
#include "font.h"
#include "ui.h"
#include "mouse.h"
#include "cursor.h"

bool showMenu = false;

void DisplayDesktop() {
    InitializeMouse(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.5, 15);

    while (true) {
        ClearUI();
        InitializeUI();
        UpdateMouse();

        screen_clear(COLOR(0, 0, 0));

        Render();

        screen_swap();
    }
}

int DummyCallback(void) {
    return 0;
}

int ShowStartMenu(void) {
    showMenu = !showMenu;
    return 0;
}

void InitializeUI() {
    UIRect(0, SCREEN_HEIGHT - 15, SCREEN_WIDTH, 15, COLOR(0, 19, 19), DummyCallback);
    UIButton("Start", 0, SCREEN_HEIGHT - 15, (50 / 2) - (font_width("Start") / 2), (15 / 2) - 3, 50, 15, COLOR(255, 255, 255), COLOR(0, 17, 17), ShowStartMenu);
    if(showMenu) {
        UIRect(0, (SCREEN_HEIGHT - 15) - 120, 100, 120, COLOR(1, 1, 1), DummyCallback);
    }
}

void DrawCursor() {
    int x = -1;
    int y = 0;

    for(int i = 0; i < sizeof(CURSOR_DATA); i++) {
        x++;

        if(CURSOR_DATA[i] == 1 && mouse_y + y < SCREEN_HEIGHT && x < 11 && mouse_x + x < SCREEN_WIDTH) {
            screen_fill(COLOR(0, 0, 0), mouse_x + x, mouse_y + y, 1, 1);
        } 
        if(CURSOR_DATA[i] == 2 && mouse_y + y < SCREEN_HEIGHT && x < 11 && mouse_x + x < SCREEN_WIDTH) {
            screen_fill(COLOR(255, 255, 255), mouse_x + x, mouse_y + y, 1, 1);
        } else if(CURSOR_DATA[i] == 3) {
            y++;
            x = -1;
        }
    }
}

void Render() {
    DrawWallpaper();
    DrawUI();
    CheckMouse(mouse_x, mouse_y);
    DrawCursor();
}

void DrawWallpaper() {
    screen_fill(COLOR(0, 18, 18), 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
}
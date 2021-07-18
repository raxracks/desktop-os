#ifndef MOUSE_H
#define MOUSE_H

#include "util.h"
#include "screen.h"

int mouse_x;
int mouse_y;
int mouse_sensitivity;

void InitializeMouse(int starting_x, int starting_y, int sensitivity, int cursor_size);
void UpdateMouse();

#endif

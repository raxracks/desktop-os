#include "system.h"
#include "screen.h"

u8 mouse_cycle = 0; //unsigned char
i8 mouse_byte[3];   //signed char
i8 rel_mouse_x = 0;     //signed char
i8 rel_mouse_y = 0;     //signed char
int mouse_x = 0;
int mouse_y = 0;
int mouse_sensitivity = 1;

//Mouse functions
void mouse_handler(struct regs *a_r) //struct regs *a_r (not used but just there)
{
    switch (mouse_cycle)
    {
    case 0:
        mouse_byte[0] = inportb(0x60);
        mouse_cycle++;
        break;
    case 1:
        mouse_byte[1] = inportb(0x60);
        mouse_cycle++;
        break;
    case 2:
        mouse_byte[2] = inportb(0x60);
        rel_mouse_x = mouse_byte[1];
        rel_mouse_y = mouse_byte[2];
        mouse_cycle = 0;
        break;
    }
}

inline void mouse_wait(u8 a_type) //unsigned char
{
    u32 _time_out = 100000; //unsigned int
    if (a_type == 0)
    {
        while (_time_out--) //Data
        {
            if ((inportb(0x64) & 1) == 1)
            {
                return;
            }
        }
        return;
    }
    else
    {
        while (_time_out--) //Signal
        {
            if ((inportb(0x64) & 2) == 0)
            {
                return;
            }
        }
        return;
    }
}

inline void mouse_write(u8 a_write) //unsigned char
{
    //Wait to be able to send a command
    mouse_wait(1);
    //Tell the mouse we are sending a command
    outportb(0x64, 0xD4);
    //Wait for the final part
    mouse_wait(1);
    //Finally write
    outportb(0x60, a_write);
}

u8 mouse_read()
{
    //Get's response from mouse
    mouse_wait(0);
    return inportb(0x60);
}

void mouse_install()
{
    u8 _status; //unsigned char

    //Enable the auxiliary mouse device
    mouse_wait(1);
    outportb(0x64, 0xA8);

    //Enable the interrupts
    mouse_wait(1);
    outportb(0x64, 0x20);
    mouse_wait(0);
    _status = (inportb(0x60) | 2);
    mouse_wait(1);
    outportb(0x64, 0x60);
    mouse_wait(1);
    outportb(0x60, _status);

    mouse_write(0xFE);

    //Tell the mouse to use default settings
    mouse_write(0xF6);
    mouse_read(); //Acknowledge

    //Enable the mouse
    mouse_write(0xF4);
    mouse_read(); //Acknowledge

    //Setup the mouse handler
    irq_install(12, mouse_handler);
}

void InitializeMouse(int starting_x, int starting_y, int sensitivity) {
    mouse_x = starting_x;
    mouse_y = starting_y;
    mouse_sensitivity = sensitivity;
    mouse_install();
}

void UpdateMouse() {
    mouse_x += (rel_mouse_x / mouse_sensitivity);
    mouse_y -= (rel_mouse_y / mouse_sensitivity);

    if(mouse_x < 0) mouse_x = 0;
    if(mouse_y < 0) mouse_y = 0;

    if(mouse_x > SCREEN_WIDTH) mouse_x = SCREEN_WIDTH;
    if(mouse_y > SCREEN_HEIGHT) mouse_y = SCREEN_HEIGHT;
}
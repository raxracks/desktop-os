#include "util.h"
#include "syscalls.h"
#include "irq.h"

void syscall_handler(struct Registers *regs)
{
    int syscall = regs->ebx;
    switch(syscall) {
        case 0x1:
            int length = regs->ebp;

            print_message(0x200000 + regs->edi, length);
            break;
    }
}

void syscalls_init() {
    isr_install(0x28, syscall_handler);
}
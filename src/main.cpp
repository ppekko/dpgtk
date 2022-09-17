#include "include/dpgtk.h"

extern "C" void _start(){
    asm volatile("push %rax\n");
    int winresx = 0;
    int winresy = 0;
    int fps = 0;
    
    dpgtk(&winresx, &winresy, &fps);

    printf("resolution: %d, %dzn", winresx, winresy);
    printf("fps: %d", fps);
}
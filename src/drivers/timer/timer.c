// #include <drivers/timer.h>

// uint32_t tick = 0;
// uint32_t upTime = 0;

// void timer_callback()
// {
//     tick++;
//     printf("Tick: %d\n",tick);    
// }

// void init_timer(uint32_t freq, void (*timer_callback)()) {
//     /* Install the function we just wrote */
//     register_interrupt_handler(IRQ0, timer_callback);

//     /* Get the PIT value: hardware clock at 1193180 Hz */
//     uint32_t divisor = 1193180 / freq;
//     uint8_t low  = (uint8_t)(divisor & 0xFF);
//     uint8_t high = (uint8_t)( (divisor >> 8) & 0xFF);
//     /* Send the command */
//     outb(0x43, 0x36); /* Command port */
//     outb(0x40, low);
//     outb(0x40, high);
// }

// void uptime_callback()
// {
//     upTime++;
//     // printf("Uptime is %x\n", upTime);
// }

// void uptime()
// {
//     asm volatile("sti");
//     init_timer(1000, timer_callback);
// }

// uint32_t getUptime()
// {
//     // printf("%d\n", tick);
//     return tick;
// }

// void sleep(uint32_t time)
// {
//     uint32_t up1 = getUptime();
//     while(getUptime() - up1 == time) ;
// }



#include <drivers/timer.h>
#include <cpu/isr.h>
#include <lib/string.h>
#include <ports.h>
// #include "timer.h"
// #include "isr.h"
// #include "../drivers/screen.h"
// #include "../kernel/utils.h"
// #include "../drivers/ports.h"

uint32_t tick = 0;

void timer_interrupt_handler(registers_t *regs) {
    tick++;
}

uint32_t getTime()
{
    return tick;
}

void sleep(uint32_t time)
{
    uint32_t up1 = getTime();
    while(getTime() - up1 <= time);
}


void init_timer(uint32_t freq) {
    register_interrupt_handler(IRQ0, &timer_interrupt_handler);

    uint32_t d = 1193180 / freq;

    outb(0x43, 0x36);
    outb(0x40, (uint8_t)(d & 0xFF));
    outb(0x40, (uint8_t)((d >> 8) & 0xFF));
}
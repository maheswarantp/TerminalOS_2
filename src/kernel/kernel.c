#include <kernel.h>

int main()
{
    clear_screen();
    init_gdt();
    isr_install();

    asm volatile("int $0x10");
}
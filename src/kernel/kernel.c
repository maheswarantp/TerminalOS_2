#include <kernel.h>

int main()
{
    clear_screen();
    init_gdt();
    isr_install();


    // asm volatile("sti");
    // init_timer(1);
    readBootSector();
    initGlobalVariables();
    readFat();

    uint8_t* FILENAME = "TEST    TXT";

    findFile(FILENAME);
}
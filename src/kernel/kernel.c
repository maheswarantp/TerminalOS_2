#include <kernel.h>

int main(multiboot_header_t* multiboot_header)
{
    /*       CLS           */
    clear_screen();

    /*       DESCRIPTORS AND INTERRUPTS         */
    init_gdt();
    isr_install();

    /*      FAT        */
    readBootSector();
    initGlobalVariables();
    readFat();

    /*       READ FILE         */
    uint8_t* FILENAME = "TEST    TXT";
    findFile(FILENAME);

    // printf("Load entry is %x\n", multiboot_header->load_addr);

}
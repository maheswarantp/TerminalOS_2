#include <kernel.h>

int main(multiboot_header_t* multiboot_header)
{
    /*       CLS           */
    clear_screen();

    /*       DESCRIPTORS AND INTERRUPTS         */
    init_gdt();
    isr_install();

    asm volatile("sti");
    init_timer(1);

    printf("%d\n\n", getTime());

    for(int i = 0; i < 10000; i++)
        for(int j = 0; j < 10000; j++);


    printf("%d\n\n", getTime());


    /*     TIMER     */


    /*      FAT        */
    // readBootSector();
    // initGlobalVariables();
    // readFat();

    /*       READ FILE         */
    // uint8_t* FILENAME = "TEST    TXT";
    // findFile(FILENAME);

    // printf("Load entry is %x\n", multiboot_header->load_addr);

}
#include <kernel.h>

void get_memory_map(multiboot_info_t* mbd, unsigned int magic)
{
    // Check Multiboot structure validity and Print Memory Map
    if(magic != MULTIBOOT_BOOTLOADER_MAGIC)
        printf("Wrong Mulitboot bootloader number: %x vs %x\n", magic, MULTIBOOT_BOOTLOADER_MAGIC);
    else
        printf("Valid Multiboot bootloader number check\n");
        
    // Check bit 6 to see if we have valid memory map
    if(!(mbd->flags >> 6 & 0x1))
        printf("Invalid Memory Map according to Grub!!!\n");    

    int  i = 0;
    for(i = 0; i < mbd->mmap_length; i+= sizeof(multiboot_memory_map_t))
    {
        multiboot_memory_map_t* mmt = (multiboot_memory_map_t*)(mbd->mmap_addr + i);
        printf("Start Address: %x | Length: %d | Size: %d | Type: %d\n", 
        mmt->addr,mmt->len,mmt->size,mmt->type);
    }
}




int main(multiboot_info_t* mbd, unsigned int magic)
{
    /*       CLS           */
    clear_screen();

    /*       DESCRIPTORS AND INTERRUPTS         */
    init_gdt();
    isr_install();

    get_memory_map(mbd, magic);

}
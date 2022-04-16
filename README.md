# TerminalOS (V3 probably?)
- This is the third version of Terminal OS, original linked [here](https://github.com/maheswarantp/TerminalOS)
- So again, a new version of Terminal OS, hopefully the last one where i can finally make this run on hardware
- EDIT: It can successfully run on real hardware, yay!!!

# Installation

### Packages needed
- gcc compiler and binutils (i686-elf-gcc and i686-elf-ld)
- nasm
- qemu
- grub2
- some linux distro

### Steps
-   Make a mnt directory to mount the disk image for qemu to use
    ```
        mkdir mnt
    ```
-   Use make to do the following:
    ```
        make makeGrubDisk
    ```
    and then
    ```
        make run
    ```
    clean with
    ```
        make clean          # doesnt remove the disk.img created by makeGrubDisk, use cleanAll to erase all
    ```

# Known issues:
- [x] Build process has to be run twice for kernel changes to take effect, no idea why
- [ ] FAT Filesystem code can access only the first block of data from disk for now, fix to be issued later.

# Features:
- [x] 32 bit protected mode operation
- [x] FAT-12 readonly filesystem
- [x] GRUB as bootloader
- [x] TTY Text mode based interface
- [ ] POSIX compiliance         (maybe?)

- [ ] Kernel, User seperation   (maybe?)
- [ ] Paging
- [ ] Higher half kernel

![filesystem image](assets/image.jpeg)
![irq0 timer](assets/image_2.jpeg)
!![IMG_20220406_091104](https://user-images.githubusercontent.com/58566451/163684685-1e17ce01-4f0a-432a-811c-1fbcefe010a2.jpg)

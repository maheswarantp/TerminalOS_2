sudo mount disk.img mnt/ -o offset=1048576
sudo cp build/kernel.elf mnt/boot/grub/
sudo umount mnt/
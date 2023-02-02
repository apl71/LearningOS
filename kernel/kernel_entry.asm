;
; 调用内核的main函数
; nasm kernel_entry.asm -f elf64 -o kernel_entry.o
;

[bits 32]
[extern kernel_main]
call kernel_main
jmp $
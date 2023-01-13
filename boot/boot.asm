;
; 引导C内核并进入32位保护模式
; nasm boot.asm -f bin -o boot.bin
; ld -o kernel.bin -Ttext 0x1000 kernel.o --oformat binary
; cat boot.bin kernel.bin > os-image
;

[org 0x7c00]

; 定义内核地址，该地址在链接内核时也要指定，使内核程序的地址偏移量与此一致
; ld -o kernel.bin -Ttext 0x1000 kernel.o --oformat binary
KERNEL_OFFSET equ 0x1000

mov [BOOT_DRIVE], dl            ; BIOS将启动盘的盘号放在dl中，我们保存下来

mov bp, 0x9000                  ; 设置实模式下的栈
mov sp, bp

mov bx, MSG_REAL_MODE           ; 打印提示信息
call print_string

call load_kernel                ; 加载内核到主存中

call switch_to_pm               ; 进入实模式，不会从实模式返回

jmp $

%include "io.asm"
%include "switch_to_pm.asm"
%include "gdt.asm"

[bits 16]
; 把内核代码加载到内存中
load_kernel:
    mov bx, MSG_LOAD_KERNEL
    call print_string

    mov bx, KERNEL_OFFSET       ; 读取后的存放地址是[es:bx]
    mov dh, 15                  ; 读取的扇区数量
    mov dl, [BOOT_DRIVE]        ; 读取的磁盘号
    call disk_load

    ret


[bits 32]

BEGIN_PM:
    mov ebx, MSG_PROT_MODE
    call print_string_pm

    call KERNEL_OFFSET          ; 跳转到内核地址的第一个字节
                                ; 此后控制权交给内核
    jmp $

; 全局变量
BOOT_DRIVE      db  0    ; 启动盘盘号
MSG_REAL_MODE   db  "Started in 16-bit Real Mode.", 0
MSG_PROT_MODE   db  "Successfully landed in 32-bit Protected Mode.", 0
MSG_LOAD_KERNEL db  "Loading kernel into memory.", 0

; 填充
times 510 - ($ - $$) db 0
dw 0xaa55
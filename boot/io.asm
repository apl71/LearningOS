;
; A copy of real_mode/io.asm
; 输入输出库
; %include "io.asm"
;

; 从磁盘读取块
; 前态：扇区数量存放在dh中，磁盘号存放在dl中，读取到[es:bx]地址中
disk_load:
    push dx                 ; 使用pusha不方便，因为我们要返回al的值，popa会覆盖这个寄存器
    
    mov ah, 0x02            ; 设置为读取磁盘模式
    mov al, dh              ; 设置扇区数量
    mov ch, 0x00            ; 柱面0
    mov dh, 0x00            ; 磁道0
    mov cl, 0x02            ; 2号扇区，即引导块之后的块

    int 0x13                ; 读取磁盘

    jc disk_error           ; 当CF置位（即读取出错）时跳转

    pop dx
    cmp dh, al              ; 如果dh和al相等，说明读取没问题
    jne disk_error
    ret

disk_error:
    mov bx, DISK_ERROR_MSG
    call print_string
    jmp $

%include "print_string.asm"

DISK_ERROR_MSG  db "Disk read error!", 0
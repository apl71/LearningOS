;
; A copy of protected_mode/print_string.asm
; 打印字符串
; %include "print_string.asm"
;

; 在16位实模式下使用BIOS打印字符串
; 打印以空字符结尾的字符串
; 前态：字符串首地址在bx中
print_string:
    pusha
    mov ah, 0x0e            ; 准备打印
    start_print_string:
    mov al, [bx]            ; 将待打印字符放入al
    cmp al, 0               ; 检查是否为空字符
    je end_print_string     ; 空字符则直接结束
    int 0x10                ; 打印字符
    add bx, 1               ; 移动到下一个字符
    jmp start_print_string
    end_print_string:
    popa
    ret

[bits 32]

VIDEO_MEMORY   equ 0xb8000
WHITE_ON_BLACK equ 0x0f

; 前态：待打印字符串的地址存放在ebx中，以空字符结尾
print_string_pm:
    pusha
    mov edx, VIDEO_MEMORY       ; ecx存放当前的显示缓冲区地址
    start_print_string_pm:
    mov al, [ebx]               ; 保存待打印字符
    mov ah, WHITE_ON_BLACK      ; 保存颜色设置
    cmp al, 0                   ; 空字符则结束
    je end_print_string_pm
    mov [edx], ax               ; 输出字符
    add ebx, 1
    add edx, 2
    jmp start_print_string_pm
    end_print_string_pm:
    popa
    ret
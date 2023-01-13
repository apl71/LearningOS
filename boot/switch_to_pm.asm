;
; A copy of protected_mode/switch_to_pm.asm
; 切换到保护模式
; %include "switch_to_pm.asm"
;

[bits 16]

switch_to_pm:
    cli                     ; 关中断
    
    lgdt [gdt_descriptor]   ; 设置GDTR
    
    mov eax, cr0
    or  eax, 0x1
    mov cr0, eax

    jmp CODE_SEG:init_pm    ; 远转移会自动更新cs寄存器


[bits 32]

; 初始化寄存器和栈
init_pm:
    mov ax, DATA_SEG        ; 旧的段已经无效了，设置新的段寄存器
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov ebp, 0x90000        ; 设置栈指针
    mov esp, ebp

    call BEGIN_PM
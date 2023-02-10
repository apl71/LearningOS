;
; 探测主存布局
;

[bits 16]

; 保存mmap长度的地址
mmap_entry equ 0x8000

; 用BIOS的0x15中断来获取主存布局
; 前态：es:di指向24字节的结构体
; 后态：bp保存项数量
init_mmap:
    mov bx, MSG_INIT_MMAP
    call print_string
    xor ebx, ebx                ; ebx置零 7ccd
    mov edx, 0x534d4150         ; magic number
    mov di, 0x8004              ; 设置es:di
    mov bp, 0                   ; bp用于计数
    mov es, bp
mmap_loop:
    mov eax, 0xe820             ; magic number
    mov ecx, 24                 ; 请求长为24字节的项
;    mov [es:di + 20], dword 1   ; 强制要求apci项
    int 0x15
    cmp eax, 0x534d4150         ; eax不为0x534d4150时报错
    jne fail_init_mmap
    jc  fail_init_mmap          ; CF置位时也报错
    inc bp
    cmp ebx, 0                  ; ebx为0则结束探测
    je mmap_finish
    add di, 24                  ; 跳转到下一项
    jmp mmap_loop
mmap_finish:
    mov [mmap_entry], bp
    clc                         ; 将CF置零
    ret
fail_init_mmap:
    mov bx, MSG_FAIL_MMAP
    call print_string
    stc
    ret

MSG_INIT_MMAP   db  "Detecting memory layout.", 0
MSG_FAIL_MMAP   db  "Fail to detect memory layout.", 0
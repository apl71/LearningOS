;
; A copy of protected_mode/gdt.asm
; 定义GDT结构
; %include "gdt.asm"
;

; 用宏定义使得定义SD更加方便
; 宏接受3个参数，分别是：
; %1 段基址 32b
; %2 段界限 20b
; %3 属性
; 属性两个字节，结构为：
; 15  14 13  12 11 10 9 8 7 6 5 4 3 2 1 0
;  G D/B  L AVL  0  0 0 0 P DPL S    TYPE
%macro segment_descriptor 3
dw %2 & 0xffff                          ; 段界限1 2字节
dw %1 & 0xffff                          ; 段基址1 2字节，和下面的字节合并得到段基址1
db (%1 >> 16) & 0xff                    ; 段基址1 1字节
dw ((%2 >> 8) & 0x0f00) | (%3 & 0xf0ff) ; 属性和段界限2 共2字节
db (%1 >> 24) & 0xff                    ; 段基址2 1字节
%endmacro

; 根据平面存储模式的属性构造两个常量值
; 代码段属性 0 0 0 0 G=1 D/B=1 L=0 AVL=0 P=1 DPL=00 S=1 TYPE=1010
; 数据段属性 0 0 0 0 G=1 D/B=1 L=0 AVL=0 P=1 DPL=00 S=1 TYPE=0010
FLAT_MODE_CODE_PROPERTY  equ  0xc09a
FLAT_MODE_DATA_PROPERTY  equ  0xc092

; 定义GDT内容
gdt_start:

gdt_null:   segment_descriptor    0x00000000,   0x00000,    0x0000                      ; 空描述符
gdt_code:   segment_descriptor    0x00000000,   0xfffff,    FLAT_MODE_CODE_PROPERTY     ; 代码描述符
gdt_data:   segment_descriptor    0x00000000,   0xfffff,    FLAT_MODE_DATA_PROPERTY     ; 数据描述符

gdt_end:

; GDT描述符
gdt_descriptor:
    dw  gdt_end - gdt_start - 1                 ; GDT size始终比实际大小小1
    dd  gdt_start

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start
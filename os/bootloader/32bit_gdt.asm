; In 32-bit mode, segmentation works differently. Now, the offset becomes an index to a segment descriptor (SD) in the GDT.
; This descriptor defines the base address (32 bits), the size (20 bits) and some flags, like readonly, permissions, etc.
; To add confusion, the data structures are split. 
; A diagram can be found on page 34 of this pdf (https://www.cs.bham.ac.uk/~exr/lectures/opsys/10_11/lectures/os-dev.pdf)
; GDT is the abbreviation for Global Descriptor Table


; don't remove the labels, they're needed to compute sizes and jumps
gdt_start:
    ; the GDT starts with a null 8-byte
    dd 0x0 ; 4 byte
    dd 0x0 ; 4 byte


; GDT for code segment. base = 0x00000000, length = 0xfffff
; for flags, refer to os-dev.pdf document, page 36
gdt_code:
    dw 0xffff ; segment length, bits 0-15
    dw 0x0 ; segment base, bits 0-15

    db 0x0 ; segment base, bits 16-23

    db 10011010b ; flags (8 bits)
    db 11001111b ; flags (4 bits) + segment length, bits 16-19

    db 0x0 ; segment base, bits 24-31


; GDT for data segment. base and length identical to code segment
; refer to the os-dev.pdf
gdt_data:
    dw 0xffff
    dw 0x0
    db 0x0
    db 10010010b
    db 11001111b
    db 0x0


gdt_end:


gdt_descriptor:
    dw gdt_end - gdt_start - 1 ; size (16 bit), always one less of its true size
    dd gdt_start ; 32bit address


; define some constants for later use
CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start
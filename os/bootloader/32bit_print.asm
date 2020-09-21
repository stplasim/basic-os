; This print string routine works in 32-bit mode
; Here we don't have BIOS interrupts. We directly manipulating the VGA video memory instead of calling int 0x10
; The VGA memory starts at address 0xb8000 and it has a text mode which is useful to avoid manipulating direct pixels.

[bits 32] ; using 32-bit protected mode

; this is how constants are defined
VIDEO_MEMORY equ 0xb8000
WHITE_ON_BLACK equ 0x0f ; the color byte for each character

print_string_pm:
    pusha
    mov edx, VIDEO_MEMORY


print_string_pm_loop:
    mov al, [ebx] ; [ebx] is the address of our character
    mov ah, WHITE_ON_BLACK

    cmp al, 0 ; check if end of string
    je print_string_pm_done

    mov [edx], ax ; store character + attribute in video memory
    add ebx, 1 ; next char
    add edx, 2 ; next video memory position

    jmp print_string_pm_loop


print_string_pm_done:
    popa
    ret
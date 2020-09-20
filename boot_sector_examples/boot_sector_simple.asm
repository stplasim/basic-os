; Infinite loop (e9 fd ff)

loop:
    jmp loop

; Fill the boot sector with 510 zeros minus the size of the previous code
times 510-($-$$) db 0

; Magic boot number
; To make sure that the "disk is bootable", the BIOS checks that bytes 511 and 512 of the alleged boot sector are bytes 0xAA55
dw 0xaa55

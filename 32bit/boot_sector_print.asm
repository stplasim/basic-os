print:
    pusha

    ; C like:
    ; while (string[i] != 0) { print string[i]; i++ }


; the comparison for string end (null byte)
start:
    mov al, [bx] ; 'bx' is the base address for the string
    cmp al, 0
    je done

    
    ; this is the part where we print with the BIOS help
    mov ah, 0x0e
    int 0x10 ; 'al' already contains the char


    ; increment the pointer and do next loop
    add bx, 1
    jmp start


; To store the return address, the CPU will help us. Instead of using a couple of jmp to call subroutines, we use ret
; To save the register data, there is also a special command which uses the stack: 
; pusha and its brother popa, which pushes all registers to the stack automatically and recovers them afterwards.
done:
    popa
    ret


print_nl:
    pusha

    mov ah, 0x0e
    mov al, 0x0a ; newline char
    int 0x10

    mov al, 0x0d ; carriage return
    int 0x10

    popa
    ret
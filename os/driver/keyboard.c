#include "keyboard.h"
#include "../cpu/ports.h"
#include "../cpu/isr.h"
#include "screen.h"
#include "../libs/string.h"
#include "../libs/function.h"
#include "../kernel/kernel.h"
#include <stdint.h>

#define BACKSPACE 0x0E
#define ENTER 0x1C
#define SC_MAX 57

static char key_buffer[256];

// This keyboard layout is still not completely adapted. 
// It should represent a QWERTZ keyboard
const char* sc_name[] = { "ERROR", "Esc", "1", "2", "3", "4", "5", "6",
                          "7", "8", "9", "0", "?", "/", "Backspace", "Tab", "Q", "W", "E",
                          "R", "T", "Z", "U", "I", "O", "P", "[", "]", "Enter", "Lctrl",
                          "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "`",
                          "LShift", "\\", "Y", "X", "C", "V", "B", "N", "M", ",", ".",
                          "-", "RShift", "Keypad *", "LAlt", "Spacebar"};

const char sc_ascii[] = { '?', '?', '1', '2', '3', '4', '5', '6',
                          '7', '8', '9', '0', '-', '=', '?', '?', 'Q', 'W', 'E', 'R', 'T', 'Y',
                          'U', 'I', 'O', 'P', '[', ']', '?', '?', 'A', 'S', 'D', 'F', 'G',
                          'H', 'J', 'K', 'L', ';', '\'', '`', '?', '\\', 'Z', 'X', 'C', 'V',
                          'B', 'N', 'M', ',', '.', '/', '?', '?', '?', ' '};

static void keyboard_callback(registers_t *regs) {
    /* The PIC leaves us the scancode in port 0x60 */
    uint8_t scancode = port_byte_in(0x60);

    if (scancode > SC_MAX)
        return;

    if (scancode == BACKSPACE) {
        backspace(key_buffer);
        bos_print_backspace();
    }
    else if (scancode == ENTER) {
        bos_print("\n");
        user_input(key_buffer); /* kernel-controlled function */
        key_buffer[0] = '\0';
    }
    else {
        char letter = sc_ascii[(int)scancode];
        /* Remember that bos_print only accepts char[] */
        char str[2] = {letter, '\0'};
        append(key_buffer, letter);
        bos_print(str);
    }

    UNUSED(regs);
}

void init_keyboard() {
    register_interrupt_handler(IRQ1, keyboard_callback);
}
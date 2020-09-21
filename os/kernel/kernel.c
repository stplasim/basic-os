#include "kernel.h"
#include "../cpu/isr.h"
#include "../driver/screen.h"
#include "../libs/string.h"
#include "../libs/mem.h"
#include <stdint.h>

void kernel_mail() {
    isr_install();
    irq_install();

    asm("int $2");
    asm("int $3");

    bos_print("Welcome to the Basic os.\n");
    bos_print("Type something, it will go through the kernel\n");
    bos_print("Type END to halt the CPU or PAGE to request a kmalloc()\\n");
    bos_print(">");
}

void user_input(char* input) {
    // END command
    if(strcmp(input, "END") == 0) {
        bos_print("Stopping the CPU. Bye!\n");
        asm volatile("hlt");
    }

    // PAGE command
    else if (strcmp(input, "PAGE") == 0) {
        uint32_t addr;
        uint32_t page = bos_malloc(1000, 1, &addr);

        char page_str[16] = "";
        hex_to_ascii(page, page_str);

        char real_str[16] = "";
        hex_to_ascii(addr, real_str);

        bos_print("Page: ");
        bos_print(page_str);
        bos_print(", physical address: ");
        bos_print(real_str);
        bos_print("\n");
    }

    bos_print("You typed: ");
    bos_print(input);
    bos_print("\n");
    bos_print(">");
}
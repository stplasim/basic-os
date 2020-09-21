#ifndef OS_PORTS_H
#define OS_PORTS_H

#include <stdint.h>

unsigned char port_byte_in (uint16_t port);
unsigned short port_word_in (uint16_t port);

void port_byte_out (uint16_t port, uint8_t data);
void port_word_out (uint16_t port, uint16_t data);

#endif //OS_PORTS_H

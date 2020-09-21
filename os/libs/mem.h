#ifndef OS_MEM_H
#define OS_MEM_H

#include <stdint.h>
#include <stddef.h>

void mem_copy(uint8_t* src, uint8_t* dest, int bytes);
void mem_set(uint8_t* dest, uint8_t value, uint8_t len);

/* At this stage there is no 'free' implemented. */
uint32_t bos_malloc(size_t size, int align, uint32_t* addr);

#endif // OS_MEM_H

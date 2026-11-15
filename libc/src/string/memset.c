#include "string.h"
#include "common.h"

// Avoid replacing memset's code with call to itself
__LIBC_NO_LOOP_DISTRIBUTE
void* memset(void* ptr, int value, long unsigned num) {
    uint8_t* p = (uint8_t*)ptr;

    for (size_t i = 0; i < num; i++) {
        p[i] = value;
    }

    return ptr;
}

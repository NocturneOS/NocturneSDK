#include <stddef.h>
#include "common.h"

// Avoid replacing strlen's code with call to itself
__LIBC_NO_LOOP_DISTRIBUTE
size_t strlen(const char *str){
    if(str == NULL) {
        return 0;
    }

    size_t len = 0;
    while (str[len] != 0){
        len++;
    }
    return len;
}

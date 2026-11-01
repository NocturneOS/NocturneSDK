#include <stdio.h>
__attribute__((noreturn)) void abort() {
    printf("abort(): program aborted.\n");

    __asm__ volatile("ud2");

    while(1);
}
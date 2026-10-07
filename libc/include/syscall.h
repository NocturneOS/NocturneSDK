#pragma once

#include "stddef.h"

#define SYS_EXIT 2
#define SYS_PROCESS_EXIT 3

#define SYS_GETERROR 4

#define SYS_WAITPID 5

#define SYS_OPEN 7
#define SYS_CLOSE 8
#define SYS_READ 9
#define SYS_WRITE 10
#define SYS_SEEK 11
#define SYS_TELL 12

#define SYS_SBRK 13

#define SYS_EVENT_QUEUE_OPEN 14

#define SYS_FLUSH 15

#define SYS_TIME 16
#define SYS_MILLISLEEP 17
#define SYS_NANOSLEEP 18

#define SYS_YIELD 19

#define SYS_GETCWD 21

size_t _syscall1(size_t num, size_t p1);
size_t _syscall2(size_t num, size_t p1, size_t p2);
size_t _syscall3(size_t num, size_t p1, size_t p2, size_t p3);
size_t _syscall4(size_t num, size_t p1, size_t p2, size_t p3, size_t p4);
size_t _syscall5(size_t num, size_t p1, size_t p2, size_t p3, size_t p4,
                 size_t p5);

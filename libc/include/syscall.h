#pragma once

#include "stddef.h"

#define SYS_EXIT 0
#define SYS_PROCESS_EXIT 1

#define SYS_GETERROR 2

#define SYS_WAITPID 3

#define SYS_OPEN 4
#define SYS_CLOSE 5
#define SYS_READ 6
#define SYS_WRITE 7
#define SYS_SEEK 8
#define SYS_TELL 9

#define SYS_SBRK 10

#define SYS_EVENT_QUEUE_OPEN 11

#define SYS_FLUSH 12

#define SYS_MILLISLEEP 13
#define SYS_NANOSLEEP 14

#define SYS_YIELD 15

#define SYS_VIDEO_ACQUIRE 16

#define SYS_GETCWD 17

#define SYS_CHDIR 18

#define SYS_PROCRUN 19

#define SYS_MREQUEST 20
#define SYS_MFREE 21

#define SYS_GETTIMEOFDAY 22

#define SYS_VIDEO_CONTROL 23
#define SYS_VIDEO_RELEASE 24

#define SYS_GETDIRENTS 25

size_t _syscall1(size_t num, size_t p1);
size_t _syscall2(size_t num, size_t p1, size_t p2);
size_t _syscall3(size_t num, size_t p1, size_t p2, size_t p3);
size_t _syscall4(size_t num, size_t p1, size_t p2, size_t p3, size_t p4);
size_t _syscall5(size_t num, size_t p1, size_t p2, size_t p3, size_t p4,
                 size_t p5);

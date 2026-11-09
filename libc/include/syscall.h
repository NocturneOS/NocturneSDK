#pragma once

#include "stddef.h"

#include "sys/syscall.h"

size_t _syscall1(size_t num, size_t p1);
size_t _syscall2(size_t num, size_t p1, size_t p2);
size_t _syscall3(size_t num, size_t p1, size_t p2, size_t p3);
size_t _syscall4(size_t num, size_t p1, size_t p2, size_t p3, size_t p4);
size_t _syscall5(size_t num, size_t p1, size_t p2, size_t p3, size_t p4,
                 size_t p5);

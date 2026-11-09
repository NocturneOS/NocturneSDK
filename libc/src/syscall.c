/**
 * @file syscall.c
 * @author NDRAEY >_
 * @brief Syscall management
 * @version 0.3.4
 * @date 2023-12-10
 * @copyright Copyright SayoriOS Team (c) 2023;
 * @copyright NocturneOS developers (c) 2025-2026;
 */

#include "syscall.h"
#include "stddef.h"

size_t _syscall1(size_t num, size_t p1) {
#if defined __x86_64__
  register size_t rax __asm__("rax") = num;
  register size_t rdi __asm__("rdi") = p1;

  __asm__ volatile("syscall" : "+r"(rax) : "r"(rdi) : "rcx", "r11", "memory");

  return rax;
#else
  size_t result = 0;
  __asm__ volatile("int $0x80" : "=a"(result) : "a"(num), "b"(p1));
  return result;
#endif
}

size_t _syscall2(size_t num, size_t p1, size_t p2) {
#if defined __x86_64__
  register size_t rax __asm__("rax") = num;
  register size_t rdi __asm__("rdi") = p1;
  register size_t rsi __asm__("rsi") = p2;

  __asm__ volatile("syscall"
                   : "+r"(rax)
                   : "r"(rdi), "r"(rsi)
                   : "rcx", "r11", "memory");
  return rax;
#else
  size_t result = 0;
  __asm__ volatile("int $0x80" : "=a"(result) : "a"(num), "b"(p1), "c"(p2));
  return result;
#endif
}

size_t _syscall3(size_t num, size_t p1, size_t p2, size_t p3) {
#if defined __x86_64__
  register size_t rax __asm__("rax") = num;
  register size_t rdi __asm__("rdi") = p1;
  register size_t rsi __asm__("rsi") = p2;
  register size_t rdx __asm__("rdx") = p3;

  __asm__ volatile("syscall"
                   : "+r"(rax)
                   : "r"(rdi), "r"(rsi), "r"(rdx)
                   : "rcx", "r11", "memory");
  return rax;
#else
  size_t result = 0;
  __asm__ volatile("int $0x80"
                   : "=a"(result)
                   : "a"(num), "b"(p1), "c"(p2), "d"(p3));
  return result;
#endif
}

size_t _syscall4(size_t num, size_t p1, size_t p2, size_t p3, size_t p4) {
#if defined __x86_64__
  register size_t rax __asm__("rax") = num;
  register size_t rdi __asm__("rdi") = p1;
  register size_t rsi __asm__("rsi") = p2;
  register size_t rdx __asm__("rdx") = p3;
  register size_t r10 __asm__("r10") = p4;

  __asm__ volatile("syscall"
                   : "+r"(rax)
                   : "r"(rdi), "r"(rsi), "r"(rdx), "r"(r10)
                   : "rcx", "r11", "memory");
  return rax;
#else
  size_t result = 0;
  __asm__ volatile("int $0x80"
                   : "=a"(result)
                   : "a"(num), "b"(p1), "c"(p2), "d"(p3), "S"(p4));
  return result;
#endif
}

size_t _syscall5(size_t num, size_t p1, size_t p2, size_t p3, size_t p4,
                 size_t p5) {
#if defined __x86_64__
  register size_t rax __asm__("rax") = num;
  register size_t rdi __asm__("rdi") = p1;
  register size_t rsi __asm__("rsi") = p2;
  register size_t rdx __asm__("rdx") = p3;
  register size_t r10 __asm__("r10") = p4;
  register size_t r8 __asm__("r8") = p5;

  __asm__ volatile("syscall"
                   : "+r"(rax)
                   : "r"(rdi), "r"(rsi), "r"(rdx), "r"(r10), "r"(r8)
                   : "rcx", "r11", "memory");
  return rax;
#else
  size_t result = 0;
  __asm__ volatile("int $0x80"
                   : "=a"(result)
                   : "a"(num), "b"(p1), "c"(p2), "d"(p3), "S"(p4), "D"(p5));
  return result;
#endif
}

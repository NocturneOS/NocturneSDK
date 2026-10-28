#include "exit.h"
#include "syscall.h"

__attribute__((noreturn)) void exit(int status) {
  _syscall1(SYS_EXIT, status);

  while (1)
    ;
}

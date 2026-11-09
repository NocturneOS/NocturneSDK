#pragma once

#include "sys/types.h"

typedef void (*sighandler_t)(int);

sighandler_t signal(int sig, sighandler_t hdl);

int kill(pid_t pid, int sig);
int raise(int sig);

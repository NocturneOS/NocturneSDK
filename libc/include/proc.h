#pragma once

#include <stddef.h>
#include <sys/types.h>

#define PROCRUN_NOSTDIN (1 << 0)
#define PROCRUN_NOSTDOUT (1 << 1)
#define PROCRUN_NOSTDERR (1 << 2)

int proc_run(const char *path, const char **argv, size_t argc, size_t flags);
int waitpid(pid_t pid);

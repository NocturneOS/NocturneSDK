#pragma once

#include <stddef.h>
#include <sys/types.h>

#define NAME_MAX 256

struct dirent {
  ino_t node_id;

  char name[NAME_MAX];
};

int getdirents(int fd, struct dirent *out_ptr, size_t count);

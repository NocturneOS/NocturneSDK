#pragma once

#include <stddef.h>
#include <sys/types.h>
#include <stdbool.h>

#define NAME_MAX 256

struct dirent {
  ino_t node_id;

  char d_name[NAME_MAX];
};

int getdirents(int fd, struct dirent *out_ptr, size_t count);



typedef struct __dirstream DIR;

#define DIR_BATCH 4

struct __dirstream {
  int fd;
  size_t index;
  size_t count;
  bool eof;

  struct dirent entries[DIR_BATCH];
};

DIR* opendir(const char* path);
struct dirent* readdir(DIR* dir);
void closedir(DIR* dir);

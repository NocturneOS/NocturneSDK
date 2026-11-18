#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>

DIR *opendir(const char *path) {
  int fd = open(path, O_DIRECTORY);

  if (fd == -1) {
    // errno propagation from `open()`
    return NULL;
  }

  DIR* dir = calloc(1, sizeof(DIR));

  if(dir == NULL) {
    close(fd);
    // XXX: errno?
    return NULL;
  }

  dir->fd = fd;

  return dir;
}

struct dirent *readdir(DIR *dir) {
  if (dir->index >= dir->count) {
    // Refill

    if (dir->eof) {
      return NULL;
    }

    int n = getdirents(dir->fd, dir->entries, DIR_BATCH);

    if(n < 0) {
        // errno propagation from `getdirents()`
        return NULL;
    }

    if(n == 0) {
        dir->eof = true;
        return NULL;
    }

    dir->count = n;
    dir->index = 0;
  }

  return &dir->entries[dir->index++];
}

void closedir(DIR *dir) {
    if(dir != NULL) {
        free(dir);
    }
}
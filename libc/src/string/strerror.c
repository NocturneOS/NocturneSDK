#include "errno.h"
#include <string.h>

char *strerror(int errnum) {
  switch (errnum) {
  case EAGAIN:
    return "Try again";
  case ENOTDIR:
    return "Not a directory";
  case ENOSYS:
    return "Not implemented";
  case EIO:
    return "I/O error";
  case ENOENT:
    return "No file or directory";
  default:
    return "Unknown";
  }
}

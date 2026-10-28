#ifndef _ERRNO_H
#define _ERRNO_H

extern int errno;

#define ENOTSUP 14
#define ENOSYS 15
#define EINVAL 5
#define ENOMEM 16
#define EAGAIN 3
#define EBADF 7
#define EIO 11
#define ENOENT 12
#define EACCES 13
#define ENOSPC 18

#define EDOM 1000
#define EILSEQ 1001
#define ERANGE 1001

#endif

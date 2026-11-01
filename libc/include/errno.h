#ifndef _ERRNO_H
#define _ERRNO_H

extern int errno;

#define EEXIST 1
#define EAGAIN 3
#define EINVAL 5
#define EBADF 7
#define ESPIPE 9
#define EIO 11
#define ENOENT 12
#define EACCES 13
#define ENOTSUP 14
#define ENOSYS 15
#define EROFS 16
#define ENOMEM 17
#define ENOSPC 18
#define EPERM 20
#define EBUSY 21
#define ENOEXEC 22

// Errors below are not thrown by kernel. They are thrown in libc itself.

#define EDOM 1000
#define EILSEQ 1001
#define ERANGE 1002

// Errors below are not implemented by NocturneOS, but used by UNIX.
// Kernel doesn't throw them, but those errors are used for
// UNIX/POSIX-compatibility.

#define EFAULT 9000
#define EFBIG 9001
#define ECHILD 9002
#define EDEADLK 9003
#define E2BIG 9004
#define ESRCH 9006
#define ENXIO 9007
#define ENOTTY 9008
#define EPIPE 9009
#define ENODEV 9011
#define EXDEV 9012
#define EINTR 9013
#define EISDIR 9014
#define EMFILE 9015
#define EMLINK 9016
#define ENAMETOOLONG 9017
#define ENFILE 9018
#define ENOLCK 9019
#define ENOTDIR 9020
#define ENOTEMPTY 9021

#endif

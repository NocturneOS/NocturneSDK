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

#define EFAULT 2000
#define EFBIG 2001
#define ECHILD 2002
#define EDEADLK 2003
#define E2BIG 2004
#define ESRCH 2006
#define ENXIO 2007
#define ENOTTY 2008
#define EPIPE 2009
#define ENODEV 2011
#define EXDEV 2012
#define EINTR 2013
#define EISDIR 2014
#define EMFILE 2015
#define EMLINK 2016
#define ENAMETOOLONG 2017
#define ENFILE 2018
#define ENOLCK 2019
#define ENOTDIR 2020
#define ENOTEMPTY 2021

#endif

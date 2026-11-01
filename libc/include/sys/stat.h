#pragma once

#include <sys/types.h>
#include <time.h>

// From glibc.
#define S_IFMT 0170000   /* These bits determine file type.  */
#define S_IFDIR 0040000  /* Directory.  */
#define S_IFCHR 0020000  /* Character device.  */
#define S_IFBLK 0060000  /* Block device.  */
#define S_IFREG 0100000  /* Regular file.  */
#define S_IFIFO 0010000  /* FIFO.  */
#define S_IFLNK 0120000  /* Symbolic link.  */
#define S_IFSOCK 0140000 /* Socket.  */

#define __S_ISTYPE(mode, mask) (((mode) & __S_IFMT) == (mask))

#define S_ISDIR(mode) __S_ISTYPE((mode), __S_IFDIR)
#define S_ISCHR(mode) __S_ISTYPE((mode), __S_IFCHR)
#define S_ISBLK(mode) __S_ISTYPE((mode), __S_IFBLK)
#define S_ISREG(mode) __S_ISTYPE((mode), __S_IFREG)
#define S_ISFIFO(mode) __S_ISTYPE((mode), __S_IFIFO)
#define S_ISLNK(mode) __S_ISTYPE((mode), __S_IFLNK)

// stat. Some of fields are zeroed out in NocturneOS, and left for POSIX
// compatibility
struct stat {
  dev_t st_dev; // ID of device containing file (SET TO 0 in NocturneOS)

  ino_t st_ino;   // File number (Linux INO / Nocturne's NodeId)
  mode_t st_mode; // File mode

  nlink_t st_nlink; // Number of links to the file (SET TO 0 in NocturneOS)

  uid_t st_uid; // File owner's user id.
  uid_t st_gid; // File owner's group id.  (SET TO 0 in NocturneOS)

  dev_t st_rdev; // Device ID (SET TO 0 in NocturneOS)

  off_t st_size; // File size

  time_t st_atime; // Access time
  time_t st_mtime; // Modification time
  time_t st_ctime; // Creation time

  blksize_t st_blksize; // Block size for this concrete file.
  blkcnt_t st_blocks;   // Number of blocks allocated for this object.
};

int stat(const char *restrict file, struct stat *restrict buf);
int fstat(int fd, struct stat *buf);

int mkdir(const char *path, mode_t mode);

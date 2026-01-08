#pragma once

#define SEEK_SET	0
#define SEEK_CUR	1
#define SEEK_END	2

#define EOF (-1)

__attribute__((format(printf, 1, 2)))
void printf(const char *text, ...);

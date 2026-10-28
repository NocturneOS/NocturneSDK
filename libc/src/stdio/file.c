#include "file.h"
#include "stdio.h"
#include "stdlib.h"
#include <assert.h>

static size_t chrmode2intmode(const char* mode) {
    size_t imode = 0;

    char mode_byte;

    while((mode_byte = *mode++)) {
        switch(mode_byte) {
            case 'r':
                imode |= O_READ;
                break;
            case 'w':
                imode |= O_WRITE;
                break;
            case 'a':
                imode |= O_APPEND;
                break;
        }
    }

    return imode;
}

FILE *fopen(const char *filename, const char *mode) {
    assert(mode != NULL);

    FILE* fp = malloc(sizeof(FILE));

    if(fp == NULL) {
        return NULL;
    }

    size_t imode = chrmode2intmode(mode);

    int fd = open(filename, imode);

    if(fd < 0) {
        free(fp);

        return NULL;
    }

    fp->__fd = fd;
    fp->__last_read_end = false;

    return fp;
}

void fclose(FILE *stream) {
    assert(stream != NULL);

    close(stream->__fd);

    free(stream);
}

long unsigned int fread(void *buffer, long unsigned int size, long unsigned int count, FILE *stream) {
    int rd_count = read(stream->__fd, size, count, buffer);

    if(rd_count == 0) {
        stream->__last_read_end = true;
    }

    return rd_count;
}

long unsigned int fwrite(const void *buffer, long unsigned int size, long unsigned int count, FILE *stream) {
    int wr_count = write(stream->__fd, size, count, buffer);

    return wr_count;
}

int fseek(FILE *stream, long offset, int origin) {
    return seek(stream->__fd, offset, origin);
}

long int ftell(FILE *stream) {
    return tell(stream->__fd);
}

int feof(FILE* stream) {
    return (int)stream->__last_read_end;
}
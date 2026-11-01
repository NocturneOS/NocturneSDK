#include <stdio.h>

FILE __stdin = { .__fd = 0, .__mode = 0, .__last_read_end = false };
FILE __stdout = { .__fd = 1, .__mode = 0, .__last_read_end = false };
FILE __stderr = { .__fd = 2, .__mode = 0, .__last_read_end = false };

FILE* stdin = &__stdin;
FILE* stdout = &__stdout;
FILE* stderr = &__stderr;
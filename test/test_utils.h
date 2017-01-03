#include <stdio.h>

#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#define MEMD_DISPLAY_OFF    0
#define MEMD_DISPLAY_ASCII  1

int is_big_endian(void);

void memdump(void *start, unsigned int length, unsigned int display);

#endif

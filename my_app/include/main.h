#ifndef MAIN_H
#define MAIN_H

#include "utils.h"
#define ERROR_EXIT(ret, msg) do { \
    if (ret == -1) { \
        fprintf(stderr, "%s failed: %s (errno=%d)\n", \
                msg, strerror(errno), errno); \
        exit(EXIT_FAILURE); \
    } \
} while (0)

#endif // MAIN_H

#ifndef INCLUDE_CUY_CLI_FLAG_H_
#define INCLUDE_CUY_CLI_FLAG_H_

#include <stdbool.h>

enum {
    K_MAX_ARGS = 5,
};

typedef enum {
    FLAG_INDEX_HELP = 0,
    FLAG_INDEX_VERSION = 1,
    FLAG_INDEX_FILE = 2,
    FLAG_INDEX_LINES = 3,
} CliFlagIndex;

typedef struct {
    char* short_str;
    char* long_str;
    char* description;
    bool is_used;
    int nbr_args;
    char* args[K_MAX_ARGS];
} CliFlag;

static const int kTotalCliFlags = 4;

#endif  // INCLUDE_CUY_CLI_FLAG_H_

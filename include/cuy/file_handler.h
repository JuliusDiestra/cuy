#ifndef INCLUDE_CUY_FILE_HANDLER_H_
#define INCLUDE_CUY_FILE_HANDLER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

#include "cuy/status_code.h"

typedef enum {
    FILE_READ = 0,
    FILE_WRITE = 1,
} FileOpenMode;

StatusCode file_open(const char* file_path, const FileOpenMode mode, int* fd);

StatusCode file_close(const int fd);

#ifdef __cplusplus
}
#endif

#endif  // INCLUDE_CUY_FILE_HANDLER_H_


#include "file_handler.h"

#include <sys/stat.h>
#include <stdbool.h>

static bool file_exists(const char* file_path) {
    struct stat buffer;
    return (stat(file_path, &buffer) == 0);
}

StatusCode file_open(const char* file_path, const char* mode, FILE** file) {
    *file = NULL;
    if (!file_exists(file_path)) {
        return CUY_ERROR_FILE_HANDLER_FILE_DOES_NOT_EXIST;
    }
    *file = fopen(file_path, mode);
    if (*file == NULL) {
        return CUY_ERROR_FILE_HANDLER_FILE_OPEN;
    }
}

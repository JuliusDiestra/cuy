
#include "cuy/file_handler.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

static bool file_exists(const char* file_path) {
    struct stat buffer;
    return (stat(file_path, &buffer) == 0);
}

StatusCode file_open(const char* file_path, const FileOpenMode mode, int* fd) {
    if (!file_exists(file_path)) {
        return CUY_ERROR_FILE_HANDLER_FILE_DOES_NOT_EXIST;
    }
    int oflag = 0;
    switch (mode) {
        case FILE_READ:
            oflag = O_RDONLY;
            break;
        case FILE_WRITE:
            oflag = O_WRONLY;
            break;
        default:
            return CUY_ERROR_FILE_HANDLER_OPEN_MODE;
    }
    *fd = open(file_path, oflag);
    if (*fd < 0) {
        return CUY_ERROR_FILE_HANDLER_FILE_OPEN;
    }
    return CUY_SUCCESS;
}

StatusCode file_close(const int fd) {
    int close_result = close(fd);
    if (close_result != 0) {
        return CUY_ERROR_FILE_HANDLER_FILE_CLOSE;
    }
    return CUY_SUCCESS;
}


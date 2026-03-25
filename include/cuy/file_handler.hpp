#ifndef INCLUDE_CUY_FILE_HANDLER_H_
#define INCLUDE_CUY_FILE_HANDLER_H_

StatusCode file_open(const char* filename, const char* mode, FILE** file);

StatusCode file_close(FILE* file);

#endif  // INCLUDE_CUY_FILE_HANDLER_H_

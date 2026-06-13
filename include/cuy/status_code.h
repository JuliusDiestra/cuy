#ifndef INCLUDE_KLEINUR_STATUS_CODE_H_
#define INCLUDE_KLEINUR_STATUS_CODE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

typedef enum {
    CUY_SUCCESS = 0,
    CUY_ERROR_ARG_PARSER_FLAG_FILE_MISSING_ARG = 1,
    CUY_ERROR_ARG_PARSER_FLAG_LINES_MISSING_ARG = 2,
    CUY_ERROR_ARG_PARSER_VALIDATION_FILE_LINES = 3,
    CUY_ERROR_FILE_HANDLER_FILE_DOES_NOT_EXIST = 4,
    CUY_ERROR_FILE_HANDLER_OPEN_MODE = 5,
    CUY_ERROR_FILE_HANDLER_FILE_OPEN = 6,
    CUY_ERROR_FILE_HANDLER_FILE_CLOSE = 7,
    CUY_ERROR_LINES_FILE_SIZE = 8,
    CUY_ERROR_LINES_MAP_FILE = 9,
    /*
    CUY_ERROR_FILE_HANDLER_FILE_CLOSE_NULL = 7,
    CUY_ERROR_FILE_HANDLER_FILE_CLOSE = 8,
    */
    CUY_ERROR_UNKNOWN = 99,
} StatusCode;

// @brief Print a message corresponding to the status code.
// @param code The status code to print the message for.
void status_code_print_message(StatusCode code);

// @brief Check if the status code indicates success.
// @param code The status code to check.
// @return true if the status code indicates success, false otherwise.
bool status_code_is_success(StatusCode code);

#ifdef __cplusplus
}
#endif

#endif  // INCLUDE_KLEINUR_STATUS_CODE_H_


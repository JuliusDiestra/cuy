#ifndef INCLUDE_KLEINUR_STATUS_CODE_H_
#define INCLUDE_KLEINUR_STATUS_CODE_H_

#include <stdbool.h>

typedef enum {
    CUY_SUCCESS = 0,
    CUY_ERROR_ARG_PARSER_FLAG_FILE_MISSING_ARG = 1,
    CUY_ERROR_ARG_PARSER_FLAG_LINES_MISSING_ARG = 2,
    CUY_ERROR_ARG_PARSER_VALIDATION_FILE_LINES = 3,
    CUY_ERROR_FILE_HANDLER_FILE_DOES_NOT_EXIST = 4,
    CUY_ERROR_FILE_HANDLER_FILE_OPEN = 5;
    CUY_ERROR_UNKNOWN = 99,
} StatusCode;

// @brief Print a message corresponding to the status code.
// @param code The status code to print the message for.
void status_code_print_message(StatusCode code);

// @brief Check if the status code indicates success.
// @param code The status code to check.
// @return true if the status code indicates success, false otherwise.
bool status_code_is_success(StatusCode code);

#endif  // INCLUDE_KLEINUR_STATUS_CODE_H_


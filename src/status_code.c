#include "cuy/status_code.h"

#include <stdio.h>

void status_code_print_message(StatusCode code) {
    switch (code) {
        case CUY_SUCCESS:
            printf("Operation completed successfully.\n");
            break;
        case CUY_ERROR_ARG_PARSER_FLAG_FILE_MISSING_ARG:
            printf("Error: Flag --file or -f is missing argument.\n");
            break;
        case CUY_ERROR_ARG_PARSER_FLAG_LINES_MISSING_ARG:
            printf("Error: Flag --lines or -l is missing argument.\n");
            break;
        case CUY_ERROR_ARG_PARSER_VALIDATION_FILE_LINES:
            printf("Error: Flag --lines or -l must be used with --file or -f.\n");
            break;
        case CUY_ERROR_FILE_HANDLER_FILE_DOES_NOT_EXIST:
            printf("Error: File argument of --file does not exists.\n");
            break;
        case CUY_ERROR_UNKNOWN:
            printf("Error: An unknown error occurred.\n");
            break;
        default:
            printf("Error: Unrecognized status code.\n");
            break;
    }
}

bool status_code_is_success(StatusCode code) {
    return code == CUY_SUCCESS;
}


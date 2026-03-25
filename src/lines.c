
#include "cuy/lines.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <stddef.h>
#include <ctype.h>
#include <sys/mman.h>
#include <unistd.h>

#include "cuy/file_handler.h"

static const int kNumLength = 6;
static const int kMaxArgLength = kNumLength + kNumLength + 1; // Added one for ":"

typedef enum {
    ARG_CASE_UNKNOWN = 0,
    ARG_CASE_1 = 1,
    ARG_CASE_2 = 2,
    ARG_CASE_3 = 3,
    ARG_CASE_4 = 4,
} ArgCase;

// Formats accepted:
//      CASE 1 : "num1"
//      CASE 2 : ":num2"
//      CASE 3 : "num1:"
//      CASE 4 : "num1:num2"
static StatusCode parse_lines_arg(char* lines_arg, size_t* start_line, size_t* end_line, ArgCase* arg_case) {

    const int arg_length = strlen(lines_arg);
    if (arg_length > kMaxArgLength) {
        // TODO : Add custon status code.
        return CUY_ERROR_UNKNOWN;
    }

    // Flags to start storing
    bool flag_num1 = false;
    bool flag_num2 = false;
    char num1_string[kNumLength+1];
    char num2_string[kNumLength+1];
    int ix1 = 0;
    int ix2 = 0;
    bool is_colon_used = false;
    for (int ix = 0; ix < arg_length; ++ix) {
        char current_char = lines_arg[ix];
        bool is_first_char = (ix == 0);
        if ( ix1 > kNumLength || ix2 > kNumLength) {
            // Return error too long numbers
            // TODO : Add custon status code.
            return CUY_ERROR_UNKNOWN;
        }
        if (isdigit(current_char)) {
            if (is_first_char) {
                flag_num1 = true;
                flag_num2 = false;
            }
            if (flag_num1) {
                num1_string[ix1] = current_char;
                ++ix1;
            }
            if (flag_num2) {
                num2_string[ix2] = current_char;
                ++ix2;
            }
        } else if (current_char == ':') {
            if (is_colon_used) {
                // Return error for double colon.
                // TODO : Add custon status code.
                return CUY_ERROR_UNKNOWN;
            } else {
                flag_num1 = false;
                flag_num2 = true;
                is_colon_used = true;
            }
        } else {
            // Return error unknown character.
            // TODO : Add custon status code.
            return CUY_ERROR_UNKNOWN;
        }
    }
    num1_string[ix1] = '\0';
    num2_string[ix2] = '\0';

    *start_line = strtoul(num1_string, NULL, 10);
    *end_line = strtoul(num2_string, NULL, 10);

    bool is_num1_set = (*start_line != 0) && (ix1 != 0);
    bool is_num2_set = (*end_line != 0) && (ix2 != 0);

    int is_case_one = is_num1_set && !is_colon_used && !is_num2_set;
    int is_case_two = !is_num1_set && is_colon_used && is_num2_set;
    int is_case_three = is_num1_set && is_colon_used && !is_num2_set;
    int is_case_four = is_num1_set && is_colon_used && is_num2_set;

    bool pass_case_verification = (is_case_one + is_case_two + is_case_three + is_case_four) == 1;

    if (!pass_case_verification) {
        // Error passing case verification
        // TODO : Add custon status code.
        return CUY_ERROR_UNKNOWN;
    }

    if (is_case_one) {
        *arg_case = ARG_CASE_1;
    } else if (is_case_two) {
        *arg_case = ARG_CASE_2;
    } else if (is_case_three) {
        *arg_case = ARG_CASE_3;
    } else if (is_case_four) {
        *arg_case = ARG_CASE_4;
    } else {
        // Error all are negative. Should never happen
        // TODO : Add custon status code.
        return CUY_ERROR_UNKNOWN;
    }

    return CUY_SUCCESS;
}

static StatusCode print_line(char* data, const size_t size, const size_t start_index) {
    size_t line_length = 0;
    while (start_index + line_length  < size && data[start_index + line_length] != '\n') {
        ++line_length;
    }
    ssize_t status_write = write(STDOUT_FILENO, &data[start_index], line_length + 1);
    if (status_write != line_length + 1) {
        // Return custom status code
        return CUY_ERROR_UNKNOWN;
    } else {
        return CUY_SUCCESS;
    }
}

static StatusCode run_case_1_logic(char* data, size_t size, size_t target_line) {
    size_t current_line = 1;
    for (size_t ix = 0; ix < size; ++ix) {
        if (current_line == target_line) {
            StatusCode status_print = print_line(data, size, ix);
            if (!status_code_is_success(status_print)) {
                return status_print;
            }
            break;
        }
        if (data[ix] == '\n') {
            ++current_line;
        }
    }
    return CUY_SUCCESS;
}

StatusCode run_lines(char* file_path, char* lines_arg) {
    int fd;
    StatusCode file_open_status = file_open(file_path, FILE_READ, &fd);
    if (!status_code_is_success(file_open_status)) {
        return file_open_status;
    }

    // File size
    struct stat st;

    int fstat_status = fstat(fd, &st);

    if (fstat_status < 0) {
        StatusCode file_close_status = file_close(fd);
        if (!status_code_is_success(file_close_status)) {
            return file_close_status;
        }
        return CUY_ERROR_LINES_FILE_SIZE;
    }

    size_t size = st.st_size;

    // Map file to memory
    char* data = mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (data == MAP_FAILED) {
        StatusCode file_close_status = file_close(fd);
        if (!status_code_is_success(file_close_status)) {
            return file_close_status;
        }
        return CUY_ERROR_LINES_MAP_FILE;
    }

    size_t start_line = 0;
    size_t end_line = 0;
    ArgCase arg_case = ARG_CASE_UNKNOWN;

    StatusCode lines_arg_status = parse_lines_arg(lines_arg, &start_line, &end_line, &arg_case);
    if (!status_code_is_success(lines_arg_status)) {
        return lines_arg_status;
    }

    StatusCode logic_status = CUY_ERROR_UNKNOWN;
    switch (arg_case) {
        case ARG_CASE_1:
            printf("CASE 1\n");
            // Run case 1 logic
            logic_status = run_case_1_logic(data, size, start_line);
            break;
        case ARG_CASE_2:
            printf("CASE 2\n");
            // Run case 2 logic
            //logic_status = run_case_2_logic(data, size, end_line);
            logic_status = CUY_SUCCESS;
            break;
        case ARG_CASE_3:
            printf("CASE 3\n");
            // Run case 3 logic
            //logic_status = run_case_3_logic(data, size, start_line);
            logic_status = CUY_SUCCESS;
            break;
        case ARG_CASE_4:
            printf("CASE 4\n");
            // Run case 4 logic
            //logic_status = run_case_4_logic(data, size, start_line, end_line);
            logic_status = CUY_SUCCESS;
            break;
        default:
            // Should never happen
            return CUY_ERROR_UNKNOWN;
    }
    if (!status_code_is_success(logic_status)) {
        return logic_status;
    }

    munmap(data, size);
    StatusCode file_close_status = file_close(fd);
    if (!status_code_is_success(file_close_status)) {
        return file_close_status;
    }
    return CUY_SUCCESS;
}


#include "cuy/arg_parser.h"

#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>


static inline bool compare_string(char* rhs, char* lhs) {
    return (strcmp(rhs, lhs) == 0);
}

static inline bool is_flag(char* cli_input, CliFlag* flag) {
    return compare_string(cli_input, flag->short_str) || compare_string(cli_input, flag->long_str);
}

void init_arg_parser_config(CliFlag* flags) {
    // help
    flags[FLAG_INDEX_HELP].short_str = "-h";
    flags[FLAG_INDEX_HELP].long_str = "--help";
    flags[FLAG_INDEX_HELP].description = "Shows help menu.";
    flags[FLAG_INDEX_HELP].is_used  = false;
    flags[FLAG_INDEX_HELP].nbr_args  = 0;
    // version
    flags[FLAG_INDEX_VERSION].short_str = "-v";
    flags[FLAG_INDEX_VERSION].long_str = "--version";
    flags[FLAG_INDEX_VERSION].description = "Shows tool version.";
    flags[FLAG_INDEX_VERSION].is_used  = false;
    flags[FLAG_INDEX_VERSION].nbr_args  = 0;
    // file
    flags[FLAG_INDEX_FILE].short_str = "-f";
    flags[FLAG_INDEX_FILE].long_str = "--file";
    flags[FLAG_INDEX_FILE].description = "Path to file.";
    flags[FLAG_INDEX_FILE].is_used  = false;
    flags[FLAG_INDEX_FILE].nbr_args  = 1;
    // lines
    flags[FLAG_INDEX_LINES].short_str = "-l";
    flags[FLAG_INDEX_LINES].long_str = "--lines";
    flags[FLAG_INDEX_LINES].description = "Lines to show.";
    flags[FLAG_INDEX_LINES].is_used  = false;
    flags[FLAG_INDEX_LINES].nbr_args  = 1;
}

StatusCode arg_parser(CliFlag* flags, int argc, char* argv[]) {
    for (int j = 1; j < argc ; ++j) {
        // Argument --help or -h
        if (is_flag(argv[j], &flags[FLAG_INDEX_HELP])) {
            flags[FLAG_INDEX_HELP].is_used = true;
        }
        // Argument --version or -v
        if (is_flag(argv[j], &flags[FLAG_INDEX_VERSION])) {
            flags[FLAG_INDEX_VERSION].is_used = true;
        }
        // Argument --file or -f
        if (is_flag(argv[j], &flags[FLAG_INDEX_FILE])) {
            // NOTE: Add verification if we are in boundaries for j+1 and also check how many arguments I need to copy.
            if (j+1 >= argc) {
                return CUY_ERROR_ARG_PARSER_FLAG_FILE_MISSING_ARG;
            }
            flags[FLAG_INDEX_FILE].is_used = true;
            flags[FLAG_INDEX_FILE].args[0] = argv[j+1];
        }
        // Argument --lines or -l
        if (is_flag(argv[j], &flags[FLAG_INDEX_LINES])) {
            if (j+1 >= argc) {
                return CUY_ERROR_ARG_PARSER_FLAG_LINES_MISSING_ARG;
            }
            flags[FLAG_INDEX_LINES].is_used = true;
            flags[FLAG_INDEX_LINES].args[0] = argv[j+1];
        }
    }
    // Validations
    if (!flags[FLAG_INDEX_FILE].is_used && flags[FLAG_INDEX_LINES].is_used) {
        return CUY_ERROR_ARG_PARSER_VALIDATION_FILE_LINES;
    }
    return CUY_SUCCESS;
}




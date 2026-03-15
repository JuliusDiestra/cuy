

#include "cuy/print_help.h"

#include <stdio.h>
#include <string.h>

static const char* kSingleArgText = " $ARG";
static const char* kMultipleArgText = " $ARG...";
static const char* kSeparateFlags = ", ";

static inline void print_with_indentation(char* str) {
    printf("%*c%s\n", 4, ' ', str);
}

static inline void print_flag_line(CliFlag* flag) {
    const int kTotalSpaceToDescription = 30;
    int length_flags = strlen(flag->short_str) + strlen(kSeparateFlags) + strlen(flag->long_str);
    char flag_line_help[100] = "";
    strcat(flag_line_help, flag->short_str);
    strcat(flag_line_help, kSeparateFlags);
    strcat(flag_line_help, flag->long_str);
    if (flag->nbr_args == 1) {
        length_flags += strlen(kSingleArgText);
        strcat(flag_line_help, kSingleArgText);
    }
    if (flag->nbr_args >= 2) {
        length_flags += strlen(kMultipleArgText);
        strcat(flag_line_help, kMultipleArgText);
    }
    memset(flag_line_help + length_flags, ' ', (kTotalSpaceToDescription - length_flags)*sizeof(char));
    strcat(flag_line_help, flag->description);
    print_with_indentation(flag_line_help);
    return;
}

void print_help(CliFlag* flags) {
    printf("Usage: cuy [FLAGS] [ARGUMENTS]\n");
    printf("Description:\n");
    print_with_indentation("Cuy is a tool to handle operations in files.");
    printf("FLAGS:\n");
    for (int ix = 0; ix < kTotalCliFlags; ++ix) {
        print_flag_line(&flags[ix]);
    }
}

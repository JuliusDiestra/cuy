
#include "cuy/cli.h"

#include <stdio.h>

#include "cuy/arg_parser.h"
#include "cuy/print_help.h"
#include "cuy/print_version.h"
#include "cuy/lines.h"

StatusCode cli_run(int argc, char* argv[]) {
    CliFlag flags[kTotalCliFlags];
    init_arg_parser_config(flags);
    StatusCode arg_parse_status = arg_parser(flags, argc, argv);
    if (!status_code_is_success(arg_parse_status)) {
        status_code_print_message(arg_parse_status);
        return arg_parse_status;
    }
    // Help menu
    if (flags[FLAG_INDEX_HELP].is_used) {
        print_help(flags);
        return CUY_SUCCESS;
    }
    // Print version
    if (flags[FLAG_INDEX_VERSION].is_used) {
        print_version();
        return CUY_SUCCESS;
    }
    if (flags[FLAG_INDEX_FILE].is_used && flags[FLAG_INDEX_LINES].is_used) {
        StatusCode run_lines_status = run_lines(flags[FLAG_INDEX_FILE].args[0], flags[FLAG_INDEX_LINES].args[0]);
        if (!status_code_is_success(run_lines_status)) {
            status_code_print_message(run_lines_status);
        }
        return run_lines_status;
    }
    return CUY_SUCCESS;
}

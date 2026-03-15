#ifndef INCLUDE_CUY_ARG_PARSER_H_
#define INCLUDE_CUY_ARG_PARSER_H_

#include "cuy/status_code.h"
#include "cuy/cli_flag.h"

// @brief Initialize ArgParserConfig with default values.
// @param config Struct with CLI argument values.
void init_arg_parser_config(CliFlag* flags);

// @brief Parser CLI arguments and store them in ArgParserConfig.
// @param flags Pointer to CliFlag. Values are set based on argc and argv.
// @param argc CLI argument counts.
// @param argv CLI arguments.
StatusCode arg_parser(CliFlag* flags, int argc, char* argv[]);

#endif  // INCLUDE_CUY_ARG_PARSER_H_

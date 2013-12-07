#pragma once

#include "command_line_argument_parser.hpp"

class application {
public:
  int run(int argc, const char* argv[]) {
    command_line_argument_parser parser;

    parser.parse(argc, argv);

    return 0;
  }
};

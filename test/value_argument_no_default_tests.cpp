#include <boost/test/unit_test.hpp>

#include "command_line_argument_parser.hpp"

BOOST_AUTO_TEST_CASE(recognises_username_argument) {
  command_line_argument_parser parser;
  const char *argv[] = {"app", "--username","graham"};
  auto args = parser.parse(sizeof(argv)/sizeof(*argv), argv);
  
  BOOST_CHECK_EQUAL("graham", args.username());
}

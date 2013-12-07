#include <boost/test/unit_test.hpp>

#include "command_line_argument_parser.hpp"

BOOST_AUTO_TEST_CASE(recognises_a_switch_argument) {
  command_line_argument_parser parser;
  const char *argv[] = {"app", "--verbose"};
  auto args = parser.parse(sizeof(argv)/sizeof(*argv), argv);
  
  BOOST_CHECK(args.verbose());
}

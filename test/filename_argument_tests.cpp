#include <boost/test/unit_test.hpp>

#include "command_line_argument_parser.hpp"

BOOST_AUTO_TEST_CASE(captures_filenames_from_the_commandline) {
  command_line_argument_parser parser;
  const char *argv[] = {"app", "a", "b", "c"};
  auto args = parser.parse(sizeof(argv)/sizeof(*argv), argv);
  
  auto filename_arguments =  args.filenames();

  BOOST_CHECK_EQUAL(3, filename_arguments.size());
  BOOST_CHECK_EQUAL("a", filename_arguments[0]);
  BOOST_CHECK_EQUAL("b", filename_arguments[1]);
  BOOST_CHECK_EQUAL("c", filename_arguments[2]);
}

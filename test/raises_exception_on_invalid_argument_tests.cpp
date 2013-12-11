#include <boost/test/unit_test.hpp>

#include "command_line_argument_parser.hpp"

BOOST_AUTO_TEST_CASE(raise_exception_on_invalid_argument) {
  command_line_argument_parser parser;
  const char *argv[] = {"app", "--silly-argument"};

  BOOST_CHECK_EXCEPTION(parser.parse(sizeof(argv)/sizeof(*argv), argv),
			std::logic_error,
			[] (std::logic_error const& e) -> bool {return strcmp(e.what(), "unrecognised option '--silly-argument'") == 0;});
}

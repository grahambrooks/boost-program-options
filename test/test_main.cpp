#define BOOST_TEST_MAIN
#ifndef MAKEFILE_BUILD
// Work around for xcode's default to always link against dynamic libraries and the need to static linking for distribution.
#define BOOST_TEST_DYN_LINK
#endif
#define BOOST_TEST_MODULE DupsTests

#include <boost/test/unit_test.hpp>

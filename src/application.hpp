#pragma once

#include "command_line_argument_parser.hpp"

using namespace std;

class application {
public:
  int run(int argc, const char* argv[]) {
    command_line_argument_parser parser;
    try {
      auto args = parser.parse(argc, argv);

      if (args.no_arguments()) {
	cout << "No arguments supplied on the command line" << endl;
      }
      
      if (args.verbose()) {
	cout << "Verbose option set" << endl;
      }

      cout << "Username set to '" << args.username() << "'" << endl;
      
      auto filenames  = args.filenames();
      
      cout << filenames.size() << " Filenames supplied" << endl;

    } catch (std::logic_error e) {
      cerr << e.what() << endl;
    }
    return 0;
  }
};

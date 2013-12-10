#pragma once

#include <boost/program_options.hpp>
#include <vector>

using namespace std;

class arguments {
  constexpr static auto username_option_name = "username";
  constexpr static auto username_option = "username,u";
  constexpr static auto verbose_option_name = "verbose";
  constexpr static auto verbose_option = "verbose,v";
  constexpr static auto files_option_name = "input-files";
  
  boost::program_options::variables_map variables;
  friend class command_line_argument_parser;
public:
  arguments(boost::program_options::variables_map variables) : variables(variables) {}

  bool no_arguments() {
    return variables.size() == 0;
  }

  bool verbose() {
    return variables.count(verbose_option_name) > 0;
  }

  string username() {
    return (variables.count(username_option_name) > 0) ? variables[username_option_name].as<string>() : "";
  }
  
  const vector<string> filenames() {
    return (variables.count(files_option_name) > 0) ? variables[files_option_name].as<vector<string>>() : vector<string>();
  }
};

class command_line_argument_parser {
    boost::program_options::options_description desc;
  public:
    command_line_argument_parser() {
      desc.add_options()
	(arguments::verbose_option, "Typical long and short switch argument")
        (arguments::username_option, boost::program_options::value<std::string>(), "username to use")
	(arguments::files_option_name,  boost::program_options::value<vector<string>>(), "input file");
    }

  arguments parse(int argc, const char *argv[]) {
    boost::program_options::variables_map variables;
    
    boost::program_options::positional_options_description p;
    p.add(arguments::files_option_name, -1);

    boost::program_options::store(boost::program_options::command_line_parser(argc, argv).options(desc).positional(p).run(), variables);
    
    boost::program_options::notify(variables);

    return arguments(variables);
  }
};

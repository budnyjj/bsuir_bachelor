#ifndef CLI_OPTS
#define CLI_OPTS

struct Cli_opts 
{
  Cli_opts()
    : start_node(0), input_filename("") { };

  size_t start_node;
  std::string input_filename;
};

Cli_opts get_cli_opts(int argc, char *const argv[]);

#endif

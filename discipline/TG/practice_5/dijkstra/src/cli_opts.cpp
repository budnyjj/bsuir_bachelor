#include <cstddef>
#include <cstdlib>
#include <getopt.h>
#include <unistd.h>

#include <string>
#include <iostream>
#include <sstream>

#include <cli_opts.hpp>


static void
print_usage(std::ostream& os, const std::string program_name, const int exit_code);

Cli_opts get_cli_opts(int argc, char *const argv[])
{
  Cli_opts opts;
  int next_option;
  const std::string program_name = argv[0];
  std::stringstream converter;

  const char* const short_options = "hf:s:";
  const struct option long_options[] = {
    {"help"       , 0, NULL, 'h' },
    {"file"       , 1, NULL, 'f' },
    {"start-node" , 1, NULL, 's' },
    {NULL         , 0, NULL, 0 }
  };
  
  do {
    next_option = getopt_long(argc, argv, short_options,
                              long_options, NULL);
    switch (next_option) {
    case 'h':
      print_usage(std::cout, program_name, 0);
      break;
    case 'f':
      opts.input_filename = optarg;
      break;
    case 's':
      // convert c-string to size_t 
      converter << optarg;
      converter >> opts.start_node;
      break;
    case '?':
      print_usage(std::cerr, program_name, 1);
    case -1:
      break;
    default:
      abort();
    }

  } 
  while (next_option != -1);
  return opts;
}

static void
print_usage(std::ostream& os, const std::string program_name, const int exit_code)
{
  os << "Usage: " << program_name << "-f filename [-s node_number]\n";
  os << "    -h --help                          Display this usage information.\n";
  os << "    -f --file filename                 Read graph from file.\n";
  os << "    -s --start-node node_number        Specify start node number." << std::endl;
  exit(exit_code);
}

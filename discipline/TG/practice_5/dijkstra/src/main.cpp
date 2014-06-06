#include <vector>
#include <iostream>
#include <fstream>
#include <string>

#include <cli_opts.hpp>
#include <edge.hpp>
#include <graph.hpp>
#include <dijkstra.hpp>

using namespace std;

int 
main(int argc, char *const argv[]) 
{
  Cli_opts opts = get_cli_opts(argc, argv);
  Graph g;

  ifstream file(opts.input_filename.c_str());
  if (file) {
    file >> g;
    if (file.fail()) {
      cerr << "Input graph file format is incorrect!" << endl;
      file.close();
      return 1;
    }
    file.close();
  }
  else {
    cerr << "Cannot open specified file!" << endl;
    return 1;
  }

  vector <Path> paths = get_shortest_paths(g, opts.start_node);
  
  vector<Path>::iterator it;
  for (it = paths.begin(); it != paths.end(); ++it) 
    cout << *it;

  return 0;
}

// process arguments with getopt_long function
// return tree path, not only costs

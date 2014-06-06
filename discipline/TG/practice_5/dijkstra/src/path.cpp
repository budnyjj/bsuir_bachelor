#include <vector>

#include <path.hpp>

std::ostream& operator<<(std::ostream& os, const Path& p)
{
  try {
    os << "Path " << p.get_src() << " -> " << p.get_dest()
       << " (cost = " << p.get_cost() << "): \t";
    std::vector <size_t>::const_iterator it;

    for (it = p.begin(); it != p.end(); ++it)
      os << *it << " -> ";

    os << "(end)\n";
  } 
  catch (Destination_node_error& e) { }
  catch (...) 
    {
      os << "There were unexpected errors while printing\n";
    }

  return os;
}

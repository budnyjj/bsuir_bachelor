#include <istream>
#include <ostream>

#include <edge.hpp>

std::ostream&
operator<<(std::ostream& os, const Edge& e)
{
  os << "Edge: " << e.get_src() << " -> " << e.get_dest()
     << " (" << e.get_weight() << ")" << std::endl;
  return os;
}

std::istream& 
operator>>(std::istream& is, Edge& e)
{
  is >> e.src >> e.dest >> e.weight;
  return is;
}

#include <node.hpp>

inline size_t
Node::get_num() const
{
  return this->num;
}

inline int
Node::get_cost() const
{
  return this->cost;
}
  
std::ostream& operator<<(std::ostream& os, const Node& n)
{
os << "Node #" << n.get_num() << '\n';
os << "Cost: " << n.get_cost();
  return os;
}

std::istream& operator>>(std::istream& is, Node& n)
{
  is >> n.num >> n.cost;
  return is;
}

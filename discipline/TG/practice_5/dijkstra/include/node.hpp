#ifndef NODE
#define NODE

#include <iostream>

class Node {
public:
  Node()
    : num(0), cost(0) {};

  Node(const size_t num_,  const int cost_ = 0)
    : num(num_), cost(cost_) {};

  Node(const Node& n)
    : num(n.get_num()), cost(n.get_cost()) {}

  size_t
  get_num() const;

  int
  get_cost() const;
  
  inline void 
  set_cost(int cost_) { this->cost = cost_; };

  friend std::istream& 
  operator>>(std::istream& is, Node& n);
private:
  size_t num;
  int cost;
};

std::ostream& operator<<(std::ostream& os, const Node& n);

#endif

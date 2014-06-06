#ifndef EDGE
#define EDGE

#include <iostream>

class Edge {
public:
  Edge()
    : src(0), dest(0), weight(1) {};

  Edge(int src_, int dest_, int weight_ = 1)
    : src(src_), dest(dest_), weight(weight_) {};

  Edge(const Edge& e)
    : src(e.get_src()), 
      dest(e.get_dest()), 
      weight(e.get_weight()) {};

  size_t
  get_src() const { return this->src; }

  size_t
  get_dest() const { return this->dest; }

  int
  get_weight() const { return this->weight; }
  
  friend std::istream& operator>>(std::istream& is, Edge& e);
private:
  size_t src;
  size_t dest;
  int weight;
};

std::ostream& operator<<(std::ostream& os, const Edge& n);

#endif

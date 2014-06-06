#ifndef GRAPH
#define GRAPH

#include <vector>
#include <iostream>
#include <fstream>

#include <node.hpp>
#include <edge.hpp>
#include <path.hpp>
#include <max_cost.hpp>
#include <exceptions.hpp>

class Graph {
public:
  Graph() {};

  Graph(size_t n_nodes) { this->content.resize(n_nodes); }

  template <class Iterator>
  Graph(Iterator first, Iterator last)
    : content(first, last) { }

  size_t 
  get_num_nodes() const { return this->content.size(); }

  size_t
  get_num_edges() const;

  bool 
  empty() const { return this->content.empty(); }

  inline void 
  add_node(const Node& n);

  void
  add_edge(const Edge& e);

  void 
  resize(const size_t new_size) { this->content.resize(new_size); };

  const std::vector<Edge>& 
  get_edges(size_t node_num) const;

  friend std::ostream& 
  operator<<(std::ostream& os, const Graph& g);
private:
  std::vector <std::vector <Edge> > content;
};

std::istream& 
operator>>(std::istream& is, Graph& g);

#endif

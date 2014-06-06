#include <graph.hpp>
#include <iostream>
#include <fstream>

inline void 
Graph::add_node(const Node& n)
{
  size_t req_size = n.get_num() + 1;
  if (this->content.size() <= req_size)
    this->content.resize(req_size);
}

void 
Graph::add_edge(const Edge& e)
{
  size_t from = e.get_src();
  size_t to = e.get_dest();
  if (this->content.size() > from)
    if (this->content.size() > to)
      this->content[from].push_back(e);
    else 
      throw Destination_node_error(__FILE__, __LINE__);
  else
    throw Source_node_error(__FILE__, __LINE__);
}

size_t 
Graph::get_num_edges() const
{
  size_t num_edges = 0;
  std::vector <std::vector <Edge> >::const_iterator it;
  for (it = this->content.begin(); it != this->content.end(); ++it)
    num_edges += it->size();
  return num_edges;
}

const std::vector<Edge>& 
Graph::get_edges(size_t node_num) const
{
  if (this->content.size() > node_num)
    return this->content[node_num];
  else throw Index_error(__FILE__, __LINE__);
}

std::ostream&
operator<<(std::ostream& os, const Graph& g)
{
  os << "Graph ("
     << g.get_num_nodes() << " node(s), " 
     << g.get_num_edges() << " edge(s))\n";

  for (size_t node_num = 0; node_num < g.content.size(); ++node_num) {
    os << "Node #" << node_num;
    if (g.content[node_num].size() > 0) {
      os << ", edges: \n";
      std::vector <Edge>::const_iterator edge_it;
      for (edge_it = g.content[node_num].begin();
           edge_it != g.content[node_num].end();
           ++edge_it) {
        os << *edge_it;
      }
    }
    else {
      os << " has no edges\n";
    }
  }
  os << std::endl;
  return os;
}

std::istream& 
operator>>(std::istream& is, Graph& g)
{
  size_t num_nodes = 0;
  size_t num_edges = 0;
  
  is >> num_nodes >> num_edges; 
  g.resize(num_nodes + 1);

  for (size_t i = 0; i < num_edges; i++)
    {
      Edge e;
      is >> e;
      g.add_edge(e);
    }

  return is;
}

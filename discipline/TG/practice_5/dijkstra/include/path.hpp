#ifndef PATH
#define PATH

#include <ostream>

#include <node.hpp>
#include <edge.hpp>
#include <max_cost.hpp>
#include <exceptions.hpp>

class Path {
public:
  Path(int cost_ = 0)
    : cost(cost_) { }
  
  template <class Iterator>
  Path(Iterator first, Iterator last, int cost_ = 0)
    : content(first, last), cost(cost_) { }

  Path(const Path& p)
    : content(p.begin(), p.end()),
      cost(p.get_cost()) { }

  int
  get_cost() const { return this->cost; }

  void set_cost(const int cost_) { this->cost = cost_; }

  size_t get_src() const 
  {
    if (!this->content.empty())
      return this->content.front();
    else
      throw Source_node_error(__FILE__, __LINE__);
  }

  size_t get_dest() const
  {
    if (!this->content.empty())
      return this->content.back();
    else
      throw Destination_node_error(__FILE__, __LINE__);
  }

  bool empty() const
  {
    return this->content.empty();
  }

  void clear() 
  {
    this->content.clear();
    this->cost = 0;
  }
  
  size_t get_num_nodes() const
  {
    return this->content.size();
  }

  size_t get_num_edges() const
  {
    // there is no edges in path if graph is unchained
    if (this->cost >= MAX_COST)
      return 0;

    size_t num_nodes = this->content.size();

    if (num_nodes > 0)
      return num_nodes - 1;
    else
      return 0;
  }

  void push_back(const Node& n)
  {
    this->content.push_back(n.get_num());
  }

  void push_back(const Edge& e)
  {
    if ((!this->content.empty()) &&
        (this->content.back() == e.get_src()))
      {
        this->content.push_back(e.get_dest());
        this->cost += e.get_weight();
      }
    else
      throw Source_node_error(__FILE__, __LINE__);
  }

  template <class Iterator>
  void insert(std::vector<size_t>::iterator pos, Iterator first, Iterator last)
  {
    this->content.insert(pos, first, last);
  }

  Node pop_back()
  {
    if (!this->content.empty())
      {
        Node back = this->content.back();
        this->content.pop_back();
        return back;
      }
    else throw Index_error(__FILE__, __LINE__);
  }

  std::vector<size_t>::const_iterator begin() const
  {
    return this->content.begin();
  }
  
  std::vector<size_t>::const_iterator end() const
  {
    return this->content.end();
  }

  std::vector<size_t>::iterator begin()
  {
    return this->content.begin();
  }
  
  std::vector<size_t>::iterator end()
  {
    return this->content.end();
  }
private:
  std::vector<size_t> content;
  int cost;
};

std::ostream& operator<<(std::ostream& os, const Path& p);

#endif

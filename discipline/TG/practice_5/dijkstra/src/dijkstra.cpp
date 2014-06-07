#include <vector>
#include <queue>

#include <node.hpp>
#include <edge.hpp>
#include <path.hpp>
#include <graph.hpp>
// #include <min_heap.hpp>
#include <dijkstra.hpp>

static void 
restore_paths(std::vector<Path>& paths, size_t src);

static bool operator<(const Node& lhs, const Node& rhs)
{
  return lhs.get_cost() > rhs.get_cost();
}

// heap-based realization of Dijkstra algorithm
// @see http://e-maxx.ru/algo/dijkstra_sparse
std::vector<Path> get_shortest_paths(Graph& graph, const size_t from)
{
  size_t num_nodes = graph.get_num_nodes();
  if (from >= num_nodes)
    throw Source_node_error(__FILE__, __LINE__);

  // initialization
  std::vector <Path> paths;
  for (size_t i = 0; i < num_nodes; ++i) 
    paths.push_back(Path(MAX_COST));
  paths[from].set_cost(0);

  std::vector <Node> nodes;
  for (size_t i = 0; i < num_nodes; ++i)
    nodes.push_back(Node(i, MAX_COST));
  nodes[from].set_cost(0);

  std::priority_queue<Node, std::vector<Node>, std::less<Node> >
    node_min_heap(nodes.begin(), nodes.end());

  // main loop
  while (!node_min_heap.empty())
    {
      Node cur_node = node_min_heap.top();
      node_min_heap.pop();

      int cur_node_cost = cur_node.get_cost();
      size_t cur_node_num = cur_node.get_num();

      if (cur_node_cost > paths[cur_node_num].get_cost())
        continue;

      std::vector<Edge>::const_iterator edge_it;
      for (edge_it = graph.get_edges(cur_node_num).begin();
           edge_it != graph.get_edges(cur_node_num).end();
           ++edge_it) {
        size_t dest_node_num = edge_it->get_dest();
        Path& path = paths[dest_node_num];

        int new_cost = cur_node_cost + edge_it->get_weight();
        if (new_cost < path.get_cost()) {
          path.clear();
          path.push_back(Node(cur_node_num));
          path.push_back(Edge(cur_node_num, dest_node_num));

          path.set_cost(new_cost);

          // insert updated node to heap
          node_min_heap.push(Node(dest_node_num, new_cost));
        }
      }
    }

  restore_paths(paths, from);
  return paths;
}

static void restore_paths(std::vector<Path>& paths, size_t src) 
{
  std::queue <size_t> wait_processing;

  for (std::vector <Path>::const_iterator it = paths.begin();
       it != paths.end(); ++it) {
    if ((!it->empty()) && (it->get_src() != src))
      wait_processing.push(it->get_dest());
  }

  while (!wait_processing.empty()) {
    size_t cur_path_num = wait_processing.front();
    wait_processing.pop();
    
    size_t prev_path_num = paths[cur_path_num].get_src();
    
    paths[cur_path_num].insert(paths[cur_path_num].begin(),
                               paths[prev_path_num].begin(),
                               paths[prev_path_num].end() - 1);

    if (paths[cur_path_num].get_src() != src)
      wait_processing.push(paths[cur_path_num].get_dest());  
  }
}



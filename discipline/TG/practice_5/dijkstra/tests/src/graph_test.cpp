#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Graph

#include <boost/test/unit_test.hpp>
#include <iostream>
#include <cstdlib>
#include <climits>

#include <max_cost.hpp>
#include <graph.hpp>

using namespace std;

BOOST_AUTO_TEST_CASE(default_constructor_test)
{
  Graph g;

  BOOST_CHECK_EQUAL(g.get_num_nodes(), 0);
  BOOST_CHECK_EQUAL(g.empty(), true);
}

BOOST_AUTO_TEST_CASE(by_size_constructor_test)
{
  const int NUM_NODES = 10;
  Graph g(NUM_NODES);

  BOOST_CHECK_EQUAL(g.get_num_nodes(), 10);
}


BOOST_AUTO_TEST_CASE(initializer_constructor_test)
{
  const int NUM_NODES = 10;

  vector <vector <Edge> > v;
  v.resize(NUM_NODES);

  Graph g(v.begin(), v.end());

  BOOST_CHECK_EQUAL(g.get_num_nodes(), 10);
}

BOOST_AUTO_TEST_CASE(add_node_test)
{
  const int NUM_NODES = 10;
  Graph g;

  // resize graph to appropriate size
  for (int i = 0; i < NUM_NODES; ++i)
    {
      BOOST_CHECK_EQUAL(g.get_num_nodes(), i);

      Node n(i);
      g.add_node(n);

      BOOST_CHECK_EQUAL(g.get_num_nodes(), i+1);
    }

  // insert nodes with lower index should not resize graph
  for (int i = NUM_NODES - 1; i >= 0; --i)
    {
      Node n(i);
      g.add_node(n);

      BOOST_CHECK_EQUAL(g.get_num_nodes(), NUM_NODES);
    }
}

BOOST_AUTO_TEST_CASE(add_edge_test)
{
  const int NUM_NODES = 10;
  const int NUM_EDGES = 100;

  Graph g(NUM_NODES);

  srand(42);
  for (size_t i = 0; i < NUM_EDGES; ++i)
    {
      g.add_edge(Edge((int) (rand() % NUM_NODES),
                      (int) (rand() % NUM_NODES)));
      BOOST_CHECK_EQUAL(g.get_num_edges(), i+1);
    }
}

BOOST_AUTO_TEST_CASE(add_edge_exc_test)
{
  Graph g;
  // cannot insert edge to empty graph
  BOOST_CHECK_THROW(g.add_edge(Edge(0, 1)), Source_node_error);

  g.add_node(Node(0));

  // cannot insert edges to graph without destination node
  BOOST_CHECK_THROW(g.add_edge(Edge(0, 1)), Destination_node_error);
}

// shortest paths tests

BOOST_AUTO_TEST_CASE(get_shortest_paths_no_nodes_test)
{
  Graph g;
  BOOST_CHECK_THROW(g.get_shortest_paths(0), Source_node_error);
}

BOOST_AUTO_TEST_CASE(get_shortest_paths_one_node_test)
{
  Graph g(1);
  g.add_edge(Edge(0, 0, 2)); // edge weight must be > 0
  vector<Path> paths = g.get_shortest_paths(0);

  BOOST_CHECK_EQUAL(paths.size(), 1);
  BOOST_CHECK_EQUAL(paths[0].get_num_edges(), 0);
  BOOST_CHECK_EQUAL(paths[0].get_cost(), 0);
}

BOOST_AUTO_TEST_CASE(get_shortest_paths_two_nodes_test)
{
  Graph g(2);
  g.add_edge(Edge(1, 0));

  // there is NO path from 0 to 1
  vector<Path> paths_0 = g.get_shortest_paths(0);
  BOOST_CHECK_EQUAL(paths_0.size(), 2);

  BOOST_CHECK_EQUAL(paths_0[0].get_num_edges(), 0);
  BOOST_CHECK_EQUAL(paths_0[0].get_cost(), 0);

  BOOST_CHECK_EQUAL(paths_0[1].get_num_edges(), 0);
  BOOST_CHECK_EQUAL(paths_0[1].get_cost(), MAX_COST);
  
  // there is path from 1 to 0
  vector<Path> paths_1 = g.get_shortest_paths(1);
  BOOST_CHECK_EQUAL(paths_1.size(), 2);

  BOOST_CHECK_EQUAL(paths_1[0].get_num_edges(), 1);
  BOOST_CHECK_EQUAL(paths_1[0].get_cost(), 1);

  BOOST_CHECK_EQUAL(paths_1[1].get_num_edges(), 0);
  BOOST_CHECK_EQUAL(paths_1[1].get_cost(), 0);
}

BOOST_AUTO_TEST_CASE(get_shortest_paths_three_nodes_test)
{
  Graph g(3);
  g.add_edge(Edge(0, 1, 1));
  g.add_edge(Edge(0, 2, 4));
  g.add_edge(Edge(1, 2, 2));

  vector<Path> paths = g.get_shortest_paths(0);
  BOOST_CHECK_EQUAL(paths.size(), 3);

  BOOST_CHECK_EQUAL(paths[0].get_cost(), 0);
  BOOST_CHECK_EQUAL(paths[1].get_cost(), 1);
  BOOST_CHECK_EQUAL(paths[2].get_cost(), 3);
}

BOOST_AUTO_TEST_CASE(get_shortest_paths_exc_test)
{
  Graph g(2);
  BOOST_CHECK_THROW(g.get_shortest_paths(3), Source_node_error);
}

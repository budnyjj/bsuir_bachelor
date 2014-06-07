#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Path

#include <boost/test/unit_test.hpp>
#include <iostream>

#include <node.hpp>
#include <path.hpp>

using namespace std;

BOOST_AUTO_TEST_CASE(default_constructor_test)
{
  Path p;

  BOOST_CHECK_EQUAL(p.get_cost(), 0);
  BOOST_CHECK_EQUAL(p.get_num_nodes(), 0);
  BOOST_CHECK_EQUAL(p.get_num_edges(), 0);
}

BOOST_AUTO_TEST_CASE(inititalizer_constructor_test)
{
  const size_t PATH_SIZE = 10;
  vector<size_t> v;

  for (size_t i = 0; i < PATH_SIZE; ++i) {
      v.push_back(i);
  }
  
  Path p(v.begin(), v.end(), 2);

  BOOST_CHECK_EQUAL(p.get_cost(), 2);
  BOOST_CHECK_EQUAL(p.get_num_nodes(), PATH_SIZE);
  BOOST_CHECK_EQUAL(p.get_num_edges(), PATH_SIZE - 1);

  BOOST_CHECK_EQUAL(p.get_src(), 0);
  BOOST_CHECK_EQUAL(p.get_dest(), PATH_SIZE - 1);
}

BOOST_AUTO_TEST_CASE(copy_constructor_test)
{
  const size_t PATH_SIZE = 10;
  vector<size_t> v;

  for (size_t i = 0; i < PATH_SIZE; ++i) {
      v.push_back(i);
  }
  
  Path p(v.begin(), v.end());
  Path p2(p);

  BOOST_CHECK_EQUAL(p.get_src(), p2.get_src());
  BOOST_CHECK_EQUAL(p.get_dest(), p2.get_dest());
  BOOST_CHECK_EQUAL(p.get_cost(), p2.get_cost());
  
  vector <size_t>::const_iterator it;
  vector <size_t>::const_iterator it2;
  for (it = p.begin(), it2 = p2.begin();
       (it < p.end()) || (it2 < p2.end());
       ++it, ++it2) {
    BOOST_CHECK_EQUAL(*it, *it2);
  }
}

BOOST_AUTO_TEST_CASE(add_node_test)
{
  const size_t NUM_NODES = 10;
  const int PATH_COST = 10;
  Path p;

  p.set_cost(PATH_COST);

  for (size_t i = 0; i < NUM_NODES; i++) {
    p.push_back(Node(i));
  }

  BOOST_CHECK_EQUAL(p.get_cost(), PATH_COST);
  BOOST_CHECK_EQUAL(p.get_num_nodes(), NUM_NODES);
  BOOST_CHECK_EQUAL(p.get_num_edges(), NUM_NODES - 1);

  int i;
  vector <size_t>::const_iterator it;
  for (i = 0, it = p.begin();
       it != p.end(); ++it, ++i)
    {
      BOOST_CHECK_EQUAL(*it, i);
    }
}

BOOST_AUTO_TEST_CASE(add_edge_test)
{
  const size_t NUM_EDGES = 10;
  Path p;
  // add source node
  p.push_back(Node(0));

  for (size_t i = 0; i < NUM_EDGES; i++) {
    p.push_back(Edge(i, i+1));
  }

  // auto additions edge costs
  BOOST_CHECK_EQUAL(p.get_cost(), NUM_EDGES);
  BOOST_CHECK_EQUAL(p.get_num_edges(), NUM_EDGES);
  BOOST_CHECK_EQUAL(p.get_num_nodes(), NUM_EDGES + 1);

  cout << p << endl;

  int i;
  vector <size_t>::const_iterator it;
  for (i = 0, it = p.begin();
       it != p.end(); ++it, ++i)
    {
      BOOST_CHECK_EQUAL(*it, i);
    }
}

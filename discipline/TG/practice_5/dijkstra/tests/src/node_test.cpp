#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Node

#include <boost/test/unit_test.hpp>
#include <iostream>

#include <node.hpp>

using namespace std;

BOOST_AUTO_TEST_CASE(default_constructor_test)
{
  Node n;

  BOOST_CHECK_EQUAL(n.get_num(), 0);
  BOOST_CHECK_EQUAL(n.get_cost(), 0);
}

BOOST_AUTO_TEST_CASE(initializer_constructor_test)
{
  Node n(1, 2);

  BOOST_CHECK_EQUAL(n.get_num(), 1);
  BOOST_CHECK_EQUAL(n.get_cost(), 2);
}

BOOST_AUTO_TEST_CASE(copy_constructor_test)
{
  Node n(1, 2);
  Node n2(n);

  BOOST_CHECK_EQUAL(n2.get_num(), 1);
  BOOST_CHECK_EQUAL(n2.get_cost(), 2);
}

BOOST_AUTO_TEST_CASE(comparison_test)
{
  BOOST_CHECK_EQUAL(Node(0, 1), Node(1, 1));
  BOOST_CHECK_NE(Node(0, 1), Node(0, 2));

  BOOST_CHECK_LE(Node(0, 0), Node(0, 1));
  BOOST_CHECK_GE(Node(0, 2), Node(0, 1));

  BOOST_CHECK_GT(Node(0, 2), Node(0, 1));
  BOOST_CHECK_LT(Node(0, 2), Node(0, 3));
}



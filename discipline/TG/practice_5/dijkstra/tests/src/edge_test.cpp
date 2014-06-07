#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Edge

#include <boost/test/unit_test.hpp>
#include <iostream>

#include <edge.hpp>

using namespace std;

BOOST_AUTO_TEST_CASE(default_constructor_test)
{
  Edge e;

  BOOST_CHECK_EQUAL(e.get_src(), 0);
  BOOST_CHECK_EQUAL(e.get_dest(), 0);
  BOOST_CHECK_EQUAL(e.get_weight(), 1);
}

BOOST_AUTO_TEST_CASE(inititalizer_constructor_test)
{
  Edge e(2, 3, -1);

  BOOST_CHECK_EQUAL(e.get_src(), 2);
  BOOST_CHECK_EQUAL(e.get_dest(), 3);
  BOOST_CHECK_EQUAL(e.get_weight(), -1);
}

BOOST_AUTO_TEST_CASE(copy_constructor_test)
{
  Edge e(2, 3, -1);
  Edge e2(e);

  BOOST_CHECK_EQUAL(e2.get_src(), 2);
  BOOST_CHECK_EQUAL(e2.get_dest(), 3);
  BOOST_CHECK_EQUAL(e2.get_weight(), -1);
}


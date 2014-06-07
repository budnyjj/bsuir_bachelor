#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Min_heap

#include <boost/test/unit_test.hpp>
#include <vector>
#include <stdlib.h>
#include <iostream>

#include <min_heap.hpp>

using namespace std;

BOOST_AUTO_TEST_CASE(default_constructor_test)
{
  Min_heap <int> h;
  BOOST_CHECK_EQUAL(h.size(), 0);
  BOOST_CHECK_EQUAL(h.empty(), true);

  BOOST_CHECK_THROW(h.get(), Index_error);
}

BOOST_AUTO_TEST_CASE(iterator_constructor_test)
{
  vector <int> v;
  for (int i = 0; i < 10; i++)
    {
      v.push_back(i);
    }

  Min_heap <int> h(v.begin(), v.end());
  BOOST_CHECK_EQUAL(v.size(), 10);
}

BOOST_AUTO_TEST_CASE(get_case)
{
  vector <int> v;
  const int VALUE = 0;

  v.push_back(VALUE);
  Min_heap <int> h(v.begin(), v.end());
  BOOST_CHECK_EQUAL(h.get(), VALUE);
  h.extract();
  BOOST_CHECK_THROW(h.get(), Index_error);
  
}

BOOST_AUTO_TEST_CASE(extract_case)
{
  const int HEAP_SIZE = 9;

  vector <int> v;
  for (int i = HEAP_SIZE; i >= 0; i--)
    {
      v.push_back(i);
    }

  // extract values in sorted order 
  Min_heap <int> h(v.begin(), v.end());

  for (int i = 0; i <= HEAP_SIZE; i++)
    BOOST_CHECK_EQUAL(h.extract(), i);

  // heap is empty
  BOOST_CHECK_EQUAL(h.size(), 0);

  // throws error when try to extract
  BOOST_CHECK_THROW(h.extract(), Index_error);
}

BOOST_AUTO_TEST_CASE(insert_case)
{
  const int HEAP_SIZE = 10;

  Min_heap <int> h;
  for (int i = HEAP_SIZE; i >= 0; i--)
    {
      h.insert(i);
    }

  // extract values in sorted order 
  int previous = h.extract();
  for (int i = 0; i < HEAP_SIZE; i++)
    { 
      int current = h.extract();
      BOOST_CHECK_GE(current, previous);
      previous = current;
    }
  
  // heap is empty
  BOOST_CHECK_EQUAL(h.size(), 0);

  // throws error when try to extract
  BOOST_CHECK_THROW(h.extract(), Index_error);
}


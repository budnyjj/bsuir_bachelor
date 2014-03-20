#include "../src/node.hpp"
#include <sstream>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Node
#include <boost/test/unit_test.hpp>


BOOST_AUTO_TEST_CASE(constructorsTest)
{
  node::Node n1;
  BOOST_CHECK_EQUAL(n1.getName(), "");
  BOOST_CHECK_EQUAL(n1.getLevel(), 0);

  node::Node n2("test string");
  BOOST_CHECK_EQUAL(n2.getName(), "test string");
  BOOST_CHECK_EQUAL(n2.getLevel(), 0);

  node::Node cn2(n2);
  BOOST_CHECK_EQUAL(cn2.getName(), n2.getName());
  BOOST_CHECK_EQUAL(cn2.getLevel(), 0);

  node::Node root("root");
  root.addLeft("l").addRight("r");
  root.getLeft().addLeft("l-l").addRight("l-r");
  root.getLeft().getLeft().addLeft("l-l-l").addRight("l-l-r");
  root.getRight().addLeft("r-l").addRight("r-r");
  root.getRight().getLeft().addLeft("r-l-l").addRight("r-l-r");

  node::Node cLeft(root.getLeft());
  BOOST_CHECK_EQUAL(cLeft.getName(), root.getLeft().getName());
  BOOST_CHECK_EQUAL(cLeft.getLeft().getName(), root.getLeft().getLeft().getName());
  BOOST_CHECK_EQUAL(cLeft.getLeft().getRight().getName(), root.getLeft().getLeft().getRight().getName());
  BOOST_CHECK_EQUAL(cLeft.getLeft().getLeft().getName(), root.getLeft().getLeft().getLeft().getName());
  BOOST_CHECK_THROW(cLeft.getLeft().getLeft().getLeft(), node::AddressError);

  BOOST_CHECK_EQUAL(cLeft.getLevel(), 1);
  BOOST_CHECK_EQUAL(cLeft.getLeft().getLevel(), 2);
  BOOST_CHECK_EQUAL(cLeft.getLeft().getLeft().getLevel(), 3);
  BOOST_CHECK_EQUAL(cLeft.getLeft().getRight().getLevel(), 3);

  cLeft.normalizeLevel();
  BOOST_CHECK_EQUAL(cLeft.getLevel(), 0);
  BOOST_CHECK_EQUAL(cLeft.getLeft().getLevel(), 1);
  BOOST_CHECK_EQUAL(cLeft.getLeft().getLeft().getLevel(), 2);
  BOOST_CHECK_EQUAL(cLeft.getLeft().getRight().getLevel(), 2);
}


BOOST_AUTO_TEST_CASE(addNodeTest)
{
  node::Node sRoot("sRoot");
  {
    node::Node root("root");

    root.addLeft("left").addRight("right");
    BOOST_CHECK_EQUAL(root.getLeft().getName(), "left");
    BOOST_CHECK_EQUAL(root.getLeft().getLevel(), 1);
    BOOST_CHECK_EQUAL(root.getRight().getName(), "right");
    BOOST_CHECK_EQUAL(root.getRight().getLevel(), 1);

    BOOST_CHECK_THROW(root.addLeft("left"), node::InsertError);

    sRoot.addLeft(root);
  }
  BOOST_CHECK_EQUAL(sRoot.getName(), "sRoot");
  BOOST_CHECK_EQUAL(sRoot.getLevel(), 0);
  BOOST_CHECK_EQUAL(sRoot.getLeft().getName(), "root");
  BOOST_CHECK_EQUAL(sRoot.getLeft().getLevel(), 1);
  BOOST_CHECK_EQUAL(sRoot.getLeft().getLeft().getName(), "left");
  BOOST_CHECK_EQUAL(sRoot.getLeft().getLeft().getLevel(), 2);
  BOOST_CHECK_EQUAL(sRoot.getLeft().getRight().getName(), "right");
  BOOST_CHECK_EQUAL(sRoot.getLeft().getRight().getLevel(), 2);
}

BOOST_AUTO_TEST_CASE(getTopTest)
{
  node::Node nRoot("newRoot");
  {
    node::Node root("root");
    root.addLeft("l").addRight("r");
    root.getLeft().addLeft("l-l").addRight("l-r");
    root.getLeft().getLeft().addLeft("l-l-l").addRight("l-l-r");
    root.getRight().addLeft("r-l").addRight("r-r");
    root.getRight().getLeft().addLeft("r-l-l").addRight("r-l-r");

    node::Node& cLeft = root.getLeft();
    BOOST_CHECK_EQUAL(cLeft.getTop().getName(), "root");

    nRoot.addLeft(cLeft);
  }
  node::Node& cLeft = nRoot.getLeft();
  BOOST_CHECK_EQUAL(cLeft.getTop().getName(), "newRoot");
  BOOST_CHECK_EQUAL(cLeft.getName(), "l");
}


BOOST_AUTO_TEST_CASE(delNodeTest)
{
  node::Node root("root");
  root.addLeft("left").addRight("right");

  node::Node& lBranch = root.getLeft();
  lBranch.addLeft("left-left").addRight("left-right");
  BOOST_CHECK_EQUAL(root.getLeft().getLeft().getName(), "left-left");
  BOOST_CHECK_EQUAL(lBranch.getLeft().getName(), root.getLeft().getLeft().getName());

  node::Node& lrBranch = root.getLeft().getRight();
  lrBranch.addLeft("left-right-left").addRight("left-right-right");
  BOOST_CHECK_EQUAL(root.getLeft().getRight().getLeft().getName(), "left-right-left");
  BOOST_CHECK_EQUAL(lrBranch.getLeft().getName(), root.getLeft().getRight().getLeft().getName());

  lrBranch.deleteLeft();
  BOOST_CHECK_THROW(root.getLeft().getRight().getLeft(), node::AddressError);

  root.getLeft().deleteLeft().deleteRight();

  BOOST_CHECK_THROW(root.getLeft().getRight(), node::AddressError);
  BOOST_CHECK_THROW(root.getLeft().getLeft(), node::AddressError);
}

BOOST_AUTO_TEST_CASE(operatorSetEqualNodeTest)
{
  // set equal to branch from another set
  node::Node nodeNew("node_new"); 
  nodeNew.addLeft("left_new").addRight("right_new");
  node::Node& lBranchNew = nodeNew.getLeft();
  lBranchNew.addLeft("left-left_new").addRight("left-right_new"); 
  {
    node::Node nodeOld("node_old");
    nodeOld.addLeft("left_old").addRight("right_old");
    node::Node& lBranchOld = nodeOld.getLeft();
    lBranchOld.addLeft("left-left_old").addRight("left-right_old");

    lBranchNew = lBranchOld;
  }
  BOOST_CHECK_EQUAL(nodeNew.getName(), "node_new"); // not changed
  BOOST_CHECK_EQUAL(nodeNew.getLeft().getName(), "left_old"); 
  BOOST_CHECK_EQUAL(nodeNew.getRight().getName(), "right_new"); //not changed
  BOOST_CHECK_EQUAL(nodeNew.getLeft().getLeft().getName(), "left-left_old");
  BOOST_CHECK_EQUAL(nodeNew.getLeft().getRight().getName(), "left-right_old");
  
  //set equal to own subset
  nodeNew = nodeNew.getLeft();
  BOOST_CHECK_EQUAL(nodeNew.getName(), "left_old");
  BOOST_CHECK_EQUAL(nodeNew.getLeft().getName(), "left-left_old");
  BOOST_CHECK_EQUAL(nodeNew.getRight().getName(), "left-right_old");
  
  // set equal to string
  nodeNew = "new";
  BOOST_CHECK_EQUAL(nodeNew.getName(), "new");
  BOOST_CHECK_THROW(nodeNew.getLeft(), node::AddressError);
  BOOST_CHECK_THROW(nodeNew.getRight(), node::AddressError);
}

BOOST_AUTO_TEST_CASE(operatorAddLeftRightNodeTest)
{
  node::Node root("root");
  root.addLeft("left").addRight("right");

  node::Node& lBranch = root.getLeft();
  lBranch.addLeft("left-left").addRight("left-right");
  node::Node& l2Branch = lBranch.getLeft();
  {
    node::Node l3Node("left-left-left");
    l3Node.addLeft("4left");
    l3Node.addRight("3left-right");
    // add simple left child node set
    l2Branch < l3Node;
  }
  node::Node &l3Branch = l2Branch.getLeft();
  BOOST_CHECK_EQUAL(l3Branch.getName(), "left-left-left");
  BOOST_CHECK_EQUAL(l3Branch.getLeft().getName(), "4left");
  BOOST_CHECK_EQUAL(l3Branch.getRight().getName(), "3left-right");
  
  // add simple right child
  l2Branch > "right-right-right";
  BOOST_CHECK_EQUAL(l2Branch.getRight().getName(), "right-right-right");

  // cannot insert because due to busy place
  BOOST_CHECK_THROW(root > "falseRight", node::InsertError);

  // add child to right from *left* subset
  // delete left subset
  node::Node& rBranch = root.getRight();
  rBranch < lBranch;
  root.deleteLeft();
  BOOST_CHECK_THROW(root.getLeft(), node::AddressError);
    
  BOOST_CHECK_EQUAL(rBranch.getName(), "right");

  node::Node& rlBranch = rBranch.getLeft();
  BOOST_CHECK_THROW(rBranch.getRight(), node::AddressError);

  BOOST_CHECK_EQUAL(rlBranch.getName(), "left");
  BOOST_CHECK_EQUAL(rlBranch.getLeft().getName(), "left-left");
  BOOST_CHECK_EQUAL(rlBranch.getRight().getName(), "left-right");

  node::Node& rllBranch = rlBranch.getLeft();
  BOOST_CHECK_THROW(rlBranch.getRight().getRight(), node::AddressError);
  BOOST_CHECK_THROW(rlBranch.getRight().getLeft(), node::AddressError);
  BOOST_CHECK_EQUAL(rllBranch.getLeft().getName(), "left-left-left");

  node::Node& r3lBranch = rllBranch.getLeft();
  BOOST_CHECK_EQUAL(r3lBranch.getLeft().getName(), "4left");
  BOOST_CHECK_EQUAL(r3lBranch.getRight().getName(), "3left-right");

  BOOST_CHECK_THROW(r3lBranch.getRight().getLeft(), node::AddressError);
  BOOST_CHECK_THROW(r3lBranch.getRight().getRight(), node::AddressError);
  BOOST_CHECK_THROW(r3lBranch.getLeft().getLeft(), node::AddressError);
  BOOST_CHECK_THROW(r3lBranch.getLeft().getRight(), node::AddressError);
}

BOOST_AUTO_TEST_CASE(operatorPushToOutStreamNodeTest)
{
  node::Node root("root");
  root.addLeft("left").addRight("right");

  node::Node& lBranch = root.getLeft();
  lBranch.addLeft("left-left").addRight("left-right");

  std::ostringstream s;

  s << root;

  BOOST_CHECK_EQUAL(s.str(), "root");
}


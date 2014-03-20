#include "../src/tree.hpp"
#include <sstream>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Tree
#include <boost/test/unit_test.hpp>


BOOST_AUTO_TEST_CASE(constructorsTest)
{
  {
    tree::Tree myTree1;
    BOOST_CHECK_EQUAL(myTree1.getName(), "");
    BOOST_CHECK_EQUAL(myTree1.getLevel(), 0);
    BOOST_CHECK_EQUAL(myTree1.getDepth(), 1);
  }
  {
    tree::Tree myTree2("abc");
    BOOST_CHECK_EQUAL(myTree2.getName(), "abc");
    BOOST_CHECK_EQUAL(myTree2.getLevel(), 0);
    BOOST_CHECK_EQUAL(myTree2.getDepth(), 1);
  }
  {
    node::Node myRootNode("root");
    myRootNode.addLeft("left");
    myRootNode.addRight("right");

    tree::Tree myCopyTree(myRootNode);
    BOOST_CHECK_EQUAL(myCopyTree.getDepth(), 2);

    BOOST_CHECK_EQUAL(myCopyTree.getName(), "root");
    BOOST_CHECK_EQUAL(myCopyTree.getLevel(), 0);

    myCopyTree.moveLeft();
    BOOST_CHECK_EQUAL(myCopyTree.getName(), "left");
    BOOST_CHECK_EQUAL(myCopyTree.getLevel(), 1);

    myCopyTree.moveTop();
    myCopyTree.moveRight();
    BOOST_CHECK_EQUAL(myCopyTree.getName(), "right");
    BOOST_CHECK_EQUAL(myCopyTree.getLevel(), 1);


    tree::Tree my2CopyTree(myCopyTree);
    BOOST_CHECK_EQUAL(my2CopyTree.getDepth(), 2);
    BOOST_CHECK_EQUAL(my2CopyTree.getName(), "root");
    BOOST_CHECK_EQUAL(my2CopyTree.getLevel(), 0);

    my2CopyTree.moveLeft();
    BOOST_CHECK_EQUAL(my2CopyTree.getName(), "left");
    BOOST_CHECK_EQUAL(my2CopyTree.getLevel(), 1);

    my2CopyTree.moveRoot();
    my2CopyTree.moveRight();
    BOOST_CHECK_EQUAL(my2CopyTree.getName(), "right");
    BOOST_CHECK_EQUAL(my2CopyTree.getLevel(), 1);
  }
}

BOOST_AUTO_TEST_CASE(getNodesTest)
{
  node::Node copyToNode;
  {
    tree::Tree initTree("root");
    initTree.addLeft("l").addRight("r");
    initTree.moveLeft();
    initTree.addLeft("l-l").addRight("l-r");

    copyToNode = initTree.getNodes();   
  }

  BOOST_CHECK_EQUAL(copyToNode.getName(), "root");
  BOOST_CHECK_EQUAL(copyToNode.getLevel(), 0);

  BOOST_CHECK_EQUAL(copyToNode.getLeft().getName(), "l");
  BOOST_CHECK_EQUAL(copyToNode.getLeft().getLevel(), 1);
  BOOST_CHECK_EQUAL(copyToNode.getRight().getName(), "r");
  BOOST_CHECK_EQUAL(copyToNode.getRight().getLevel(), 1);

  BOOST_CHECK_EQUAL(copyToNode.getLeft().getLeft().getName(), "l-l");
  BOOST_CHECK_EQUAL(copyToNode.getLeft().getLeft().getLevel(), 2);
  BOOST_CHECK_EQUAL(copyToNode.getLeft().getRight().getName(), "l-r");
  BOOST_CHECK_EQUAL(copyToNode.getLeft().getRight().getLevel(), 2);

  tree::Tree copyTree(copyToNode.getLeft());
  BOOST_CHECK_EQUAL(copyTree.getDepth(), 2);

  BOOST_CHECK_EQUAL(copyTree.getName(), "l");
  BOOST_CHECK_EQUAL(copyTree.getLevel(), 0);

  copyTree.moveLeft();
  BOOST_CHECK_EQUAL(copyTree.getName(), "l-l");
  BOOST_CHECK_EQUAL(copyTree.getLevel(), 1);

  copyTree.moveTop();
  copyTree.moveRight();
  BOOST_CHECK_EQUAL(copyTree.getName(), "l-r");
  BOOST_CHECK_EQUAL(copyTree.getLevel(), 1);
}

BOOST_AUTO_TEST_CASE(addMoveTest)
{
  tree::Tree myTree("root");
  BOOST_CHECK_EQUAL(myTree.getDepth(), 1);

  myTree.addLeft("l");
  BOOST_CHECK_EQUAL(myTree.getDepth(), 2);
  {
    node::Node rNode("r");
    rNode.addLeft("r-l");
    myTree.addRight(rNode);
  }
  BOOST_CHECK_EQUAL(myTree.getDepth(), 3);

  myTree.moveLeft();
  BOOST_CHECK_EQUAL(myTree.getName(), "l"); 

  myTree.moveTop();
  myTree.moveRight();
  BOOST_CHECK_EQUAL(myTree.getName(), "r");

  myTree.moveLeft();
  BOOST_CHECK_EQUAL(myTree.getName(), "r-l");

  tree::Tree my2Tree("s-root");
  my2Tree.addLeft(myTree);
  my2Tree.addRight(myTree);
  BOOST_CHECK_EQUAL(my2Tree.getDepth(), 4);
  my2Tree.moveLeft();
  BOOST_CHECK_EQUAL(my2Tree.getName(), "root");
  my2Tree.moveRight();
  BOOST_CHECK_EQUAL(my2Tree.getName(), "r");
  my2Tree.moveLeft();
  BOOST_CHECK_EQUAL(my2Tree.getName(), "r-l");
}

BOOST_AUTO_TEST_CASE(selfAddTest)
{
  tree::Tree myTree("test");
  myTree.addLeft(myTree);
  myTree.addRight(myTree);
  BOOST_CHECK_EQUAL(myTree.getDepth(), 3);
  BOOST_CHECK_EQUAL(myTree.moveRight().moveLeft().getName(), "test");
}

BOOST_AUTO_TEST_CASE(deleteTest)
{
  tree::Tree myTree("root");
  myTree.addLeft("l");

  myTree.moveLeft();
  myTree.addLeft("l-l");
  myTree.addRight("l-r");

  myTree.moveTop();
  {
    node::Node myRightNode("r");
    myRightNode.addLeft("r-l");
    myRightNode.addRight("r-r");
    myRightNode.getLeft().addRight("r-l-r");
    
    myTree.addRight(myRightNode);
    BOOST_CHECK_EQUAL(myTree.getDepth(), 4);
  }
  myTree.moveTop();
  myTree.deleteLeft();
  BOOST_CHECK_EQUAL(myTree.getDepth(), 4);

  myTree.moveRight();
  myTree.deleteRight();
  BOOST_CHECK_EQUAL(myTree.getDepth(), 4);

  myTree.deleteLeft();
  BOOST_CHECK_EQUAL(myTree.getDepth(), 2);
}

BOOST_AUTO_TEST_CASE(getContentTest)
{
  tree::Tree myTree("root");
  myTree.addLeft("l");

  myTree.moveLeft();
  myTree.addLeft("l-l");
  myTree.addRight("l-r");

  tree::TreeContent myTreeContent = myTree.getContent();
  BOOST_CHECK_EQUAL(myTreeContent.size(), 3);
  BOOST_CHECK_EQUAL(myTreeContent[0][0], "root");
  BOOST_CHECK_EQUAL(myTreeContent[1][0], "l");
  BOOST_CHECK_EQUAL(myTreeContent[2][0], "l-l");
  BOOST_CHECK_EQUAL(myTreeContent[2][1], "l-r");
}

BOOST_AUTO_TEST_CASE(operatorSetEqualTreeTest)
{
  // set equal to branch from another set
  tree::Tree myTree("root_new");
  myTree.addLeft("left_new").addRight("right_new");

  myTree.moveLeft();
  myTree.addLeft("left-left_new").addRight("left-right_new"); 
  {
    tree::Tree treeOld("root_old");
    treeOld.addLeft("left_old").addRight("right_old");
    treeOld.moveLeft();
    treeOld.addLeft("left-left_old").addRight("left-right_old");
    
    myTree = treeOld;
  }
  myTree.moveRoot();
  BOOST_CHECK_EQUAL(myTree.getName(), "root_new"); // not changed

  BOOST_CHECK_EQUAL(myTree.moveRight().getName(), "right_new"); //not changed
  myTree.moveTop();
  
  myTree.moveLeft();
  BOOST_CHECK_EQUAL(myTree.getName(), "root_old");

  BOOST_CHECK_EQUAL(myTree.moveLeft().getName(), "left_old"); 
  myTree.moveTop();

  myTree.moveLeft();
  BOOST_CHECK_EQUAL(myTree.moveLeft().getName(), "left-left_old");
  myTree.moveTop();

  BOOST_CHECK_EQUAL(myTree.moveRight().getName(), "left-right_old");
  myTree.moveTop();

  // set equal to own subset
  node::Node l2Branch = myTree.moveRoot().moveLeft().moveLeft().getNodes();
  myTree.moveRoot().moveLeft() = l2Branch; // assign all myTree to r-l subtree 
  myTree.moveTop();
  BOOST_CHECK_EQUAL(myTree.getName(), "root_new"); // not changed

  BOOST_CHECK_EQUAL(myTree.moveRight().getName(), "right_new"); //not changed
  myTree.moveTop().moveLeft();

  BOOST_CHECK_EQUAL(myTree.getName(), "root_new"); // self-copy

  BOOST_CHECK_EQUAL(myTree.moveRight().getName(), "right_new"); // self-copy
  myTree.moveTop().moveLeft();

  BOOST_CHECK_EQUAL(myTree.getName(), "root_old");
  BOOST_CHECK_EQUAL(myTree.moveRight().getName(), "right_old");
  
  myTree.moveTop().moveLeft();

  BOOST_CHECK_EQUAL(myTree.getName(), "left_old");
  BOOST_CHECK_EQUAL(myTree.moveLeft().getName(), "left-left_old");

  myTree.moveTop();
  BOOST_CHECK_EQUAL(myTree.moveRight().getName(), "left-right_old");

  // set equal to string
  myTree.moveRoot();
  myTree = "new";
  BOOST_CHECK_EQUAL(myTree.getName(), "new");
  BOOST_CHECK_THROW(myTree.moveLeft(), tree::AddressError);
  myTree.moveTop();
  BOOST_CHECK_THROW(myTree.moveRight(), tree::AddressError);
}

BOOST_AUTO_TEST_CASE(operatorAddLeftRightTreeTest)
{
  tree::Tree myTree("root");
  myTree.addLeft("left").addRight("right");

  myTree.moveLeft();
  myTree.addLeft("left-left").addRight("left-right");
  myTree.moveLeft();
  {
    node::Node l3Node("left-left-left");
  
    myTree < l3Node;
  }
  BOOST_CHECK_EQUAL(myTree.moveLeft().getName(), "left-left-left");

  myTree.moveTop();
  myTree > "right-right-right";
  BOOST_CHECK_EQUAL(myTree.moveRight().getName(), "right-right-right");

  myTree.moveTop();
  BOOST_CHECK_THROW(myTree > "falseRight", tree::InsertError);

  tree::Tree myTree2("root2");
  {
    tree::Tree myTree3("left2");
    myTree2 < myTree3;
    myTree3.setName("right2");
    myTree2 > myTree3;
  }

  BOOST_CHECK_EQUAL(myTree2.getName(), "root2");
  BOOST_CHECK_EQUAL(myTree2.moveLeft().getName(), "left2");
  BOOST_CHECK_THROW(myTree2.moveLeft(), tree::AddressError);

  myTree2.moveTop();

  BOOST_CHECK_EQUAL(myTree2.moveRight().getName(), "right2");
  BOOST_CHECK_THROW(myTree2.moveRight(), tree::AddressError);
}

BOOST_AUTO_TEST_CASE(operatorPushToOutStreamNodeTest)
{
  tree::Tree myTree("root");
  myTree.addLeft("left").addRight("right");

  myTree.moveLeft();
  myTree.addLeft("left-left").addRight("left-right");

  std::ostringstream s;

  s << myTree;

  BOOST_CHECK_EQUAL(s.str(), "0: root, \n1: left, right, \n2: left-left, left-right, \n");
}

BOOST_AUTO_TEST_CASE(operatorGetByNameTreeTest)
{
  tree::Tree myTree("root");
  myTree.addLeft("left").addRight("right");
  myTree.moveRight().addLeft("left-left").moveTop();

  myTree.moveLeft();
  myTree.addLeft("left-left").addRight("left-right");

  BOOST_CHECK_EQUAL(myTree["left-left"].size(), 2);
  BOOST_CHECK_EQUAL(myTree["left-left"][0], myTree["left-left"][1]);
  BOOST_CHECK_EQUAL(myTree["left-left"][0], "left-left");

  BOOST_CHECK_EQUAL(myTree["fakeName"].size(), 0);
}

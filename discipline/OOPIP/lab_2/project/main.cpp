#include "tree.h"

int main() {
  node * myTree = new node();
  
  myTree->init("4")->addNode("5")->addNode("1")->addNode("7")->addNode("6")
    ->addNode("2")->addNode("3")->addNode("8");
  
  myTree->print();
  cout << endl;
  cout << "tree depth: " << node::getDepth() << endl;
  myTree->delTree();

  return 0;
}

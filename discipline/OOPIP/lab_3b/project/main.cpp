#include "tree.h"

int main() {
  Node * firstTree = new Node();
  firstTree->init("30");
  firstTree->addNode("1")->addNode("5")->addNode("2");
  firstTree->print();

  cout << "===" << endl;
  Node * secondTree = new Node(firstTree);

  //cout << firstTree << endl;
  //cout << secondTree->left << endl;
  secondTree->print();
  //cout << secondTree->right->name << endl;
  
  firstTree->delTree();
  secondTree->delTree();
  return 0;
}


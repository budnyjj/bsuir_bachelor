#include <string.h>
#include <iostream>
#include <vector>
#define NAME_LENGTH 10

using namespace std;

typedef vector <const char * > NodeList;

class Node {
  char name[NAME_LENGTH];
  Node * left;
  Node * right;
  NodeList * traverse(NodeList * contents);
  
public:
  Node();
  Node(const char * name);
  Node(const Node * source);

  Node * init(const char * name);
  Node * addNode(const char * name);
  void print();
  void delTree();
};

Node::Node() {
  this->left = 0;
  this->right = 0;
  strncpy(this->name, name, NAME_LENGTH);
}

Node::Node(const char * name) {
  this->left = 0;
  this->right = 0;
  strncpy(this->name, name,NAME_LENGTH);
}

Node::Node(const Node * source) {
  strncpy(this->name, source->name, NAME_LENGTH);
  this->left = 0;
  this->right = 0;

  if (source->left != 0) {
    NodeList * leftSubtree = new NodeList;
    source->left->traverse(leftSubtree);

    for (int i = 0; i < leftSubtree->size(); i++)
      this->addNode(leftSubtree->at(i));
  
    delete leftSubtree;
  }

  if (source->right != 0) {
    NodeList * rightSubtree = new NodeList;
    source->right->traverse(rightSubtree);

    for (int i = 0; i < rightSubtree->size(); i++)
      this->addNode(rightSubtree->at(i));
  
    delete rightSubtree;
  }
}

Node * Node::init(const char * name) {
  this->left = 0;
  this->right = 0;
  strncpy(this->name, name, NAME_LENGTH);
  return this;
}

Node * Node::addNode(const char * name) {
  Node * cur = new Node(name);
  
  Node * parent = this;
  Node * leaf = (strcmp(cur->name, parent->name) > 0 ? parent->right : parent->left);

  while (leaf != 0) {
    parent = leaf;
    if (strcmp(cur->name, parent->name) > 0)
      leaf = leaf->right;
    else
      leaf = leaf->left;
  }
   if (strcmp(cur->name, parent->name) > 0)
     parent->right = cur;
   else
     parent->left = cur;
   return this;
}

void Node::print() {
  NodeList * treeContent = new NodeList;
  this->traverse(treeContent);
  for (int i = 0; i < treeContent->size(); i++) 
    cout << treeContent->at(i) << endl;

  delete treeContent;
}

void Node::delTree() {
  if (this->left != 0)
    this->left->delTree();
  if (this->right != 0)
    this->right->delTree();
  if (this != 0)
    delete this;
};


NodeList * Node::traverse(NodeList * contents) {
  if (this->left != 0)
    this->left->traverse(contents);
  contents->push_back(this->name);
  if (this->right != 0)
    this->right->traverse(contents);
}

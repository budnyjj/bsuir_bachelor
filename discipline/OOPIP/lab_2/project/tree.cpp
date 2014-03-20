#include <string.h>
#include <iostream>
#define NAME_LENGTH 10

using namespace std;

class node {
  char name[NAME_LENGTH];
  node * left;
  node * right;
  static int depth;
public:
  node * init(const char * name);
  node * addNode(const char * name);
  void print() const;
  void delTree();
  static int getDepth();
};

int node::depth;

node * node::init(const char * name) {
  this->left = 0;
  this->right = 0;
  strncpy(this->name, name, NAME_LENGTH);
  node::depth = 1;
  return this;
}

node * node::addNode(const char * name) {
  node * cur = new node;
  cur->init(name);
  
  node * parent = this;
  node * leaf = (strcmp(cur->name, parent->name) > 0 ? parent->right : parent->left);
  
  int cur_depth = 2;

  while (leaf != 0) {
    parent = leaf;
    if (strcmp(cur->name, parent->name) > 0)
      leaf = leaf->right;
    else
      leaf = leaf->left;
    cur_depth++;
  }
   if (strcmp(cur->name, parent->name) > 0)
     parent->right = cur;
   else
     parent->left = cur;

   if (cur_depth > node::depth)
     node::depth = cur_depth;

   return this;
}

void node::print() const {
  if (this != 0) {
    if (this->left != 0) this->left->print();
    cout << this->name << endl;
    if (this->right != 0) this->right->print();
  }
}

void node::delTree() {
  if (this->left != 0)
    this->left->delTree();
  if (this->right != 0)
    this->right->delTree();
  if (this != 0)
    delete this;
};

int node::getDepth() {
  return node::depth;
}

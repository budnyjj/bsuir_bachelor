#include <string.h>
#include <iostream>
#define NAME_LENGTH 10

using namespace std;

struct node {
  int level;
  char name[NAME_LENGTH];
  node * left;
  node * right;
};

node * createTree(const char * name);
node * addNode(node * parent, const char * name);
void printTree(node * parent);
void delTree(node * parent);

int main() {
  node * myTree = createTree("a");

  addNode(myTree, "32");
  addNode(myTree, "z");
  addNode(myTree, "e");
  addNode(myTree, "c");

  printTree(myTree);

  delTree(myTree);
  return 0;
}

node * createTree(const char * name) {
  node * root = new node;
  root->left = 0;
  root->right = 0;
  root->level = 0;
  strncpy(root->name, name, NAME_LENGTH);
  return root;
}

node * addNode(node * parent, const char * name) {
  node * cur = new node;
  cur->left = 0;
  cur->right = 0;
  strncpy(cur->name, name, NAME_LENGTH);
  cur->level = 1;

  node * leaf = (strcmp(cur->name, parent->name) > 0 ? parent->right : parent->left);

  while (leaf != 0) {
    parent = leaf;
    if (strcmp(cur->name, parent->name) > 0)
      leaf = leaf->right;
    else
      leaf = leaf->left;
    cur->level++;
  }
   if (strcmp(cur->name, parent->name) > 0)
     parent->right = cur;
   else
     parent->left = cur;
   return cur;
}

void printTree(node * parent) {
  if (parent != 0) {
    if (parent->left != 0) printTree(parent->left);
    cout << parent->level << ": " << parent->name << endl;
    if (parent->right != 0) printTree(parent->right);
  }
}

void delTree(node * parent) {
  if (parent->left != 0)
    delTree(parent->left);
  if (parent->right != 0)
    delTree(parent->right);
  if (parent != 0)
    delete parent;
};

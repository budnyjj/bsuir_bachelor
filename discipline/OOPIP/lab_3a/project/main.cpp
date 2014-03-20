#include <vector>

#include "binary_tree.h"
#include "user_menu.h"

int main() {
	std::vector<Tree*> trees;
	std::vector<Tree*>::iterator it;
	Tree *tree = 0;

	treeOperationsMenu(tree, trees, it);

	return 0;
}
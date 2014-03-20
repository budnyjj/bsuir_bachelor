#ifndef USER_MENU_H
#define USER_MENU_H

#include <iostream>
#include <string>

void printFirstTreeMenu();
void firstTreeMenu(Tree *, std::vector<Tree*> &);
void printTreeOperationsMenu();
void treeOperationsMenu(Tree *, std::vector<Tree*> &, std::vector<Tree*>::iterator &);
void printCreateTreeMenu();
void createTreeMenu(Tree *, std::vector<Tree*> &);

int elem = 0;

void printFirstTreeMenu() {
	const std::string createTreeMenu[] = {
		"+-------Create binary tree:-----------------------------+",
		"|  c -- Create tree                                     |",
		"|  e -- create tree based on the Element                |",
		"|  q -- Quit                                            |",
		"+-------------------------------------------------------+"
	};
	
	for (int i = 0; i < sizeof(createTreeMenu)/sizeof(*createTreeMenu); i++) {
		std::cout << createTreeMenu[i] << std::endl;
	}
}

void firstTreeMenu(Tree *tree, std::vector<Tree*> &trees) {
	printFirstTreeMenu();
	std::cin.sync();
	std::cin.clear();

	elem = 0;
	switch (std::cin.get())
	{
	case 'q':
	case 'Q':
		exit(0);
	case 'c':
	case 'C':
		tree = new Tree();
		trees.push_back(tree);
		break;
	case 'e':
	case 'E':
		std::cout << "Enter the element:" << std::endl;
		std::cin.clear();
		std::cin.sync();
		elem = 0;
		std::cin >> elem;

		if (!elem) {
			std::cout << "Error! Enter Integer data" << std::endl;
			firstTreeMenu(tree, trees);
			break;
		}
		tree = new Tree(elem);
		trees.push_back(tree);
		break;
	default:
		std::cout << "Entered the wrong character!" << std::endl;
		firstTreeMenu(tree, trees);
		return;
	}
}

void printTreeOperationsMenu() {
	const std::string treeOperationsMenu[] = {
		"+-------Binary tree operations:-------------------------+",
		"|  a -- Add element                                     |",
		"|  u -- level Up                                        |",
		"|  l -- level down (Left branch)                        |",
		"|  r -- level down (Right branch)                       |",
		"|  m -- Move to the root element                        |",
		"|  f -- Find from the root                              |",
		"|  p -- Print tree                                      |",
		"|  d -- Delete subtrees                                 |",
		"|  c -- Create new tree                                 |",
		"|  s -- Switch trees                                    |",
		"|       - - - - - - - - - - - - - - - - - - - - - -     |",
		"|  h -- this Help                                       |",
		"|  q -- Quit                                            |",
		"+-------------------------------------------------------+"
	};
	
	for (int i = 0; i < sizeof(treeOperationsMenu)/sizeof(*treeOperationsMenu); i++) {
		std::cout << treeOperationsMenu[i] << std::endl;
	}
}

void treeOperationsMenu(Tree *tree, std::vector<Tree*> &trees, std::vector<Tree*>::iterator &it) {
	firstTreeMenu(tree, trees);
	
	printTreeOperationsMenu();
	tree = trees[0];
	int position = 0;

	while (1) {
		elem = 0;
		std::cin.sync();
		std::cin.clear();
	
		char ch = std::cin.get();
		switch (ch)
		{
		case 'a':
		case 'A':
			std::cout << "Enter the element:" << std::endl;
			elem = 0;
			std::cin >> elem;

			if (!elem) {
				std::cout << "Error! Enter Integer data" << std::endl;
				break;
			}
			try
			{
				tree->add(elem);
			}
			catch (InsertError &err)
			{
				err.printMsg();
			}
			break;
		case 'u':
		case 'U':
			try
			{
				tree->levelUp();
			}
			catch (TreeError &err)
			{
				err.printMsg();
			}
			break;
		case 'l':
		case 'L':
			try
			{
				tree->levelDownToLeft();
			}
			catch (TreeError &err)
			{
				err.printMsg();
			}
			break;
		case 'r':
		case 'R':
			try
			{
				tree->levelDownToRight();
			}
			catch (TreeError &err)
			{
				err.printMsg();
			}
			break;
		case 'm':
		case 'M':
			tree->goToRoot();
			break;
		case 'f':
		case 'F':
			std::cout << "Enter the element:" << std::endl;
			elem = 0;
			std::cin >> elem;

			if (!elem) {
				std::cout << "Error! Enter Integer data" << std::endl;
				break;
			}
			tree->find(elem);
			break;
		case 'p':
		case 'P':
			// position of selected tree
			it = find(trees.begin(), trees.end(), tree);
			it++;
			position = std::distance(trees.begin(), it);
			
			std::cout << "---- Tree number: " << position << " of " << trees.size() << " --------------------------------" << std::endl;
			
			tree->print();
			//std::cout << *(tree);
			
			std::cout << std::endl << "---------------------------------------------------------" << std::endl;
			break;
		case 'd':
		case 'D':
			tree->del();
			break;
		case 'c':
		case 'C':
			createTreeMenu(tree, trees);
			tree = trees.back();
			break;
		case 's':
		case 'S':
			// switch trees;
			std::cout << "Choose one of the " << trees.size() << " trees:" << std::endl; 
			std::cin.sync();
			std::cin.clear();
			elem = 0;
			std::cin >> elem;
			if (!elem) {
				std::cout << "Error! Enter Integer data" << std::endl;
				break;
			}
			tree = trees[elem-1];
			break;
		case 'h':
		case 'H':
			printTreeOperationsMenu();
			break;
		case 'q':
		case 'Q':
			exit(0);
		default:
			std::cout << "Entered the wrong character!" << std::endl;
			break;
		}
	}
}

void printCreateTreeMenu() {
	const std::string createTreeMenu[] = {
		"+-------Create binary tree:-----------------------------+",
		"|  c -- Create tree                                     |",
		"|  e -- create tree based on the Element                |",
		"|  t -- create tree based on the existing Tree          |",
		"|  q -- quit                                            |",
		"+-------------------------------------------------------+"
	};
	
	for (int i = 0; i < sizeof(createTreeMenu)/sizeof(*createTreeMenu); i++) {
		std::cout << createTreeMenu[i] << std::endl;
	}
}

void createTreeMenu(Tree *tree, std::vector<Tree*> &trees) {
	printCreateTreeMenu();

	std::cin.sync();
	std::cin.clear();
	char ch = std::cin.get();
	switch (ch)
	{
	case 'q':
	case 'Q':
		break;
	case 'c':
	case 'C':
		trees.push_back(new Tree());
		tree = trees.back();
		break;
	case 'e':
	case 'E':
		std::cin.sync();
		std::cin.clear();
		std::cout << "Enter the element:" << std::endl;
		elem = 0;
		std::cin >> elem;
		if (!elem) {
			std::cout << "Error! Enter Integer data" << std::endl;
			break;
		}
		
		trees.push_back(new Tree(elem));
		break;
	case 't':
	case 'T':
		std::cout << "Choose the basic tree (one of the " << trees.size() << " trees):" << std::endl; 
		std::cin.sync();
		std::cin.clear();
		elem = 0;
		std::cin >> elem;
		if (!elem) {
			std::cout << "Error! Enter Integer data" << std::endl;
			break;
		}
		trees.push_back(new Tree(*trees[elem-1]));
		tree = trees.back();
		break;
	default:
		std::cout << "Entered the wrong character!" << std::endl;
		break;
	}
}

#endif
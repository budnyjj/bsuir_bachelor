#include "tree.hpp"
#include "cli.hpp"

int main(int argc, char *argv[])
{
  std::string initName = cli::inputName();
  tree::Tree myTree(initName);

  cli::printUseMsg();

  char ch;
  while (std::cin >> ch) 
    {
      cli::clear();
      switch(ch)
	{
	case 'H':
	case 'h':
	  {
	    cli::printHelpMsg();
	    break;
	  }
	case 'I':
	case 'i':
	  {
	    std::string iName = cli::inputName();
	    if (cli::chooseBranch())
	      try
		{
		  myTree > iName;
		}
	      catch(tree::InsertError& e)
		{
		  std::cout << e << std::endl;
		}
	    else
	      try 
		{
		  myTree < iName;
		}
	      catch(tree::InsertError& e)
		{
		  std::cout << e << std::endl;
		}
	    break;
	  }
	case 'U':
	case 'u':
	  {
	    myTree.setName(cli::inputName());
	    break;
	  }
	case 'd':
	case 'D':
	  {
	    if (cli::chooseBranch())
	      {
		myTree.deleteRight();
	      }
	    else
	      {
		myTree.deleteLeft();
	      }
	    break;
	  }
	case 'L':
	case 'l':
	  {
	    try
	      {
		myTree.moveLeft();
	      }
	    catch (tree::AddressError& e)
	      {
		std::cout << e << std::endl; 
	      }
	    break;
	  }
	case 'R':
	case 'r':
	  {
	    try
	      {
		myTree.moveRight();
	      }
	    catch (tree::AddressError& e)
	      {
		std::cout << e << std::endl;
	      }
	    break;
	  }
	case 'T':
	case 't':
	  {
	    myTree.moveTop();
	    break;
	  }
	case 'G':
	case 'g': 
	  {
	    std::string oName = myTree.getName();
	    std::string oLeftName = "NULL";
	    std::string oRightName = "NULL";

	    try 
	      {
		myTree.moveLeft();
		oLeftName = myTree.getName();
		myTree.moveTop();
	      }
	    catch (tree::AddressError)
	      {
		oLeftName = "NULL";
	      }

	    try
	      {
		myTree.moveRight();
		oRightName = myTree.getName();
		myTree.moveTop();
	      }
	    catch (tree::AddressError)
	      {
		oRightName = "NULL";
	      }

	    std::cout << oName << ": "
		      << oLeftName << ", "
		      << oRightName << std::endl;
	    break;
	  }
	case 'P':
	case 'p':
	  {
	    std::cout << myTree;
	    break;
	  }
	case 'Q':
	case 'q':
	  {
	    return 0;
	  }
	default:
	  break;
	}
    }
  
  return 0;
}

#include <iostream>
#include <limits>

/// Used for work with class Tree in CLI
namespace cli {
  /// Clears input stream.
  void clear()
  {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }

  /// Prints basic usage message.
  void printUseMsg() {
    const std::string helpMessage =
      "Usage: press H to get list if commands, Q to quit.";
    std::cout << helpMessage << std::endl;
  }

  /// Prints help message.
  void printHelpMsg() {
    const int helpLength = 12;
    const std::string helpMessage[] = {
      "+-| Help |-------------------------+",
      "| G	-- Get node content    	   |",
      "| P	-- Print subtree content   |",
      "| I	-- Insert child node	   |",
      "| U	-- Update node content	   |",
      "| D	-- Delete subtree 	   |",
      "| L	-- move to Left branch     |",
      "| R	-- move to Right branch    |",
      "| T	-- move to Top             |",
      "| H	-- get Help		   |",
      "| Q	-- Quit			   |",
      "+----------------------------------+",
    };
    for (int i = 0; i < helpLength; i++)
      {
	std::cout << helpMessage[i] << std::endl;
      }
  }

  /// Gets and process strings (may be with spaces) from input stream.
  std::string inputName()
  {
    std::string iName;
    std::cout << "Input content to store: ";
    std::getline(std::cin, iName);
    return iName;
  }

  ///\brief Process user selection of tree branch to use.
  /// 
  /// User may select left(default) or right branch.
  /// Returns 1 if right selected; 0 in other way.
  ///
  bool chooseBranch()
  {
    char cBranch;
    std::cout << "Choose branch (L/r): ";
    while (std::cin.get(cBranch))
      {
	switch (cBranch)
	  {
	  case '\n':
	  case 'L':
	  case 'l':
	    return 0;
	    break;
	  case 'R':
	  case 'r':
	    return 1;
	    break;
	  default:
	    std::cout << "Error! Choose branch: _L_eft (default) or _R_ight: ";
	    break;
	  }
	clear();
      }	
    }
}

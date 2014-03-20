#include "node.hpp"
#include <ostream>
#include <vector>

/// Used for Tree-relation clasees.
namespace tree
{
  /// Vector of node content.
  typedef std::vector< std::string > TreeNodes;

  /// Provides pretty tree representation.
  typedef std::vector< TreeNodes > TreeContent;

  /// Basic error class
  class BasicError {
  protected:
    const node::Node *const ePointer;
  public:
    BasicError(const node::Node *const iPointer = NULL)
      : ePointer(iPointer) {};
  };
  
  /// Thrown if try to add something to busy place.
  class InsertError : protected BasicError
  {
    std::string msg;
  public:
    InsertError(const node::Node *const iPointer = NULL)
      : BasicError(iPointer) {
      this->msg = "Cannot insert element to busy place";
    }
    friend std::ostream& operator<<(std::ostream& os, const InsertError& e);
  }; 

  /// Thrown if try to access empty place.
  class AddressError : protected BasicError
  {
    std::string msg;
  public:
    AddressError(const node::Node *const iPointer = NULL)
      : BasicError(iPointer) {
      this->msg = "Cannot get access to NULL pointer";
    }
    friend std::ostream& operator<<(std::ostream& os, const AddressError& e);
  };

  ///\brief Used for encapsulate node::Node structures.
  ///
  /// This class provides tree-oriented operations based on node::Node class.
  class Tree
  {
    unsigned int depth;
    node::Node root;
    node::Node * pCur;

    void _getContent(const node::Node& cNode, TreeContent& content) const;
    void _search(const std::string& sName, const node::Node& cNode, TreeNodes& found) const;
  public:
    /// Creates tree with unnamed node and depth == 1.
    Tree()
      : root(), pCur(&root), depth(1) 
      {};

    ///\brief Creates tree with specified name and depth == 1.
    ///
    ///\param iName -- name for node.
    Tree(const std::string& iName)
      : root(iName), pCur(&root), depth(1)
      {};

    ///\brief Creates tree from node::Node structure.
    ///
    /// Normalizes node levels.
    ///\param iNode -- source node node::Node to copy.
    Tree(const node::Node& iNode)
      : root(iNode), pCur(&root)
      {	this->depth = this->pCur->normalizeLevel(); };

    ///\brief Creates tree from other tree.
    ///
    /// Insert nodes from *copy* of source tree.
    /// Normalizes node levels.
    ///\param iTree -- source tree to copy.
    Tree(const tree::Tree& iTree)
      : root(iTree.getNodes()), pCur(&root), depth(iTree.getDepth())
      {};
    
    Tree& addLeft(const std::string& iName); 
    Tree& addLeft(const node::Node& iNode); 
    Tree& addLeft(const Tree& iTree); 

    Tree& addRight(const std::string& iName);
    Tree& addRight(const node::Node& iNode);
    Tree& addRight(const Tree& iTree);

    Tree& moveLeft();
    Tree& moveRight();
    Tree& moveTop();
    Tree& moveRoot();

    Tree& deleteLeft();
    Tree& deleteRight();

    std::string getName() const;
    Tree& setName(const std::string& iName);

    Tree& operator=(const tree::Tree& iTree);
    Tree& operator=(const node::Node& iNode); 
    Tree& operator=(const std::string& iName);

    Tree& operator<(const tree::Tree& iTree);
    Tree& operator<(const node::Node& iNode);
    Tree& operator<(const std::string& iName);

    Tree& operator>(const tree::Tree& iTree);
    Tree& operator>(const node::Node& iNode);
    Tree& operator>(const std::string& iName);
    
    unsigned int getLevel() const;
    unsigned int getDepth() const;

    node::Node& getNodes() const;

    TreeNodes search(const std::string& sName) const;
    TreeContent getContent() const;

    TreeNodes operator[](const std::string& sName) const;
  };

  ///\brief Adds left child.
  ///
  /// Inserts node with specified name as left child, if not exists.
  /// Normalizes inserted node.
  /// Throws tree::InsertError exception in other way.
  ///
  ///\param iName -- name of node to insert.
  Tree& Tree::addLeft(const std::string& iName)
  {
    try
      {
	this->pCur->addLeft(iName);
      }
    catch(node::InsertError)
      {
	throw InsertError(this->pCur);
      }
    this->depth = (this->root).normalizeLevel(); 
    return *this;
  }

  ///\brief Adds left child.
  ///
  /// Inserts node structure as left child, if not exists.
  /// Normalizes inserted subtree.
  /// Throws tree::InsertError exception in other way.
  ///
  ///\param iNode -- source of node structure to insert.
  Tree& Tree::addLeft(const node::Node& iNode) 
  {
    try
      {
	this->pCur->addLeft(iNode);
      }
    catch(node::InsertError)
      {
	throw InsertError(this->pCur);
      }
    this->depth = (this->root).normalizeLevel(); 
    return *this;
  }

  ///\brief Adds left child.
  ///
  /// Inserts *copy* of *whole* tree as left child, if not exists.
  /// Normalizes inserted subtree.
  /// Throws tree::InsertError exception in other way.
  ///
  ///\param iTree -- source tree to insert.
  Tree& Tree::addLeft(const tree::Tree& iTree) 
  {
    try
      {
	this->pCur->addLeft(iTree.getNodes());
      }
    catch(node::InsertError)
      {
	throw InsertError(this->pCur);
      }
    this->depth = (this->root).normalizeLevel(); 
    return *this;
  }

  ///\brief Adds right child.
  ///
  /// Inserts node with specified name as right child, if not exists.
  /// Normalizes inserted node.
  /// Throws tree::InsertError exception in other way.
  ///
  ///\param iName -- name of node to insert.
  Tree& Tree::addRight(const std::string& iName)
  {
    try
      {
	this->pCur->addRight(iName);
      }
    catch(node::InsertError)
      {
	throw InsertError(this->pCur);	
      }
    this->depth = (this->root).normalizeLevel(); 
    return *this;
  }

  ///\brief Adds right child.
  ///
  /// Inserts node structure as right child, if not exists.
  /// Normalizes inserted subtree.
  /// Throws tree::InsertError exception in other way.
  ///
  ///\param iNode -- source of node structure to insert.
  Tree& Tree::addRight(const node::Node& iNode) 
  {
    try
      {
	this->pCur->addRight(iNode);
      }
    catch(node::InsertError)
      {
	throw InsertError(this->pCur);	
      }
    this->depth = (this->root).normalizeLevel(); 
    return *this;
  }

  ///\brief Adds right child.
  ///
  /// Inserts *copy* of *whole* tree as right child, if not exists.
  /// Normalizes inserted subtree.
  /// Throws tree::InsertError exception in other way.
  ///
  ///\param iTree -- source tree to insert.
  Tree& Tree::addRight(const tree::Tree& iTree) 
  {
    try
      {
	this->pCur->addRight(iTree.getNodes());
      }
    catch(node::InsertError)
      {
	
      }
    this->depth = (this->root).normalizeLevel(); 
    return *this;
  }

  ///\brief Move operation pointer to left child.
  ///
  /// Throws tree::AddressError exception if there is no left child.
  Tree& Tree::moveLeft()
  {
    try
      {
	this->pCur = &(this->pCur->getLeft());
      }
    catch(node::AddressError)
      {
	throw AddressError(this->pCur);	
      }
    return *this;
  }

  ///\brief Move operation pointer to right child.
  ///
  /// Throws tree::AddressError exception if there is no right child.
  Tree& Tree::moveRight()
  {
    try
      {
	this->pCur = &(this->pCur->getRight());
      }
    catch(node::AddressError)
      {
	throw AddressError(this->pCur);	
      }
    return *this;
  }

  /// Move operation pointer to parent node.
  Tree& Tree::moveTop()
    {
      try
	{
	  this->pCur = &(this->pCur->getTop());
	}
      catch(node::AddressError)
	{
	  this->pCur = &(this->root);
	}
      return *this;
    }
    
  /// Move operation pointer to root node.
  Tree& Tree::moveRoot()
  {
    this->pCur = &(this->root);
    return *this;
  }

  /// Deletes selected left subtree.
  Tree& Tree::deleteLeft() 
  {
    this->pCur->deleteLeft();
    this->depth = (this->root).normalizeLevel();
    return *this;
  }

  /// Deletes selected right subtree.  
  Tree& Tree::deleteRight()
  {
    this->pCur->deleteRight();
    this->depth = (this->root).normalizeLevel();
    return *this;
  }

  /// Get selected node name.
  std::string Tree::getName() const 
  {
    return std::string(this->pCur->getName());
  }

  /// Set selected node name.
  Tree& Tree::setName(const std::string& iName)
  {
    this->pCur->setName(iName);
    return *this;
  }

  /// Get level of selected node.
  unsigned int Tree::getLevel() const 
  {
    return this->pCur->getLevel();
  }

  /// Get tree depth.
  unsigned int Tree::getDepth() const 
  {
    return this->depth;
  }
  
  /// Get *copy* node structure of tree.
  node::Node& Tree::getNodes() const
    {
      return *(new node::Node(this->root));
    }

  ///\brief Sets content under operation pointer equal to *copy*
  /// of whole tree structure.
  ///
  ///\param iTree -- source tree.
  Tree& Tree::operator=(const Tree& iTree)
  {
    // copies data from whole @iTree without changing top pointer
    node::Node iCopyNodes = iTree.getNodes();
    this->deleteLeft();
    this->deleteRight();
    this->setName(iCopyNodes.getName());
    this->addLeft(iCopyNodes.getLeft());
    this->addRight(iCopyNodes.getRight());

    this->depth = (this->root).normalizeLevel(); 	

    return *this;
  }

  ///\brief Sets content under operation pointer equal to *copy*
  /// of specified node structure.
  ///
  ///\param iNode -- source node structure.
  Tree& Tree::operator=(const node::Node& iNode)
  {
    // copies data from iNode without changing top pointer
    this->deleteLeft();
    this->deleteRight();
    this->setName(iNode.getName());
    this->addLeft(iNode.getLeft());
    this->addRight(iNode.getRight());

    this->depth = (this->root).normalizeLevel(); 	
    
    return *this;
  }

  ///\brief Sets content under operation pointer equal to node with specified name.
  ///
  ///\param iName -- source name for node to replace.
  Tree& Tree::operator=(const std::string& iName)
  {
    this->deleteLeft();
    this->deleteRight();
    this->setName(iName);

    this->depth = (this->root).normalizeLevel(); 	
    return *this;
  }

  ///\brief Adds *copy* of whole source tree as left child
  /// of operation pointer.
  ///
  /// Normalizes inserted subtree.
  /// Throws tree::InsertError exception if try to insert iNode to busy place.
  ///
  ///\param iTree -- source tree.
  Tree& Tree::operator<(const tree::Tree& iTree)
  {
    // copy node because of recursion possibility
    node::Node iTreeNodes = iTree.getNodes();
    // insert nodes as left child
    this->addLeft(iTreeNodes);
    return *this;
  }

  ///\brief Adds specified node structure as left child
  /// of operation pointer.
  ///
  /// Normalizes inserted subtree.
  /// Throws tree::InsertError exception if try to insert iNode to busy place.
  ///
  ///\param iNode -- source node structure.
  Tree& Tree::operator<(const node::Node& iNode)
  {
    // insert node as left child
    this->addLeft(iNode);
    return *this;
  }

  ///\brief Adds node with specified name as left child of
  /// operation pointer.
  ///
  /// Throws node::InsertError exception if try to insert iNode to busy place.
  /// Normalizes inserted node.
  ///
  ///\param iName -- source name for node to insert.
  Tree& Tree::operator<(const std::string& iName)
  {
    // insert node as left child
    this->addLeft(iName);
    return *this;
  }

  ///\brief Adds *copy* of whole source tree as right child
  /// of operation pointer.
  ///
  /// Normalizes inserted subtree.
  /// Throws tree::InsertError exception if try to insert iNode to busy place.
  ///
  ///\param iTree -- source tree.
  Tree& Tree::operator>(const tree::Tree& iTree)
  {
    // copy node because of recursion possibility
    node::Node iTreeNodes = iTree.getNodes();
    // insert nodes as left child
    this->addRight(iTreeNodes);
    return *this;
  }

  ///\brief Adds specified node structure as right child
  /// of operation pointer.
  ///
  /// Normalizes inserted subtree.
  /// Throws tree::InsertError exception if try to insert iNode to busy place.
  ///
  ///\param iNode -- source node structure.
  Tree& Tree::operator>(const node::Node& iNode)
  {
    // insert node as right child
    this->addRight(iNode);
    return *this;
  }

  ///\brief Adds node with specified name as right child of
  /// operation pointer.
  ///
  /// Throws node::InsertError exception if try to insert iNode to busy place.
  /// Normalizes inserted node.
  ///
  ///\param iName -- source name for node to insert.
  Tree& Tree::operator>(const std::string& iName)
  {
    // insert node as right child
    this->addRight(iName);
    return *this;
  }

  std::ostream& operator<<(std::ostream& os, const tree::Tree& cTree)
  {
    TreeContent cTreeContent = cTree.getContent();
    for (int i = 0; i < cTreeContent.size(); i++)
      {
	os << i << ": ";
	for (int j = 0; j < cTreeContent[i].size(); j++)
	  os << cTreeContent[i][j] << ", ";
	os << std::endl;
      }
      return os;
    }

  void Tree::_getContent(const node::Node& cNode, TreeContent& content) const
  {
    content[cNode.getLevel()].push_back(cNode.getName());
    try
      {
	this->_getContent(cNode.getLeft(), content);
      }
    catch (node::AddressError) {}
    try
      {
	this->_getContent(cNode.getRight(), content);
      }
    catch (node::AddressError) {}
  }

  /// Gets tree content in vector-based representation.
  TreeContent Tree::getContent() const
  {
    TreeContent content;
    content.resize(this->depth);
    this->_getContent(this->root, content);
    return content; 
  }

  void Tree::_search(const std::string& sName, const node::Node& cNode, TreeNodes& found) const
  {
    if (cNode.getName() == sName)
      found.push_back(cNode.getName());
    try
      {
	this->_search(sName, cNode.getLeft(), found);
      }
    catch (node::AddressError) {}
    try
      {
	this->_search(sName, cNode.getRight(), found);
      }
    catch (node::AddressError) {}
  }

  ///\brief Finds nodes with specified name.
  ///
  /// Returns a vector of found node contents.
  TreeNodes Tree::search(const std::string& sName) const
  {
    TreeNodes found;
    this->_search(sName, this->root, found);
    return found;
  }

  ///\brief Finds nodes with specified name.
  ///
  /// Returns a vector of found node contents.
  TreeNodes Tree::operator[](const std::string& sName) const
  {
    return this->search(sName);
  }

  std::ostream& operator<<(std::ostream& os, const InsertError& e)
  {
    os << e.msg << " at " << e.ePointer; 
    return os;
  }

  std::ostream& operator<<(std::ostream& os, const AddressError& e)
  {
    os << e.msg << " at " << e.ePointer; 
    return os;
  }
}


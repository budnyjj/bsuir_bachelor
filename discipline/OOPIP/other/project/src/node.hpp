#include <string>
#include <ostream>

/// Used for Node-relation classes.
namespace node
{
  class Node;

  /// Basic error class
  class BasicError {
  protected:
    const Node *const ePointer;
  public:
    BasicError(const Node *const iPointer = NULL)
      : ePointer(iPointer) {};
  };

  /// Thrown if try to add node to busy place.
  class InsertError : protected BasicError
  {
    std::string msg;
  public:
    InsertError(const Node *const iPointer = NULL)
      : BasicError(iPointer) {
      this->msg = "Cannot insert node to busy place";
    }
    friend std::ostream& operator<<(std::ostream& os, const InsertError& e);
  }; 

  /// Thrown if try to access empty place.
  class AddressError : protected BasicError
  {
    std::string msg;
  public:
    AddressError(const Node *const iPointer = NULL)
      : BasicError(iPointer) {
      this->msg = "Cannot get access to NULL pointer";
    }
    friend std::ostream& operator<<(std::ostream& os, const AddressError& e);
  };

  /// This class provides atomized operations relationed to current node.
  class Node
  {
    unsigned int level; 
    
    std::string name;	
    Node * left;	
    Node * right;	
    Node * top; 

    friend void _connect(Node* cNode, const Node* pNode);
    void _normalizeLevel(const unsigned int& iLevel, unsigned int& maxLevel);
  public:
    Node();
    Node(const std::string& iName);
    Node(const Node& iNode);
    ~Node();

    Node& getLeft() const; 
    Node& getRight() const;
    Node& getTop() const;

    Node& addLeft(const std::string& iName);
    Node& addLeft(const Node& iNode);

    Node& addRight(const std::string& iName);
    Node& addRight(const Node& iNode);

    Node& deleteLeft();
    Node& deleteRight();

    std::string getName() const;
    Node& setName(const std::string& iName);

    Node& operator=(const Node& iNode);
    Node& operator=(const std::string& iName);

    Node& operator<(const Node& iNode);
    Node& operator<(const std::string& iName);

    Node& operator>(const Node& iNode);
    Node& operator>(const std::string& iName);
 
    unsigned int getLevel() const;
    unsigned int normalizeLevel();
  };

  /// Creates node with empty name and zero level.
  Node::Node()
    : name(""), level(0)
  {
    this->top = NULL;
    this->left = NULL;
    this->right = NULL;
  }

  ///\brief Creates node with specified name and zero level.
  ///
  ///\param iName -- name for node.
  Node::Node(const std::string& iName)
    : name(iName), level(0)
  {
    this->top = NULL;
    this->left = NULL;
    this->right = NULL;
  }

  ///\brief Copy constructor.
  ///
  /// Creates node from other node structure.
  /// Level may be not normalized, but grown.
  ///\param iNode -- source node to copy.
  Node::Node(const Node& iNode)
    : name(iNode.getName()), level(iNode.getLevel())
  {
    try
      {
	this->left = new Node(iNode.getLeft());
	_connect(this->left, this);
      }
    catch(AddressError)
      {
	this->left = NULL;
      }
    try 
      {
	this->right = new Node(iNode.getRight());
	_connect(this->right, this);
      }
    catch(AddressError)
      {
	this->right = NULL;
      }
  }
  
  /// Recursive destructor.
  Node::~Node()
    {
      delete this->left;
      delete this->right;
    }

  /// Get node name.
  std::string Node::getName() const 
  {
    return std::string(this->name);
  }

  /// Set node name.
  Node& Node::setName(const std::string& iName)
  {
    this->name = iName;
    return *this;
  }
  
  /// Get node level.
  unsigned int Node::getLevel() const 
  {
    return this->level;
  }

  ///\brief Get reference to left child.
  ///
  /// Returns reference to left child, if exists.
  /// Throws node::AddressError exception in other way.
  Node& Node::getLeft() const 
  {
    if (this->left != 0)
      return *(this->left);
    else 
      throw AddressError(this);
  }

  ///\brief Get reference to right child.
  ///
  /// Returns reference to right child, if exists.
  /// Throws node::AddressError exception in other way.
  Node& Node::getRight() const 
  {
    if (this->right != 0)
      return *(this->right);
    else
      throw AddressError(this);
  }

  ///\brief Get reference to parent node.
  ///
  /// Returns reference to parent node, if exists.
  /// Throws node::AddressError exception in other way.
  ///
  Node& Node::getTop() const 
  {
    if (this->top != 0)
      return *(this->top);
    else
      throw AddressError(this);
  }

  ///\brief Adds left child.
  ///
  /// Inserts node with specified name as left child, if not exists.
  /// Normalizes inserted node.
  /// Throws node::InsertError exception in other way.
  ///
  ///\param iName -- name of node to insert.
  Node& Node::addLeft(const std::string& iName)
  {
    if (this->left == 0)
      {
	this->left = new Node(iName);
	_connect(this->left, this);
      }
    else
      throw InsertError(this);

    unsigned int maxLevel = this->level;
    this->_normalizeLevel(this->level, maxLevel);
    return *this;
  }

  ///\brief Adds left child.
  ///
  /// Inserts node structure as left child, if not exists.
  /// Normalizes inserted subtree.
  /// Throws node::InsertError exception in other way.
  ///
  ///\param iNode -- source of node structure to insert.
  Node& Node::addLeft(const Node& iNode)
  {
    if (this->left == 0) {
	this->left = new Node(iNode);
	_connect(this->left, this);
    }
    else
      throw InsertError(this);

    unsigned int maxLevel = this->level;
    this->_normalizeLevel(this->level, maxLevel);
    return *this;
  }

  ///\brief Adds right child.
  ///
  /// Inserts node with specified name as right child, if not exists.
  /// Normalizes inserted node.
  /// Throws node::InsertError exception in other way.
  ///
  ///\param iName -- name of node to insert.
  Node& Node::addRight(const std::string& iName)
  {
    if (this->right == 0)
      {      
	this->right = new Node(iName);
	_connect(this->right, this);
      }
    else
      throw InsertError(this);

    unsigned int maxLevel = this->level;
    this->_normalizeLevel(this->level, maxLevel);
    return *this;
  }

  ///\brief Adds left child.
  ///
  /// Inserts node structure as right child, if not exists.
  /// Normalizes inserted subtree.
  /// Throws node::InsertError exception in other way.
  ///
  ///\param iNode -- source of node structure to insert.
  Node& Node::addRight(const Node& iNode)
  {
    if (this->right == 0)
      {
	this->right = new Node(iNode);
	_connect(this->right, this);
      }
    else
      throw InsertError(this);

    unsigned int maxLevel = this->level;
    this->_normalizeLevel(this->level, maxLevel);
    return *this;
  }

  /// Deletes left subtree.
  Node& Node::deleteLeft() 
  {
    delete this->left;
    this->left = NULL;
    return *this;
  }

  /// Deletes right subtree.
  Node& Node::deleteRight()
  {
    delete this->right;
    this->right = NULL;
    return *this;
  }

  ///\brief Sets current node equal to *copy* of specified node structure.
  ///
  ///\param iNode -- source node structure.
  Node& Node::operator=(const Node& iNode)
  {
    // copy data from iNode without changing top pointer
    if (this != &iNode)
      {
	// iNode can be subset of *this
	Node iCopyNode(iNode);
  	this->deleteLeft();
  	this->deleteRight();
  	this->setName(iCopyNode.getName());
  	this->addLeft(iCopyNode.getLeft());
  	this->addRight(iCopyNode.getRight());
	
  	unsigned int maxLevel = this->level;
  	this->_normalizeLevel(this->level, maxLevel);
      }  
    return *this;
  }

  ///\brief Sets current node equal to node with specified name.
  ///
  ///\param iName -- source name for node to replace.
  Node& Node::operator=(const std::string& iName)
  {
    // copy data from iName without changing top pointer
    this->deleteLeft();
    this->deleteRight();
    this->setName(iName);
    return *this;
  }

  ///\brief Adds specified node structure as left child.
  ///
  /// Normalizes inserted subtree.
  /// Throws node::InsertError exception if try to insert iNode to busy place.
  ///
  ///\param iNode -- source node structure inserted node.
  Node& Node::operator<(const Node& iNode)
  {
    // insert node as left child
    this->addLeft(iNode);
    return *this;
  }

  ///\brief Adds node with specified name as left child.
  ///
  /// Throws node::InsertError exception if try to insert iNode to busy place.
  /// Normalizes inserted node.
  ///
  ///\param iName -- source name for node to insert.
  Node& Node::operator<(const std::string& iName)
  {
    // insert node as left child
    this->addLeft(iName);
    return *this;
  }

  ///\brief Adds specified node structure as right child.
  /// Normalizes inserted subtree.
  /// Throws node::InsertError exception if try to insert iNode to busy place.
  ///
  ///\param iNode -- source node structure inserted node.
  Node& Node::operator>(const Node& iNode)
  {
    // insert node as right child
    this->addRight(iNode);
    return *this;
  }

  ///\brief Adds node with specified name as right child.
  /// Throws node::InsertError exception if try to insert iNode to busy place.
  ///
  ///\param iName -- source name for node to insert.
  Node& Node::operator>(const std::string& iName)
  {
    // insert node as right child
    this->addRight(iName);
    return *this;
  }

  /// Outputs name of current node to output stream.
  std::ostream& operator<<(std::ostream& os, const node::Node& cNode)
    {
      os << cNode.getName();
      return os;
    }
  
  ///\brief Makes node levels growing in order, counted form root.
  /// Root level == 0.
  /// Returns counted depth of tree.
  unsigned int Node::normalizeLevel()
    {
      unsigned int maxLevel = 0;
      this->_normalizeLevel(0, maxLevel);
      return maxLevel + 1;
    }
  
  ///\brief Set pointer to parent of current node to selected node.
  ///
  ///\param cNode -- current Node
  ///\param pNode -- parent Node
  void _connect(Node * cNode, const Node * pNode)
  {
    cNode->top = const_cast <Node *>(pNode);
  }

  void Node::_normalizeLevel(const unsigned int& iLevel, unsigned int& maxLevel)
  {
    this->level = iLevel;

    if (iLevel > maxLevel)
      maxLevel = iLevel;

    if (this->left)
      this->left->_normalizeLevel(iLevel + 1, maxLevel);
    if (this->right)
      this->right->_normalizeLevel(iLevel + 1, maxLevel);
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

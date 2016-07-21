/**
 * bst.h
 *  Implements a(n unbalanced) BST storing Key,Value pairs
 */
#ifndef BST_H
#define BST_H
#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>

/* -----------------------------------------------------
 * Regular Binary Tree Nodes
 ------------------------------------------------------*/

template <class KeyType, class ValueType>
  class Node {
 public:
  Node (const KeyType & k, const ValueType & v, Node<KeyType, ValueType> *p)
    : _item(k, v)
   // the default is to create new nodes as leaves
    { _parent = p; _left = _right = NULL; }
  
  virtual ~Node()
  { }
  
  std::pair<const KeyType, ValueType> const & getItem () const
    { return _item; }
  
  std::pair<const KeyType, ValueType> & getItem ()
    { return _item; }
  
  const KeyType & getKey () const
  { return _item.first; }
  
  const ValueType & getValue () const
  { return _item.second; }
  
  /* the next three functions are virtual because for AVL-Trees,
     we'll want to use AVL nodes, and for those, the
     getParent, getLeft, and getRight functions should return 
     AVL nodes, not just ordinary nodes.
     That's an advantage of using getters/setters rather than a struct. */
  
  virtual Node<KeyType, ValueType> *getParent () const
    { return _parent; }
  
  virtual Node<KeyType, ValueType> *getLeft () const
    { return _left; }
  
  virtual Node<KeyType, ValueType> *getRight () const
    { return _right; }
  
  
  void setParent (Node<KeyType, ValueType> *p)
  { _parent = p; }
  
  void setLeft (Node<KeyType, ValueType> *l)
  { _left = l; }
  
  void setRight (Node<KeyType, ValueType> *r)
  { _right = r; }
  
  void setValue (const ValueType &v)
  { _item.second = v; }
  
 protected:
  std::pair<const KeyType, ValueType> _item;
  Node <KeyType, ValueType> *_left, *_right, *_parent;
};

/* -----------------------------------------------------
 * Regular Binary Search Tree
 ------------------------------------------------------*/

template <class KeyType, class ValueType>
class BinarySearchTree {
 protected:
  // Main data member of the class
  Node<KeyType, ValueType> *root;

 public:
  /**
   * Constructor
   */
  BinarySearchTree () { root = NULL; }

  /**
   * Destructor
   */
  ~BinarySearchTree () { deleteAll (root); }

  /**
   * Prints the entire tree structure in a nice format 
   *  
   * It will denote subtrees in [] brackets.
   *  This could be helpful if you want to debug your functions. 
   */  
  void print () const
  { 
    printRoot (root);
    std::cout << "\n";
  }

  void setRoot(Node<KeyType,ValueType>* ptr)
  {
    root = ptr;
  }

  /**
   * An In-Order iterator
   *  !!! You must implement this !!!
   */
  class iterator {
  public:
    /**
     * Initialize the internal members of the iterator
     */
    iterator(Node<KeyType,ValueType>* ptr) : curr(ptr) {}
    
    std::pair<const KeyType,ValueType>& operator*()
      { return curr->getItem();  }
    
    std::pair<const KeyType,ValueType>* operator->() 
      { return &(curr->getItem()); }
    
    /**
     * Checks if 'this' iterator's internals have the same value
     *  as 'rhs'
     */
    bool operator==(const iterator& rhs) const
    {
      return this->curr == rhs.curr;
    }
    
    /**
     * Checks if 'this' iterator's internals have a different value
     *  as 'rhs'
     */
    bool operator!=(const iterator& rhs) const
    {
      return this->curr != rhs.curr;
    }
    
    /**
     * Advances the iterator's location using an in-order sequencing
     */
    iterator& operator++()
    { 
      curr = successor(curr); // point to next node
      return *this;
    }
    
  protected:
    Node<KeyType, ValueType>* curr;
    //you are welcome to add any necessary variables and helper functions here.

    Node<KeyType, ValueType>* successor(Node<KeyType, ValueType>* & current) const
    { 
      Node<KeyType, ValueType>* temp;
      
      // right child exists 
      // successor leftmost node of the right subtree
      if(current->getRight() != NULL)
      {
        temp = current->getRight(); // getRight()
        
        
        while(temp->getLeft() != NULL) // all the way getLeft()
        {
          temp = temp->getLeft(); 
        }
          
        return temp;
      }

      // no getRight() child
      // if someone's getLeft() child, then go up one
      if(current->getParent()->getLeft() == current)
      {
      temp = current->getParent(); //return your getParent()
      return temp;
      }
            
      // if getParent()s's getRight() child, then go up until the current
      // is someone's getLeft() child, then go up one more
      temp = current->getParent();

      while(temp->getParent() && temp->getParent()->getLeft() != temp)
      {
        temp = temp->getParent(); //go up 
      }
      
      temp = temp->getParent(); //return your parent
      return temp;
    }

  };
  
  /**
   * Returns an iterator to the "smallest" item in the tree
   */
  iterator begin()
  {
    // return a pointer to leftmost node

    Node<KeyType, ValueType>* temp = root;

    while(temp->getLeft() != NULL)
        temp = temp->getLeft();

    return iterator(temp);
  }

  /**
   * Returns an iterator whose value means INVALID
   */
  iterator end()
  {
    return iterator(NULL);
  }
  
 protected:
  /**
   * Helper function to find a node with given key, k and 
   * return a pointer to it or NULL if no item with that key
   * exists
   */
  Node<KeyType, ValueType>* internalFind(const KeyType& k) const 
  {
    Node<KeyType, ValueType> *curr = root;

    while (curr){
      if (curr->getKey() == k) {
        return curr;
      } 
      else if (k < curr->getKey()) {
        curr = curr->getLeft();
      } 
      else {
        curr = curr->getRight();
      }
    }
    
    return NULL;
  }
  
  /**
   * Helper function to print the tree's contents
   */
  void printRoot (Node<KeyType, ValueType> *r) const
  {
    if (r != NULL)
      {
	std::cout << "[";
	printRoot (r->getLeft());
	std::cout << " (" << r->getKey() << ", " << r->getValue() << ") ";
	printRoot (r->getRight());
	std::cout << "]";
      }
  }
  
  /**
   * Helper function to delete all the items
   */
  void deleteAll (Node<KeyType, ValueType> *r)
  {
    if (r != NULL)
    {
	   deleteAll (r->getLeft());
	   deleteAll (r->getRight());
	   delete r;
    }
  }
};

/* Feel free to add member function definitions here if you need */

#endif

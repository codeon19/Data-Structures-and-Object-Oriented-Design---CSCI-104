/**
 * splay.h
 *  Implements a(n unbalanced) splay tree storing Key,Value pairs
 */
#ifndef SPLAY_H
#define SPLAY_H

#include <cstdlib>

#include "bst.h"
#include "Map.h"

using namespace std;

// change the BST to string
// Valuetype = count 
template <class KeyType, class ValueType>
class splay_tree : public BinarySearchTree<KeyType, ValueType>, public Map
{

public:

	splay_tree() : root(NULL), p_size(0) {}
	~splay_tree() {}

	void add(const string& word)
	{	
		Node<KeyType, ValueType> *search = this->internalFind(word); 

		// if word does not exist, then create a new node
		if(!search) {
			
			Node<KeyType, ValueType> *new_node = root;
			Node<KeyType, ValueType> *new_parent = NULL;

			// finding the place to insert the new node

			while(new_node) {

		   		new_parent = new_node;

		   		if(new_node->getKey() < word) 
					new_node = new_node->getRight();
				else 
					new_node = new_node->getLeft();
			}

			new_node = new Node<KeyType, ValueType>(word, 1, new_parent);

			if(!new_parent) // if the tree is empty 
			{
				root = new_node;
			}
			else if(new_node->getKey() > new_parent->getKey()) // otherwise set the new node to the parent's left or right
			{	
				new_parent->setRight(new_node);
			}
			else
			{
				new_parent->setLeft(new_node);
			}

			p_size++;

		   	splay(new_node);
		   
	   }
	   else {

	   	splay(search);

	   	search->setValue(search->getValue() + 1);

	   }
	   
	   this->setRoot(root); // setting the splay_root as the root of the BST
	}

	void reportAll(ostream& output){

		// itereating through the successors to print in order
 		for(BinarySearchTree<string,int>::iterator it = this->begin(); it != this->end(); ++it){
			output << it->first << " ";
			output << it->second;
	 		output << endl;
 		}
	}


private:
	
	int p_size;

	Node<KeyType, ValueType> *root;

	// splay the most recently added node to the top
	void splay(Node<KeyType, ValueType> *new_node)
	{
		while(new_node->getParent()){

			// five different cases for rotation
			if(!new_node->getParent()->getParent()) // if the new_node does not have a grandparent
			{ 
	        	if(new_node->getParent()->getLeft() == new_node)
	        	{
	        		right_rotate(new_node->getParent()); // single right rotation
	        	}
	       		else
	       		{
	       		 	left_rotate(new_node->getParent()); // single left rotation
	       		}
	      	}
	      	else if(new_node->getParent()->getParent()->getRight() == new_node->getParent() && new_node->getParent()->getLeft() == new_node)
	      	{
	      		// right_left rotation
	        	right_rotate(new_node->getParent());
	        	left_rotate(new_node->getParent());
	      	}
	      	else if(new_node->getParent()->getParent()->getRight() == new_node->getParent() && new_node->getParent()->getRight() == new_node)
	      	{
	      		// double left_left rotation
	      		left_rotate(new_node->getParent()->getParent()); 
	        	left_rotate(new_node->getParent());

	      	} 
	      	else if(new_node->getParent()->getParent()->getLeft() == new_node->getParent() && new_node->getParent()->getLeft() == new_node)
	      	{
	      		// double right_right rotation
	        	right_rotate(new_node->getParent()->getParent());
	        	right_rotate(new_node->getParent());
	      	}
	      	else
	      	{
	      		// left_right rotation
	        	left_rotate(new_node->getParent());
	        	right_rotate(new_node->getParent());
	      	}
      	}
    }
  	
  	// mirror of left_left rotation 
  	void right_rotate(Node<KeyType, ValueType> *parent )
  	{	
    	Node<KeyType, ValueType> *child = parent->getLeft();
    	
    	if(child)
    	{
      		parent->setLeft(child->getRight());

      		if(child->getRight())
      		{
      			child->getRight()->setParent(parent);
      		}
      		
      		child->setParent(parent->getParent());
    	}
    	
    	if(!parent->getParent())
    	{
    		root = child;
    	}
    	else if(parent == parent->getParent()->getLeft())
    	{
    		parent->getParent()->setLeft(child);
    	}
    	else
    	{
    		parent->getParent()->setRight(child);
    	}
   		
   		if(child)
		{
   			child->setRight(parent);
		}
    	
    	parent->setParent(child);
  	}

	void left_rotate(Node<KeyType, ValueType> *parent)
    {
    	Node<KeyType, ValueType> *child = parent->getRight();

    	if(child)
    	{
    		parent->setRight(child->getLeft());
    
      		if(child->getLeft())
      		{
      			child->getLeft()->setParent(parent);
      		}

     	 	child->setParent(parent->getParent()); // setting the grandparent to child
    	}
    
    	// resetting the parents
    	if(!parent->getParent()) // if the parent was the root
    	{
    		root = child;
    	}
    	else if( parent == parent->getParent()->getLeft()) // if parent was on the leftside of its parent
    	{
    		parent->getParent()->setLeft(child);
    	}
    	else
    	{
    		parent->getParent()->setRight(child);
    	}
    	
    	if(child)
    	{
    		child->setLeft(parent);
    	}

    	parent->setParent(child);
 	}

};

#endif
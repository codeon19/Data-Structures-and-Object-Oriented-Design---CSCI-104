#include "../lib/llistint.h"

#include <cstdlib>
#include <stdexcept>
#include <iostream>

using namespace std;

LListInt::LListInt()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

LListInt::~LListInt()
{
  clear();
}

bool LListInt::empty() const
{
  return size_ == 0;
}

int LListInt::size() const
{
  return size_;
}

// insert function that takes a location and inserts a value
void LListInt::insert(int loc, const int& val)
{

	// if the location is wrong, then it will return
	if(loc < 0 || loc > size_){
		cout << "Invalid Location" << endl;
		return;
	}

	Item* insert = new Item;
	insert->val = val;

	// check if the list is empty
	if(size_== 0){

		head_ = insert;
		tail_ = insert;

		size_ += 1;
		return;
	}

	Item* location = head_;
	Item* temp;

	// if the location is at the beginning
	if(loc == 0){

		location->prev = insert;
		insert->next = location;

		insert->prev = NULL;

		head_ = insert;

		size_ += 1;
		return; 
	}

	// if the location is at the tail
	if(loc == size_){

		temp = tail_;
		
		temp->next = insert;
		insert->prev = temp;

		insert->next = NULL;

		tail_ = insert;

		size_ += 1;
		return;
	}

	for(int i = 0; i < loc; i++){
		location = location->next;
	}

	// breaking the links
	temp = location->prev;
	
	location->prev = insert;
	temp->next = insert;

	// linking the new 
	insert->prev = temp;
	insert->next = location;

	size_ += 1;
	return;
}

// remove function that removes from the location
void LListInt::remove(int loc)
{

	if(loc < 0 || loc > (size_-1)){
		cout << "Invalid Location" << endl;
		return;
	}

	Item* location = head_;
	Item* rem;
	Item* pre_location;

	// if remove is at the beginning
	if(loc == 0){

		// if the remove is last element
		if(tail_ == head_){

			head_ = NULL;
			tail_ = NULL;

			delete location; 

			size_ -= 1;
			return;
		}

		rem = head_;

		location = rem->next;

		location->prev = NULL;

		head_ = location;

		delete rem;
		size_ -= 1;
		return;
	}

	// if remove is at the end
	if(loc == size_-1){

		rem = tail_;

		location = rem->prev;

		location->next = NULL;

		tail_ = location;

		delete rem;
		size_ -= 1;
		return;
	}

	for(int i = 0; i < loc; i++){
		location = location->next;
	}

	rem = location;

	pre_location = location->prev;

	location = rem->next;

	pre_location->next = location;
	location->prev = pre_location;

	delete rem;
	size_ -= 1;
	return; 
}

void LListInt::set(int loc, const int& val)
{
  Item *temp = getNodeAt(loc);
  temp->val = val;
}

int& LListInt::get(int loc)
{
  if(loc < 0 || loc >= size_){
    throw std::invalid_argument("bad location");
  }
  Item *temp = getNodeAt(loc);
  return temp->val;
}

int const & LListInt::get(int loc) const
{
  if(loc < 0 || loc >= size_){
    throw std::invalid_argument("bad location");
  }
  Item *temp = getNodeAt(loc);
  return temp->val;
}

void LListInt::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}

LListInt::Item* LListInt::getNodeAt(int loc) const
{
	if(loc < 0 || loc > (size_-1)){
		cout << "Invalid Location" << endl; 
		return NULL; 
	}

	Item* location = head_;

	for(int i = 0; i < loc; i++){ // going through the linkedlist
		location = location->next;
	}

	return location; // returning the location

}

/**
* Copy constructor (deep copy)
*/
LListInt::LListInt(const LListInt& other){

	head_ = NULL;
	tail_ = NULL; // constructing the object that is copying
	
	size_ = 0;

	for(int i = 0; i < other.size(); i++){
		this->insert(i, other.get(i));
	}

}

/**
* Assignment Operator (deep copy)
*/
LListInt& LListInt::operator=(const LListInt& other){

	if(this == &other) // returning if they are the same already
	return *this;
	
	this->clear(); // clearing the current object in order to be assigned

	for(int i = 0; i < other.size(); i++){
		this->insert(i, other.get(i));
	}

	return *this;
}

/**
* Concatenation Operator (other should be appended to the end of this)
*/
LListInt LListInt::operator+(const LListInt& other) const{

	LListInt temp = *this; // new temporary LinkedList that will be returned

	for(int i = 0; i < other.size(); i++){
		
		temp.insert(i + this->size(), other.get(i)); // inserting to the end of the object on the left hand side
	}

	return temp;
}

/**
* Access Operator
*/
int const & LListInt::operator[](int position) const{

	return this->get(position); // acessing the elements like an array

}
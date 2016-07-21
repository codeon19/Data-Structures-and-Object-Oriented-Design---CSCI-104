#include "../lib/stackint.h"

#include <cstdlib>
#include <stdexcept>
#include <iostream>

using namespace std;

StackInt::StackInt(){}

StackInt::~StackInt(){}

/**
* Returns true if the stack is empty, false otherwise
*/
bool StackInt::empty() const{
	return list.empty();
}

/**
* Pushes a new value, val, onto the top of the stack
*/
void StackInt::push(const int& val){
	list.insert(list.size(), val); // appending to the back 
}

/**
* Returns the top value on the stack
*/
int const &  StackInt::top() const{
	return list.get(list.size()-1); // getting the most recently inserted element
}

/**
* Removes the top element on the stack
*/
void StackInt::pop(){
	list.remove(list.size()-1); // popping the most recently inserted element
}


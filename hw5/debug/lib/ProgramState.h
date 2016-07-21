// ProgramState.h
//
// CS 104 / Spring 2016
//
// The ProgramState class encapsulates the state of an executing Facile
// program.  The state of a Facile program consists of three parts:
//
//    * The program counter, which specifies the line number of the
//      statement that will execute next.
//    * A map, as explained by the problem writeup.
//    * A stack of integers, which is used to hold return lines for GOSUB
//      statements.
//
// I've provided you a start on this class, but you'll need to add methods
// to it as you go along.  In particular, you'll need methods to access and
// modify the state; these methods will be called primarily by the various
// execute() methods in the Statement subclasses, to allow the execution of
// a statement to change the state of a program.  For example, executing a
// GOTO statement will cause the program counter to be changed.

#ifndef PROGRAM_STATE_INCLUDED
#define PROGRAM_STATE_INCLUDED

#include "stackint.h"
#include "llistint.h"

#include <map>
#include <string>

using namespace std;

class ProgramState
{
public:
	
	ProgramState(int numLines);

	// You'll need to add a variety of methods here.  Rather than trying to
	// think of what you'll need to add ahead of time, add them as you find
	// that you need them.

	int getLine(); // get the current line 
	int getCounter(); // for debugging purposes 
	int getValue(string var); // for the operator purposes
	int getNumLines(); // get the total number of lines
	map<string, int> getItems(); // returning the map functions

	void updateCounter(); // update the counter
	void updateLine(); // updates the line to go to the next line

	void setVariable(string var, int value); // sets a given variable a val

	void printVariable(string var, ostream &outf); // prints a single variable
	void printAll(ostream &outf); // prints all of the given vars in the map in alphabetical order
	void addVariable(string var, int value); // adds a var and a value
	void subVariable(string var, int value); // subtracts a var and a value
	void multVariable(string var, int value); // multiplies a var and a value 
	void divVariable(string var, int value); // divides a var and a value
	void toStatement(int value); // sets line to the line number passed in value
	void goSubStatement(int value); // temporarily jumps to the line number passed
	void returnStatement(); // returns to line after goSub
	void ifStatement(string var, string op, int compare, int GoToLine); // given the conditional, if true, then it sets the current line number to the last value passed in

	void resetState(); // reset the state

private:

	// holds the total number of lines
	int m_numLines;

	// counts the number of lines executed
	int counter;

	// what the current line you are executing
	int line;

	// map to hold the variables
	map<string, int> items;

	// stack to track GOSUB and RETURN
	StackInt stack;
};

#endif




#include "../lib/ProgramState.h"

#include <stdexcept>
#include <iostream>

using namespace std;

	ProgramState::ProgramState(int numLines){

		m_numLines = numLines;
		counter = 1;
		line = 1;
	}

	int ProgramState::getLine(){
		return line;
	}

	int ProgramState::getCounter(){
		return counter;
	}

	int ProgramState::getValue(string var){
		return items[var];
	}

	int ProgramState::getNumLines(){
		return m_numLines;
	}

	void ProgramState::updateCounter(){	
		counter++;
	}

	void ProgramState::updateLine(){
		line++;
	}

	// sets a given variable a val
	void ProgramState::setVariable(string var, int value){
		if (items.find(var) == items.end()){ // if the var does not exists, then it creates one
  			items.insert(make_pair(var, value));
		}else{
			items[var] = value;
		}
	}

	// prints a single variable given the name
	void ProgramState::printVariable(string var, ostream &outf){ 
		if (items.find(var) == items.end()){ // if the var does not exist, it sets the default to 0
  			setVariable(var, 0);
		}

		outf << items[var] << endl; // print
	}

	// prints all of the vars in the map 
	void ProgramState::printAll(ostream &outf){
		if(items.size() > 0){ // only prints if there are items in the map, otherwise nothing happens
			map<string, int>::iterator it;
			for(it = items.begin(); it != items.end(); ++it){
				outf << it->first << " " << it->second << endl;
			}
		}
	}

	// adds a var and a value
	void ProgramState::addVariable(string var, int value){
		if(items.find(var) == items.end()){ // if the var does not exist, then create the var
  			setVariable(var, 0);
		}

		int sum = getValue(var) + value;
		items[var] = sum; // setting the var with the new value
	}

	// subtracts a var and value
	void ProgramState::subVariable(string var, int value){
		if(items.find(var) == items.end()){ // if the var does not exist, then create the var
  			setVariable(var, 0);
		}

		int sum = getValue(var) - value;
		items[var] = sum; // setting the var with the new value
	}

	// multiplie a var and value
	void ProgramState::multVariable(string var, int value){
		if(items.find(var) == items.end()){ // if the var does not exists, then create the var
  			setVariable(var, 0);
		}

		int product = ((getValue(var))*(value)); 
		items[var] = product; // set the var with the new value 
	}


	// divide a var and value
	void ProgramState::divVariable(string var, int value){
		if(items.find(var) == items.end()){ // if the var does not exists, then create the var
  			setVariable(var, 0);
		}

		if(value == 0){ // ends the program if the program attempts to divide by 0
			throw std::invalid_argument("Divide by Zero exception");
		}

		int quotient = ((getValue(var))/(value));
		items[var] = quotient; // sets the var with the new value 
	}

	// sets line to the line number passed in value
	void ProgramState::toStatement(int value){
		line = value;
	}

	// temporarily jumps to a line number
	void ProgramState::goSubStatement(int value){ 
		stack.push(line); // push the current line number onto the stack
		toStatement(value);
	}

	// returns to the line before goSub
	void ProgramState::returnStatement(){
		if(stack.empty()){
			toStatement(m_numLines); // if return is given prematurely, then end the program
		}
		else{
			toStatement(stack.top() + 1); // want to return back to next line of GoSub
			stack.pop();
		}
	}

	// conditional if true, then skip to the line number
	void ProgramState::ifStatement(string var, string op, int compare, int GoToLine){
		if(items.find(var) == items.end()){ // if the var does not exists, then create the var
  			setVariable(var, 0);
		}

		bool then = false;

		int value = getValue(var); // gets the value of the given the var

		// different conditionals
		if(op == "<"){
			if(value < compare)
				then = true;
		}
		else if(op == "<="){
			if(value <= compare)
				then = true;
		}
		else if(op == ">"){
			if(value > compare)
				then = true;
		}
		else if(op == ">="){
			if(value >= compare)
				then = true;
		}
		else if(op == "="){
			if(value == compare)
				then = true;
		}
		else if(op == "<>"){
			if(value != compare)
				then = true;
		}
		else{
			throw std::invalid_argument("Illegal operator"); // if wrong operator, end the program
		}

		if(then)
			toStatement(GoToLine);

	}
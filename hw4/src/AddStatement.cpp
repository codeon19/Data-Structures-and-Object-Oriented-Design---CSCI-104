// AddStatement.cpp:
#include "../lib/AddStatement.h"

using namespace std;

AddStatement::AddStatement(string variableName, int value)
	: m_variableName(variableName), m_value(value), var(false){}

// need multiple constructors to handle var vs int 
AddStatement::AddStatement(string variableName, string AddName)
	: m_variableName(variableName), m_addName(AddName), var(true){}

// The AddStatement version of execute() should
//
//		* Adds *p* to the value of the variable *var*, 
//		  where *p* is an int or variable.

void AddStatement::execute(ProgramState* state, ostream &outf)
{
	if(var){
	m_value = state->getValue(m_addName); // get the val if there is a var
	}
	
	state->addVariable(m_variableName, m_value);
	state->updateCounter();
	state->updateLine();
}
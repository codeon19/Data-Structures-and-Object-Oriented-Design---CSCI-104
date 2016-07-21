// AddStatement.cpp:
#include "../lib/SubStatement.h"

using namespace std;

SubStatement::SubStatement(string variableName, int value)
	: m_variableName(variableName), m_value(value), var(false){}

// need multiple constructors
SubStatement::SubStatement(string variableName, string SubName)
	: m_variableName(variableName), m_subName(SubName), var(true){}

// The SubStatement version of execute() should
//
//*Subtracts *p* from  the value of the variable *var*, where *p* is an int or variable.

void SubStatement::execute(ProgramState* state, ostream &outf)
{
	if(var){
	m_value = state->getValue(m_subName);
	}
	
	state->subVariable(m_variableName, m_value);
	state->updateCounter();
	state->updateLine();
}
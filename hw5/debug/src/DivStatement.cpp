// DivStatement.cpp:
#include "../lib/DivStatement.h"

using namespace std;

DivStatement::DivStatement(string variableName, int value)
	: m_variableName(variableName), m_value(value), var(false){}

// need multiple constructors
DivStatement::DivStatement(string variableName, string DivName)
	: m_variableName(variableName), m_divName(DivName), var(true){}

// The DivStatement version of execute() should
//
// *Divides the value of the variable *var* by the integer or variable *p*

void DivStatement::execute(ProgramState* state, ostream &outf)
{
	if(var){
	m_value = state->getValue(m_divName);
	}
	
	state->divVariable(m_variableName, m_value);
	state->updateCounter();
	state->updateLine();
}
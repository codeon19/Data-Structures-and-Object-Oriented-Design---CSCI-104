// MultStatement.cpp:
#include "../lib/MultStatement.h"

using namespace std;

MultStatement::MultStatement(string variableName, int value)
	: m_variableName(variableName), m_value(value), var(false){}

// need multiple constructors
MultStatement::MultStatement(string variableName, string MultName)
	: m_variableName(variableName), m_multName(MultName), var(true){}

// The MultStatement version of execute() should
//
// *Multiplies the value of the variable *var* by the integer or variable *p*

void MultStatement::execute(ProgramState* state, ostream &outf)
{
	if(var){
	m_value = state->getValue(m_multName);
	}
	
	state->multVariable(m_variableName, m_value);
	state->updateCounter();
	state->updateLine();
}
// LetStatement.cpp:
#include "../lib/LetStatement.h"

using namespace std;

LetStatement::LetStatement(string variableName, int value)
	: m_variableName(variableName), m_value(value){}

// The LetStatement version of execute() should make two changes to the
// state of the program:
//
//    * set the value of the appropriate variable
//    * increment the program counter
void LetStatement::execute(ProgramState* state, ostream &outf)
{

	state->setVariable(m_variableName, m_value); // calling to set the var with a value
	state->updateCounter(); 
	state->updateLine(); // more onto the next line 
}
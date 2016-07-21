// ToStatement.cpp:
#include "../lib/ToStatement.h"

#include <stdexcept>

using namespace std;

ToStatement::ToStatement(int value)
	: m_value(value){}

// The ToStatement version of execute() should
//
// *Jumps execution of the program to the line numbered *linenum*

void ToStatement::execute(ProgramState* state, ostream &outf)
{
	if((m_value >= 1) && (m_value <= (state->getNumLines()))){ // need to see if within bounds
		state->toStatement(m_value);
		state->updateCounter(); // no updateLine() called
	}
	else{
		throw std::out_of_range("Illegal jump instruction");
	}

}
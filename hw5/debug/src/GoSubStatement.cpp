// GoSubStatement.cpp:
#include "../lib/GoSubStatement.h"

#include <stdexcept>

using namespace std;

GoSubStatement::GoSubStatement(int value)
	: m_value(value){}

// The GoSubStatement version of execute() should
//
// *Temporarily jumps to line *linenum*, and jumps back after a RETURN

void GoSubStatement::execute(ProgramState* state, ostream &outf)
{
	if((m_value >= 1) && (m_value <= (state->getNumLines()))){ // checks if it is within the bounds 
		state->goSubStatement(m_value);
		state->updateCounter();
	}
	else{
		throw std::invalid_argument("Illegal jump instruction");
	}

}
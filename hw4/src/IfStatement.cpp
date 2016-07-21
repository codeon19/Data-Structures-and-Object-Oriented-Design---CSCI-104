// GoSubStatement.cpp:
#include "../lib/IfStatement.h"

#include <stdexcept> 

using namespace std;

IfStatement::IfStatement(string var, string op, int compare, int GoToLine)
	: m_var(var), m_op(op), m_compare(compare), m_GoToLine(GoToLine){}

// The IfStatement version of execute() should
//
// *Compares the value of the variable *var* to the integer *int*
// via the operator *op* (<, <=, >, >=, =, <>), and jumps
// execution of the program to line *linenum* if true.

void IfStatement::execute(ProgramState* state, ostream &outf)
{
	if((m_GoToLine >= 1) && (m_GoToLine <= (state->getNumLines()))){ // checks to see if it is within the bounds
		state->ifStatement(m_var, m_op, m_compare, m_GoToLine);
		state->updateCounter();
	}
	else{
		throw std::invalid_argument("Illegal jump instruction");
	}

}
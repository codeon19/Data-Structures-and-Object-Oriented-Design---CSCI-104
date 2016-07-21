// ReturnStatement.cpp:
#include "../lib/ReturnStatement.h"

using namespace std;

ReturnStatement::ReturnStatement(){}

// The returnStatement version of execute() should
//
// *Jumps execution of the program back to the most recently executed GOSUB.

void ReturnStatement::execute(ProgramState* state, ostream &outf)
{
	state->returnStatement();
	state->updateCounter();
}
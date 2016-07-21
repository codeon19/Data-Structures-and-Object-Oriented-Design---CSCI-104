// PrintStatement.cpp:
#include "../lib/PrintAllStatement.h"

using namespace std;

PrintAllStatement::PrintAllStatement(){}

// The PrintAllStatement version of execute() should
//    *Prints the value of all used variables to output, one per line.

void PrintAllStatement::execute(ProgramState* state, ostream &outf)
{
	state->printAll(outf); // prints with just the outf
	state->updateCounter();
	state->updateLine();
}
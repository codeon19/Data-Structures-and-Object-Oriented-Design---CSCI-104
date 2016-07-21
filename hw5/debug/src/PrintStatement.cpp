// PrintStatement.cpp:
#include "../lib/PrintStatement.h"

using namespace std;

PrintStatement::PrintStatement(string variableName)
	: p_variableName(variableName){}

// The PrintStatement version of execute() should
//    *Print the value of variable *var* to output

void PrintStatement::execute(ProgramState* state, ostream &outf)
{
	state->printVariable(p_variableName, outf); // var print and output file 
	state->updateCounter();
	state->updateLine();
}
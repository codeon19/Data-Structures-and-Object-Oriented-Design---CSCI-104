#ifndef PRINT_STATEMENT_INCLUDED
#define PRINT_STATEMENT_INCLUDED

#include "Statement.h"
#include "ProgramState.h"

class PrintStatement: public Statement
{
private:
	std::string p_variableName; // holds the var that you want to print

public:
	PrintStatement(std::string variableName);
	
	virtual void execute(ProgramState * state, std::ostream &outf);
};

#endif
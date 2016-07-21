#ifndef RETURN_STATEMENT_INCLUDED
#define RETURN_STATEMENT_INCLUDED

#include "Statement.h"
#include "ProgramState.h"

class ReturnStatement: public Statement
{
	// no need for private data member
public:
	ReturnStatement();
	
	virtual void execute(ProgramState * state, std::ostream &outf);
};

#endif
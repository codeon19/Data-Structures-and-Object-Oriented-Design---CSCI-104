#ifndef TO_STATEMENT_INCLUDED
#define TO_STATEMENT_INCLUDED

#include "Statement.h"
#include "ProgramState.h"

class ToStatement: public Statement
{
private:
	int m_value; // line number to jump to 

public:
	ToStatement(int value); 
	
	virtual void execute(ProgramState * state, std::ostream &outf);
};

#endif
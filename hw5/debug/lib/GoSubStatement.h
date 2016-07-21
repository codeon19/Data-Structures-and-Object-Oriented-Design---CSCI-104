#ifndef GOSUB_STATEMENT_INCLUDED
#define GOSUB_STATEMENT_INCLUDED

#include "Statement.h"
#include "ProgramState.h"

class GoSubStatement: public Statement
{
private:
	int m_value; // line number to jump to 

public:
	GoSubStatement(int value);
	
	virtual void execute(ProgramState * state, std::ostream &outf);
};

#endif
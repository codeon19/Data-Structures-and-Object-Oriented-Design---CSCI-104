#ifndef IF_STATEMENT_INCLUDED
#define IF_STATEMENT_INCLUDED

#include "Statement.h"
#include "ProgramState.h"

class IfStatement: public Statement
{
private:
	string m_var; 
	string m_op;
	int m_compare;
	int m_GoToLine;
	// does not pass down var

public:
	IfStatement(string var, string op, int compare, int GoToLine);
	
	virtual void execute(ProgramState * state, std::ostream &outf);
};

#endif
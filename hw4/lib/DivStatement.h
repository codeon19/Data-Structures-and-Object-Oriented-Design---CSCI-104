#ifndef DIV_STATEMENT_INCLUDED
#define DIV_STATEMENT_INCLUDED

#include "Statement.h"
#include "ProgramState.h"

class DivStatement: public Statement
{
private:
	std::string m_variableName;
	std::string m_divName;

	int m_value;

	bool var; // to see if its a var or not

public:
	DivStatement(std::string variableName, int value);
	
	DivStatement(std::string variableName, std::string divName);
	
	virtual void execute(ProgramState * state, std::ostream &outf);
};

#endif
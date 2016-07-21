#ifndef MULT_STATEMENT_INCLUDED
#define MULT_STATEMENT_INCLUDED

#include "Statement.h"
#include "ProgramState.h"

class MultStatement: public Statement
{
private:
	std::string m_variableName;
	std::string m_multName;

	int m_value;

	bool var; // to see if its a var or not

public:
	MultStatement(std::string variableName, int value);
	
	MultStatement(std::string variableName, std::string MultName);
	
	virtual void execute(ProgramState * state, std::ostream &outf);
};

#endif
#ifndef ADD_STATEMENT_INCLUDED
#define ADD_STATEMENT_INCLUDED

#include "Statement.h"
#include "ProgramState.h"

class AddStatement: public Statement
{
private:
	std::string m_variableName;
	std::string m_addName;

	int m_value;

	bool var; // check to see if a var was passed 

public:
	AddStatement(std::string variableName, int value);
	
	AddStatement(std::string variableName, std::string addName);
	
	virtual void execute(ProgramState * state, std::ostream &outf);
};

#endif
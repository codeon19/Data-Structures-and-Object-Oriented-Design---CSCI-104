#ifndef SUB_STATEMENT_INCLUDED
#define SUB_STATEMENT_INCLUDED

#include "Statement.h"
#include "ProgramState.h"

class SubStatement: public Statement
{
private:
	std::string m_variableName;
	std::string m_subName;

	int m_value;

	bool var; // to see if its a var or not

public:
	SubStatement(std::string variableName, int value);
	
	SubStatement(std::string variableName, std::string subName);
	
	virtual void execute(ProgramState * state, std::ostream &outf);
};

#endif
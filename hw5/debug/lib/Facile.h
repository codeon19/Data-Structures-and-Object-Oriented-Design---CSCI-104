#ifndef FACILE_H
#define FACILE_H

#include "Statement.h"
#include "ProgramState.h"

#include "LetStatement.h"
#include "PrintStatement.h"
#include "PrintAllStatement.h"
#include "AddStatement.h"
#include "SubStatement.h"
#include "MultStatement.h"
#include "DivStatement.h"
#include "ToStatement.h"
#include "GoSubStatement.h"
#include "ReturnStatement.h"
#include "IfStatement.h"

#include <vector>
#include <string>
#include <sstream> 
#include <fstream>
#include <cstdlib>

#include <typeinfo>

#include <stdexcept>
#include <exception>

#include <iostream>

class Facile{

public:

	Facile(string nameFile);
	~Facile();

	// getting current line of the program state
	int getCurrLine();

	// getting the various pairs to load onto the screen
	vector<pair<string,int> > getPairs();

	// breakpoint funtions 
	void setBreakPoint(int i);
	void removeBreakPoint(int i);
	bool breakPointExists(int i);

	void continues();

	void step();

	void next();


	// get statements for getting the program in text form sand the statement objects
	vector<string> getText();
	vector<Statement*> getStatements();

	void reset();

private:

	// parseProgram() takes a filename as a parameter, opens and reads the
	// contents of the file, and returns an vector of pointers to Statement.
	void parseProgram(istream& inf, vector<Statement *> & program);

	// parseLine() takes a line from the input file and returns a Statement
	// pointer of the appropriate type.  This will be a handy method to call
	// within your parseProgram() method.
	Statement * parseLine(string line);

	// offset by -1 from the current line
	vector<string> text;

	// start from 1
	vector<Statement *> programStatements;

	// aligned with the actual breakpoints
	vector<int> breakpoints;

	// the current program state
	ProgramState* state;

};

#endif
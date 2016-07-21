// Facile.cpp
#include "lib/Statement.h"
#include "lib/ProgramState.h"

#include "lib/LetStatement.h"
#include "lib/PrintStatement.h"
#include "lib/PrintAllStatement.h"
#include "lib/AddStatement.h"
#include "lib/SubStatement.h"
#include "lib/MultStatement.h"
#include "lib/DivStatement.h"
#include "lib/ToStatement.h"
#include "lib/GoSubStatement.h"
#include "lib/ReturnStatement.h"
#include "lib/IfStatement.h"

#include <vector>
#include <string>
#include <sstream> 
#include <fstream>
#include <cstdlib>

#include <iostream>


using namespace std;

// parseProgram() takes a filename as a parameter, opens and reads the
// contents of the file, and returns an vector of pointers to Statement.
void parseProgram(istream& inf, vector<Statement *> & program);

// parseLine() takes a line from the input file and returns a Statement
// pointer of the appropriate type.  This will be a handy method to call
// within your parseProgram() method.
Statement * parseLine(string line);

// interpretProgram() reads a program from the given input stream
// and interprets it, writing any output to the given output stream.
// Note:  you are required to implement this function!
void interpretProgram(istream& inf, ostream& outf);


int main() {

    cout << "Enter Facile program file name: ";
    string filename;
    getline(cin, filename);
    ifstream infile(filename.c_str());
    
    if(!infile)
    {
            cout << "Cannot open " << filename << "!" << endl;
            return 1;
    }
    interpretProgram(infile, cout);
}

void parseProgram(istream &inf, vector<Statement *> & program) {

	program.push_back(NULL);
	
	string line;
	while( ! inf.eof() )
	{
		getline(inf, line);
		program.push_back( parseLine( line ) );
	}
}

Statement * parseLine(string line){

	Statement * statement;	
	stringstream ss;
	string type;
	
	string var;
	string var2;

	string op;

	char c;

	int val;
	int GoToLine;

	ss << line;
	ss >> type;
	
	if(type == "LET"){
		ss >> var;
		ss >> val;
		// Note:  Because the project spec states that we can assume the file
		//	  contains a syntactically legal Facile program, we know that
		//	  any line that begins with "LET" will be followed by a space
		//	  and then a variable and then an integer value.
		statement = new LetStatement(var, val);
	}
	else if(type == "PRINT"){
		ss >> var;
		statement = new PrintStatement(var);
	}
	else if(type == "PRINTALL"){
		ss >> var;
		statement = new PrintAllStatement();
	}
	else if(type == "ADD"){
		ss >> var;
		ss >> c;
		if(c >= '0' && c <= '9'){
			ss.unget(); // puts back the most recent stringstream 
			ss >> val;
			statement = new AddStatement(var, val);
		}
		else{
			ss.unget();
			ss >> var2;
			statement = new AddStatement(var, var2);
		}
	}
	else if(type == "SUB"){
		ss >> var;
		ss >> c;
		if(c >= '0' && c <= '9'){
			ss.unget();
			ss >> val;
			statement = new SubStatement(var, val);
		}
		else{
			ss.unget();
			ss >> var2;
			statement = new SubStatement(var, var2);
		}
	}
	else if(type == "MULT"){
		ss >> var;
		ss >> c;
		if(c >= '0' && c <= '9'){
			ss.unget();
			ss >> val;
			statement = new MultStatement(var, val);
		}
		else{
			ss.unget();
			ss >> var2;
			statement = new MultStatement(var, var2);
		}
	}
	else if(type == "DIV"){
		ss >> var;
		ss >> c;
		if(c >= '0' && c <= '9'){
			ss.unget();
			ss >> val;
			statement = new DivStatement(var, val);
		}
		else{
			ss.unget();
			ss >> var2;
			statement = new DivStatement(var, var2);
		}
	}
	else if(type == "GOTO"){
		ss >> val;
		statement = new ToStatement(val); 
	}
	else if(type == "GOSUB"){
		ss >> val;
		statement = new GoSubStatement(val);
	}
	else if(type == "RETURN"){
		statement = new ReturnStatement();
	}
	else if( type == "IF"){
		ss >> var; // grabbing the various parts of an IfStatement
		ss >> op; 
		ss >> val;
		ss >> var2; 
		ss >> GoToLine;
		statement = new IfStatement(var, op, val, GoToLine);
	}
	else if(type == "END" || type == "."){
		statement = NULL;
		
	}
	else{ // if an invalid statement is given, just treat as an END
		statement = NULL; 
	}
	
	return statement;
}


void interpretProgram(istream& inf, ostream& outf){

	vector<Statement *> program;
	parseProgram(inf, program);

	int numLines = program.size() - 1; // Statements start at 1 

	ProgramState* state = new ProgramState(numLines);

	if(numLines <= 1000){// limits program to 1000 lines

		// also need to start at line 1
		while(program[state->getLine()] != NULL){ // if the statement is NULL, then exit the program 
			program[state->getLine()]->execute(state, outf);
		}

		/*
		For debugging purposes
		outf << "Number of lines executed: " << state->getCounter() << endl;
		*/
	}
	else{

		outf << "Program exceeds 1000 lines, did not execute" << endl;
	}
	
	// delete through the virtual destructor
	for(int i = 0; i < numLines; i++){
		delete program[i];
	}

	delete state;
}


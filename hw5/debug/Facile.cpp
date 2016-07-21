#include "lib/Facile.h"

using namespace std;

Facile::Facile(string nameFile){

		// Facile turned into an object

        ifstream infile(nameFile.c_str());
        
        parseProgram(infile, programStatements);

        state = new ProgramState(programStatements.size() - 1);

        infile.close();

}
Facile::~Facile(){

	// cleanup of memory
	for(int i = 0; i < programStatements.size(); i++){
		delete programStatements[i];
	}

	delete state;}

void Facile::parseProgram(istream &inf, vector<Statement *> & program){

	program.push_back(NULL); // start at 1
	
	string line;
	while( ! inf.eof() )
	{
		getline(inf, line);
		text.push_back(line);
		program.push_back(parseLine(line));
	}
}

Statement* Facile::parseLine(string line){

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

int Facile::getCurrLine(){
	return state->getLine();
}

vector<string> Facile::getText(){
	return text;
}

vector<pair<string,int> > Facile::getPairs(){

	vector<pair<string, int> > pairList;

	map<string, int> items = (state->getItems());

	for (map<string,int>::iterator it = items.begin(); it != items.end(); ++it){
        pair<string, int> pairs = make_pair(it->first, it->second);
        pairList.push_back(pairs);
    }

    return pairList;
}

// return of the vector statements
vector<Statement*> Facile::getStatements(){
	return programStatements;
}

// setting a breakpoint at the given index
void Facile::setBreakPoint(int i){

	int newBreakPoint = i;

	breakpoints.push_back(newBreakPoint);
}

void Facile::removeBreakPoint(int i){
	int rmBreakPoint = i;

	for(int j = 0; j < breakpoints.size(); j++){
		if(rmBreakPoint == breakpoints[j]){
			breakpoints.erase(breakpoints.begin() + j); // removing the given breakpoint
		}
	}
}

// checking if the given breakpoint exists
bool Facile::breakPointExists(int i){
	int newBreakPoint = i;
	bool exists = false;

	for(int j = 0; j < breakpoints.size(); j++){
		if(newBreakPoint == breakpoints[j])
			exists = true;
	}

	return exists;
}

// stepping through the program until a breakpoint is reached
void Facile::continues(){
	
	bool hitBreakPoint = false;

	while(!hitBreakPoint && programStatements[state->getLine()] != NULL){ // until a breakpoint 

		step();

		for(int i = 0; i < breakpoints.size(); i++){
			if(state->getLine() == breakpoints[i])
			hitBreakPoint = true; 
		}
	}
}

void Facile::step(){

	if(programStatements[state->getLine()] != NULL){
		programStatements[state->getLine()]->execute(state, cout); // executing the current line
	}
}

// similar to step(), but sees that a GOSUB will completely execute
void Facile::next(){

	string type;

	bool hitBreakPoint = false;

	stringstream s1;

	s1 << text[state->getLine() - 1]; // because it is offset
	s1 >> type;

	if(type == "GOSUB"){

		cout << "Hi" << endl;

		while(programStatements[state->getLine()] != NULL && (type != "RETURN")){ // checking for the RETURN 

			for(int i = 0; i < breakpoints.size(); i++){
				if(state->getLine() == breakpoints[i])
				hitBreakPoint = true;
			}

			if(hitBreakPoint)
			break;

			step();

			stringstream s2;

			s2 << text[state->getLine() - 1];
			s2 >> type;
		}
	}
	else
	step();

	if(type == "RETURN"){
		step();
	}
}

// reset the state and the breakpoints
void Facile::reset(){
	breakpoints.clear();
	state->resetState();
}
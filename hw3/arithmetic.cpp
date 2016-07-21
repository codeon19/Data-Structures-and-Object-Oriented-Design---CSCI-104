
#include "stackint.h"

#include <iostream>
#include <fstream>
#include <cstdlib> // holds atoi()

#include <string>

#include <sstream> 

using namespace std;

int main(int argc, char *argv[]){

	if(argc < 2){ // check to see how many arguments passed
		cerr << "No file inputed" << endl;
		return(1);
	}

	ifstream in(argv[1]);

	if(!in){ // Check to see if file was opened 
		cerr << "Error reading file..." << endl;
		return(1);
	}

	const int OPEN_PAREN = -1;
	// const int CLOSED_PAREN = -2;
	
	const int PLUS = -3;
	const int MULT = -4;

	const int LEFT = -5;
	const int RIGHT = -6;

	string line;

	while(getline(in, line)){

	bool malformed = false; // checking to see for general errors
	bool mix = false; // checking to see if operators are mixed within parenthesis
	bool extra = false; // checking to see if there are extra operators 
	bool miss = false; // check to see if there is a missing operator

	StackInt list;

	stringstream ss(line);

	int size = line.size();

	for(int i = 0; i < size; i++){ // iterating through each line
		char c; // a placeholder for the ss

		// all these conditionals push to the stack until it reaches the end
		// or a }, then it does the operations within the parenthesis
		if(line[i] == '('){
			ss >> c;
			list.push(OPEN_PAREN);
		}
		else if(line[i] == ')'){ // goes through the stack to execute operators
			ss >> c;

			bool match = false;

			bool add = false;
			bool multiply = false;

			int rightValue = -1; // edge case of operators to the right of the parenthesis

			while(!match){ // loop through until a matching ( is found

				// if the list is empty before a matching ( is found, then there are
				// extra operators

				if(list.empty() == true){
					match = true;
					extra = true;
					continue;
				}
				
				int nextElement = list.top();

				if(nextElement >= 0){ // check to see if there are missing operators, if not, then put it back in the stack 
					list.pop();
					int number = list.top();

					if(number >= 0)
					miss = true;

					list.push(nextElement);
				}

				if(nextElement == OPEN_PAREN){ // ends the while loop
					list.pop();
					match = true;
				}
				else if(nextElement == PLUS){
					list.pop();
					nextElement = list.top();

					if(rightValue == -1){ // first checks for misplaced operators
						cerr << "misplaced operators" << endl;
						malformed = true;
					}

					if(nextElement >= 0){
						list.pop(); // moving through the stack
						
						int checkSHIFT = list.top();
						
						bool moreSHIFT = true;
						while(moreSHIFT){ // check to see if there are shift lefts and rights
							checkSHIFT = list.top();
							if(checkSHIFT == LEFT){
								list.pop();
								nextElement *= 2;
							}
							else if(checkSHIFT == RIGHT){
								list.pop();
								nextElement /= 2;
							}
							else{
								moreSHIFT = false;
							}
						}

						nextElement = nextElement + rightValue;
						list.push(nextElement); // pushing the value of the sum onto the stack
						add = true;
					}
					else{
						cerr << "extra operators" << endl; // if there are two operators in a row
						malformed = true;
					}
				}
				else if(nextElement == MULT){ // same as addition, but with multiplication
					list.pop();
					nextElement = list.top();

					if(rightValue == -1){
						cerr << "misplaced operators" << endl;
						malformed = true; 
					}

					if(nextElement >= 0){

						list.pop();
						int checkSHIFT = list.top();
						
						bool moreSHIFT = true;
						while(moreSHIFT){
							checkSHIFT = list.top();
							if(checkSHIFT == LEFT){
								list.pop();
								nextElement *= 2;
							}
							else if(checkSHIFT == RIGHT){
								list.pop();
								nextElement /= 2;
							}
							else{
								moreSHIFT = false;

							}
						}

						nextElement = nextElement * rightValue;
						list.push(nextElement);
						multiply = true;

					}
					else{
						cerr << "extra operators" << endl;
						malformed = true;
					}
				}
				else if(nextElement == LEFT){ // shift left operator
					list.pop();
					rightValue *= 2;
					list.push(rightValue);
				}
				else if(nextElement == RIGHT){ // shift right operator
					list.pop();
					rightValue /= 2;
					list.push(rightValue);
				}
				else { // if the next element is a value

					rightValue = nextElement;
					list.pop();
				}


			}

			list.push(rightValue);

			// checking to see if within the parenthesis there were a mix of operators
			if(add && multiply)
				mix = true;
		}
		else if(line[i] == '+'){ // pushing to the stack
			ss >> c;
			list.push(PLUS);
		}
		else if(line[i] == '*'){ // pushing to the stack
			ss >> c;
			list.push(MULT);
		}
		else if(line[i] == '<'){ // pushing to the stack
			ss >> c;
			list.push(LEFT);
		}
		else if(line[i] == '>'){ // pushing to the stack
			ss >> c;
			list.push(RIGHT);
		}
		else if(line[i] == ' '){ // making sure the white spaces are not mistaken for integers
			// do nothing here
		}
		else{ // getting the int through ss

			int count = 0;

			while(line[i + 1 + count] != '(' && line[i + 1 + count] != ')' && 
			line[i + 1 + count] != '+' && line[i + 1 + count] != '*' && 
			line[i + 1+  count] != '<' && line[i + 1+ count] != '>'){
				count++;
			} // need to count how many spaces the int took up
			
			int number;
			ss >> number;
			list.push(number);

			i += count; // skipping the index of the int

		}

	}

	if(malformed){ // if any erros, do not print
		continue;
	}

	if(miss){ // if there are missing operators, then error
		cerr << "missing operators" << endl;
		continue;
	}

	if(mix){ // output if there are errors concering mixed operators
		cerr << "mixing operators" << endl;
		continue;
	}

	if(extra){ // output if there are extra parenthesis
		cerr << "extra parenthesis at the end" << endl;
		continue;
	}

	int calculated = list.top();
	list.pop();

	if(calculated < 0){
		cerr << "extra operator at the end" << endl;
		malformed = true;
	}


	if(!list.empty()){ // edge case if there are operators before the last matching parenthesis

		while(!list.empty()){ // looping through if there are multiple

			int leftovers = list.top();
			if(leftovers == LEFT){
				list.pop();
				calculated *= 2;
			}
			
			if(leftovers == RIGHT){
				list.pop();
				calculated /= 2;
			}

			if(leftovers == PLUS){
				list.pop();
				cerr << "extra + at the beginning" << endl;
				malformed = true;
			}

			if(leftovers == MULT){
				list.pop();
				cerr << "extra * at the beginning" << endl;
				malformed = true;
			}

			if(leftovers == OPEN_PAREN){
				list.pop();
				cerr << "missing parenthesis" << endl;
				malformed = true;
			}

			// if the leftover is an integer, then it is invalid due to extra parenthesis
			if(leftovers >= 0){
				list.pop();
			} 
		}
	}
	
	if(!malformed) // if no erros, then output the value
	cout << calculated << endl;
	
	}
	// end of while loop
	
	return 0;
}
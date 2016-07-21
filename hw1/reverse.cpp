#include <iostream>
#include <fstream>
#include <cstdlib>

#include <iostream>
#include <sstream>
#include <cstring> 

using namespace std;

int main(int argc, char* argv[]){

	if(argc < 2){ // check to see how many arguments passed

		cerr << "No file inputted" << endl;
  		return(1);

  	}
	
	ifstream inFile(argv[1]);

	if(!inFile){ // see if ok to open up a file

		cerr << "Error reading file..." << endl; 
		return(1);

	}

	int num;
	  
	if(inFile >> num){

		string* words = new string[num];

		for(int i = 0; i < num; i++){

			inFile >> words[i]; // adding input into dynamic array

		}

		for(int i = 0; i < num; i++){

			cout << words[(num -1) - i] << endl; // outputting input in reverse
		} 

		delete [] words; // deleting dynamic memory

	}
	else{

		inFile.close();
		cerr << "Inavlid File" << endl;
		return(1);

	}

	return 0;

}
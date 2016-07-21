#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main(int argc, char* argv[])
{
  
  if(argc < 3){
    cerr << "Please provide an input and output file." << endl;
    return 1;
  }
  
  ifstream input(argv[1]);
  ofstream output(argv[2]);

  if(!input){

  	cerr << "Error reading file..." << endl;
	return(1);

  }

  int floors;
  int *floorsizes;
  int **possessions;

  string ***trojans;
  string curr;

  input >> floors;

  trojans = new string**[floors];

  //you will need to keep track of how many people are on each floor.
  
  floorsizes = new int[floors];
  
  //keep track how many posessions people have
  
  possessions = new int*[floors];

  for (int i = 0; i < floors; i++) {
	  
	  floorsizes[i] = 0;
	  trojans[i] = NULL;
	  possessions[i] = 0;

  }

  while(getline(input, curr)){
	  
	  stringstream ss;
	  ss << curr;
	  ss >> curr;

	  if (curr == "MOVEIN") {
		  
		  int i,k;
		  ss >> i;
		  ss >> k;
		  
		  if(ss.fail()) {

			  output << "Error - incorrect command" << endl;
		  }
		  else {

		  	if(i < floors && i >= 0){ // check to see if it was on the floor

		  		if(floorsizes[i] == 0){

		  			trojans[i] = new string*[k];

		  			floorsizes[i] = k; // add number of people onto a certain floor

		  		}
		  		else{

		  			output << "Error - floor " << i << " is not empty" << endl;
		  		}

		  	}
		  	else{

		  		output << "Error - floor " << i << " does not exist" << endl;

		  	}

		  }
	  }
	  else if (curr == "MOVEOUT") {
			
			int i;
		  	ss >> i;

		  	if(ss.fail()){

			  	output << "Error - incorrect command" << endl;

		  	}
		  	else {

		  		if(i < floors && i >= 0){

		  			if(floorsizes[i] != 0){ // check to see if the floor is empty

		  				int size = floorsizes[i];

		  				for(int n = 0; n < size; n++){

		  					delete[] trojans[i][n]; // deallocate

		  				}

		  				floorsizes[i] = 0;

		  			}
		  			else{

		  				output << "Error - floor " << i << " is already empty" << endl;

		  			}

		  		}
		  		else{

		  		output << "Error - floor " << i << " does not exist" << endl;

		  		}

		  	}
	  }
	  else if (curr == "OBTAIN") {

	  	int i,j,k;

		ss >> i; // floor #
		ss >> j; // student #
		ss >> k; // number of possesions


		if(j < floorsizes[i] && j >= 0){

			if(possessions[i] == 0){ 

				possessions[i] = new int[floorsizes[i]]; // create posessions if none yet

				for(int n = 0; n < floorsizes[i]; n++){

					possessions[i][n] = 0;

				}

			}

			if(possessions[i][j] == 0){

				trojans[i][j] = new string[k];

				for(int n = 0; n < k; n++){

					string poss;

					ss >> poss;

					trojans[i][j][n] += poss;

				}

				possessions[i][j] = k;

			}
			else{

				output << "Error - student " << j << " already has possesions" << endl;

			}
		}
		else{

			output << "Error - student " << j << " does not exist" << endl;

		}


	  }
	  else if (curr == "OUTPUT") {

	  	int i,j; 

		ss >> i; // floor #
		ss >> j; // student #

		if(j < floorsizes[i] && j >= 0){

			if(possessions[i][j] != 0 ){

				for(int n = 0; n < possessions[i][j]; n++){ // iterate through trojans

					output << trojans[i][j][n] << endl; 
				}

			}
			else{

				output << "Error - student " << j << " has no possesions" << endl;
			}


		}
		else {

			output << "Error - student " << j << " does not exist" << endl;

		}

	  }
	  else {

	 	output << "Error - incorrect command" << endl;

	  }

  }

  // deallocation of all the memory

  for(int i = 0; i < floors; i++){
    
    for(int j =0; j < floorsizes[i]; j++){

    	delete[] trojans[i][j];
    }

    delete[] trojans[i];
  }
	
  delete[] trojans;

  for(int i = 0; i < floors; i++){

  	delete[] possessions[i];

  }

  delete[] possessions;

  delete[] floorsizes;

  return 0;
}
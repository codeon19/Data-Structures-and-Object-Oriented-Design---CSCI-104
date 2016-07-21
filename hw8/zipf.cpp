#include <iostream>
#include <fstream>
#include <cstdlib> // holds atoi()
#include <ctime>
#include <cstring>
#include <string>

#include <algorithm>

#include "splay.h"
#include "hashtable.h"

using namespace std;

int main(int argc, char *argv[]) {
  
  if(argc < 3) // check to see how many arguments passed
  { 
  
  cerr << "No file inputted" << endl;
  return(0);
  
  }

  int option = atoi(argv[1]);
  
  ifstream inFile(argv[2]); // Open the user inputted file

  if(!inFile) // Check to see if file was opened 
  { 
  
  cerr << "Error reading file..." << endl;
  return(1); 
   
  }

  string word;

  clock_t start;
  double duration;

  start = clock();

  if(option == 4)
  {
    splay_tree<string, int> mytree;

    inFile >> word;

    while(inFile)
    {

      transform(word.begin(), word.end(), word.begin(),(int (*)(int))tolower);

      if(word.size() <= 28)
      {
        mytree.add(word);
      }

      inFile >> word;
    }

    mytree.reportAll(cout);
  }
  else if (option == 5)
  {
    hashtable mytable;

    inFile >> word;

    while(inFile)
    {

      transform(word.begin(), word.end(), word.begin(),(int (*)(int))tolower);

      if(word.size() <= 28)
      {
        mytable.add(word);
      }

      inFile >> word;
    }

    mytable.reportAll(cout); 
  }
  else
  {
    cerr << "Wrong Option inputted" << endl;
    return(1); 
  }

  duration = (clock() - start)/(double) CLOCKS_PER_SEC;

  cout << duration << endl;

  return 0;

}
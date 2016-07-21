#include <iostream>
#include <fstream>
#include <cstdlib> // holds atoi()
#include <cstring>
#include <sstream>
#include <map>

#include <vector>

#include "avlbst.h"

using namespace std;

bool check_conflict(int class1, int class2, vector<pair<int, int> > conflicts)
{
	bool conflicted = false;

	for(int i = 0; i < conflicts.size(); i++)
	{
		if((conflicts[i].first == class1 && conflicts[i].second == class2)
			|| (conflicts[i].second == class1 && conflicts[i].first == class2))
		{
			conflicted = true;
		}
	}

	return conflicted;
}

bool noConflicts (int class_num, int exam_time, vector<int> exams, vector<pair<int, int> > conflicts, map<int, int> &timesOfClass) 
{ 
  for (int i = 0; i < exams.size(); i++) 
  { 
  	// if i is already schedule at this time
  	// and c conflicts with class
  	// then we can't schedule class at this time

   	if(timesOfClass[exams[i]] == exam_time && check_conflict(exams[i], class_num, conflicts)) 
       return false;             							
  }

  return true; 
}

bool schedule(int class_num, int num_timeslots, vector<int> exams, vector<pair<int, int> > conflicts, map<int, int> &timesOfClass) 
{

  if (class_num == exams[exams.size()]) // base case
    return true; 
  else
  {
  	for (int t = 1; t <= num_timeslots; ++t) 
    { 
       if (noConflicts(class_num, t, exams, conflicts, timesOfClass)) 
       {

       	timesOfClass[class_num] = t; // assign to the scheduled times 

       	int index;
       	for(int i = 0; i < exams.size(); i++)
       	{
       		if(exams[i] == class_num)
       			index = i;
       	}

        if(schedule(exams[index +1], num_timeslots, exams, conflicts, timesOfClass)) return true;
       } 
    }

  return false;
  }   			

} 

int main(int argc, char *argv[])
{
  
  if(argc < 2){ 
  
  cerr << "No file inputted" << endl;
  return(0);
  
  }
  
  ifstream inFile(argv[1]); 

  if(!inFile)
  { 
  	cerr << "Error reading file..." << endl;
  	return(1); 
  } 

  int num_exams;
  int num_students;
  int num_timeslots;

  map<int, int> timesOfClass;

  vector<pair<int, int> > conflicts;
  vector<int> exams; 

  inFile >> num_exams;
  inFile >> num_students;
  inFile >> num_timeslots;

  // this whole while statement reads in everything
  string line;
  while(!inFile.eof())
  {
	getline(inFile, line);
	
	vector<int> exam_conflicts;
	stringstream ss;
	string dummy;
	int var;

	ss << line;

	ss >> dummy;

	bool read = ss >> var;

	// getting the times from each student
	while(read)
	{
		exam_conflicts.push_back(var);

		bool norepeats = true;
		for(int i = 0; i < exams.size(); i++)
		{
			// getting the exam times individually
			if(var == exams[i])
				norepeats = false;
		}

		if(norepeats)
		{
			exams.push_back(var);

			// timeOfClass.push_back(make_pair(var, -1));
			timesOfClass.insert(make_pair(var, -1));
		}

		read = ss >> var;
	}

	if(exam_conflicts.size() > 1) // puts all the conflicts in a vector
	{
		for(int i = 0; i < exam_conflicts.size()-1; i++)
		{
			for(int j = i + 1; j < exam_conflicts.size(); j++)
			{
				conflicts.push_back(make_pair(exam_conflicts[i], exam_conflicts[j]));
			}
		}
	}

  }


  if(schedule(exams[0], num_timeslots, exams, conflicts, timesOfClass))
  {
  	for(map<int,int>::iterator it = timesOfClass.begin(); it != timesOfClass.end(); ++it)
  	{
  		cout << it->first << " " << it->second << endl;
  	}
  }
  else
  {
  	cout << "No valid solution" << endl;
  }

  return 0;
 }
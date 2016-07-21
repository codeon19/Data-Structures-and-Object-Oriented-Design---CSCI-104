#ifndef M_SORT_H
#define M_SORT_H

#include <vector>
#include <string>
#include <cstdlib>

using namespace std; 

template <class T, class Comparator>
void mergeStart(vector<T>& myArray, Comparator comp){

	vector<T> tmp(myArray.size());
  	
  	mergeSort(myArray,tmp,0,myArray.size()-1, comp);
}

template <class T, class Comparator>
void mergeSort(vector<T>& myArray, vector<T>& tmp, int start, int end, Comparator comp){
	
	if (start < end){

		int mid=(start+end)/2;
    	mergeSort(myArray,tmp,start,mid,comp);
    	mergeSort(myArray,tmp,mid+1,end,comp);
    	merge(myArray,tmp,start,mid+1,end,comp);

  	}
}
  
template <class T, class Comparator>
void merge(vector<T>& myArray, vector<T>& tmp, int start, int start2, int end, Comparator comp){

	int aptr = start;
	int bptr = start2;
  	int i = start;
  	

  	// comp compares lhs < rhs

  	while((aptr < start2) && (bptr < end + 1)){

    	if(comp(myArray[aptr],myArray[bptr]))
      	tmp[i++] = myArray[aptr++];
    	else
      	tmp[i++] = myArray[bptr++];
  	}
  	
  	while(aptr <start2){
    	tmp[i++] = myArray[aptr++];
  	}

  	while(bptr < end +1){
    	tmp[i++] = myArray[bptr++];
  	}

  	for(i = start; i <= end; i++){
     myArray[i] = tmp[i];
  	}
  
  }

#endif
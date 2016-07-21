#include <iostream>
#include <cstdlib>

#include "heap.h"

using namespace std;

int main() {
	
	MinHeap<string> heap(3);

	heap.add("B", 1);

	if(heap.isEmpty()){
		cout << "NOT CORRECT" << endl; 
	}
	else {
		cout << "CORRECT" << endl;
	}

	heap.remove();

	if(heap.isEmpty()){
		cout << "CORRECT" << endl; 
	}
	else {
		cout << "NOT CORRECT" << endl;
	}

	heap.add("C", 2);
	heap.add("D", 3);
	heap.add("E", 4);
	heap.add("F", 5);

	heap.add("A", 0);

	heap.add("YAS", -8);

	heap.remove();

	cout << heap.peek() << endl;

	return 0;
}
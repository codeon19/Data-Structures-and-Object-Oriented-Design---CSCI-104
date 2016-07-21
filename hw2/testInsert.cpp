/* 

Renamed file of testADDToEmptyList.cpp that
tests various cases of insertion. 

*/
#include "llistint.h"
#include <iostream>

using namespace std;

int main() {
  LListInt * list = new LListInt();

  // Check if the list is initially empty.
  if (list->empty()) {
    cout << "SUCCESS: List is empty initially." << endl;
  } else {
    cout << "FAIL: List is not empty initially when it should be." << endl;
  }

  // Test -> Insert an item at the head
  list->insert(0, 3);

  // Check if the list is still empty
  if (!list->empty()) {
    cout << "SUCCESS: List is not empty after one insertion." << endl;
  } else {
    cout << "FAIL: List is empty after one insertion." << endl;
  }

  // Check if the size
  if (list->size() == 1) {
    cout << "SUCCESS: List has size 1 after one insertion." << endl;
  } else {
    cout << "FAIL: List has size " << list->size() << " after one insertion.";
    cout << endl;
  }

  // Check if the value is correct.
  if (list->get(0) == 3) {
    cout << "SUCCESS: 3 is at the 0th index of the list." << endl;
  } else {
    cout << "FAIL: 3 is not at the 0th index of the list, " << list->get(0);
    cout << " is instead." << endl;
  }

  // Test -> Insert an item at the beginning
  list->insert(0, 2);

  if (list->get(0) == 2) {
    cout << "SUCCESS: 2 is at the 0th index of the list." << endl;
  } else {
    cout << "FAIL: 2 is not at the 0th index of the list, " << list->get(0);
    cout << " is instead." << endl;
  }

  // Test -> Insert an item at the end
  list->insert(2, 5);

  if (list->get(2) == 5) {
    cout << "SUCCESS: 5 is at the 2th index of the list." << endl;
  } else {
    cout << "FAIL: 5 is not at the 2th index of the list, " << list->get(0);
    cout << " is instead." << endl;
  }

  // Test -> Insert item in the middle 
  list->insert(2, 4);

  if (list->get(2) == 4) {
    cout << "SUCCESS: 4 is at the 2th index of the list." << endl;
  } else {
    cout << "FAIL: 4 is not at the 2th index of the list, " << list->get(0);
    cout << " is instead." << endl;
  }

  // Test -> inserting at a wrong location
  list->insert(5, 0);

  // Clean up memory.
  delete list;
}
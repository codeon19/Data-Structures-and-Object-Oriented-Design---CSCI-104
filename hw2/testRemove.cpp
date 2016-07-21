/*

Tests various cases of remove.

*/
#include "llistint.h"
#include <iostream>

using namespace std;

int main() {
  LListInt * list = new LListInt();

  // Test -> removal of an empty list, should output Invalid Location 
  list->remove(0);

  // filling list with values
  list->insert(0, 4); // 3
  list->insert(0, 3); // 2 
  list->insert(0, 2); // 1 
  list->insert(0, 1); // 0 

  cout << "Size: " << list->size() << endl;
  
  // Test -> removal of one element in the middle
  list->remove(1);
  if (list->size() == 3) {
    cout << "SUCCESS: List has size 3 after one removal" << endl;
  } else {
    cout << "FAIL: List has size " << list->size() << " after one removal";
    cout << endl;
  }
  cout << "Size: " << list->size() << endl;

  // Test -> removal from the beginning
  list->remove(0);
  if (list->get(0) == 3) {
    cout << "SUCCESS: 3 is at the 0th index of the list." << endl;
  } else {
    cout << "FAIL: 3 is not at the 0th index of the list, " << list->get(0);
    cout << " is instead." << endl;
  }
  cout << "Size: " << list->size() << endl;

  // Test -> removal from a wrong location, should output Invalid Location
  list->remove(2);

  // Test -> removal from the end
  list->remove(1);
  if (list->get(0) == 3) {
    cout << "SUCCESS: 3 is at the 0th index of the list." << endl;
  } else {
    cout << "FAIL: 3 is not at the 0th index of the list, " << list->get(0);
    cout << " is instead." << endl;
  }
  cout << "Size: " << list->size() << endl; 
  
  // Test -> removing the last element
  list->remove(0);
  if (list->size() == 0) {
    cout << "SUCCESS: List has size 0 after last removal" << endl;
  } else {
    cout << "FAIL: List has size " << list->size() << " after last removal" << endl; 
    cout << endl;
  }

  // Clean up memory.
  delete list;
}
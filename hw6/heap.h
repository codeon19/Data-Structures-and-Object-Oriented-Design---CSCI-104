#include <vector>
#include <iostream>

using namespace std;

template <typename T>
class MinHeap {

  public:

    MinHeap (int d);
    /* Constructor that builds a d-ary Min Heap
    This should work for any d >= 2,
    but doesn't have to do anything for smaller d.*/

    ~MinHeap ();

    void add (T item, int priority);
    /* adds the item to the heap, with the given priority. */

    const T & peek () const;
    /* returns the element with smallest priority. */

    void remove ();
    /* removes the element with smallest priority. */

    bool isEmpty ();
    /* returns true iff there are no elements on the heap. */


    /* EXTRA HELPER FUNCTIONS  */

    void bubbleUp(int i);

    int parent(int i);

    int kthChild(int i, int k);

    void bubbleDown(); 

    int smallChild(int curr);

  private:

  // whatever you need to naturally store things.
  // You may also add helper functions here.

  vector<pair<T,int> > nodes;

  int vector_size;

  int n;

};

// NOTES
// Root @ nodes[1]
// Children at nodes[2] to nodes[d+1]
// Their children  at nodes[d+2] to nodes[d^2 + d + 1]
// Parent (i-1)/d
// kth child d(i-1) + k

template<typename T>
MinHeap<T>::MinHeap(int d) {

  if(d < 2){
    cerr << ("Illegal Tree Size");
  }

  vector_size = 0;
  n = d;

}

template<typename T>
MinHeap<T>::~MinHeap() {}

template<typename T>
void MinHeap<T>::add (T item, int priority){

  int curr = vector_size; 
  nodes.push_back(make_pair(item, priority));
  vector_size++;

  bubbleUp(curr);
}

template<typename T>
const T & MinHeap<T>::peek () const {
  return nodes[0].first;
}

template<typename T>
void MinHeap<T>::remove() {
  
  if(isEmpty()){
    cerr << "Cannot Remove from an Empty Tree";
  }

  nodes[0] = nodes[vector_size-1];
  nodes.erase(nodes.begin() + (vector_size-1));

  vector_size--;

  bubbleDown();
}

template<typename T>
bool MinHeap<T>::isEmpty() {
  return vector_size == 0;
}

/* EXTRA HELPER FUNCTIONS  */

template<typename T>
void MinHeap<T>::bubbleUp(int i) {

  int curr = i; 
  
  pair<T,int> tmp = nodes[curr];

  for (; curr > 0 && tmp.second < nodes[parent(curr)].second; curr = parent(curr))
  nodes[curr] = nodes[parent(curr)];

  nodes[curr] = tmp;
}

template<typename T>
int MinHeap<T>::parent(int i) { return ((i - 1) / n); }

template<typename T>
void MinHeap<T>::bubbleDown(){

  int child;

  int curr = 0;
  pair<T, int> tmp = nodes[curr];

  for(; kthChild(curr, 1) < vector_size; curr = child) {
    
    child = smallChild(curr);

    if(nodes[child].second < tmp.second)
      nodes[curr] = nodes[child];
    else
    break;

  }

  nodes[curr] = tmp;
}

template<typename T>
int MinHeap<T>::kthChild(int i, int k) { return (n * i + k); }

template<typename T>
int MinHeap<T>::smallChild(int curr) {

  int k = 2;

  int best = kthChild(curr, 1);
  int nextChild = kthChild(curr, k);
  
  while((k <= n) && (nextChild < vector_size)){

    if (nodes[nextChild].second < nodes[best].second)
      best = nextChild;
    
    k++;
    nextChild = kthChild(curr, k);

  }

  return best;
}
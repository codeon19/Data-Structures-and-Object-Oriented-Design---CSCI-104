#include <iostream> 

using namespace std;

struct Node {
    int value;
    Node *next;
};

Node* merge (Node*& first, Node*& second){

	// declaring lowNodes and highNodes
	Node* lowNode = NULL;
	Node* highNode = NULL;
	Node* temp = NULL;	
	
	// base case1
	if(first == NULL || second == NULL){
		return NULL;
	}

	// finding the lower node value of the two passed
	if((first->value) < (second->value)){
		lowNode = first;
		highNode = second;
	}
	else{
		lowNode = second;
		highNode = first;
	}

	// base case2
	if((lowNode->next) == NULL){
		lowNode->next = highNode;
		return NULL;
	}

	// creating a temp to hold the next node of the low node
	temp = lowNode->next;

	if((temp->value) < (highNode->value)){
		
		lowNode->next = temp;

		if(temp->next == NULL){
			temp->next = highNode;
			temp = NULL;
		}
		else{
		temp = temp->next;
		}

		merge(highNode, temp);
	}
	else{ 
		lowNode->next = highNode;
		merge(temp, highNode);
	}

	return lowNode; // return the start of the linked list
}

int main(){

	// first linked list
	Node* first_a = new Node;
	first_a->value = 2;

	Node* first_b = new Node;
	first_b->value = 4;
	first_a->next = first_b;

	Node* first_c = new Node;
	first_c->value = 6;
	first_b->next = first_c;

	first_c->next = NULL;

	// second linked list
	Node* second_a = new Node;
	second_a->value = 1;

	Node* second_b = new Node;
	second_b->value = 20;
	second_a->next = second_b;
	
	Node* second_c = new Node;
	second_c->value = 21;
	second_b->next = second_c; 

	second_c->next = NULL;

	Node* n = merge(first_a, second_a);

	while (n != NULL) {
		cout << n->value << endl;
		n = n->next;
	}

	// deleting nodes

	delete first_a;
	delete first_b;
	delete first_c;
	
	delete second_a;
	delete second_b;
	delete second_c;

	return 0;
 }
  
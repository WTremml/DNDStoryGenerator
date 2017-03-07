//easier just to do everything in-line

/* Will Tremml
Linked List post-fix stack
2/23/17
*/

//checking
#include "Linked.h"


/* Function for create/insert node at the beginning of Linked list */
void linkedlist::insert_beginning(int _x, int _y) {
	//new list variable
	list *node_new = new list;

	node_new->x = _x;
	node_new->y = _y;

	//creates a new LL if there is none
	if(first == NULL) {
		node_new->prev = NULL;
		node_new->next = NULL;
		first = node_new;
		last = node_new;
		//cout << "Linked list created" << endl;
	}
	//points the first node to the new node
	else {
		node_new->prev = NULL;
		first->prev = node_new;
		node_new->next = first;
		first = node_new;
		//cout << "Data Inserted at the beginning" << endl;
	}
	//increasing length
	length++;
}

/* Function for create/insert node at the end of Linked list */
void linkedlist::insert_end(int _x, int _y) {
	list *addEnd = new list;
	addEnd->x = _x;
	addEnd->y = _y;

	//checking to see if LL is empty
	if(first == NULL) {
		addEnd->prev = NULL;
		addEnd->next = NULL;
		first = addEnd;
		last = addEnd;
		//cout << "Linked list Created!" << endl;
	}
	//attaches previous last to the new node
	else {
		addEnd->next = NULL;
		last->next = addEnd;
		addEnd->prev = last;
		last = addEnd;
		//cout << "Data Inserted at the end" << endl;
	}
	length++;
	//display();
}

/* Function for Display Linked list */
void linkedlist::display() {

	cout << "Linked List is: ";
	node = first;
	// cout << "List of data in Linked list in Ascending order!" << endl;
	while(node != NULL) {
		cout << "X: " << node->x << "Y: " << node->x ;
		node = node->next;
	}
	node = last;
	cout << endl;

	/*
	cout << "List of data in Linked list in Descending order!" << endl;
	while(node != NULL) {
		cout << node->oper << endl;
		node = node->prev;
	}
	*/

	node = first;	//needed to avoid seg fault in del
	
}

/* Function for delete node from Linked list */
void linkedlist::del(int _number) {
	int count = 0, number, i;
	number = _number;

	node = node1 = node2 = first;
	for(node = first; node != NULL; node = node->next){
		count++;
	}

	//without this line node will = NULL due to the count++
	node = first;
	/*
			cout << "Enter value for the node:" << endl;
			display();
			cout << count << " nodes available here!" << endl;
			cout << "Enter the node number which you want to delete:" << endl;
			cin >> number;
	*/

	if(number != 1) {
		//checking bounds
		if(number < count && number > 0) {
			for(i = 2; i <= number; i++){
				node = node->next;
			}
			for(i = 2; i <= number-1; i++){
				node1 = node1->next;
			}
			for(i = 2; i <= number+1; i++){
				node2 = node2->next;
			}
			node2->prev = node1;
			node1->next = node2;
			node->prev = NULL;
			node->next = NULL;
			node = NULL;
		}
		//deleteing last node
		else if(number == count) {
			node = last;
			last = node->prev;
			last->next = NULL;
			node = NULL;
			}
		else
			cout << "Invalid node number!" << endl;
	}
	//deletes first node.
	else {
		node = first;
		first = node->next;
		first->prev = NULL;
		delete node;
	}
	//cout << "Node has been deleted successfully!" << endl;
	length--;
}


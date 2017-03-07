//easier just to do everything in-line

/* Will Tremml
Linked List post-fix stack
2/23/17
*/

//checking
#ifndef LIST_H
#define LIST_H

// libraries
#include <iostream>
#include <string>

using namespace std;


/* Linked list structure */
struct list {
	struct list *prev;

	//discussion of why char was picked is in the other file. Lots of limitations but so easy.
	int x;
	int y;

	struct list *next;
};
// defining list variables above
extern list *node;
extern list *first;
extern list *last;
extern list *node1;
extern list *node2;

class linkedlist {

	//only class variable
	int length;

	public: 
		//initializer
		linkedlist(){ length=0;}

		/* Function for create/insert node at the beginning of Linked list */
		void insert_beginning(int _x, int _y);

		/* Function for create/insert node at the end of Linked list */
		void insert_end(int _x, int _y);

		/* Function for Display Linked list */
		void display();
	
		/* Function for delete node from Linked list */
		void del(int _number);

		//gets value at node i
		int* getNode(int i){
			int n;
			int* arr;
			arr = new int[2];

			node = first;

			if(i>length || i<0) throw runtime_error("Node DNE");

			for(n=1;n<i;n++) {
				node = node->next;
			}
			arr[0]=node->x;
			arr[1]=node->y;

			return(arr);

			node = first;
		}


		//interaction with private variable.
		int getLength(){ return(this->length);}
		void changeLength(int l){ this->length = l;}

	};


#endif
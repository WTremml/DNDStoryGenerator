/*
 * World.h
 *
 *  Created on: Feb 24, 2017
 *      header file for generating the entire world dyamically
 *		
 *  Will Tremml
 */




// iostream is for testing, ncurses is for actual display
//Do NOT use both sets of commands at the same time
#ifndef WORLD_H
#define WORLD_H


#include <iostream>
#include <ncurses.h>
#include <string>

//for random number generator
#include <cstdlib>
#include <math.h>
#include <ctime>
#include "linked.h"

#include "item.h"
#include "character.h"


#define MAX_PLAYERS 20
#define MAX_ROOM_SIZE 8
// Minimum room size is 3

//number of rooms on each floor. Could be changed to random in the future
#define ROOM_ITER 6

//map dimensions
#define MAP_WIDTH 20
#define MAP_HEIGHT 20
#define MAP_LEVELS 1
    //really map is 20 rows and 40 columns because of spaces between the columns


// Tile types
#define TILE_ROCKFLOOR		0
#define TILE_WALL			1
#define TILE_LOCKEDDOOR		2
#define TILE_OPENDOOR		3
#define TILE_CORRIDOR		4
#define TILE_FINISHED		5

// Item Types
#define ITEM_NONE			6
#define ITEM_POTION			7
#define ITEM_GOLD			8
#define ITEM_KEY			9
#define ITEM_Weapon 		10

// Character Types
#define CHAR_None   		11
#define CHAR_BMONSTER		12
#define CHAR_SMONSTER		13
#define CHAR_DUMMY   		14
#define CHAR_USER   		15



//////////////////////////////////////

/*
MUST INCLUDE -lncurses !!!
How to run the code:

g++ -o World World.cpp -lncurses

*/

//////////////////////////////////////

//these are in World.h as prototypes
struct Item_Type{
  char dispCharacter;
  int color;
  std::string name;
};

struct Tile_Type {

  char dispCharacter;
  int dispColor;
  bool Passable;
};
struct Char_Type {
    
  char dispCharacter;
  int color;
  std::string name;
};

//the actual structs are defines in Game.cpp
extern Tile_Type TileIndex[];
extern Item_Type ItemIndex[];
extern Char_Type CharIndex[];

extern list *node;
extern list *first;
extern list *last;
extern list *node1;
extern list *node2;


class Room {
	//Room vertices
	//Defined as follows:
	// X1, X2, Y1, Y2, Z
	// X1 is always < X2
	// Y1 is always < Y2
	int location[5];

	//number of doors
	int num;

	//location of doors int[6]
	int* D_xy;

	//approximate center
	int center[2];

  public:

  	//initialized to -1 just in case
	Room();
	//Makes a room with given vertices
	Room(int* arr);
	//copy constructor
	Room(const Room& old);

	//simple get command
	int getD_num(){ return(num); }

	//changes door information on rooms
	void changeDoors(int _num, int* arr);

	//changes vertices
	void changeRoom(int x1, int x2, int y1, int y2, int z);

	//produces a new pointer
	//must remember to delete
	int* getLoc();

	//produces a new pointer
	//must remember to delete
	int* getDoors(){
		int i;
		int* arr = new int[6];

		for(i=0;i<6;i++){ arr[i]=D_xy[i];}
		return(arr);
	}

	//only gets the 'x' or 'y' value
	// 0-> X , 1-> Y
	// anything else will throw
	int getCenter(int n);

	// for testing, prints vertices
	void printLoc();

	//returns false if does not intersect
	bool intersects( int* loc_);

	// returns true if it is inside
	bool inside(int x, int y, int z);

	// returns distance between centers of rooms
	int distance(Room A);

	//put in coordinates
	float distance(int x, int y);

};

//////////////////////////////////////
class SparseMat{
  private:
    bool* arr;

    int size;
    int M;

  public:
    //constructor
     SparseMat();
    //destructor
     ~SparseMat();
    //copy constructor
    SparseMat(const SparseMat& old);

    // Simple return-by-value for class variables
    // length is the number of array elements
    int length(){return(size);} 
    int NxN(){return(M);}

    //Priting loop for efficiency
    void printMat();

    //overloading getInd for strings or indices
    bool getInd(int row, int col);

    //function to change an value for strings and index
    void changeInd(int row, int col, bool value);
};


//////////////////////////////////////



class World{

	// Main storage array
	int*** MapArray;
	// Room storage array
	Room** Room_List;
	// Boolean Array of if rooms are connected
	SparseMat R_Connections[MAP_LEVELS];
    
    // Potion array
    Potion potions[30];
    int pArray;
    // Gold array
    Gold golds[30];
    int gArray;
    // Key array
    Key keys[30];
    int kArray;
    // Weapon array
    Weapon weapons[30];
    int wArray;
    
    // Monster array
    Monster monsters[40];
    int mArray;
    // Dummy array
    Dummy dummies[30];
    int dArray;
    
    //Screen dimensions
    int rows;
    int cols;
    
  public:
	//constructor
	World();
	//destructor
	~World();

	//Generates a 20x20x3 array with 1 as walls
	void GenerateMap( void );
	//takes Room coordinates and puts them on the map
	void makeRoom(Room A);
	// generates doors for rooms
	void generateDoors();
	// makes corridors
	void generatePaths();
	// makes items
	void generateItems(Room A);
    // makes characters
    void generateCharacters(Room A);
    
    //sets screen dimensions
    void setScreen(int r, int c) {
        rows=r;
        cols=c;
    }
    
	int* getStart(int z){
		int i = rand()%ROOM_ITER;
		int* arr;

		arr = new int[2];
		arr[0] = Room_List[z][i].getCenter(0);
		arr[1] = Room_List[z][i].getCenter(1);

		return(arr);

	}
	//returns the map values
	int getMapVal(int x, int y, int z){return(MapArray[x][y][z]);}
	//changes mapval and returns what was previously there
	void changeMapVal(int x, int y, int z, int Input){
		//int temp = MapArray[x][y][z];
		MapArray[x][y][z] = Input;
	}
	//based on tile type, if a person can walk through it. Mostly used for corridors
	bool IsPassable( int x, int y, int z );
	// prints map to screen for testing using std::cout, not for the final version
	void printMap();

	// prints map to screen using NCURSES 
	void printMap(int row, int col, int level, Person User);
    
    //check if user has found an object or computer character
     int checkUserLoc(Person user);

};
#endif


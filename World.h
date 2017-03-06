/*
 * Wolrd.h
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

//for random number geerator
#include <cstdlib>
#include <math.h>
#include <ctime>


#define MAX_PLAYERS 20
#define MAX_ROOM_SIZE 8
// Minimum room size is 3

//number of rooms on each floor. Could be changed to random in the future/
#define ROOM_ITER 6

//map dimensions
#define MAP_WIDTH 20
#define MAP_HEIGHT 20
#define MAP_LEVELS 2


// Tile types
#define TILE_ROCKFLOOR		0
#define TILE_WALL			1
#define TILE_LOCKEDDOOR		2
#define TILE_OPENDOOR		3
#define TILE_CORRIDOR		4
#define TILE_TREE			5

// Item Types
#define ITEM_NONE			6
#define ITEM_POTION			7
#define ITEM_GOLD			8
#define ITEM_KEY			9
#define ITEM_Weapon 		10


//////////////////////////////////////

/*
MUST INCLUDE -lncurses !!!
How to run the code:

g++ -o World World.cpp -lncurses

*/

//////////////////////////////////////

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

extern Tile_Type TileIndex[];
extern Item_Type ItemIndex[];


class Room {
	//Room vertices
	//Defined as follows:
	// X1, X2, Y1, Y2, Z
	// X1 is always < X2
	// Y1 is always < Y2
	int location[5];
	int num;
	int* D_xy;
	int center[2];

  public:

  	//initialized to -1 just in case
	Room();
	//Makes a room with given vertices
	Room(int* arr);

	//copy constructor
	Room(const Room& old);

	int getD_num(){ return(num); }

	// changes door information on rooms 
	void changeDoors(int _num, int* arr);

	//changes vertices
	void changeRoom(int x1, int x2, int y1, int y2, int z);

	//produces a new pointer
	//must remember to delete
	int* getLoc();
	int getCenter(int n);

	// for testing, prints vertices
	void printLoc();

	//returns false if does not intersect
	bool intersects( int* loc_);

	// returns true if it is inside
	bool inside(int x, int y, int z);

	// returns distance between centers of rooms
	int distance(Room A);

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
	Room** Room_List;
	SparseMat R_Connections[MAP_LEVELS];

  public:
  	int buffer;  	

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


	//based on tile type, if a person can walk through it. Mostly used for corridors
	bool IsPassable( int x, int y, int z );
	// prints map to screen for testing using std::cout, not for the final version
	void printMap();

};



#endif


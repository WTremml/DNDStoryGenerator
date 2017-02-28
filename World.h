// iostream is for testing, nncurses is for actual display
//Do NOT use both sets of commands at the same time
#ifndef WORLD_H
#define WORLD_H


#include <iostream>
#include <ncurses.h>
#include <string>

//for random number geerator
#include <cstdlib>
#include <ctime>


#define MAX_PLAYERS 20
#define MAX_ROOM_SIZE 8
// Minimum room size is 3

//number of rooms on each floor. Could be changed to random in the future/
#define ROOM_ITER 6

//map dimensions
#define MAP_WIDTH 20
#define MAP_HEIGHT 20
#define MAP_LEVELS 3


// Tile types
#define TILE_ROCKFLOOR		0
#define TILE_WALL			1
#define TILE_CLOSEDDOOR		2
#define TILE_OPENDOOR		3
#define TILE_CORRIDOR		4
#define TILE_TREE			5
#define TILE_LOCKEDDOOR		6

// Item Types
#define ITEM_NONE			0
#define ITEM_POTION			1
#define ITEM_GOLD			2
#define ITEM_KEY			3
#define ITEM_Weapon 		4


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

Tile_Type TileIndex[] = {
	{' ', COLOR_WHITE, true},		//Rockfloor 	(0)
	{'#', COLOR_BLACK, true},		//Wall 			(1)
	{'+', COLOR_BLUE, false},		//Closed Door 	(2)
	{'/', COLOR_BLUE, true},		//Open Door 	(3)
	{'#', COLOR_RED, true},			//Corridor 		(4)
	{'T', COLOR_GREEN, false},		//Tree 			(5)
};

Item_Type ItemIndex[] = {
	{' ', 		COLOR_WHITE, 	"Empty"},		//None 		 	(0)
	{(char)173, COLOR_CYAN, 	"Potion"},		//Potion 		(1)
	{(char)169, COLOR_YELLOW, 	"Gold"},	    //Gold 		 	(2)
	{(char)170, COLOR_BLACK,    "Key"},			//key 		 	(3)
	{(char)159, COLOR_RED, 		"Weapon"},		//weapon 		(4)
};



class Room {
	//Room vertices
	//Defined as follows:
	// X1, X2, Y1, Y2, Z
	// X1 is always < X2
	// Y1 is always < Y2
	int location[5];

  public:
  	//initialized to -1 just in case
	Room();
	//Makes a room with given vertices
	Room(int* arr);

	//changes vertices
	void changeRoom(int x1, int x2, int y1, int y2, int z);

	//produces a new pointer
	//must remember to delete
	int* getLoc();

	// for testing, prints vertices
	void printLoc();

	//returns false if does not intersect
	bool intersects( int* loc_);

	// returns true if it is inside
	bool inside(int x, int y, int z);

};


//////////////////////////////////////



class World{

	// Main storage array
	int*** MapArray;

public:
	//constructor
	World();
	//destructor
	~World();

	//Generates a 20x20x3 array with 1 as walls
	void GenerateMap( void );
	//takes Room coordinates and puts them on the map
	void makeRoom(Room A);
	//based on tile type, if a person can walk through it. Mostly used for corridors
	bool IsPassable( int x, int y, int z );
	// prints map to screen for testing using std::cout, not for the final version
	void printMap();

};



#endif


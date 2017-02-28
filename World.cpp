// iostream is for testing, nncurses is for actual display
//Do NOT use both sets of commands at the same time
#include <iostream>
#include <ncurses.h>
#include <string>

//for random number geerator
#include <cstdlib>
#include <ctime>
#include "World.h"


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




/*
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
*/


Room::Room(){
	location[0]=-1;
	location[1]=-1;
	location[2]=-1;
	location[3]=-1;
	location[4]=-1;
}
//Makes a room with given vertices
Room::Room(int* arr){
	int i, temp;
	for(i=0;i<5;i++){
		location[i]= arr[i];
	}

	//enforcing the ordering
	if(location[0]>location[1]){
		temp=location[0];
		location[0]=location[1];
		location[1]=temp;
	}
	if(location[2]>location[3]){
		temp=location[2];
		location[2]=location[3];
		location[3]=temp;
	}
}

//changes vertices
void Room::changeRoom(int x1, int x2, int y1, int y2, int z){
	int temp;

	//enforces ordering
	if(x1>x2){
		temp=x2;
		x2=x1;
		x1=temp;
	}
	if(y1>y2){
		temp=y2;
		y2=y1;
		y1=temp;
	}

	location[0]=x1;
	location[1]=x2;
	location[2]=y1;
	location[3]=y2;
	location[4]=z;
}

//produces a new pointer
//must remember to delete
int* Room::getLoc(){
	int i;
	int* arr = new int[5];
	
	for(i=0;i<5;i++){
		arr[i]= this->location[i];
	}
	return(arr);
}

// for testing, prints vertices
void Room::printLoc(){
	int i;
	for(i=0;i<5;i++){
		std::cout << location[i] << " " << std::endl;
	}
	std::cout << std::endl;
}

//returns false if does not intersect
bool Room::intersects( int* loc_){
	// all comparisons include the '=' for no shared walls

	// checks z location. If Z1 != Z2 then it can't intersect
	if(loc_[4]==location[4]){

		//checks if test x is inside room's x bounds	
		// if (x2 > x_1 > x1) OR (x2 > x_2 > x1)
		if( (location[1]>=loc_[0] && loc_[0]>=location[0]) || (location[1]>=loc_[1] && loc_[1]>=location[0]) ){

			// checks if test y's are inside the room's bounds
			if ( (location[3]>=loc_[2] && loc_[2]>=location[2]) || (location[3]>=loc_[3] && loc_[3]>=location[2]) ){
				return(true);
			}

			// checks if test y's span greater than the room
			//if y1 < y_1 AND y2 > y_2
			else if(location[2] >= loc_[2] && location[3] <= loc_[3]){
				return(true);

			//does not intersect if it makes it this far
			}else{
				return(false);
			}

		// checks if test x's span greater than the room
		//if x1 < x_1 AND x2 > x_2
		} else if (location[0] >= loc_[0] && location[1] <= loc_[1]){

			//checks if test y's is inside room's y bounds	
			// if (y2 > y_1 > y1) OR (y2 > y_2 > y1)
			if ( (location[3]>=loc_[2] && loc_[2]>=location[2]) || (location[3]>=loc_[3] && loc_[3]>=location[2]) ){
				return(true);

			// checks if test y's span greater than the room
			//if y1 < y_1 AND y2 > y_2
			}else if(location[2] >= loc_[2] && location[3] <= loc_[3]){
				return(true);

			//does not intersect if it makes it this far
			}else{
				return(false);
			}

		// Redundant else because x's must either be outside of, or inside the room
		}else{
			return(false);
		}

	// Z statement
	}else{
		return(false);
	}
}

// returns true if it is inside
bool Room::inside(int x, int y, int z){
	if(z == location[4]){
		if( location[1]> x && location[0] < x){
			if( location[3]> y && location[2] < y){
				return(true);
			}else{return(false);}
		}else{return(false);}
	}else{return(false);}
}


//////////////////////////////////////



World::World(){
	int i,j,k;

	//allocating memory
	MapArray = new int**[MAP_WIDTH];
	for (int i = 0; i < MAP_WIDTH; ++i) {
		MapArray[i] = new int*[MAP_HEIGHT];
	    for (int j = 0; j < MAP_WIDTH; ++j){
	     	MapArray[i][j] = new int[MAP_LEVELS];
	  	}
	 }

	 //Initializing to zero
	for(i=0;i<MAP_WIDTH;i++){
		for(j=0;j<MAP_HEIGHT;j++){
			for(k=0;k<MAP_LEVELS;k++){
				MapArray[i][j][k] = 0;
			}
		}
	}
}

//destructor
World::~World(){
	int i,j;

	//deallocating memory
	for (i = 0; i < MAP_WIDTH; ++i) {
		for (j = 0; j < MAP_HEIGHT; ++j){
  			delete [] MapArray[i][j];
  		}	
		delete [] MapArray[i];
		}
		delete [] MapArray;
}

//RANDOMLY GENERATES map locations
void World::GenerateMap( void ){

	int i,j,temp;
	int iter=0;
	int location[5];

	//intersection flag
	int flag = -1;

	//list of all the rooms
	Room Room_List[MAP_LEVELS][ROOM_ITER];


	for(j=0;j<MAP_LEVELS;j++){

		iter =0;

		while(iter< ROOM_ITER){

			//Gennerating random x1,x2
			location[0] = rand() % (MAP_WIDTH-1);
			//enforces MAXIMUM room width of 8
			location[1] = location[0] + (rand() % 17) -8;

			//enforces MINIMUM room width of 3 and that the bounds must be within the map
			while( (location[1] > location[0]-2 && location[1]< location[0]+2) || (location[1]>MAP_WIDTH-1 || location[1]<0) ) {
				location [1] = location[0] + (rand() % 17) -8;
			}

			//Generating random y1, y2
			location[2] = rand() % (MAP_HEIGHT-1);
			//enforces MAXIMUM room width of 8
			location[3] = location[2] + (rand() % 17) -8;

			//enforces MINIMUM room width of 3 and that the bounds must be within the map
			while( (location[3] > location[2]-2 && location[3]< location[2]+2) || (location[3]>MAP_WIDTH-1 || location[3]<0) ){
				location [3] = location[2] + (rand() % 17) -8;
			}

			//Sets Z
			location[4] = j;

			// switiching so x1 < x2 and y1 < y2
			if(location[0]>location[1]){
				temp=location[0];
				location[0]=location[1];
				location[1]=temp;
			}
			if(location[2]>location[3]){
				temp=location[2];
				location[2]=location[3];
				location[3]=temp;
			}

			//resets the flag
			flag = -1;

			//if this is the first room, then it can't intersect. Saves computation
			if(iter == 0){
				Room_List[j][0].changeRoom(location[0],location[1],location[2],location[3], j);
				makeRoom(Room_List[j][iter]);

				//Iter only increases if a room creation is successful
				iter++;
			}else{
				for(i=0;i<iter;i++){
					if(Room_List[j][i].intersects(location)){
						//sets flag to show that there is an intersection
						flag=0;
					}
				}
				if(flag ==-1){
					Room_List[j][iter].changeRoom(location[0],location[1],location[2],location[3], j);
					makeRoom(Room_List[j][iter]);
					
					//Iter only increases if a room creation is successful
					iter++;
				}
			}

		}
	}
}

void World::makeRoom(Room A){
	int temp;

	int* arr = A.getLoc();

	temp=arr[0];


	while(temp <= arr[1]){
		MapArray[temp] [arr[2]] [arr[4]] = 1;
		MapArray[temp] [arr[3]] [arr[4]] = 1;

		temp++;
	}


	temp=arr[2];
	while(temp <= arr[3]){
		MapArray[arr[0]] [temp] [arr[4]] = 1;
		MapArray[arr[1]] [temp] [arr[4]] = 1;

		temp++;
	}

	//cleaning memory
	delete[] arr;
}


bool World::IsPassable( int x, int y, int z )
{
	// Before we do anything, make sure that the coordinates are valid
	if( x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT )
		return false;

	// Store the value of the tile specified
	int TileValue = MapArray[y][x][z];

	// Return true if it's passable
	return TileIndex[TileValue].Passable;
}


void World::printMap(){
	int i, j ,k;

	for(i=0;i<MAP_LEVELS;i++){
		for(j=0;j<MAP_HEIGHT;j++){
			for(k=0;k<MAP_WIDTH;k++){
				std::cout << MapArray[k][j][i] << " ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
		std::cout << std::endl;
	}
}








/*
int main(void){
	
	//MUST include in MAIN for World.cpp to work
	srand(time(NULL));

	Room test;
	test.changeRoom(1,4,1,4,0);
	std::cout<< test.inside(2,2,0) << std::endl;

	
	World game;
	game.GenerateMap();
	game.printMap();
	


	return(0);

}
*/




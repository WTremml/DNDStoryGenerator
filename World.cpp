 /*
 * Wolrd.h
 *
 *  Created on: Feb 24, 2017
 *      header file for generating the entire world dyamically
 *		
 *  Will Tremml
 */



// iostream is for testing, nncurses is for actual display
//Do NOT use both sets of commands at the same time

#include "World.h"



//////////////////////////////////////

/*
MUST INCLUDE -lncurses !!!
How to run the code:

g++ -o World World.cpp -lncurses

*/

//////////////////////////////////////




Room::Room(){
	int i;
	num=0;

	center[0] = -1;
	center[1] = -1;

	for(i=0;i<5;i++){
		location[i]=-1;
	}

	//allows for 3 door coordinates. Only two are implemented, but three is still reasonable
	//see generateDoors() for how to change it.
	D_xy = new int[6];
	for(i=0;i<6;i++){
		D_xy[i]=-1;
	}
}
//Makes a room with given vertices
Room::Room(int* arr){
	int i, temp;
	num = 0;

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

	center[0] = arr[0]+(arr[1]-arr[0])/2;
	center[1] = arr[2]+(arr[3]-arr[2])/2;

	D_xy = new int[6];
	for(i=0;i<6;i++){
		D_xy[i]=-1;
	}

}

//copy constructor
Room::Room(const Room& old){
	center[0] = old.center[0];
	center[1] = old.center[1];


	this->location[0]=old.location[0];
	this->location[1]=old.location[1];
	this->location[2]=old.location[2];
	this->location[3]=old.location[3];
	this->location[4]=old.location[4];
}

int Room::getCenter(int n){
		if(n==0 || n ==1){
			return(center[n]);
		}else{
			throw;
		}
	}



void Room::changeDoors(int _num, int* arr){
	int i;

	num = _num;

	for(i=0;i<6;i++){
		D_xy[i]=arr[i];
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

	center[0] = location[0]+(location[1]-location[0])/2;
	center[1] = location[2]+(location[3]-location[2])/2;
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

int Room::distance(Room A){
	int x,y,temp;
	int a,b;

	a=getCenter(0);
	b=getCenter(1);

	x = abs(a-A.getCenter(0));
	y = abs(b-A.getCenter(1));

	temp = pow(x,2)+pow(y,2);
	temp = sqrt(temp);

	return(temp);
}





















//////////////////////////////////////



World::World(){
	int i,j,k;
	
	buffer =0;

	//SparseMat R_Connections[MAP_LEVELS];

	//allocating memory
	MapArray = new int**[MAP_WIDTH];
	for (int i = 0; i < MAP_WIDTH; ++i) {
		MapArray[i] = new int*[MAP_HEIGHT];
	    for (int j = 0; j < MAP_WIDTH; ++j){
	     	MapArray[i][j] = new int[MAP_LEVELS];
	  	}
	 }

	Room_List = new Room*[MAP_LEVELS];
	for (int i = 0; i < ROOM_ITER; ++i) {
		Room_List[i] = new Room[ROOM_ITER];
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

	

	// potential problems with deallocation
	
	for (i = 0; i < MAP_LEVELS; ++i) {
		delete [] Room_List[i];
	}
	delete [] Room_List;
	
}

//RANDOMLY GENERATES map locations
void World::GenerateMap( void ){

	int i,j,temp;
	int iter=0;
	int location[5];

	//intersection flag
	int flag = -1;


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
		for(i=0;i<iter;i++){

			generateItems( Room_List[j][i] );

		}	
	// end of for loop that goes through floors
	}

	//Doors function must come before path function
	//outside of floor loop because they do go through all the floor independantly
	generateDoors( );
	generatePaths();
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

void World::generateDoors(){
	int temp,i,j,count;
	int iter;
	int* arr;
	int XYs[6];

	for(i=0;i<MAP_LEVELS;i++){
		for(j=0;j<ROOM_ITER;j++){

			count =0;
			arr = Room_List[i][j].getLoc();
			for(iter=0;iter<6;iter++){
				XYs[iter]=-1;
			}

			// measuring distance that doors can go on. DN Include corners
			int dx = arr[1]-arr[0];
			int dy = arr[3]-arr[2];

			//number of doors from 1->2
			// Change modulus to '3' if you want three doors per room.
			int D_num = (rand()%2)+1;

			// Array of which walls will have doors.
			// for example: x1 wall, x2 wall (vertical) or y1, y2 walls (horizontal)
			int wall[4];
			wall[0]=rand()%4;


			for(iter=1;iter<4;iter++){
				wall[iter]= (wall[iter-1]+1)%4;
			}
			


			// emergency run through if no doors
			iter=0;
			while( count < D_num && iter<4 ){

				if( wall[iter] == 0 && arr[0]!=0){
					temp = arr[2]+dy/2;

					if(IsPassable(arr[0]-1,temp,arr[4])){
						XYs[2*count] = arr[0];
						XYs[2*count+1] = temp;
						MapArray[arr[0]][temp][arr[4]]=3;
						count ++;
					}
				}
				if(wall[iter] == 1 && arr[1]!=MAP_WIDTH){
					temp = arr[2]+dy/2;

					if(IsPassable(arr[1]+1,temp,arr[4])){
						XYs[2*count] = arr[1];
						XYs[2*count+1] = temp;
						MapArray[arr[1]][temp][arr[4]]=3;
						count ++;
					}
				}
				if(wall[iter] == 2 && arr[2]!=0){
					temp = arr[0]+dx/2;

					if(IsPassable(temp,arr[2]-1,arr[4])){
						XYs[2*count+1] = arr[2];
						XYs[2*count] = temp;
						MapArray[temp][arr[2]][arr[4]]=3;
						count ++;
					}
				}
				if(wall[iter] == 3 && arr[3]!=MAP_HEIGHT){
					temp = arr[0]+dx/2;

					if(IsPassable(temp,arr[3]+1,arr[4])){
						XYs[2*count+1] = arr[3];
						XYs[2*count] = temp;
						MapArray[temp][arr[3]][arr[4]]=3;
						count ++;
					}
				}
				iter++;
			}

			//std::cout << i << ", " << j << ", " << count << std::endl;
			//std::cout << count << " doors at " << XYs[0] << " " << XYs[1] << "," << XYs[2] << " "<< XYs[3] << "," << XYs[4] << " " << XYs[5]<< std::endl;
			Room_List[i][j].changeDoors(count, XYs);

			
		}
	}

	

	delete[] arr;

}

void World::generateItems(Room A){
	int* arr = A.getLoc();

	int x,y,i;
	int N_items = (rand()%3);

	for(i=0;i<N_items;i++){
		x = (rand()%(arr[1]-arr[0]-1))+arr[0]+1;
		y = (rand()%(arr[3]-arr[2]-1))+arr[2]+1;

		if(MapArray[x][y][arr[4]]==0) {
			MapArray[x][y][arr[4]]=(rand()%5)+6;
		}
	}
	

	delete[] arr;
}


void World::generatePaths(){
	int i,j,k,iter;
	int dist;

	int temp[6];

	// Room number followed by distance
	temp[0]=-1;
	temp[1]=MAP_HEIGHT*MAP_WIDTH;
	temp[2]=-1;
	temp[3]=MAP_HEIGHT*MAP_WIDTH;
	temp[4]=-1;
	temp[5]=MAP_HEIGHT*MAP_WIDTH;

	for(k=0;k<MAP_LEVELS;k++){
		std::cout << "Generating Level: " << k << std::endl;
		for(j=0;j<ROOM_ITER;j++){
			for(i=0;i<ROOM_ITER;i++){
				if(i!=j){
					dist =Room_List[k][j].distance(Room_List[k][i]);
					//std::cout << j << ", " << i << ": " << dist << std::endl;
					if (dist < temp[1]){
						temp[4]=temp[2];
						temp[5]=temp[3];

						temp[2]=temp[0];
						temp[3]=temp[1];

						temp[0]=i;
						temp[1]=dist;
					}else if ( dist < temp[3] ){
						temp[4]=temp[2];
						temp[5]=temp[3];

						temp[2]=i;
						temp[3]=dist;
					}else if ( dist < temp[5]) {
						temp[4]=i;
						temp[5]=dist;
					}
				}
			}
			//std::cout << "Room " << j << " is closest to " << temp[0] << ", " << temp[2] << ", " << temp[4] << std::endl;
			std::cout << Room_List[k][j].getD_num() << std::endl;
			
			for(iter=0;iter<Room_List[k][j].getD_num();iter++){
				R_Connections[k].changeInd(j,temp[0+2*iter],true);
			}
			
			temp[0]=-1;
			temp[1]=MAP_HEIGHT*MAP_WIDTH;
			temp[2]=-1;
			temp[3]=MAP_HEIGHT*MAP_WIDTH;
			

		}
		R_Connections[k].printMat();
	}
	

}


bool World::IsPassable( int x, int y, int z )
{
	// Before we do anything, make sure that the coordinates are valid
	if( x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT )
		return false;

	// Store the value of the tile specified
	int TileValue = MapArray[x][y][z];

	// Return true if it's passable
	return TileIndex[TileValue].Passable;
}


void World::printMap(){
	int i, j ,k;

	for(i=0;i<MAP_LEVELS;i++){
		for(j=0;j<MAP_HEIGHT;j++){
			for(k=0;k<MAP_WIDTH;k++){
					if(MapArray[k][j][i]<6){
						std::cout << TileIndex[ MapArray[k][j][i] ].dispCharacter << " ";
					}else{
						std::cout << ItemIndex[ MapArray[k][j][i] -6 ].dispCharacter << " ";
					}
				
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
		std::cout << std::endl;
	}
}
















SparseMat::SparseMat(){
	int i,j;
	i=0;
	j=ROOM_ITER;

	while(j != 0){
		i=i+j ;
		j-- ;
	}

	size=j;
	M=ROOM_ITER;

	arr = new bool [j];

	for(i=0;i<j;i++){
		arr[i]=0;
	}

}
//destructor
SparseMat::~SparseMat(){
  delete [] arr;
}
//copy constructor
SparseMat::SparseMat(const SparseMat& old){
  int i;
  arr = new bool [old.size];
  for(i=0;i<old.size;i++) arr[i]=old.arr[i];
}


//Priting loop for efficiency
void SparseMat::printMat(){
  int i,j;

  for(i=0;i<M;i++){
    std::cout << std::endl;

    for(j=0;j<M;j++){
      std::cout<< this->getInd(i,j) << "\t";
    }
  }

  std::cout << std::endl;
  std::cout << std::endl;
}


// This matrix starts at the indice 0x0
// Note that this is not Math notation, but CS
bool SparseMat::getInd(int row, int col){
  int c,i;
  int score=0;
  // Checking inputs
  if (row<0 || col<0 || row>M || col>M){
    std::cout << "invalid inputs" << std::endl;
    return(0);
  }
  else if (row == col){
    return(0);
  // Continues if inputs are good
  } else {
    if(col > row){
      c = col;
      col = row;
      row = c;
    }
    for(i=0;i<col;i++){
      score=score+(M-1)-i;
    }
    score=score+row-col-1;

    return(arr[score]);
  } 
}


//changes the actual data for the matrix
void SparseMat::changeInd(int row, int col, bool value){
  
  int c,i;
  int score=0;
  // Checking inputs
  if (row == col){
    return;
  // Continues if inputs are good
  } else {
    if(col > row){
      c = col;
      col = row;
      row = c;
    }
    for(i=0;i<col;i++){
      score=score+(M-1)-i;
    }
    score=score+row-col-1;
  } 


  arr[score]= value;

  //cout << "Value of " << row << "," << col << " changed to " << arr[score] << endl;
}









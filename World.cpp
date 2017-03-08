 /*
 * World.h
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



// empty construction
Room::Room(){
	int i;

	//set number of doors to zero
	num=0;

	//set center to -1,-1 so it will throw in map generation
	center[0] = -1;
	center[1] = -1;

	//setting locations to -1 for throw
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

// Makes a room with given vertices
// input array MUST be int[5]
// X1 X2 Y1 Y2 Z
Room::Room(int* arr){
	int i, temp;

	//number of doors still 0. Must generate doors after
	num = 0;

	//setting locations equal
	for(i=0;i<5;i++){
		location[i]= arr[i];
	}

	//enforcing the ordering that X1 < X2 and Y1 < Y2
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

	// finding approximate integer center of room
	center[0] = arr[0]+(arr[1]-arr[0])/2;
	center[1] = arr[2]+(arr[3]-arr[2])/2;

	// setting doors to -1 to throw if used
	D_xy = new int[6];
	for(i=0;i<6;i++){
		D_xy[i]=-1;
	}

}

//copy constructor
Room::Room(const Room& old){
	int i;
	// copying number of doors
	num = old.num;

	//copying door locations
	D_xy = new int[6];
	for(i=0;i<6;i++){
		D_xy[i]=old.D_xy[i];
	}	

	//copying center
	center[0] = old.center[0];
	center[1] = old.center[1];

	//copying locations
	this->location[0]=old.location[0];
	this->location[1]=old.location[1];
	this->location[2]=old.location[2];
	this->location[3]=old.location[3];
	this->location[4]=old.location[4];
}

//returns the center integer
// 0 for X
// 1 for Y
// Sepaaration is useful in some situations
int Room::getCenter(int n){
		//checks that input is good
		if(n==0 || n ==1){
			return(center[n]);
		}else{
			throw;
		}
	}

//changes the Door information for the Room class
void Room::changeDoors(int _num, int* arr){
	int i;

	num = _num;

	//copies the whole 6 element array
	for(i=0;i<6;i++){
		D_xy[i]=arr[i];
	}	
}

//changes vertices
//in this case it was easier to use separate integers instead of an array
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
//probabily a better way to do this, but this works perfectly
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
		//std::cout << "zs are equal" << std::endl;
		if( (location[1]> x) && (location[0] < x) ){
			if( (location[3]> y) && (location[2] < y) ){
				//std::cout << x << ", " << y << " True" << std::endl;
				return(true);
			}else{return(false);}
		}else{return(false);}
	}else{return(false);}
}

//calculates the (approximate) distance between centers
//used for determining connections
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

float Room::distance(int x, int y){
	float X_,Y_,temp;
	int a,b;

	a=getCenter(0);
	b=getCenter(1);

	X_ = abs(a-x);
	Y_ = abs(b-y);

	temp = pow(X_,2)+pow(Y_,2);
	temp = sqrt(temp);

	return(temp);
}




//////////////////////////////////////////////////////////////////////////////////////////////////////////////////




World::World(){
	int i,j,k;

	//allocating memory for map
	MapArray = new int**[MAP_WIDTH];
	for (int i = 0; i < MAP_WIDTH; ++i) {
		MapArray[i] = new int*[MAP_HEIGHT];
	    for (int j = 0; j < MAP_WIDTH; ++j){
	     	MapArray[i][j] = new int[MAP_LEVELS];
	  	}
	 }

	//allocating memory for room list
	Room_List = new Room*[MAP_LEVELS];
	for (int i = 0; i < ROOM_ITER; ++i) {
		Room_List[i] = new Room[ROOM_ITER];
	 }

	//Initializing map to zero. No need to do this for the room list
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

	//like allocating but in reverse for MapArray
	for (i = 0; i < MAP_WIDTH; ++i) {
		for (j = 0; j < MAP_HEIGHT; ++j){
  			delete [] MapArray[i][j];
  		}	
		delete [] MapArray[i];
	}
	delete [] MapArray;

	//like allocating but in reverse for room list
	for (i = 0; i < MAP_LEVELS; ++i) {
		delete [] Room_List[i];
	}
	delete [] Room_List;
	
}

//Randomly generates entire map! How impressive!
void World::GenerateMap( void ){
	//temperary variables
	int i,j,temp;
	int iter=0;
	int location[5];

	//intersection flag
	int flag = -1;

	//loops through for each level
	for(j=0;j<MAP_LEVELS;j++){
		//remember to set iter to 0 at each floor
		iter =0;
		//generates Room_Iter number of rooms per level
		while(iter< ROOM_ITER){

			//Gennerating random x1,x2
			location[0] = rand() % (MAP_WIDTH-2) + 1;
			//enforces MAXIMUM room width of 8
			location[1] = location[0] + (rand() % (2*MAX_ROOM_SIZE+1)) - MAX_ROOM_SIZE;

			//enforces MINIMUM room width of 3 and that the bounds must be within the map
			while( (location[1] > location[0]-2 && location[1]< location[0]+2) || (location[1]>MAP_WIDTH-2 || location[1]<=0) ) {
				location [1] = location[0] + (rand() % (2*MAX_ROOM_SIZE+1)) - MAX_ROOM_SIZE;
			}

			//Generating random y1, y2
			location[2] = rand() % (MAP_HEIGHT-2) + 1;
			//enforces MAXIMUM room width of 8
			location[3] = location[2] + (rand() % (2*MAX_ROOM_SIZE+1) ) - MAX_ROOM_SIZE;

			//enforces MINIMUM room width of 3 and that the bounds must be within the map
			while( (location[3] > location[2]-2 && location[3]< location[2]+2) || (location[3]>MAP_WIDTH-2 || location[3]<=0) ){
				location [3] = location[2] + (rand() % (2*MAX_ROOM_SIZE+1) ) - MAX_ROOM_SIZE;
			}

			//Sets Z to the current floor
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
			//items are generated floor by floor, room by room.
			generateItems( Room_List[j][i] );

		}	
	// end of for loop that goes through floors
	}

	//Doors function must come before path function
	//outside of floor loop because they cycle through the entire map on their own
	generateDoors( );
	generatePaths();
}

//takes vertices of room and draws it on the map array
void World::makeRoom(Room A){
	int temp;

	//temporary storage for vertices
	int* arr = A.getLoc();

	//stores the verticle room traces in map array
	temp=arr[0];
	while(temp <= arr[1]){
		MapArray[temp] [arr[2]] [arr[4]] = 1;
		MapArray[temp] [arr[3]] [arr[4]] = 1;

		temp++;
	}

	//stores the horizontal room traces in map array
	temp=arr[2];
	while(temp <= arr[3]){
		MapArray[arr[0]] [temp] [arr[4]] = 1;
		MapArray[arr[1]] [temp] [arr[4]] = 1;

		temp++;
	}

	//cleaning memory
	delete[] arr;
}

// this randomly generates 1->2 doors for each room
// arrays are setup so 3 doors are possible.
void World::generateDoors(){
	//temporary storage
	int temp,i,j,count;
	int iter;
	int* arr;
	int XYs[6];

	//goes through every room on every floor using the World Room array
	for(i=0;i<MAP_LEVELS;i++){
		for(j=0;j<ROOM_ITER;j++){

			//resets temp variables for each room
			count =0;
			arr = Room_List[i][j].getLoc();
			for(iter=0;iter<6;iter++){
				XYs[iter]=-1;
			}

			// measuring distance that doors can go on. DN Include corners
			int dx = arr[1]-arr[0];
			int dy = arr[3]-arr[2];

			//number of doors = 1
			// Change modulus to '3' if you want three doors per room.
			int D_num = (rand()%1)+1;

			// Array of which walls will have doors.
			// for example: x1 wall, x2 wall (vertical) or y1, y2 walls (horizontal)
			int wall[4];
			wall[0]=rand()%4;

			//the random generates the starting wall, cycles from there to avoid duplicates
			for(iter=1;iter<4;iter++){
				//mod 4 needed to prevent seg fault
				wall[iter]= (wall[iter-1]+1)%4;
			}
			


			// gaurentees that there is at least one door (unless the room is completely surrounded)
			// if room has 0 doors, then the programs throws in the Room::changeDoors function
			iter=0;
			while( count < D_num && iter<4 ){

				//case for each wall, commenting on the first case should be sufficient
				//makes sure the wall is not against the edge of the map
				if( wall[iter] == 0 && arr[0]!=0){
					//temp stores the 'middle' of the wall - where the door will go
					temp = arr[2]+dy/2;

					//MAakes sure that the door does not open into another wall
					if(IsPassable(arr[0]-1,temp,arr[4])){
						//stores the x locaiton in 0,2,4
						XYs[2*count] = arr[0];
						//stores the y locaiton in 1,3,5 for pairing
						XYs[2*count+1] = temp;
						//makes door in map
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
			//debugging
			//std::cout << i << ", " << j << ", " << count << std::endl;
			//std::cout << count << " doors at " << XYs[0] << " " << XYs[1] << "," << XYs[2] << " "<< XYs[3] << "," << XYs[4] << " " << XYs[5]<< std::endl;
			
			//finally changes the doors in the Room class
			Room_List[i][j].changeDoors(count, XYs);	
		}
	}

	//cleans temporary array
	delete[] arr;
}

//randomly puts items in rooms, does not matter the room size
void World::generateItems(Room A){
	int* arr = A.getLoc();

	int x,y,i;
	int N_items = (rand()%3);

	for(i=0;i<N_items;i++){
		//generating random location in the room
		x = (rand()%(arr[1]-arr[0]-1))+arr[0]+1;
		y = (rand()%(arr[3]-arr[2]-1))+arr[2]+1;

		//items are numbered 6-10
		//items can only be placed on empty floor space
		if(MapArray[x][y][arr[4]]==0) {
			MapArray[x][y][arr[4]]=(rand()%5)+6;
		}
	}
	
	//cleaning temporary storage
	delete[] arr;
}
//randomly puts characters in rooms, does not matter the room size
void World::generateCharacters(Room A){
    int* arr = A.getLoc();
    
    int x,y,i;
    int N_chars = (rand()%3);
    
    for(i=0;i<N_chars;i++){
        //generating random location in the room
        x = (rand()%(arr[1]-arr[0]-1))+arr[0]+1;
        y = (rand()%(arr[3]-arr[2]-1))+arr[2]+1;
        
        //characters are numbered 11-15
        //items can only be placed on empty floor space
        if(MapArray[x][y][arr[4]]==0) {
            MapArray[x][y][arr[4]]=(rand()%5)+11;
        }
    }
    
    //cleaning temporary storage
    delete[] arr;
}

//generates a boolean matrix of which rooms are connected
void World::generatePaths(){
	linkedlist pathway;
	int i,j,k,iter,n;
	int x,y,X1,Y1;
	int dist;
	int N_Room[ROOM_ITER];
	for(i=0;i<ROOM_ITER;i++){
		N_Room[i]=-1;
	}

	//static so no need to clean
	int temp[6];
	int* pathloc;
	float holder[4];
	float temporary[2];

	// Room number followed by distance
	temp[0]=-1;
	temp[1]=MAP_HEIGHT*MAP_WIDTH;
	temp[2]=-1;
	temp[3]=MAP_HEIGHT*MAP_WIDTH;
	temp[4]=-1;
	temp[5]=MAP_HEIGHT*MAP_WIDTH;

	for(k=0;k<MAP_LEVELS;k++){
		//std::cout << "Generating Level: " << k << std::endl;
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
			//debugging
			//std::cout << "Room " << j << " is closest to " << temp[0] << ", " << temp[2] << ", " << temp[4] << std::endl;
			//std::cout << Room_List[k][j].getD_num() << std::endl;
			
			//stores the boolean in sparse matrix
			// Read: I am using a SPARSE MATRIX
			for(iter=0;iter<Room_List[k][j].getD_num();iter++){
				R_Connections[k].changeInd(j,temp[0+2*iter],true);
			}
			
			//resettig variables for next one
			temp[0]=-1;
			temp[1]=MAP_HEIGHT*MAP_WIDTH;
			temp[2]=-1;
			temp[3]=MAP_HEIGHT*MAP_WIDTH;
			temp[4]=-1;
			temp[5]=MAP_HEIGHT*MAP_WIDTH;
			

		}
		//debugging
		R_Connections[k].printMat();
		//printMap();
	}

	for(k=0;k<MAP_LEVELS;k++){
    //std::cout << "Generating Level: " << k << std::endl;
    for(j=0;j<1 /*ROOM_ITER*/;j++){

      for(iter=0;iter<Room_List[k][j].getD_num();iter++){
        x =  Room_List[k][j].getDoors()[0];
        y =  Room_List[k][j].getDoors()[1];

        int l=0;
        for(i=0;i<ROOM_ITER;i++){
          if ( R_Connections[k].getInd(i,j) ){
            N_Room[l] = i;
            l++;
          }
        }

        X1 =  Room_List[k][N_Room[iter]].getDoors()[0];
        Y1 =  Room_List[k][N_Room[iter]].getDoors()[1];

        /*
        std::cout << "Door Path from: to:" << std::endl;
        std::cout << X1 << ", "<< Y1 << std::endl;
        std::cout << x << ", "<< y << std::endl;
        std::cout << std::endl;
        */

        iter=0;
        while((x!=X1 || y!=Y1) && iter<40){

          for(n=0;n<4;n++){
            holder[n]=0;
          }

          //std::cout << "Here 1" << std::endl;
          if(x<MAP_WIDTH-1){
            if( (MapArray[x+1][y][k]==0 || MapArray[x+1][y][k]==5)  && !Room_List[k][j].inside(x+1,y,k) ){
              holder[1]= pow(X1-x+1,2)+pow(Y1-y,2);
              //std::cout << "1: "<< holder[1]<< "    "<< MapArray[x+1][y][k] << std::endl;
            }else{
              holder[1]=0;
            }
          }else{};

          //std::cout << "Here 2" << std::endl;
          if(x>0){
            if( (MapArray[x-1][y][k]==0 || MapArray[x-1][y][k]==5)  && !Room_List[k][j].inside(x-1,y,k) ){
              holder[0]= pow(X1-x-1,2)+pow(Y1-y,2);
              //std::cout<< "0: " << holder[0]<< "    "<< MapArray[x-1][y][k] << std::endl;
            }else{
              holder[0]=0;
            }
          }else{}

          //std::cout << "Here 3" << std::endl;
          if(y<MAP_HEIGHT-1){
            if( (MapArray[x][y+1][k]==0 || MapArray[x][y+1][k]==5) && !Room_List[k][j].inside(x,y+1,k) ){
              holder[2]= pow(X1-x,2)+pow(Y1-y+1,2);
              //std::cout<< "2: " << holder[2]<< "    "<< MapArray[x][y+1][k] << std::endl;
            }else{
              holder[2]=0;
            }
          }else{}

          //std::cout << "Here 4" << std::endl;
          if(y>0){
            if( (MapArray[x][y-1][k]==0 || MapArray[x][y-1][k]==5) && !Room_List[k][j].inside(x,y-1,k) ){
              holder[3]= pow(X1-x,2)+pow(Y1-y-1,2);
              //std::cout<< "3: " << holder[3]<< "    "<< MapArray[x][y-1][k] << std::endl;
            }else{
              holder[3]=0;
            }
          }else{}

          temporary[0]=0;
          temporary[1]=0;

          for(n=0;n<4;n++){
            if(holder[n]>temporary[1]){
              temporary[0]=n;
              temporary[1]=holder[n];
               //std::cout << "The new temporary" << std::endl;
               //std::cout << temporary[0] << ": " << temporary[1] << std::endl << std::endl;
            }
          }

             
          //std::cout << x << ", "<< y<<  std::endl;
          //std::cout << temporary[0] <<  std::endl;

          if(temporary[0]==0){
            x--;
          }else if(temporary[0] ==1){
            x++;
          }else if(temporary[0]==2){
            y++;
          }else if(temporary[0]==3){
            y--;
          }else{
          	throw;
          }

          


          iter++;

          if(x==X1){
          	if(y+1==Y1 || y-1==Y1){
          		std::cout << "you found the door!" << std::endl;
          		iter=40;
          	}
          }else if(y==Y1){
          	if(x+1==X1 || x-1==X1){
          		std::cout << "you found the door!" << std::endl;
          		iter=40;
          	}
          }else{}

          pathway.insert_end(x,y);
          //std::cout << x << ", "<< y<< "        ";
          MapArray[x][y][k]=4;

          //debugging
          //std::cout << MapArray[x][y][k] << std::endl;
          //std::cout << "END OF SEQUENCE" <<std::endl;

        } //while loop
        for(i=0;i<pathway.getLength()+1;i++){
        	pathloc=pathway.getNode(i);
        	MapArray[pathloc[0]][pathloc[1]][k] = 5; 



        	//std::cout << "Location: " << pathloc[0] << ", " << pathloc[1];
        }

      }// generating path number of connections

    }//generating paths for each room

  }// generating for each level
}

//decides if the character can walk on that tile or not
bool World::IsPassable( int x, int y, int z )
{
	// Before we do anything, make sure that the coordinates are valid
	if( x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT )
		return false;

	// Store the value of the tile specified
	int TileValue = MapArray[x][y][z];

	// Return true if it's passable
    if(TileValue<6){
        return TileIndex[TileValue].Passable;
    }else{
        return(true);
    }
	
}

//prints the map with the std::cout in terminal
void World::printMap(){
	int i, j ,k;
	int temp;

	for(i=0;i<MAP_LEVELS;i++){
		for(temp=0;temp<MAP_WIDTH;temp++){
			std::cout << "~ ";
		}
		std::cout << std::endl;

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

//prints the map with the NCURSES
void World::printMap(int row, int col, int level){
	int i, j ,k;

	if(level<0 || level>=MAP_LEVELS){
		throw;
	}
	k=level;

	for(j=0;j<MAP_HEIGHT;j++){
		move((row-MAP_WIDTH)/2 + j, (col-3*MAP_HEIGHT)/2);
		for(i=0;i<MAP_WIDTH;i++){
			if(MapArray[i][j][k]<2){
				printw("%c ", TileIndex[ MapArray[i][j][k] ].dispCharacter  );

			}else if(MapArray[i][j][k]<4){
				attron(COLOR_PAIR(3));
				printw("%c ", TileIndex[ MapArray[i][j][k] ].dispCharacter );
				attroff(COLOR_PAIR(3));

			}else if(MapArray[i][j][k]<6){
				attron(COLOR_PAIR(1));
				printw("%c ", TileIndex[ MapArray[i][j][k] ].dispCharacter );
				attroff(COLOR_PAIR(1));

			}else{
				attron(COLOR_PAIR(2));
				printw("%c ", ItemIndex[ MapArray[i][j][k] -6 ].dispCharacter );
				attroff(COLOR_PAIR(2));
			}
			
		}
	}

	refresh();
  	getch();
  	erase();
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////



//constructor sparse matrix
SparseMat::SparseMat(){
	int i,j;
	i=0;
	j=ROOM_ITER;

	//determines how large the array needs to be based on number of rooms
	while(j != 0){
		i=i+j ;
		j-- ;
	}

	size=j;
	M=ROOM_ITER;

	//boolean matrix to save space
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
//Prints out a "square" matrix even though this is a linear array that acts as a lower-triangualar matrix
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

  //debugging
  //cout << "Value of " << row << "," << col << " changed to " << arr[score] << endl;
}









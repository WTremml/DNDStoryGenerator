//============================================================================
// Name        : Game.cpp
// Author      : Will Tremml and Emily Chao
// Description : main class for Final Project ENGS 65 17W
//============================================================================
#include <iostream>
#include <ncurses.h>
#include <string>

//for random number generator
#include <cstdlib>
#include <ctime>
using namespace std;

#include "character.h"
#include "magic.h"
#include "World.h"
#include "Screens.h"
#include "item.h"
#include "linked.h"


Tile_Type TileIndex[] = {
  {' ', COLOR_WHITE, true},   //Rockfloor   (0)
  {'#', COLOR_BLACK, false},  //Wall        (1)
  {'+', COLOR_BLUE, false},   //Locked Door (2)
  {'/', COLOR_BLUE, true},    //Open Door   (3)
  {'@', COLOR_RED, true},     //Corridor    (4)
  {'#', COLOR_GREEN, true},   //finished    (5)
};

Item_Type ItemIndex[] = {
  {' '  , COLOR_WHITE, "Empty"},    //None      (0)
  {'!'  , COLOR_CYAN,   "Potion"},  //Potion    (1)
  {'$'  , COLOR_YELLOW, "Gold"},    //Gold      (2)
  {'='  , COLOR_BLACK,  "Key"},     //Key       (3)
  {'S'  , COLOR_RED,  "Weapon"},    //Weapon    (4)
};

Char_Type CharIndex[] = {
    //Monster is included twice so that there will be 2x as many monsters as dummies
    {' '  , COLOR_BLACK,  "Empty"},    //None         (0)
    {'M'  , COLOR_BLACK,  "Monster1"}, //1 Monster    (1)
    {'M'  , COLOR_BLACK,  "Monster2"}, //2 Monster    (2)
    {'D'  , COLOR_BLACK, "Dummy"},     //Dummy        (3)
    {'O'  , COLOR_BLACK, "User"},      //Person       (4)
};


list *node = NULL;
list *first = NULL;
list *last = NULL;
list *node1 = NULL;
list *node2 = NULL;




int main() {
	srand(time(NULL));

    int ch= 0;                // input buffer
    int buffer = 0;
    int direction, mag;
    int won=0;
    int dead=0;
    int* start;               // random start location
    char* name;         // name of character
    int level=0;        //start at level 0

    //making the world
    World game;
	game.GenerateMap();
    game.printMap();

	int row,col;       		    // to store the number of rows columns of the screen 
    initscr();       			// start the curses mode
    curs_set(0);                // makes cursor invisible

    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_CYAN, COLOR_BLACK);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    init_pair(5, COLOR_BLUE, COLOR_BLACK);
    init_pair(6, COLOR_BLACK, COLOR_BLACK);



    getmaxyx(stdscr,row,col); // get the number of rows and columns

    //getting name and starting location
    Intro(row, col);
    name = Name(row, col);
    std::string UserName(name);
    delete[] name;
    
    //must happen after the world is generated
    start = game.getStart(0);

    //storing whatever was under the character
    //buffer = game.getMapVal(start[0],start[1],0)
    //actaully we'll just replace whatever was under the character with 0
    game.changeMapVal(start[0],start[1],0,15);



    //getting magic
    noecho();                 // Does not show characters
    mag = Magic(row, col);

    //creating character
    //Person User(UserName, mag, start[0], start[1], 0);
    Person User(UserName, mag, start[0],start[1],0);
    
    game.printMapLIMITED(row,col,level, User);
    
    keypad(stdscr, TRUE);     // Initializing keypad
    
    //test level up
    Key k, k1, k2;
    User.foundKey(k);
    User.foundKey(k1);
    User.foundKey(k2);
    

    while(level<=MAP_LEVELS && won==0 && (ch=getch())!= 'q' && dead==0){
        switch(ch){
            //User movement on screen
            case KEY_UP: direction= 2; 
                if (game.IsPassable(User.getXLoc(), User.getYLoc()-1, User.getZLoc())) {
                    //changing map back to previous tile
                    game.changeMapVal(User.getXLoc(), User.getYLoc(), User.getZLoc(), buffer);

                    User.moveUp(); 
                    //storeing buffer for where character is moving
                    buffer = game.getMapVal(User.getXLoc(), User.getYLoc(), User.getZLoc());
                    //moving character onto location and puts map value of 15
                    game.changeMapVal(User.getXLoc(), User.getYLoc(), User.getZLoc(), 15);
                    
                }
                break;
            case KEY_DOWN: direction= 3;
                if (game.IsPassable(User.getXLoc(), User.getYLoc()+1, User.getZLoc())) {
                    //changing map back to previous tile
                    game.changeMapVal(User.getXLoc(), User.getYLoc(), User.getZLoc(), buffer);

                    User.moveDown(); 
                    //storeing buffer for where character is moving
                    buffer = game.getMapVal(User.getXLoc(), User.getYLoc(), User.getZLoc());
                    //moving character onto location and puts map value of 15
                    game.changeMapVal(User.getXLoc(), User.getYLoc(), User.getZLoc(), 15);

                }
                break;
            case KEY_RIGHT: direction= 1;
                if (game.IsPassable(User.getXLoc()+1, User.getYLoc(), User.getZLoc())) {
                    //changing map back to previous tile
                    game.changeMapVal(User.getXLoc(), User.getYLoc(), User.getZLoc(), buffer);

                    User.moveRight(); 
                    //storeing buffer for where character is moving
                    buffer = game.getMapVal(User.getXLoc(), User.getYLoc(), User.getZLoc());
                    //moving character onto location and puts map value of 15
                    game.changeMapVal(User.getXLoc(), User.getYLoc(), User.getZLoc(), 15);

                }
                break;
            case KEY_LEFT: direction= 0;
                if (game.IsPassable(User.getXLoc()-1, User.getYLoc(), User.getZLoc())) {
                    //changing map back to previous tile
                    game.changeMapVal(User.getXLoc(), User.getYLoc(), User.getZLoc(), buffer);

                    User.moveLeft(); 
                    //storeing buffer for where character is moving
                    buffer = game.getMapVal(User.getXLoc(), User.getYLoc(), User.getZLoc());
                    //moving character onto location and puts map value of 15
                    game.changeMapVal(User.getXLoc(), User.getYLoc(), User.getZLoc(), 15);
                }
                break;
            //User found item
            case 'p':
                //could also just check buffer??

                if(buffer>5 && buffer<11){
                    if(buffer==6){
                        
                    }else if(buffer == 7){

                    }else if(buffer == 8){

                    }else if(buffer == 9){

                    }else if(buffer == 10){

                    }

                }

                break;
            //User tries advance to next level
            case 'n':
                if (level<MAP_LEVELS && User.getBag().getKeyC()>=1) {        //if have a key
                    level++;
                    start = game.getStart(level);
                    User.setLoc(start[0],start[1],level);
                    User.upLevel();

                    // get rid of key
                    
                }
                break;
        }
        game.printMapLIMITED(row,col,level,User);
        
        //print out lose message if user is dead
        if (User.isDead()) {
            erase();
            mvprintw((row-20)/2, (col-3*20)/2, "You have died!");
            dead=-1;
            refresh();
            sleep(2);
            endwin();
        }
        //print out win message if won
        if(level==MAP_LEVELS) {
            erase();
            mvprintw((row-20)/2, (col-3*20)/2, "You won! You collected %d gold coins!", User.getBag().getGoldC());
            won=-1;
            refresh();
            sleep(2);
            endwin();

        }
    }
    game.printMap();

    
    
    //close window if still open
    if (won!=-1 && dead!=-1)
        endwin();
    
    return 0;
}



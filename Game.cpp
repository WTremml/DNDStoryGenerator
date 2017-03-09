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
    int direction, mag, flag, won;
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


    getmaxyx(stdscr,row,col); // get the number of rows and columns

    //getting name and starting location
    Intro(row, col);
    name = Name(row, col);
    std::string UserName(name);
    delete[] name;
    
    //must happen after the world is generated
    start = game.getStart();

    //getting magic
    mag = Magic(row, col);

    //creating character
    //Person User(UserName, mag, start[0], start[1], 0);
    Person User(UserName, mag, 0,0,0);
    delete[] start;
    
    game.printMap(row,col,level, User);
    
    keypad(stdscr, TRUE);     // Initializing keypad
    noecho();                 // No echo only after keypad
    
    won=0;
    
    //test level up
    Key k, k1, k2;
    User.foundKey(k);
    User.foundKey(k1);
    User.foundKey(k2);
    

    while(level<=3 && won==0 && (ch=getch())!= 'q'){
        switch(ch){
            //User movement on screen
            case KEY_UP: direction= 2; 
                if (game.IsPassable(User.getXLoc()-1, User.getYLoc(), User.getZLoc())) {
                    User.moveLeft(); //goes up
                }
                break;
            case KEY_DOWN: direction= 3;
                if (game.IsPassable(User.getXLoc()+1, User.getYLoc(), User.getZLoc())) {
                    User.moveRight(); //goes down
                }
                break;
            case KEY_RIGHT: direction= 1;
                if (game.IsPassable(User.getXLoc(), User.getYLoc()+1, User.getZLoc())) {
                    User.moveUp(); //goes right
                }
                break;
            case KEY_LEFT: direction= 0;
                if (game.IsPassable(User.getXLoc(), User.getYLoc()-1, User.getZLoc())) {
                    User.moveDown(); //goes left
                }
                break;
            //User found item
            case 'p':
                flag=game.checkUserLoc(User);
                //flag = -1 if no item found
                break;
            //User tries advance to next level
            case 'n':
                if (level<=2 && User.getBag().getKeyC()>=1) {        //if have a key
                    User.upLevel();
                    level++;
                }
                break;
        }
        game.printMap(row,col,level,User);

        //print out win message if won
        if(level==3) {
            mvprintw((row-20)/2, (col-3*20)/2, "You won! You collected %d gold coins!", User.getBag().getGoldC());
            won=-1;
            refresh();
            sleep(2);
            endwin();

        }
    }
    
    //close window if still open
    if (level!=3)
        endwin();
    
    return 0;
}



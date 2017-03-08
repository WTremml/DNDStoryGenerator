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
  {'='  , COLOR_BLACK,  "Key"},     //key       (3)
  {'S'  , COLOR_RED,  "Weapon"},    //Weapon    (4)
};

Char_Type CharIndex[] = {
    {' '  , COLOR_BLACK,  "Empty",  true},    //None         (0)
    {'M'  , COLOR_BLACK,  "BMonster", false}, //Big Monster  (1)
    {'m'  , COLOR_BLACK,  "SMonster", false}, //Small Monster(2)
    {'D'  , COLOR_BLACK, "Dummy", false},     //Dummy        (3)
    {'O'  , COLOR_BLACK, "User", false},      //Person       (4)
};


list *node = NULL;
list *first = NULL;
list *last = NULL;
list *node1 = NULL;
list *node2 = NULL;

int main() {
	srand(time(NULL));

    int ch= 0;                // input buffer
    int direction, mag;
    int* start;               // random start location
    char* name;         // name of character

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
    Person User(UserName, mag, start[0], start[1], 0);
    delete[] start;

    game.printMap(row,col,0);
    keypad(stdscr, TRUE);     // Initializing keypad
    noecho();                 // No echo only after keypad


    
    while((ch=getch())!= 'q'){
        switch(ch){
            case KEY_UP: direction= 2; 
                mvprintw(row/2,(col-24)/2,"The up key was pressed");
                if (game.IsPassable(User.getXLoc(), User.getYLoc()+1, User.getZLoc())) {
                    User.moveUp();
                }
                break;
            case KEY_DOWN: direction= 3;
                mvprintw(row/2,(col-24)/2,"The down key was pressed");
                if (game.IsPassable(User.getXLoc(), User.getYLoc()-1, User.getZLoc())) {
                    User.moveDown();
                }
                break;
            case KEY_RIGHT: direction= 1;
                mvprintw(row/2,(col-24)/2,"The right key was pressed");
                if (game.IsPassable(User.getXLoc()+1, User.getYLoc(), User.getZLoc())) {
                    User.moveRight();
                }
                break;
            case KEY_LEFT: direction= 0;
                mvprintw(row/2,(col-24)/2,"The left key was pressed");
                if (game.IsPassable(User.getXLoc()-1, User.getYLoc(), User.getZLoc())) {
                    User.moveRight();
                }
                break;
        }
        game.printMap(row,col,0);
        
        //print out health to bottom of screen
        mvprintw(row-8,10,"Health: %d", User.getHealth());
        //print out bag to bottom of screen
        mvprintw(row-7,10,"Gold: %d \t Keys: %d \t Potions: %d", User.getBag().getGoldC(), User.getBag().getKeyC(),User.getBag().getPotionC());

    }
    
    endwin(); 
    
    /*
    cout << user.getXLoc();
    user.moveRight();
    cout << user.getXLoc();
`	*/
    
    return 0;
}



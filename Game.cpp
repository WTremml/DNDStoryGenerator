

//============================================================================
// Name        : main.cpp
// Author      : Will Tremml and Emily Chao
// Description : Final Project ENGS 65 17W
//============================================================================
#include <iostream>
#include <ncurses.h>
#include <string>

//for random number geerator
#include <cstdlib>
#include <ctime>
using namespace std;

#include "character.h"
#include "magic.h"
#include "world.h"
#include "Screens.h"
#include "item.h"

Tile_Type TileIndex[] = {
  {' ', COLOR_WHITE, true},   //Rockfloor   (0)
  {'#', COLOR_BLACK, false},    //Wall      (1)
  {'+', COLOR_BLUE, false},   //Locked Door   (2)
  {'/', COLOR_BLUE, true},    //Open Door   (3)
  {'#', COLOR_RED, true},     //Corridor    (4)
  {'T', COLOR_GREEN, false},    //Tree      (5)
};

Item_Type ItemIndex[] = {
  {' '  , COLOR_WHITE,  "Empty"},   //None      (0)
  {'!'  , COLOR_CYAN,   "Potion"},    //Potion    (1)
  {'$'  , COLOR_YELLOW, "Gold"},      //Gold      (2)
  {'='  , COLOR_BLACK,  "Key"},     //key       (3)
  {'S'  , COLOR_RED,  "Weapon"},    //weapon    (4)
};



int main() {
	srand(time(NULL));

    int ch= 0;                // input buffer
    int direction;

    Person user;
    World game;
	game.GenerateMap();


	int row,col;       		    // to store the number of rows columns of the screen 
    initscr();       			    // start the curses mode
    getmaxyx(stdscr,row,col); // get the number of rows and columns 
    noecho();

    Intro(row, col);
    erase();
    keypad(stdscr, TRUE);     // Initializing keypad



    while((ch=getch())!= 'q'){
        switch(ch){
            case KEY_UP: direction= 2; 
                mvprintw(row/2,col/2,"The up key was pressed");
                break;
            case KEY_DOWN: direction= 3;
                mvprintw(row/2,col/2,"The down key was pressed");
                break;
            case KEY_RIGHT: direction= 1;
                mvprintw(row/2,col/2,"The right key was pressed");
                break;
            case KEY_LEFT: direction= 0;
                mvprintw(row/2,col/2,"The left key was pressed");
                break;
        }
  }
    
  endwin(); 
    
    /*
    cout << user.getXLoc();
    user.moveRight();
    cout << user.getXLoc();
`	*/
    
    return 0;
}



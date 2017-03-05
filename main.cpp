
/*
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

int main() {
	srand(time(NULL));
    Person user;
    World game;
	game.GenerateMap();
    
    
    cout << "HI";
    
    cout << user.getXLoc();
    user.moveRight();
    cout << user.getXLoc();

    
    return 0;
}

*/

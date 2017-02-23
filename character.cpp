/*
 * character.cpp
 *
 *  Created on: Feb 10, 2017
 *      cpp file for character class
 */

#include "character.h"

Character::Character() {			//default constructor
    health=10;				//measure of character health (10=max)
    xLocation = 0;			//get x location
    yLocation = 0;			//get ylocation
    zLocation = 0;			//get zLocation
}
Character::Character(Character& old) {	//copy constructor
    health=old.health;
    xLocation=old.xLocation;
    yLocation=old.yLocation;
    zLocation=old.zLocation;
}
void Character::injured(int n) {		//decrement health if injured
    health-=n;
}
int Character::getHealth() {			//return health
    if (health<0) {
        health=0;						//can't display negative health
    }
    return health;
}
int Character::getXLoc() {				//get x location of character
    return xLocation;
}
int Character::getYLoc() {				//get y location of character
    return yLocation;
}
int Character::getZLoc() {				//get z location of character
    return zLocation;
}
void Character::run() {					//if run away from monster
    //run
}
void Character::setLoc(int x, int y, int z) {	//set location of character
    xLocation=x;
    yLocation=y;
    zLocation=z;
}
bool Character::isDead() {				//return true if dead
    if (health<=0)
        return true;
    return false;
}

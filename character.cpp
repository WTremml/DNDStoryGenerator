/*
 * character.cpp
 *
 *  Created on: Feb 10, 2017
 *      cpp file for character class
 */

#include "character.h"

Character::Character() {			//default constructor
    health=100;						//measure of character health
    xLocation = -1;			//get x location
    yLocation = -1;			//get ylocation
    zLocation = -1;			//get zLocation
}
Character::Character(Character& old) {	//copy constructor
    health=old.health;
    xLocation=old.xLocation;
    yLocation=old.yLocation;
    zLocation=old.zLocation;

}
void Character::injured(int damage) {	//decrement health if injured
    health-=damage;
}
int Character::getHealth() {			//return health
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
void Character::setLoc(int x, int y, int z) {	//set location of character
	xLocation=x;
	yLocation=y;
	zLocation=z;

}
bool Character::isDead() {				//return true if dead
    if (health<=0) {
        health=0;
        return true;
    }
    return false;
}
void Character::setHealth(int h) {      //set health
    health=h;
}
void Character::moveRight() {           //control character location on screen
    xLocation++;
}
void Character::moveLeft() {
    xLocation--;
}
void Character::moveUp() {
    yLocation++;
}
void Character::moveDown() {
    yLocation--;
}
void Character::climbUp() {
    zLocation++;
}
void Character::climbDown() {
    zLocation--;
}

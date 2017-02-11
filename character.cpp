/*
 * character.cpp
 *
 *  Created on: Feb 10, 2017
 *      cpp file for character class
 */

#include "character.h"

Character::Character() {			//default constructor
	health=100;						//measure of character health
	xLocation = 0;			//get x location
	yLocation = 0;			//get ylocation
}
Character::Character(Character& old) {	//copy constructor
	health=old.health;
	xLocation=0;
	yLocation=0;
}
void Character::injured() {				//decrement health if injured
	health-=10;
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
void Character::fight() {				//if fight monster
	//fight 
}
void Character::run() {					//if run away from monster
	//run 
}
void Character::setLoc(int x, int y) {	//set location of character
	xLocation=x;
	yLocation=y;
}
bool Character::isDead() {				//return true if dead
	if (health==0)
		return true;
	return false;
}

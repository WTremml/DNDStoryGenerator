/*
 * monster.cpp
 *
 *  Created on: Feb 11, 2017
 *      cpp file for monster class
 */

#include "characterHeaders.h"

Monster::Monster() {		//default constructor
	xLocation=0;			//xLocation of monster
	yLocation=0;			//yLocation of monster
	aggressive=100;			//how aggressive monster is
	wandering=0;			//whether monster moves or not
	health=100;				//health of monster
}
Monster::Monster(int wander, int agg, int x, int y) {
	xLocation=x;
	yLocation=y;
	aggressive=agg;
	wandering=wander;
	health=100;
}
Monster::Monster(Monster& old){	//copy constructor
	xLocation=old.xLocation;
	yLocation=old.yLocation;
	aggressive=old.aggressive;
	wandering=old.wandering;
	health=old.health;
}

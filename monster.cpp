/*
 * monster.cpp
 *
 *  Created on: Feb 11, 2017
 *      cpp file for monster class
 */

#include "monster.h"

Monster::Monster() {		//default constructor
    xLocation=0;			//xLocation of monster
    yLocation=0;			//yLocation of monster
<<<<<<< HEAD
    zLocation=0;			//zLocation of monster
=======
    zLocation=0;
>>>>>>> master
    aggressive=rand()%101;	//how aggressive monster is 0-100
    wandering=rand()%101;	//whether monster moves or not on 0-100 scale
    health=10;				//health of monster
    type=rand()%2;			//type of monster (0=small, 1=big)
}
Monster::Monster(int type1, int wander, int agg, int x, int y, int z) {
    type=type1;
    xLocation=x;
    yLocation=y;
    zLocation=z;
    aggressive=agg;
    wandering=wander;
    health=10;
}
Monster::Monster(Monster& old) {	//copy constructor
    type=old.type;
    xLocation=old.xLocation;
    yLocation=old.yLocation;
    zLocation=old.zLocation;
    aggressive=old.aggressive;
    wandering=old.wandering;
    health=old.health;
}
int Monster::getType() {			//get type of monster
    return type;
<<<<<<< HEAD
}
int Monster::getAggressive() {		//get how aggressive
    return aggressive;
}
int Monster::getPower() {			//get how often hurt person fighting monster
    if (type==0) 		//if small monster
        return 4;			//person hurt 25% of time when fighting
    else
        return 2;			//person hurt 50% of time when fighting
=======

>>>>>>> master
}

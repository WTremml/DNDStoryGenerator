/*
 * monster.h
 *
 *  Created on: Feb 11, 2017
 *      header file for monster class
 *      	extends character class
 */

#ifndef MONSTER_H
#define MONSTER_H

#include "character.h"

class Monster: public Character {
private:
<<<<<<< HEAD
    int aggressive;			//how aggressive monster is
    int wandering;			//whether monster moves or not
    int type;				//0 if small, 1 if big monster
public:
    Monster();				//default constructor
    Monster(int type, int wander, int agg, int x, int y, int z);
    Monster(Monster& old);	//copy constructor
    ~Monster() {}			//destructor
    int getType();			//get type of monster
=======
	int aggressive;			//how aggressive monster is
	int wandering;			//whether monster moves or not
	int type;				//0 if small, 1 if big monster
public:
	Monster();				//default constructor
	Monster(int type, int wander, int agg, int x, int y, int z);
	Monster(Monster& old);	//copy constructor
	~Monster() {}			//destructor
	int getType();			//get type of monster
>>>>>>> origin/master
};

#endif

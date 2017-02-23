/*
 * weapon.cpp
 *
 *  Created on: Feb 10, 2017
 *      cpp file for weapon class
 */

#include "weapon.h"

Weapon::Weapon() {					//default constructor
<<<<<<< HEAD
    wName = sword;	//type of weapon
    weight = 3;		//weight of weapon
    damage = 3;		//how much damage each hit of weapon inflicts
    xLocation=yLocation=zLocation=0;	//set original location as (0,0,0)
}
Weapon::Weapon(int wName1, int x, int y, int z) {
    wName=wName1;
    xLocation=x;
    yLocation=y;
    zLocation=z;
    
    //if sword
    if (wName==sword) {
        weight=3;
        damage=3;
    }
    //if bow
    else if (wName==bow) {
        weight=1;
        damage=2;
    }
    //if spear
    else if (wName==spear) {
        weight=2;
        damage=3;
    }
    //if poison
    else if (wName==poison) {
        weight=1;
        damage=1;
    }
    //if fireball
    else if (wName==fireball) {
        weight=1;
        damage=3;
    }
    //if no weapon in space in bag
    else if (wName==empty) {
        weight=0;
        damage=0;
    }
    //if no weapon in space in bag
    else if (wName==medicine) {
        weight=1;
        damage=0;
        //treat medicine like weapon in bag, BUT:
        //restrict so user cannot fight monster with medicine
    }
}
Weapon::Weapon(Weapon& old){		//copy constructor
    wName=old.wName;
    weight=old.weight;
    damage=old.damage;
    xLocation=old.xLocation;
    yLocation=old.yLocation;
    zLocation=old.zLocation;
=======
	wName = sword;	//type of weapon
	weight = 3;		//weight of weapon
	damage = 3;		//how much damage each hit of weapon inflicts

	xLocation=yLocation=zLocation=0;	//set original location as (0,0,0)
}
Weapon::Weapon(int wName1, int x, int y, int z) {
	wName=wName1;
	xLocation=x;
	yLocation=y;
	zLocation=z;


	//if sword
	if (wName==sword) {
		weight=3;
		damage=3;
	}
	//if bow
	else if (wName==bow) {
		weight=1;
		damage=2;
	}
	//if spear
	else if (wName==spear) {
		weight=2;
		damage=3;
	}

	//if poison
	else if (wName==poison) {

		weight=1;
		damage=1;
	}
	//if fireball
	else if (wName==fireball) {
		weight=1;
		damage=3;
	}
	//if no weapon in space in bag
	else if (wName==empty) {
		weight=0;
		damage=0;
	}

	//if no weapon in space in bag
	else if (wName==medicine) {
		weight=1;
		damage=0;
		//treat medicine like weapon in bag, BUT:
			//restrict so user cannot fight monster with medicine
	}

}
Weapon::Weapon(Weapon& old){		//copy constructor
	wName=old.wName;
	weight=old.weight;
	damage=old.damage;

	xLocation=old.xLocation;
	yLocation=old.yLocation;
	zLocation=old.zLocation;

>>>>>>> origin/master
}
int Weapon::getWeight() {			//return weight
    return weight;
}
int Weapon::getDamage() {			//return damage inflicts
    return damage;
}
int Weapon::getType() {				//return type of weapon
    return wName;
}
<<<<<<< HEAD
void Weapon::reset(int wN, int x, int y, int z) {		//reset weapon
    wName=wN;
    xLocation=x;
    yLocation=y;
    zLocation=z;
    
    //if sword
    if (wName==sword) {
        weight=3;
        damage=3;
    }
    //if bow
    else if (wName==bow) {
        weight=1;
        damage=2;
    }
    //if spear
    else if (wName==spear) {
        weight=2;
        damage=3;
    }
    //if poison
    else if (wName==poison) {
        weight=1;
        damage=1;
    }
    //if fireball
    else if (wName==fireball) {
        weight=1;
        damage=3;
    }
    //if no weapon in space in bag
    else if (wName==empty) {
        weight=0;
        damage=0;
    }
    //if medicine
    else if (wName==medicine) {
        weight=1;
        damage=0;
    }
}
void Weapon::reset(Weapon w) {	//change type of weapon in bag
    wName=w.getType();
    weight=w.getWeight();
    damage=w.getDamage();
    xLocation=w.getX();
    yLocation=w.getY();
    zLocation=w.getZ();
}
int Weapon::getX() {	//get xLocatoin
    return xLocation;
}
int Weapon::getY() {	//get yLocatoin
    return yLocation;
}
int Weapon::getZ() {	//get zLocatoin
    return zLocation;
}
void Weapon::setLoc(int x, int y, int z) {	//set weapon location
    xLocation=x;
    yLocation=y;
    zLocation=z;			//if loc irrelevant, set as (-1, -1, -1)
=======

void Weapon::reset(int wN, int x, int y, int z) {		//reset weapon
	wName=wN;
	xLocation=x;
	yLocation=y;
	zLocation=z;


	//if sword
	if (wName==sword) {
		weight=3;
		damage=3;
	}
	//if bow
	else if (wName==bow) {
		weight=1;
		damage=2;
	}
	//if spear
	else if (wName==spear) {
		weight=2;
		damage=3;
	}

	//if poison
	else if (wName==poison) {

		weight=1;
		damage=1;
	}
	//if fireball
	else if (wName==fireball) {
		weight=1;
		damage=3;
	}
	//if no weapon in space in bag
	else if (wName==empty) {
		weight=0;
		damage=0;
	}

	//if medicine
	else if (wName==medicine) {
		weight=1;
		damage=0;
	}

}
void Weapon::reset(Weapon w) {	//change type of weapon in bag
	wName=w.getType();
	weight=w.getWeight();
	damage=w.getDamage();

	xLocation=w.getX();
	yLocation=w.getY();
	zLocation=w.getZ();
}
int Weapon::getX() {	//get xLocatoin
	return xLocation;
}
int Weapon::getY() {	//get yLocatoin
	return yLocation;
}
int Weapon::getZ() {	//get zLocatoin
	return zLocation;
}
void Weapon::setLoc(int x, int y, int z) {	//set weapon location
	xLocation=x;
	yLocation=y;
	zLocation=z;			//if loc irrelevant, set as (-1, -1, -1)

>>>>>>> origin/master
}

/*
 * weapon.cpp
 *
 *  Created on: Feb 10, 2017
 *      cpp file for weapon class
 */

#include "weapon.h"

Weapon::Weapon() {					//default constructor
    damage = 3;		//how much damage each hit of weapon inflicts
}
Weapon::Weapon(int x, int y, int z) {
    Item::setLoc(x,y,z);
    damage=3;
}
Weapon::Weapon(Weapon& old){		//copy constructor
    damage=old.damage;
}
int Weapon::getDamage() {			//return damage inflicts
    return damage;
}
void Weapon::enhance() {		//reset weapon
    //increases damage capability of weapon
    damage++;
}



/*
 * weapon.h
 *
 *  Created on: Feb 10, 2017
 *      header file for weapon class
 */
#ifndef WEAPON_H
#define WEAPON_H



#include "item.h"

class Weapon: public Item {
private:
    int damage;		//how much damage each hit of weapon inflicts
public:
    Weapon(); 				//default constructor
    Weapon(int x, int y, int z);
    Weapon(Weapon& old);	//copy constructor
    ~Weapon(){}				//destructor
    
    int getDamage();		//return damage weapon inflicts
    void enhance();         //enhance current weapon
};
#endif

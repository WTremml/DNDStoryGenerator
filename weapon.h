/*
 * weapon.h
 *
 *  Created on: Feb 10, 2017
 *      header file for weapon class
 */
#ifndef WEAPON_H
#define WEAPON_H

#include <string>
#include <iostream>
using namespace std;

class Weapon {
private:
    int weight;		//weight of weapon
    int wName;		//type of weapon (0-sword, 1-bow, 2-spear, etc)
    int damage;		//how much damage each hit of weapon inflicts
    int xLocation;	//xLocation on map
    int yLocation;	//yLocation on map
    int zLocation;	//zLocation on map
    int usesLeft;	//how many times can use weapon
public:
    enum type {sword, bow, spear, poison, fireball, empty, medicine};
    Weapon(); 				//default constructor
    Weapon(int wName1, int x, int y, int z);
    Weapon(Weapon& old);	//copy constructor
    ~Weapon(){}				//destructor
    
    int getWeight();			//return weight
    int getDamage();			//return damage inflicts
    int getType();				//return type of weapon
    void reset(int type, int x, int y, int z);	//change type of weapon
    void reset(Weapon w);		//change type of weapon given weapon
    
    int getX();							//get xLocation
    int getY();							//get yLocation
    int getZ();							//get zLocation
    int getUses();						//get how many uses left
    
    void setLoc(int x, int y, int z);	//set location
    void used();						//weapon used - decrease uses left by 1
    void setUses(int uses);				//set usesLeft
};
#endif

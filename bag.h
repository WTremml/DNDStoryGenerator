/*
 * bag.h
 *
 *  Created on: Feb 10, 2017
 *     header file for bag class
 *     		contains array of weapon classes
 */

#ifndef BAG_H
#define BAG_H

#include "weapon.h"

class Bag {
private:
    Weapon bag1[10];		//bag is array of weapons
    int bagSize;			//max capactiy of bag
    int carrying;			//number nonempty items in bag
public:
    Bag();						//default constructor
    Bag(Weapon* bag2);			//parameterized constructor
    Bag(Bag& old);				//copy constructor
    ~Bag() {}					//destructor
    int getWeight();			//get weight of items in bag
    int getSize();				//get size of bag
    int getItemNum();			//get number of non-empty items in bag
    void addWeapon(Weapon w);	//add item w to bag
    void dropWeapon(Weapon w);	//drop item w from bag
    Weapon getW(int index);		//get weapon in index in bag1 array
    void print();				//prints out types of all weapons in bag in order
};
#endif

/*
 * bag.h
 *
 *  Created on: Feb 10, 2017
 *     header file for bag class
 */

#ifndef BAG_H
#define BAG_H

#include "weapon.h"
#include "potion.h"
#include "gold.h"
#include "key.h"

#include <iostream>
using namespace std;

class Bag {
private:
    int goldCount;              //infinite amount of gold possible -> weight=value
    int potionCount;
    int keyCount;               //either has 0 or 1 key at any time
public:
    Bag();						//default constructor
    Bag(Bag& old);				//copy constructor
    ~Bag() {}					//destructor
    
    int getGoldC();             //get count of gold in bag
    int getPotionC();           //get count of potions in bag
    int getKeyC();              //get count of keys in bag
    
    void useGold(int used);     //use gold
    void usePotion();           //use potion
    void useKey();              //use key
    
    Bag& operator=(Bag& rhs);   //overload = sign in terms of bag
    
    void print();				//prints out types of all in bag in order
    
    void findGold();            //find gold
    void findPotion();          //find potion
    void findKey();             //find key
};

#endif

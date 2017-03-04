/*
 * bag.cpp
 *
 *  Created on: Feb 10, 2017=
 *      cpp for bag class
 */

#include "bag.h"

Bag::Bag() {					//default constructor
    goldCount=0;
    potionCount=0;
    keyCount=0;
}
Bag::Bag(Bag& old) {			//copy constructor
    goldCount=old.goldCount;
    potionCount=old.potionCount;
    keyCount=old.keyCount;
}
int Bag::getGoldC() {             //get count of gold in bag
    return goldCount;
}
int Bag::getPotionC() {           //get count of potions in bag
    return potionCount;
}
int Bag::getKeyC() {              //get count of keys in bag
    return keyCount;
}

void Bag::useGold(int used) {     //use gold
    goldCount-=used;
}
void Bag::usePotion() {          //use potion
    potionCount--;
}
void Bag::useKey() {              //use key
    keyCount--;
}
Bag& Bag::operator=(Bag& rhs) { //overload =
    goldCount=rhs.goldCount;
    potionCount=rhs.potionCount;
    keyCount=rhs.keyCount;
    
    return *this;
}
void Bag::print() {				//print out bag
    cout << "Gold: " << goldCount << endl;
    cout << "Potions: " << potionCount << endl;
    cout << "Keys: " << keyCount << endl;
    cout << endl;
}
void Bag::findGold() {            //find gold
    goldCount++;
}
void Bag::findPotion() {          //find potion
    potionCount++;
}
void Bag::findKey() {             //find key
    keyCount++;
}

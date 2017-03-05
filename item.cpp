//
//  item.cpp
//  
//
//  Created by Emily Chao on 3/1/17.
//
//

#include "item.h"

///////////////////////////////////////////////////////////////////
Item::Item() {            //default constructor
    xLocation=-1;
    yLocation=-1;
    zLocation=-1;
}
Item::Item(Item& old) {   //copy constructor
    xLocation=old.xLocation;
    yLocation=old.yLocation;
    zLocation=old.zLocation;
}
int Item::getX() {						//get xLocation
    return xLocation;
}
int Item::getY() {                        //get yLocation
    return yLocation;
}
int Item::getZ() {                        //get zLocation
    return zLocation;
}
void Item::setLoc(int x, int y, int z) {	//set location
    xLocation=x;
    yLocation=y;
    zLocation=z;			//if loc irrelevant, set as (-1, -1, -1)
}

///////////////////////////////////////////////////////////////////
Weapon::Weapon() {                  //default constructor
    damage = 3;     //how much damage each hit of weapon inflicts
}
Weapon::Weapon(int x, int y, int z) {
    Item::setLoc(x,y,z);
    damage=3;
}
Weapon::Weapon(Weapon& old){        //copy constructor
    damage=old.damage;
}
int Weapon::getDamage() {           //return damage inflicts
    return damage;
}
void Weapon::enhance() {        //reset weapon
    //increases damage capability of weapon
    damage++;
}

///////////////////////////////////////////////////////////////////
Key::Key() {             //constructor
    weight=1;
}
Key::Key(Key& old) {     //copy constructor
    weight=old.weight;
}
int Key::getWeight() {   //getter for weight
    return weight;
}

///////////////////////////////////////////////////////////////////
Gold::Gold() {                //constructor
    weight=1;
}
Gold::Gold(Gold& old) {       //copy constructor
    weight=old.weight;
}
int Gold::getWeight() {       //getter for weight
    return weight;
}

///////////////////////////////////////////////////////////////////
Potion::Potion() {          //constructor
    healingPower=50;
    weight=5;
}
Potion::Potion(Potion& old) {   //copy constructor
    healingPower=old.healingPower;
    weight=old.weight;
}
int Potion::getHealingPow() {   //getter for healing power
    return healingPower;
}
void Potion::setHealPow(int heal) {  //set healing power
    healingPower=heal;
}
int Potion::getWeight() {           //getter for weight
    return weight;
}
void Potion::setWeight(int w) {      //set weight
    weight=w;
}

///////////////////////////////////////////////////////////////////
Bag::Bag() {                    //default constructor
    goldCount=0;
    potionCount=0;
    keyCount=0;
}
Bag::Bag(Bag& old) {            //copy constructor
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
void Bag::print() {             //print out bag
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
/*
 * person.cpp
 *
 *  Created on: Feb 11, 2017
 *      Author: emilychao
 */

#include "person.h"

Person::Person() {			//default constructor
<<<<<<< HEAD
    name="Character";				//user names character for story output
    male=true;						//T if male, F if female
    weightMax=20;					//max weight they can carry
    health=100;						//measure of character health
    cooperative==rand()%101;	//spectrum of how cooperative character is (high=coop) 0-100
    aggressive==rand()%101; 	//spectrum of how aggressive character is (high=aggress) 0-100
    bagSize=bag1.getSize();	//get bagSize
    xLocation = 0;			//get x location
    yLocation = 0;			//get ylocation
    zLocation = 0;			//get zlocation
}
Person::Person(string name1, bool male1, int coop, int agg, int x, int y, int z) {
    name=name1;
    male=male1;
    weightMax=20;
    health=100;
    cooperative=coop;
    aggressive=agg;
    bagSize=bag1.getSize();
    xLocation=x;
    yLocation=y;
    zLocation=z;
}
Person::Person(Person& old) {	//copy constructor
    name=old.name;
    male=old.male;
    weightMax=old.weightMax;
    health=old.health;
    cooperative=old.cooperative;
    aggressive=old.aggressive;
    bagSize=old.bagSize;
    bag1=old.bag1;
    xLocation=old.xLocation;
    yLocation=old.yLocation;
    zLocation=old.zLocation;
}
void Person::healed() {				//increment health if healed
    health+=10;
}
int Person::getCoop() {				//return how cooperative
    return cooperative;
}
int Person::getAggress() {			//return how aggressive
    return aggressive;
}
void Person::foundMonster() {		//if encounter monster
    //will they fight or not?
}
void Person::foundCharacter() {		//if find another character
    //will they collaborate or not?
}
void Person::addWeapon(Weapon w) {	//add weapon to bag
    if (bag1.getWeight()<=20)
        bag1.addWeapon(w);
    else
        cout << "Bag at max weight. Cannot add weapon." << endl;
}
void Person::dropWeapon(Weapon w) {	//drop weapon from bag
    bag1.dropWeapon(w);
}
Bag Person::getBag() {				//return copy of bag
    Bag bag2;
    bag2=bag1;
    return bag2;
=======
	name="Character";				//user names character for story output
	male=true;						//T if male, F if female
	weightMax=20;					//max weight they can carry
	health=100;						//measure of character health
	cooperative==rand()%101;	//spectrum of how cooperative character is (high=coop) 0-100
	aggressive==rand()%101; 	//spectrum of how aggressive character is (high=aggress) 0-100
	bagSize=bag1.getSize();	//get bagSize
	xLocation = 0;			//get x location
	yLocation = 0;			//get ylocation
	zLocation = 0;			//get zlocation
}
Person::Person(string name1, bool male1, int coop, int agg, int x, int y, int z) {
	name=name1;
	male=male1;
	weightMax=20;
	health=100;
	cooperative=coop;
	aggressive=agg;
	bagSize=bag1.getSize();
	xLocation=x;
	yLocation=y;
	zLocation=z;
}
Person::Person(Person& old) {	//copy constructor
	name=old.name;
	male=old.male;
	weightMax=old.weightMax;
	health=old.health;
	cooperative=old.cooperative;
	aggressive=old.aggressive;
	bagSize=old.bagSize;
	bag1=old.bag1;
	xLocation=old.xLocation;
	yLocation=old.yLocation;
	zLocation=old.zLocation;
}
void Person::healed() {				//increment health if healed
	health+=10;
}
int Person::getCoop() {				//return how cooperative
	return cooperative;
}
int Person::getAggress() {			//return how aggressive
	return aggressive;
}
void Person::foundMonster() {		//if encounter monster
	//will they fight or not?
}
void Person::foundCharacter() {		//if find another character
	//will they collaborate or not?
}
void Person::addWeapon(Weapon w) {	//add weapon to bag
	if (bag1.getWeight()<=20)
		bag1.addWeapon(w);
	else
		cout << "Bag at max weight. Cannot add weapon." << endl;
}
void Person::dropWeapon(Weapon w) {	//drop weapon from bag
	bag1.dropWeapon(w);
}
Bag Person::getBag() {				//return copy of bag
	Bag bag2;
	bag2=bag1;
	return bag2;
>>>>>>> origin/master
}

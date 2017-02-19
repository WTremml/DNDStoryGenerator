/*
 * bag.cpp
 *
 *  Created on: Feb 10, 2017=
 *      cpp for bag class to hold array of weapons
 */

#include "bag.h"

	Weapon* bag1;			//bag is array of weapons
	int bagSize;			//max capactiy of bag
	int carrying;			//number nonempty items in bag


Bag::Bag() {					//default constructor
	bagSize=10;
	for (int i=0; i<bagSize; i++) {					//bag is array of weapons

		bag1[i].reset(Weapon::empty, -1, -1, -1);	//set bag as empty
	}
	carrying=0;
}
Bag::Bag(Weapon bag2[10]) {	//parameterized constructor
	bagSize=10;
	carrying=0;
	for (int i=0; i<bagSize; i++) {					//bag is array of weapons
		bag1[i].reset(bag2[i]);						//set weapon as passed in parameter
		if (bag1[i].getType() !=5) {
			carrying++;								//increase carrying if nonempty weapon
		}
	}
}
Bag::Bag(Bag& old) {			//copy constructor
	bagSize=old.bagSize;
	for (int i=0; i<bagSize; i++) {					//bag is array of weapons
		bag1[i].reset(old.bag1[i]);						//set bag as same as old bag
	}
	carrying=old.carrying;
}
int Bag::getWeight() {		//get weight of items in bag
	int weight1=0;
	for (int i=0; i<bagSize; i++) {
		weight1+=bag1[i].getWeight();
	}
	return weight1;				//return sum of weight of bag
}
int Bag::getSize() {		//get size of bag
	return bagSize;
}
int Bag::getItemNum() {		//get number of non-empty items in bag
	return carrying;
}
void Bag::addWeapon(Weapon w) {	//add item w to bag
	bool end=false;
	for (int i=0; i<bagSize && !end; i++) {
		if (bag1[i].getType() == Weapon::empty) {		//if slot in bag empty
			bag1[i]=w;									//fill slot with weapon w
			end=true;
			carrying++;									//bag holds one more item
		}
	}
}
void Bag::dropWeapon(Weapon w) {	//drop item w from bag
	bool end=false;
	for (int i=0; i<bagSize && !end; i++) {
		if (bag1[i].getType() == w.getType()) {			//if weapon is w
			bag1[i].reset(Weapon::empty, -1, -1, -1);	//make weapon slot empty in bag
			end=true;
		}
		carrying--;								//bag holds one less item
	}
}
Weapon Bag::getW(int index) {		//return weapon in index
	Weapon temp;
	temp=bag1[index];
	return temp;
}
void Bag::print() {				//print out bag
	for (int i=0; i<bagSize; i++) {
		cout << bag1[i].getType() << " ";
	}
	cout << endl;
}

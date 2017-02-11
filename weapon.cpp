/*
 * weapon.cpp
 *
 *  Created on: Feb 10, 2017
 *      cpp file for weapon class
 */

#include "weapon.h"

Weapon::Weapon() {					//default constructor
	wName = sword;	//type of weapon
	weight = 3;		//weight of weapon
	damage = 3;		//how much damage each hit of weapon inflicts
}
Weapon::Weapon(int wName1) {		//parameterized constructor
	wName=wName1;
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
	//if potion
	else if (wName==potion) {
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
}
Weapon::Weapon(Weapon& old){		//copy constructor
	wName=old.wName;
	weight=old.weight;
	damage=old.damage;
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
void Weapon::reset(int wN) {		//reset weapon type
	wName=wN;
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
	//if potion
	else if (wName==potion) {
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
}
void Weapon::reset(Weapon w) {	//change type of weapon in bag
	wName=w.getType();
	weight=w.getWeight();
	damage=w.getDamage();
}

/*
 * characterHeaders.h
 *
 *  Created on: Feb 11, 2017
 *      header file for monster class and person class
 *      	extends character class
 */
#include "character.h"
#include "bag.h"

class Monster: public Character {
private:
	int aggressive;			//how aggressive monster is
	int wandering;			//whether monster moves or not
public:
	Monster();				//default constructor
	Monster(int wander, int agg, int x, int y);
	Monster(Monster& old);	//copy constructor
	~Monster() {}			//destructor
};

class Person: public Character {
private:
	string name;		//user names character for story output
	bool male;		//T if male, F if female
	int weightMax;		//max weight they can carry
	int cooperative;	//spectrum of how cooperative character is (high=coop)
	int aggressive; 	//spectrum of how aggressive character is (high=aggress)
	Bag bag1;			//bag class is array of weapons
	int bagSize;		//size of bag
public:
	Person();				//default constructor
	Person(string name, bool male, int coop, int agg, int x, int y);
	Person(Person& old);	//copy constructor
	~Person() {}				//destructor

	void healed();				//increment health if healed
	int getCoop();				//return how cooperative
	int getAggress();			//return how aggressive
	Bag getBag();				//return copy of bag

	void foundMonster();		//if encounter monster
	void foundCharacter();		//if find another character

	void addWeapon(Weapon w);	//add weapon to bag
	void dropWeapon(Weapon w);	//drop weapon from bag
};

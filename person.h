/*
<<<<<<< HEAD
=======

>>>>>>> origin/master
 * person.h
 *
 *  Created on: Feb 14, 2017
 *      header file for person class
 *      	extends character class
 */
#ifndef PERSON_H
#define PERSON_H
<<<<<<< HEAD

#include "character.h"
#include "bag.h"

class Person: public Character {
private:
    string name;		//user names character for story output
    bool male;			//T if male, F if female
    int weightMax;		//max weight they can carry
    int cooperative;	//spectrum of how cooperative character is (high=coop)
    int aggressive; 	//spectrum of how aggressive character is (high=aggress)
    Bag bag1;			//bag class is array of weapons
    int bagSize;		//size of bag
public:
    Person();				//default constructor
    Person(string name, bool male, int coop, int agg, int x, int y, int z);
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

=======

#include "character.h"
#include "bag.h"

class Person: public Character {
private:
	string name;		//user names character for story output
	bool male;			//T if male, F if female
	int weightMax;		//max weight they can carry
	int cooperative;	//spectrum of how cooperative character is (high=coop)
	int aggressive; 	//spectrum of how aggressive character is (high=aggress)
	Bag bag1;			//bag class is array of weapons
	int bagSize;		//size of bag
public:
	Person();				//default constructor
	Person(string name, bool male, int coop, int agg, int x, int y, int z);
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

>>>>>>> origin/master
#endif

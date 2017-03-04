/*
 * person.h
 *
 *  Created on: Feb 14, 2017
 *      header file for person class
 *      	extends character class
 */
#ifndef PERSON_H
#define PERSON_H

#include "character.h"
#include "bag.h"
#include "magic.h"
#include "monster.h"

class Person: public Character {
private:
    string name;		//user names character for story output
    Bag bag1;			//bag class contains gold, potions, keys
    
    Weapon w;           //each character starts with basic weapon
    Magic m;            //each character starts with basic magic skill
    
public:
    Person();				//default constructor
    Person(string name, int mag, int x, int y, int z);
    Person(Person& old);	//copy constructor
    ~Person() {}				//destructor
    
    void healed();				//increment health if healed
    Bag getBag();				//return copy of bag
    
    bool found(int x, int y, int z);    //returns true if item 'found'
    void foundMonster(Monster m);	//if encounter monster
    void foundCharacter();          //if find another character
    void foundPotion(Potion p);             //if find potion
    void foundKey(Key k);                //if find key
    void foundGold(Gold g);               //if find gold
    void useKey();             //use key
    void usePotion();          //use potion
    void useGold(int g);       //use gold
    
    void fight(Monster m);      //fight monster
    void run(Monster m);        //run from monster

};

#endif

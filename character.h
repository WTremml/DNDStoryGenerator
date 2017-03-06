/*
 * character.h
 *
 *  Created on: Feb 10, 2017
 *      header file for character, person, and monster classes
 *
 *  Emily Chao
 */

#ifndef CHARACTER_H
#define CHARACTER_H

#include <cstdlib>
#include <iostream>
#include "item.h"
#include "magic.h"
using namespace std;

///////////////////////////////////////////////////////////////////
class Character {
protected:
    int health;			//measure of character health
    int xLocation;		//get x location
    int yLocation;		//get y location
    int zLocation;
public:
    Character();				//default constructor
    Character(Character& old);	//copy constructor
    ~Character() {}				//destructor
    
    void injured(int damage);	//decrement health if injured
    int getHealth();			//return health
    int getXLoc();				//get x location of character
    int getYLoc();				//get y location of character
    int getZLoc();				//get y location of character
    void setHealth(int h);      //set new health

    void setLoc(int x, int y, int z);	//set location of character
    bool isDead();				//returns true if health=0
    
    void moveRight();           //control character location on screen
    void moveLeft();
    void moveUp();
    void moveDown();
    void climbUp();
    void climbDown();
};

///////////////////////////////////////////////////////////////////
class Monster: public Character {
private:
    int aggressive;         //how aggressive monster is
    int wandering;          //whether monster moves or not
    int type;               //0 if small, 1 if big monster
public:
    Monster();              //default constructor
    Monster(int type, int wander, int agg, int x, int y, int z);
    Monster(Monster& old);  //copy constructor
    ~Monster() {}           //destructor
    int getType();          //get type of monster
    int getDamage();        //get damage capability of monster
    int getAggressive();    //get aggressive
    int getWander();        //get wandering
    
    void fight(Monster m);  //fight other monsters
    void foundMonster(Monster m);   //found another monster
};

///////////////////////////////////////////////////////////////////
class Person: public Character {
private:
    string name;        //user names character for story output
    Bag bag1;           //bag class contains gold, potions, keys
    
    Weapon w;           //each character starts with basic weapon
    Magic m;            //each character starts with basic magic skill
    
public:
    Person();               //default constructor
    Person(string name, int mag, int x, int y, int z);
    Person(Person& old);    //copy constructor
    ~Person() {}                //destructor
    
    void healed();              //increment health if healed
    Bag getBag();               //return copy of bag
    
    bool found(int x, int y, int z);    //returns true if item 'found'
    void foundMonster(Monster m);   //if encounter monster
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

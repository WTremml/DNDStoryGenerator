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
    Monster(int type);
    Monster(Monster& old);  //copy constructor
    ~Monster() {}           //destructor
    int getType();          //get type of monster
    int getDamage();        //get damage capability of monster
    int getAggressive();    //get aggressive
    int getWander();        //get wandering
    
    void fight(Monster m, int row, int col);  //fight other monsters
    void foundMonster(Monster m, int row, int col);   //found another monster
};
///////////////////////////////////////////////////////////////////
class Dummy: public Character {
private:
    Bag bag1;           //bag class contains gold, potions, keys
    int gift;           //each dummy can either give weapon or armor enhancements
                            //0-weapon 1-armor
    int cooperative;    //how cooperative the Dummy is
    int goldC;          //how much gold Dummy has
public:
    Dummy();               //default constructor
    Dummy(int gift1, int x, int y, int z);
    Dummy(Dummy& old);     //copy constructor
    ~Dummy() {}                 //destructor
    
    Bag getBag();               //return copy of bag
    
    int getGold();              //getter for gold pieces
    int getCoop();              //getter for cooperative characteristic
    int getGift();              //getter for type of gift
};
///////////////////////////////////////////////////////////////////
class Person: public Character {
private:
    string name;        //user names character for story output
    Bag bag1;           //bag class contains gold, potions, keys
    
    Weapon w;           //each character starts with basic weapon
    Magic m;            //each character starts with basic magic skill
    double armor;       //each character starts with basic armor
    
public:
    Person();               //default constructor
    Person(string name, int mag, int x, int y, int z);
    Person(Person& old);    //copy constructor
    ~Person() {}                //destructor
    
    void healed();              //increment health if healed
    Bag getBag();               //return copy of bag
    
    bool found(int x, int y, int z);    //returns true if item 'found'
    void foundMonster(Monster m, int row, int col);       //if encounter monster
    void foundCharacter(Dummy d, int row, int col);       //if find another character
    bool foundPotion();             //if find potion
    void foundKey();                   //if find key
    void foundGold();                 //if find gold
    void foundWEnhance(int row, int col);           //if find weapon enhancement
    void useKey();             //use key
    void usePotion();          //use potion
    void useGold(int g);       //use gold
    
    void fight(Monster m, int row, int col);      //fight monster
    void fight1(Dummy d, int row, int col);       //fight dummy
    void run(Monster m, int row, int col);        //run from monster
    void upLevel();             //move up level if have key

};


#endif

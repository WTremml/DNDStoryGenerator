/*
 * character.h
 *
 *  Created on: Feb 10, 2017
 *      header file for character class
 */
#include <cstdlib>
#ifndef CHARACTER_H
#define CHARACTER_H

#include <cstdlib>
#ifndef CHARACTER_H
#define CHARACTER_H


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
    
    void injured();				//decrement health if injured
    int getHealth();			//return health
    int getXLoc();				//get x location of character
    int getYLoc();				//get y location of character
    int getZLoc();				//get y location of character
    
    void fight();				//if fight monster
    void run();					//if run away from monster
    
    void setLoc(int x, int y, int z);	//set location of character
    bool isDead();				//returns true if health=0
};

#endif

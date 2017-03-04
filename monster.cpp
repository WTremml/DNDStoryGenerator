/*
 * monster.cpp
 *
 *  Created on: Feb 11, 2017
 *      cpp file for monster class
 */

#include "monster.h"

Monster::Monster() {		//default constructor
    aggressive=rand()%10+1;	//how aggressive monster is 1-10
    wandering=rand()%10+1;	//whether monster moves or not on 1-10 scale
    type=rand()%2;			//type of monster (0=small, 1=big)
}
Monster::Monster(int type1, int wander, int agg, int x, int y, int z) {
    type=type1;
    xLocation=x;
    yLocation=y;
    zLocation=z;
    aggressive=agg;
    wandering=wander;
    health=100;
}
Monster::Monster(Monster& old) {	//copy constructor
    type=old.type;
    aggressive=old.aggressive;
    wandering=old.wandering;
}
int Monster::getType() {			//get type of monster
    return type;
}
int Monster::getDamage() {          //get damage
    if (type==0) {   //if small
        return 3;
    }
    else if (type==1) {   //if big
        return 6;
    }
    return 0;
}
void Monster::foundMonster(Monster m) {         //if monster finds another monster
    if (getAggressive()+m.getAggressive()>10) {    //if total aggression > 10
        fight(m);                                       //two monsters fight each other
    }
}
void Monster::fight(Monster mon) {
    int hurt;
    while (!mon.isDead() && !isDead()) {        //while can fight
        //this monster injured mon during fight
        hurt=rand()%(4-getType());              //mon hurt 1/4 or 1/3 times depending on type of this monster
        if (hurt==0) {
            mon.injured(getDamage());           //mon injured by this monster
        }
        //mon injured this monster during fight
        hurt=rand()%(4-mon.getType());			//get hurt 1/4 or 1/3 times depending on type mon
        if (hurt==0) {
            health-=mon.getDamage();			//lose 3 health point if small, 6 health points if big
        }
    }
    if (!mon.isDead() || !isDead()) {           //if one monster still alive
        cout << "Two monsters just fought! One has been killed." << endl;
    }
    else {                                      //if both monsters die
        cout << "Two monsters fought to the death." << endl;
    }
}
int Monster::getAggressive() {  //get aggressive
    return aggressive;
}
int Monster::getWander() {       //get wandering
    return wandering;
}

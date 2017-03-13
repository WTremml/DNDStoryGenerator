/*
 * Magic.cpp
 *
 *  Created on: March 1, 2017
 *      cpp file for magic class
 *
 *  Emily Chao
 */

#include "magic.h"

//enum type= {speed, strength, heal, none}


Magic::Magic() {    //constructor
    magType=0;
    powerCharge=1;    //power fully charged
}
Magic::Magic(int type) {    //parameterized constructor
    magType=type;
    powerCharge=1;
}
Magic::Magic(Magic& old) {  //copy constructor
    magType=old.magType;
    powerCharge=old.powerCharge;
}
void Magic::setType(int type) {  //set magic type
    magType=type;
}
int Magic::getType() {  //return magic type
    return magType;
}
bool Magic::isCharged() {  //return true if power charged fully
    if (powerCharge==1)
        return true;        //return true if fully charged
    return false;
}
int Magic::getCharge() {    //get powerCharge
    return powerCharge;
}
void Magic::charging() {    //charge magic power
    powerCharge=1;
}
void Magic::usePower() {    //use magic power
    powerCharge=0;
}

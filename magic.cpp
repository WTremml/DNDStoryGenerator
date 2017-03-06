/*
 * Magic.h
 *
 *  Created on: March 1, 2017
 *      header file for magic class
 *
 *  Emily Chao
 */

#include "magic.h"

//enum type= {speed, strength, heal, none}


Magic::Magic() {    //constructor
    magType=0;
    powerCharge=100;    //power fully charged
}
Magic::Magic(int type) {    //parameterized constructor
    magType=type;
    powerCharge=100;
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
    if (powerCharge==100)
        return true;        //return true if fully charged
    return false;
}
int Magic::getCharge() {    //get powerCharge
    return powerCharge;
}
void Magic::charging() {    //charge magic power
    if (powerCharge<100)
        powerCharge++;
}
void Magic::usePower() {    //use magic power
    powerCharge=0;
}

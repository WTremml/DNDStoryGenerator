//
//  potion.cpp
//  
//
//  Created by Emily Chao on 3/1/17.
//
//

#include "potion.h"

Potion::Potion() {          //constructor
    healingPower=50;
    weight=5;
}
Potion::Potion(Potion& old) {   //copy constructor
    healingPower=old.healingPower;
    weight=old.weight;
}
int Potion::getHealingPow() {   //getter for healing power
    return healingPower;
}
void Potion::setHealPow(int heal) {  //set healing power
    healingPower=heal;
}
int Potion::getWeight() {           //getter for weight
    return weight;
}
void Potion::setWeight(int w) {      //set weight
    weight=w;
}

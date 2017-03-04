//
//  potion.h
//  
//
//  Created by Emily Chao on 3/1/17.
//
//

#ifndef POTION_H
#define POTION_H
#include "item.h"

class Potion: public Item {
private:
    int healingPower;
    int weight;
public:
    Potion();          //constructor
    Potion(Potion& old);   //copy constructor
    ~Potion(){}         //destructor
    int getHealingPow();   //getter for healing power
    void setHealPow(int heal);  //set healing power
    int getWeight();            //getter for weight
    void setWeight(int w);      //set weight
    
};
#endif /* POTION_H */

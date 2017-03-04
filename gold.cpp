//
//  gold.cpp
//  
//
//  Created by Emily Chao on 3/1/17.
//
//

#include "gold.h"

Gold::Gold() {                //constructor
    weight=1;
}
Gold::Gold(Gold& old) {       //copy constructor
    weight=old.weight;
}
int Gold::getWeight() {       //getter for weight
    return weight;
}

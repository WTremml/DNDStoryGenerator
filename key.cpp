//
//  key.cpp
//  
//
//  Created by Emily Chao on 3/1/17.
//
//

#include "key.h"

Key::Key() {             //constructor
    weight=1;
}
Key::Key(Key& old) {     //copy constructor
    weight=old.weight;
}
int Key::getWeight() {   //getter for weight
    return weight;
}

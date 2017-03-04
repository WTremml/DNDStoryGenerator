//
//  gold.h
//  
//
//  Created by Emily Chao on 3/1/17.
//
//

#ifndef gold_h
#define gold_h
#include "item.h"

class Gold:public Item {
private:
    int weight;             //weight of one gold piece
public:
    Gold();                //constructor
    Gold(Gold& old);       //copy constructor
    ~Gold(){}               //destructor
    int getWeight();       //getter for weight
};

#endif /* gold_h */

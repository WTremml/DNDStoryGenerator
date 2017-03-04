//
//  key.h
//  
//
//  Created by Emily Chao on 3/1/17.
//
//

#ifndef key_h
#define key_h
#include "item.h"

class Key:public Item {
private:
    int weight;
public:
    Key();            //constructor
    Key(Key& old);    //copy constructor
    ~Key(){}          //destructor
    int getWeight();  //getter for weight
};

#endif /* key_h */

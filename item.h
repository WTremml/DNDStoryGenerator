//
//  item.h
//  
//
//  Created by Emily Chao on 3/1/17.
//
//

#ifndef item_h
#define item_h
#include <string>
#include <iostream>
using namespace std;

class Item {
private:
    int xLocation;	//xLocation on map
    int yLocation;	//yLocation on map
    int zLocation;	//zLocation on map
public:
    Item();            //default constructor
    Item(Item& old);   //copy constructor
    ~Item() {}         //destructor
    int getX();                         //get xLocation
    int getY();                         //get yLocation
    int getZ();                         //get zLocation
    void setLoc(int x, int y, int z);   //set location
};
#endif /* item_h */

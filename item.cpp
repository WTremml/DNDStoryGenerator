//
//  item.cpp
//  
//
//  Created by Emily Chao on 3/1/17.
//
//

#include "item.h"
Item::Item() {            //default constructor
    xLocation=-1;
    yLocation=-1;
    zLocation=-1;
}
Item::Item(Item& old) {   //copy constructor
    xLocation=old.xLocation;
    yLocation=old.yLocation;
    zLocation=old.zLocation;
}
int Item::getX() {						//get xLocation
    return xLocation;
}
int Item::getY() {                        //get yLocation
    return yLocation;
}
int Item::getZ() {                        //get zLocation
    return zLocation;
}
void Item::setLoc(int x, int y, int z) {	//set location
    xLocation=x;
    yLocation=y;
    zLocation=z;			//if loc irrelevant, set as (-1, -1, -1)
}

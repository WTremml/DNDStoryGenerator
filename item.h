/*
 * Item.h
 *
 *  Created on: March 1, 2017
 *      header file for usable item classes (Item, Weapon, Bag, Potion, Gold, Key)
 *
 *  Emily Chao
 */

#ifndef item_h
#define item_h
#include <string>
#include <ncurses.h>

#include <iostream>
using namespace std;


#define DAMAGE 3

///////////////////////////////////////////////////////////////////
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

///////////////////////////////////////////////////////////////////
class Weapon: public Item {
private:
    int damage;     //how much damage each hit of weapon inflicts
public:
    Weapon();               //default constructor
    Weapon(int x, int y, int z);
    Weapon(Weapon& old);    //copy constructor
    ~Weapon(){}             //destructor
    
    int getDamage();        //return damage weapon inflicts
    void enhance(int row, int col);         //enhance current weapon
};

///////////////////////////////////////////////////////////////////
class Key:public Item {
private:
    int weight;
public:
    Key();            //constructor
    Key(Key& old);    //copy constructor
    ~Key(){}          //destructor
    int getWeight();  //getter for weight
};

///////////////////////////////////////////////////////////////////
class Gold:public Item {
private:
    int weight;             //weight of one gold piece
public:
    Gold();                //constructor
    Gold(Gold& old);       //copy constructor
    ~Gold(){}               //destructor
    int getWeight();       //getter for weight
};

///////////////////////////////////////////////////////////////////
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

///////////////////////////////////////////////////////////////////
class Bag {
private:
    int goldCount;              //infinite amount of gold possible -> weight=value
    int potionCount;
    int keyCount;               //either has 0 or 1 key at any time
public:
    Bag();                      //default constructor
    Bag(Bag& old);              //copy constructor
    ~Bag() {}                   //destructor
    
    int getGoldC();             //get count of gold in bag
    int getPotionC();           //get count of potions in bag
    int getKeyC();              //get count of keys in bag
    
    void useGold(int used);     //use gold
    void usePotion();           //use potion
    void useKey();              //use key
    
    Bag& operator=(Bag& rhs);   //overload = sign in terms of bag
    
    void print();               //prints out types of all in bag in order
    
    void findGold();            //find gold
    void findPotion();          //find potion
    void findKey();             //find key
};

#endif /* item_h */

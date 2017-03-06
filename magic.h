/*
 * Magic.h
 *
 *  Created on: March 1, 2017
 *      header file for magic class
 *
 *  Emily Chao
 */

#ifndef magic_h
#define magic_h

class Magic {
private:
    int magType;
    int powerCharge;
public:
    enum type {speed, strength, heal, none};
        //speed=can run from monster successfully
        //strenght=can kill monster with one hit
        //heal=can heal self back to full health
    
    Magic();    //constructor
    Magic(int type);      //create new magic and pass in type of power
    Magic(Magic& old);  //copy constructor
    ~Magic(){}  //destructor
    
    void setType(int type);    //set type of magic
    int getType();  //return magic type
    
    bool isCharged();  //return true if power charged fully
    int getCharge();    //get powerCharge
    
    void charging();    //charge magic power
    void usePower();    //use magic power
};

#endif /* magic_h */

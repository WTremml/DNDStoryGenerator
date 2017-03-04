/*
 * person.cpp
 *
 *  Created on: Feb 11, 2017
 *      Author: emilychao
 */

#include "person.h"

Person::Person() {			//default constructor
    name="Character";			//user names character for story output
}
Person::Person(string name1, int mag, int x, int y, int z) {
    name=name1;
    m.setType(mag);
    health=100;
    xLocation=x;
    yLocation=y;
    zLocation=z;
}
Person::Person(Person& old) {	//copy constructor
    name=old.name;
    bag1=old.bag1;
    w=old.w;
    m=old.m;
}
void Person::healed() {				//increment health if healed
    health+=50;
    bag1.usePotion();
}
void Person::useKey() {             //use key
    bag1.useKey();
}
void Person::usePotion() {          //use potion
    bag1.usePotion();
}
void Person::useGold(int g) {       //use gold
    bag1.useGold(g);
}
void Person::foundMonster(Monster mon) {		//if encounter monster
    int choice;
    //will they fight or not?
    cout << "Do you want to fight or run? 1-Fight 2-Run" << endl;
    cin >> choice;
    
    if (choice==1) {        //if fight
        fight(mon);
    }
    else if (choice==2) {
        run(mon);
    }
    else {
        cout << "Invalid entry. You must fight." << endl;
        fight(mon);
    }
}
bool Person::found(int x, int y, int z) {    //returns true if item 'found'
    if (zLocation==z) {         //if on same level
        if (yLocation-1<=y && y<=yLocation+1) {     //if y within 2 of object
            return true;                            //item found
        }
        else if (xLocation-1<=x && x<=xLocation+1) { //if x within 2 of object
            return true;
        }
    }
    return false;                                       //else item not found
}
void Person::foundCharacter() {		//if find another character
    //will they collaborate or not?
}
void Person::foundPotion(Potion p) {             //if find potion
    //found potion called when keypress next to potion
    if (found(p.getX(), p.getY(), p.getZ())) {         //if found
        bag1.findPotion();
        p.setLoc(-1, -1, -1);           //remove potion from screen
    }
}
void Person::foundKey(Key k) {                //if find key
    //found key called when keypress next to key
    if (found(k.getX(), k.getY(), k.getZ())) {         //if found
        bag1.findKey();
        k.setLoc(-1, -1, -1);           //remove key from screen
    }
}
void Person::foundGold(Gold g) {               //if find gold
    //found gold called when keypress next to gold
    if (found(g.getX(), g.getY(), g.getZ())) {         //if found
        bag1.findGold();
        g.setLoc(-1, -1, -1);           //remove gold from screen
    }
}
Bag Person::getBag() {				//return copy of bag
    Bag bag2;
    bag2=bag1;
    return bag2;
}
void Person::fight(Monster mon) {
    //fight
    int choice;							//choice of weapon
    int hurt;
    while (!mon.isDead() && !isDead()) {		//while can fight
        if (m.isCharged() && m.getType()==1) {    //is magic=strength AND magic charged
            cout << "Do you want to use your magic power to kill the monster? 1-Yes 2-No" << endl;
            cin >> choice;
            
            if (choice==1) {        //if use super strength
                mon.setHealth(0);       //kill monster
                cout << "You have killed the monster!" << endl;
                m.usePower();       //used power
            }
            else if (choice==2) {
                cout << "You have decided not to use your magic." << endl;
            }
            else {
                cout << "Invalid entry. Magic not used." << endl;
            }
        }
        //you injured monster during fight
        if (!mon.isDead()) {
            mon.injured(w.getDamage());           //monster injured
            cout << "You have injured the monster! ";
        }
        
        //monster injured you during fight
        hurt=rand()%(4-mon.getType());			//get hurt 1/4 or 1/3 times depending on type monster
        
        if (hurt==0) {						//if player hurt (0 is chosen remainder-->think of as 1/n probability hurt)
            health-=mon.getDamage();			//lose 3 health point if small monster, 6 health points if big monster
            cout << "But you have also been hurt by the monster.";
            
            cout << endl << "Monster health: " << mon.getHealth() << "     Your health: " << health << endl;
            
            if (isDead() && m.getType()==2 && m.isCharged()) {          //if dead and can heal self
                cout << "Do you want to use your magic power to heal yourself? 1-Yes 2-No" << endl;
                cin >> choice;
                
                if (choice==1) {        //if use healing power
                    health=100;         //fully charged health
                    cout << "You have healed yourself!" << endl;
                    m.usePower();       //used power
                }
                else if (choice==2) {
                    cout << "You have decided not to use your magic." << endl;
                }
                else {
                    cout << "Invalid entry. Magic not used." << endl;
                }
            }
        }
        if (health<=50 && bag1.getPotionC()>0) {      //if low on health and have a potion in bag
            cout << "Do you want to use a potion? 1-Yes 2-No" << endl;
            cin >> choice;
            
            if (choice==1) {        //if use potion
                healed();
                cout << "You have used a potion!" << endl;
            }
            else if (choice==2) {
                cout << "You have decided not to use your potions." << endl;
            }
            else {
                cout << "Invalid entry. Potion not used." << endl;
            }
        }
        cout << endl << "Monster health: " << mon.getHealth() << "     Your health: " << health << endl;
    }
    if (!mon.isDead()) {									//if can't fight but monster is still alive
        if (isDead()) {								//if you are out of health
            cout << "You have died! ";
        }
        health=0;										//set your health to 0
        cout << "The monster wins." << endl;
    }
    else if (mon.isDead()) {							//if monster dead
        cout << "You have beaten the monster." << endl;
    }
}
void Person::run(Monster mon) {
    int choice;
    int escape;
    if (m.isCharged() && m.getType()==0) {      //if magic charged and super speed
        //run away from monster works
        cout << "Do you want to use your magic power to run away? 1-Yes 2-No" << endl;
        cin >> choice;
        
        if (choice==1) {        //if use super speed
            //run away NEEDS TO BE IMPLEMENTED STILL _________________________________________________________
            cout << "You have run away!" << endl;
            m.usePower();       //used power
        }
        else if (choice==2) {
            cout << "You have decided not to use your magic." << endl;
            fight(mon);
        }
        else {
            cout << "Invalid entry. Magic not used." << endl;
            fight(mon);
        }
    }
    else {
        escape=rand()%(mon.getAggressive());	//can run away 1/1 - 1/10 times depending on mon aggression
        if (escape==0) {
            //run away NEEDS TO BE IMPLEMENTED STILL _________________________________________________________
            cout << "You have run away!" << endl;
        }
        else {
            cout << "The monster caught you. You must fight!" << endl;
            fight(mon);
        }
    }
}


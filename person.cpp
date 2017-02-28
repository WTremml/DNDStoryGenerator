/*
 * person.cpp
 *
 *  Created on: Feb 11, 2017
 *      Author: emilychao
 */

#include "person.h"

Person::Person() {			//default constructor
    name="Character";				//user names character for story output
    male=true;						//T if male, F if female
    weightMax=20;					//max weight they can carry
    health=10;						//measure of character health
    cooperative==rand()%101;	//spectrum of how cooperative character is (high=coop) 0-100
    aggressive==rand()%101; 	//spectrum of how aggressive character is (high=aggress) 0-100
    bagSize=bag1.getSize();	//get bagSize
    xLocation = 0;			//get x location
    yLocation = 0;			//get ylocation
    zLocation = 0;			//get zlocation
}
Person::Person(string name1, bool male1, int coop, int agg, int x, int y, int z) {
    name=name1;
    male=male1;
    weightMax=20;
    health=10;
    cooperative=coop;
    aggressive=agg;
    bagSize=bag1.getSize();
    xLocation=x;
    yLocation=y;
    zLocation=z;
}
Person::Person(Person& old) {	//copy constructor
    name=old.name;
    male=old.male;
    weightMax=old.weightMax;
    health=old.health;
    cooperative=old.cooperative;
    aggressive=old.aggressive;
    bagSize=old.bagSize;
    bag1=old.bag1;
    xLocation=old.xLocation;
    yLocation=old.yLocation;
    zLocation=old.zLocation;
}
void Person::healed() {				//increment health if healed
    health=10;
}
int Person::getCoop() {				//return how cooperative
    return cooperative;
}
int Person::getAggress() {			//return how aggressive
    return aggressive;
}
void Person::foundMonster(Monster m) {	//if encounter monster
    //will they fight or not?
    if (aggressive+m.getAggressive()>50) {
        //if person+monster's aggressiveness>50
        fight(m);
    }
    else {
        run();
    }
}
void Person::fight(Monster m) {			//if fight monster
    //fight
    int choice;							//choice of weapon
    int hurt;
    while (!m.isDead() && !isDead() && bag1.armed()) {		//while can fight
        cout << "Pick a weapon number. "; //allow user to pick weapon
        cout << "0-sword, 1-bow, 2-spear, 3-poison, 4-fireball, 5-empty, 6-medicine" << endl;
        cout << "Here is your bag: " << endl;
        bag1.print();
        
        cin >> choice;						//choice should be number 0-4
        //if weapon in bag and weapon #=0-4
        int wIndex=bag1.getIndex(choice);
        if (choice>=0 && choice<=4 && wIndex!=-1) {
            //decrease monster's health
            m.injured(bag1.getW(wIndex).getDamage());	//monster injured by chosen weapon
            cout << "You have injured the monster! ";
            bag1.weapUsed(wIndex, 1);						//decrease weapon uses left by 1
            hurt=rand()%m.getPower();						//get hurt some times depending on monster
            
            if (hurt==0) {						//if player hurt (0 is chosen remainder-->think of as 1/n probability hurt)
                health-=(m.getType()+1);			//lose 1 health point if small monster, 2 health points if big monster
                cout << "But you have also been hurt by the monster.";
            }
            cout << endl << "Monster health: " << m.getHealth() << "     Your health: " << health << endl;
        }
        else {
            //else ask to pick again
            cout << "Invalid choice." << endl << endl;	//if invalid choice, pick again
        }
    }
    if (!m.isDead()) {									//if can't fight but monster is still alive
        if (isDead()) {								//if you are out of health
            cout << "You have died! ";
        }
        else if (!bag1.armed()) {
            cout << "You had no weapons left and died! ";		//if you are out of weapons
        }
        health=0;										//set your health to 0
        cout << "The monster wins." << endl;
    }
    else if (m.isDead()) {							//if monster dead
        cout << "The monster is dead." << endl;
    }
}
void Person::foundCharacter() {		//if find another character
    //will they collaborate or not?
}
void Person::addWeapon(Weapon w) {	//add weapon to bag
    if (bag1.getWeight()<=20)
        bag1.addWeapon(w);
    else
        cout << "Bag at max weight. Cannot add weapon." << endl;
}
void Person::dropWeapon(Weapon w) {	//drop weapon from bag
    bag1.dropWeapon(w);
}
Bag Person::getBag() {				//return copy of bag
    Bag bag2;
    bag2=bag1;
    return bag2;
<<<<<<< HEAD
=======

>>>>>>> master
}

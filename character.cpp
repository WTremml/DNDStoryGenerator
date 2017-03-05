/*
 * character.cpp
 *
 *  Created on: Feb 10, 2017
 *      cpp file for character class
 */

#include "character.h"

///////////////////////////////////////////////////////////////////
Character::Character() {			//default constructor
    health=100;						//measure of character health
    xLocation = -1;			//get x location
    yLocation = -1;			//get ylocation
    zLocation = -1;			//get zLocation
}
Character::Character(Character& old) {	//copy constructor
    health=old.health;
    xLocation=old.xLocation;
    yLocation=old.yLocation;
    zLocation=old.zLocation;

}
void Character::injured(int damage) {	//decrement health if injured
    health-=damage;
}
int Character::getHealth() {			//return health
    return health;
}
int Character::getXLoc() {				//get x location of character
    return xLocation;
}
int Character::getYLoc() {				//get y location of character
    return yLocation;
}
int Character::getZLoc() {				//get z location of character
    return zLocation;
}
void Character::setLoc(int x, int y, int z) {	//set location of character
	xLocation=x;
	yLocation=y;
	zLocation=z;

}
bool Character::isDead() {				//return true if dead
    if (health<=0) {
        health=0;
        return true;
    }
    return false;
}
void Character::setHealth(int h) {      //set health
    health=h;
}
void Character::moveRight() {           //control character location on screen
    xLocation++;
}
void Character::moveLeft() {
    xLocation--;
}
void Character::moveUp() {
    yLocation++;
}
void Character::moveDown() {
    yLocation--;
}
void Character::climbUp() {
    zLocation++;
}
void Character::climbDown() {
    zLocation--;
}

///////////////////////////////////////////////////////////////////
Monster::Monster() {        //default constructor
    aggressive=rand()%10+1; //how aggressive monster is 1-10
    wandering=rand()%10+1;  //whether monster moves or not on 1-10 scale
    type=rand()%2;          //type of monster (0=small, 1=big)
}
Monster::Monster(int type1, int wander, int agg, int x, int y, int z) {
    type=type1;
    xLocation=x;
    yLocation=y;
    zLocation=z;
    aggressive=agg;
    wandering=wander;
    health=100;
}
Monster::Monster(Monster& old) {    //copy constructor
    type=old.type;
    aggressive=old.aggressive;
    wandering=old.wandering;
}
int Monster::getType() {            //get type of monster
    return type;
}
int Monster::getDamage() {          //get damage
    if (type==0) {   //if small
        return 3;
    }
    else if (type==1) {   //if big
        return 6;
    }
    return 0;
}
void Monster::foundMonster(Monster m) {         //if monster finds another monster
    if (getAggressive()+m.getAggressive()>10) {    //if total aggression > 10
        fight(m);                                       //two monsters fight each other
    }
}
void Monster::fight(Monster mon) {
    int hurt;
    while (!mon.isDead() && !isDead()) {        //while can fight
        //this monster injured mon during fight
        hurt=rand()%(4-getType());              //mon hurt 1/4 or 1/3 times depending on type of this monster
        if (hurt==0) {
            mon.injured(getDamage());           //mon injured by this monster
        }
        //mon injured this monster during fight
        hurt=rand()%(4-mon.getType());          //get hurt 1/4 or 1/3 times depending on type mon
        if (hurt==0) {
            health-=mon.getDamage();            //lose 3 health point if small, 6 health points if big
        }
    }
    if (!mon.isDead() || !isDead()) {           //if one monster still alive
        cout << "Two monsters just fought! One has been killed." << endl;
    }
    else {                                      //if both monsters die
        cout << "Two monsters fought to the death." << endl;
    }
}
int Monster::getAggressive() {  //get aggressive
    return aggressive;
}
int Monster::getWander() {       //get wandering
    return wandering;
}

///////////////////////////////////////////////////////////////////
Person::Person() {          //default constructor
    name="Character";           //user names character for story output
}
Person::Person(string name1, int mag, int x, int y, int z) {
    name=name1;
    m.setType(mag);
    health=100;
    xLocation=x;
    yLocation=y;
    zLocation=z;
}
Person::Person(Person& old) {   //copy constructor
    name=old.name;
    bag1=old.bag1;
    w=old.w;
    m=old.m;
}
void Person::healed() {             //increment health if healed
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
void Person::foundMonster(Monster mon) {        //if encounter monster
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
void Person::foundCharacter() {     //if find another character
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
Bag Person::getBag() {              //return copy of bag
    Bag bag2;
    bag2=bag1;
    return bag2;
}
void Person::fight(Monster mon) {
    //fight
    int choice;                         //choice of weapon
    int hurt;
    while (!mon.isDead() && !isDead()) {        //while can fight
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
        hurt=rand()%(4-mon.getType());          //get hurt 1/4 or 1/3 times depending on type monster
        
        if (hurt==0) {                      //if player hurt (0 is chosen remainder-->think of as 1/n probability hurt)
            health-=mon.getDamage();            //lose 3 health point if small monster, 6 health points if big monster
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
    if (!mon.isDead()) {                                    //if can't fight but monster is still alive
        if (isDead()) {                             //if you are out of health
            cout << "You have died! ";
        }
        health=0;                                       //set your health to 0
        cout << "The monster wins." << endl;
    }
    else if (mon.isDead()) {                            //if monster dead
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
        escape=rand()%(mon.getAggressive());    //can run away 1/1 - 1/10 times depending on mon aggression
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

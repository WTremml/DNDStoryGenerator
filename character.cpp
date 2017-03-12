/*
 * character.cpp
 *
 *  Created on: Feb 10, 2017
 *      cpp file for character class
 */

#include "character.h"
#include "world.h"

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
    if (health<=0) {
        health=0;
    }
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
        setLoc(-1,-1,-1);
        return true;
    }
    return false;
}
void Character::setHealth(int h) {      //set health
    health=h;
}
void Character::moveRight() {           //control character location on screen
    if(xLocation<MAP_WIDTH-1){
        xLocation++;
    }
}
void Character::moveLeft() {
    if(xLocation>0){
        xLocation--;
    }
}

//remember that y locations are switched
/*  00  10  20
    01  11  21
    02  12  22
*/
void Character::moveUp() {
    //prevents seg fault
    if(yLocation>0){
        yLocation--;
    }
}
void Character::moveDown() {
    if(yLocation<MAP_HEIGHT-1){
        yLocation++;
    }
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
Monster::Monster(int type1) {
    type=type1;
    aggressive=rand()%10+1; //how aggressive monster is 1-10
    wandering=rand()%10+1;  //whether monster moves or not on 1-10 scale   
}
Monster::Monster(Monster& old) {    //copy constructor
    type=old.type;
    aggressive=old.aggressive;
    wandering=old.wandering;
    health=old.health;
    xLocation=old.xLocation;
    yLocation=old.yLocation;
    zLocation=old.zLocation;
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
void Monster::foundMonster(Monster m, int row, int col) {         //if monster finds another monster
    if (getAggressive()+m.getAggressive()>10) {    //if total aggression > 10
        fight(m, row, col);                                  //two monsters fight each other
    }
}
void Monster::fight(Monster mon, int row, int col) {
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
int Monster::getWander() {      //get wandering
    return wandering;
}




///////////////////////////////////////////////////////////////////
Dummy::Dummy() {          //default constructor
    gift=rand()%2;
    cooperative=(rand()%10)+1;      //1-10 coopeartive
    goldC=rand()%15;                //0-14 gold pieces
    for (int i=0; i<=goldC; i++) {  //fill bag with gold
        bag1.findGold();
    }
}
Dummy::Dummy(int gift1, int x, int y, int z) {
    gift=gift1;
    xLocation=x;
    yLocation=y;
    zLocation=z;
    cooperative=(rand()%10)+1;      //1-10 coopeartive
    goldC=rand()%15;                //0-14 gold pieces
    for (int i=0; i<=goldC; i++) {  //fill bag with gold
        bag1.findGold();
    }
}
Dummy::Dummy(Dummy& old) {   //copy constructor
    bag1=old.bag1;
    cooperative=old.cooperative;
    gift=old.gift;
    goldC=old.goldC;
    health=old.health;
    xLocation=old.xLocation;
    yLocation=old.yLocation;
    zLocation=old.zLocation;
}
Bag Dummy::getBag() {              //return copy of bag
    Bag bag2;
    bag2=bag1;
    return bag2;
}
int Dummy::getGold() {
    return bag1.getGoldC();           //return gold count
}
int Dummy::getCoop() {
    return cooperative;              //return cooperative score
}
int Dummy::getGift() {
    return gift;                    //return type of gift
}
///////////////////////////////////////////////////////////////////
Person::Person() {          //default constructor
    name="Character";       //user names character for story output
    armor=1;
}
Person::Person(string name1, int mag, int x, int y, int z) {
    name=name1;
    m.setType(mag);
    health=100;
    xLocation=x;
    yLocation=y;
    zLocation=z;
    armor=1;
}
Person::Person(Person& old) {   //copy constructor
    name=old.name;
    bag1=old.bag1;
    w=old.w;
    m=old.m;
    armor=old.armor;
    health=old.health;
    xLocation=old.xLocation;
    yLocation=old.yLocation;
    zLocation=old.zLocation;
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
void Person::foundMonster(Monster mon, int row, int col) {        //if encounter monster
    int choice=0;
    
    erase();
    mvprintw(row/2,(col-34)/2,"A monster appeared out of nowhere!");
    move(row/2+4,(col-34)/2);
    refresh();
    getch();
    
    //will they fight or not?
    erase();
    mvprintw(row/2,(col-78)/2,"Would you like to: 1 - fight or 2 - run?");
    move(row/2+4,(col-78)/2);
    refresh();
    while(int(choice)>2+48 || int(choice)<1+48){
        choice = getch();
    }
    choice=choice-48;
    
    if (choice==1) {        //if fight
        fight(mon,row, col);
    }
    else if (choice==2) {   //if run
        run(mon, row, col);
    }
    else {
        cout << "Invalid entry. You must fight." << endl;
        fight(mon, row, col);
    }
}
bool Person::found(int x, int y, int z) {    //returns true if item 'found'
    if (zLocation==z) {         //if on same level
        if (yLocation-1<=y && y<=yLocation+1) {     //if y within 1 of object
            return true;                            //item found
        }
        else if (xLocation-1<=x && x<=xLocation+1) { //if x within 1 of object
            return true;
        }
    }
    return false;                                       //else item not found
}
void Person::foundCharacter(Dummy d, int row, int col) {     //if find another character
    //found dummy
    int choice=0;        //collaborate or fight

    erase();
    mvprintw(row/2,(col-78)/2,"Would you like to: 1 - fight them for their gold or 2 - collaborate with them?");
    move(row/2+4,(col-78)/2);
    refresh();
    while(int(choice)>2+48 || int(choice)<1+48){
        choice = getch();
    }
    choice=choice-48;



        
    if (choice==1) {        //if fight
        fight1(d,row, col);          //fight
    }
    else if (choice==2) {   //if collaborate
        if (d.getCoop()>5 && d.getBag().getGoldC()<10) {
            //if cooperative and not very rich -> get gift from Dummy
            if (d.getGift()==0) {
                erase();
                mvprintw(row/2,(col-30)/2,"You have been gifted a weapon!");
                move(row/2+4,(col-30)/2);
                refresh();
                getch();
                w.enhance(row, col);
            }
            else {
                if (armor>0.1) {
                    erase();
                    mvprintw(row/2,(col-26)/2,"He gave you better armour!");
                    move(row/2+4,(col-26)/2);
                    refresh();
                    getch();
                    armor-=0.01;
                }
            }
        }
        else {
        //if can't cooperate with dummy
            erase();
            mvprintw(row/2,(col-80)/2,"The other player cannot coorperate because of your poor hygiene. You will fight.");
            refresh();
            getch();
            fight1(d, row, col);
        }
    }
    else {
        //cout << "Invalid entry. You must fight." << endl;
        fight1(d, row, col);
    }
}
bool Person::foundPotion() {             //if find potion
    //found potion
    if (bag1.getPotionC() < 1) {             //limit of one potion in bag at a time
        bag1.findPotion();
        return(true);
        //p.setLoc(-1, -1, -1);               //remove potion from screen
    }
    else {
        return(false);
        //cout << "You can only carry 1 potion at a time!" << endl;
    }
}
void Person::foundKey() {                //if find key
    //found key
    bag1.findKey();
    //k.setLoc(-1, -1, -1);                          //remove key from screen
}
void Person::foundGold() {                       //if find gold
    //found gold
    bag1.findGold();
    //g.setLoc(-1, -1, -1);           //remove gold from screen
}
void Person::foundWEnhance(int row, int col) {
    //found weapon
    w.enhance(row, col);
    w.setLoc(-1, -1, -1);           //remove weapon from screen
}
Bag Person::getBag() {                  //return copy of bag
    Bag bag2;
    bag2=bag1;
    return bag2;
}
void Person::fight(Monster mon, int row, int col) {
    //fight
    int choice;                         //choice of weapon
    int hurt;
    bool flag = 1;


    while (!mon.isDead() && !isDead()) {          //while can fight
        if (m.isCharged() && m.getType()==1 && flag) {    //is magic=strength AND magic charged

            erase();
            mvprintw(row/2,(col-78)/2,"Do you want to use your magic power to Damage the monster? 1-Yes 2-No");
            move(row/2+4,(col-78)/2);
            refresh();
            while(int(choice)>2+48 || int(choice)<1+48){
                choice = getch();
            }
            choice=choice-48;
            flag=0;

            //cout << "Do you want to use your magic power to kill the monster? 1-Yes 2-No" << endl;
            //cin >> choice;
            
            if (choice==1) {                //if use super strength
                mon.setHealth(0);          //kill monster
                //cout << "You have killed the monster!" << endl;
                m.usePower();               //used power

                erase();
                mvprintw(row/2,(col-39)/2,"You have decided to use your magic!");
                refresh();
                getch();
            }
            else if (choice==2) {
                erase();
                mvprintw(row/2,(col-39)/2,"You have decided not to use your magic.");
                refresh();
                getch();
                
            }
            else {
                //cout << "Invalid entry. Magic not used." << endl;
            }
        }
        //you injured monster during fight
        if (!mon.isDead()) {
            mon.injured(w.getDamage());           //monster injured
            //cout << "You have injured the monster! ";
        }

        if (health<=50 && bag1.getPotionC()>0) {      //if low on health and have a potion in bag
            //cout << "Do you want to use a potion? 1-Yes 2-No" << endl;
            //cin >> choice;
            
            erase();
            mvprintw(row/2,(col-39)/2,"Your health is below 50 points.");
            mvprintw(row/2,(col-39)/2,"Do you want to use a potion? 1-Yes 2-No");
            move(row/2+4,(col-39)/2);
            refresh();
            while(int(choice)>2+48 || int(choice)<1+48){
                choice = getch();
            }
            choice=choice-48;
            
            if (choice==1) {        //if use potion
                healed();
                erase();
                mvprintw(row/2,(col-39)/2,"You have decided to use your potion!");
                refresh();
                getch();
            }
            else if (choice==2) {
                erase();
                mvprintw(row/2,(col-39)/2,"You have decided not to use your potion.");
                refresh();
                getch();
            }
            else {
                //cout << "Invalid entry. Potion not used." << endl;
            }
        }
        
        //monster injured you during fight
        hurt=rand()%(4-mon.getType());          //get hurt 1/4 or 1/3 times depending on type monster
        
        if (!mon.isDead() && hurt==0) {                          //if player hurt (0 is chosen remainder-->think of as 1/n probability hurt)
            float k = rand()%100;               //factor in armor -> heavier armor = hurt less often
            k=k/100;
            
            if (k<=armor) {                     //if armor didn't protect you
                injured(mon.getDamage());            //lose 3 health point if small monster, 6 health points if big monster
                //cout << "But you have also been hurt by the monster.";
                
                /*
                erase();
                mvprintw(row/2,(col-20)/2,"Your health is: %d", health);
                refresh();
                getch();
                */
            
                //cout << endl << "Monster health: " << mon.getHealth() << "     Your health: " << health << endl;
            
                if (isDead() && m.getType()==2 && m.isCharged()) {          //if dead and can heal self
                    erase();
                    mvprintw(row/2,(col-64)/2,"Do you want to use your magic power to heal yourself? 1-Yes 2-No");
                    move(row/2+4,(col-64)/2);
                    refresh();
                    while(int(choice)>2+48 || int(choice)<1+48){
                        choice = getch();
                    }
                    choice=choice-48;
                    
                
                    if (choice==1) {        //if use healing power
                        health=70;         //fully charged health
                        //cout << "You have healed yourself!" << endl;
                        m.usePower();       //used power
                    }
                    else if (choice==2) {
                        erase();
                        mvprintw(row/2,(col-39)/2,"You have decided not to use your magic.");
                        refresh();
                        getch();
                    }
                    else {
                        //cout << "Invalid entry. Magic not used." << endl;
                    }
                }
            }
        }
        //cout << endl << "Monster health: " << mon.getHealth() << "     Your health: " << health << endl;
    }
    if (!mon.isDead()) {                             //if can't fight but monster is still alive
        if (isDead()) {                              //if you are out of health
            //cout << "You have died! ";
        }
        health=0;                                    //set your health to 0
        //cout << "The monster wins." << endl;
    }
    else if (mon.isDead()) {                         //if monster dead
        
        erase();
        mvprintw(row/2,(col-39)/2,"The monster is dead!");
        mvprintw(row/2+2,(col-39)/2,"Your health is: %d", getHealth());
        refresh();
        
        if (armor>0.1) {
            //cout << "You have earned heavier armor!" << endl;
            armor-=0.01;
        }
    }

}


void Person::fight1(Dummy d, int row, int col) {
    //fight
    int choice=0;                         //choice of weapon
    int hurt;
    while (!d.isDead() && !isDead()) {            //while can fight
        if (m.isCharged() && m.getType()==1) {    //is magic=strength AND magic charged
            //cout << "Do you want to use your magic power to kill the dummy? 1-Yes 2-No" << endl;
            //cin >> choice;
            
            erase();
            mvprintw(row/2,(col-72)/2,"Do you want to use your magic power to hurt the other player? 1-Yes 2-No");
            move(row/2+4,(col-72)/2);
            refresh();
            while(int(choice)>2+48 || int(choice)<1+48){
                choice = getch();
            }
            choice=choice-48;


            if (choice==1) {          //if use super strength
                d.setHealth(0);       //kill dummy
                //cout << "You have killed the dummy!" << endl;
                m.usePower();         //used power

                erase();
                mvprintw(row/2,(col-39)/2,"You have decided to use your magic!");
                refresh();
                getch();
            }
            else if (choice==2) {
                erase();
                mvprintw(row/2,(col-26)/2,"You do not use your power.");
                refresh();
                getch();
            }
        }
        //you injured dummy during fight
        if (!d.isDead()) {
            d.injured(w.getDamage());
            //cout << "You have injured the dummy! ";
        }
        //dummy injured you during fight
        int nice;
        if (d.getCoop()>8) {
            //if cooperative dummy -> less likely to hurt you
            nice = 0;
        }
        else {
            //if aggressive dummy -> more likely to get hurt
            nice=1;
        }
        hurt=rand()%(4-nice);    //get hurt 1/4 or 1/3 times depending on how nice dummy is
        
        if (!d.isDead() && hurt==0) {                      //if player hurt (0 is chosen remainder-->think of as 1/n probability hurt)
            float k = rand()%100;           //factor in armor -> heavier armor = hurt less often
            k=k/100;
            
            if (k<=armor) {                  //if armor didn't protect you
                health-=(nice+1);            //lose 2 health point if not nice, 1 health point if big nice
                //cout << "But you have also been hurt by the dummy.";
                
                //cout << endl << "Dummy health: " << d.getHealth() << "     Your health: " << health << endl;
                
                if (isDead() && m.getType()==2 && m.isCharged()) {          //if dead and can heal self
                    erase();
                    mvprintw(row/2,(col-77)/2,"You were about to die, but in the last moment you healed yourself with magic!");
                    refresh();
                    getch();
                    
                    choice=1;           //use magic to heal yourself
                    
                    if (choice==1) {        //if use healing power
                        health=90;         //fully charged health
                        //cout << "You have healed yourself!" << endl;
                        m.usePower();       //used power
                    }
                }
            }
        }
        if (health<=50 && bag1.getPotionC()>0) {      //if low on health and have a potion in bag
            //cout << "Do you want to use a potion? 1-Yes 2-No" << endl;
            //cin >> choice;
            
            if(health<20 && d.getHealth()>20) {  //use potion if very weak and dummy strong
                choice=1;
            }
            else {
                choice=2;
            }
            
            if (choice==1) {        //if use potion
                healed();
                //cout << "You have used a potion!" << endl;
            }
            else if (choice==2) {
                //cout << "You have decided not to use your potions." << endl;
            }
            else {
                //cout << "Invalid entry. Potion not used." << endl;
            }
        }
        //cout << endl << "Dummy health: " << d.getHealth() << "     Your health: " << health << endl;
    }
    if (!d.isDead()) {                                    //if can't fight but dummy is still alive
        if (isDead()) {                             //if you are out of health
            //cout << "You have died! ";
        }
        health=0;                                       //set your health to 0
        //cout << "The dummy wins." << endl;
    }
    else if (d.isDead()) {  
        erase();
        mvprintw(row/2,(col-39)/2,"You slit the other players throat.");
        mvprintw(row/2+2,(col-39)/2,"Your health is: %d", getHealth());
        refresh();                          //if monster dead
        //cout << "You have beaten the dummy." << endl;
        if (armor>0.1) {
            //cout << "You have earned " << d.getBag().getGoldC() << " gold pieces!" << endl;
            for (int i=0; i<=d.getBag().getGoldC(); i++) {
                bag1.findGold();
            }
        }
    }
}
void Person::run(Monster mon, int row, int col) {
    int choice=0;
    int escape;
    int caught;
    if (m.isCharged() && m.getType()==0) {      //if magic charged and super speed
        //run away from monster works
        //cout << "Do you want to use your magic power to run away? 1-Yes 2-No" << endl;
        //cin >> choice;
       
        erase();
        mvprintw(row/2,(col-72)/2,"Do you want to use your magic power to run away? 1-Yes 2-No");
        move(row/2+4,(col-72)/2);
        refresh();
        while(int(choice)>2+48 || int(choice)<1+48){
            choice = getch();
        }
        choice=choice-48;
        
        if (choice==1) {        //if use super speed
            mon.setLoc(-1,-1,-1);
            erase();
            mvprintw(row/2,(col-77)/2,"You lost the monster!");
            refresh();
            getch();            m.usePower();       //used power
        }
        else if (choice==2) {
            //cout << "You have decided not to use your magic." << endl;
            fight(mon, row, col);
        }
        else {
            //cout << "Invalid entry. Magic not used." << endl;
            fight(mon, row, col);
        }
    }
    else {
        escape=rand()%(mon.getAggressive());    //can run away 1/1 - 1/10 times depending on mon aggression
        if (escape==0) {
            
            caught=rand()%(mon.getWander());    //can run away 1/1 - 1/10 times depending on mon wandering
                                                    //escape more often is mon has low wandering speed
            if (caught==0) {
                erase();
                mvprintw(row/2,(col-77)/2,"You lost the monster!");
                refresh();
                getch();            }
            else {
                erase();
                mvprintw(row/2,(col-77)/2,"The monster caught you. You must fight!");
                refresh();
                getch();
                fight(mon, row, col);
            }
        }
        else {
            erase();
            mvprintw(row/2,(col-77)/2,"The monster caught you. You must fight!");
            refresh();
            getch();
            fight(mon, row, col);
        }
    }
}
void Person::upLevel() {
    if (bag1.getKeyC()>=1) {        //if have a key
        bag1.useKey();              //use key
        m.charging();               //recharge magic power at start of each level
    }
}


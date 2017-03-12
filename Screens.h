/*
 * Screens.h
 *
 *  Created on: March 3, 2017
 *      header file for printing variaous screens to the terminal via NCURSES.h
 *
 *  Will Tremml
 */

#ifndef SCREENS_H
#define SCREENS_H

#include <ncurses.h>
#include <string>
#include <unistd.h>

using namespace std;

void Intro(int row, int col){
  int i;

  char img[45][100] = { "  ___                                                             " ,
    " (  _`\\                                                           " ,
    " | | ) | _   _   ___     __     __     _     ___    ___           " ,
    " | | | )( ) ( )/' _ `\\ /'_ `\\ /'__`\\ /'_`\\ /' _ `\\/',__)          " ,
    " | |_) || (_) || ( ) |( (_) |(  ___/( (_) )| ( ) |\\__, \\          " ,
    " (____/'`\\___/'(_) (_)`\\__  |`\\____)`\\___/'(_) (_)(____/          " ,
    "                      ( )_) |                                     " ,
    "                       \\___/'                                     " ,
    "  _____       ___                                                 " ,
    " (  _  )     (  _`\\                                               " ,
    " `\\  ,/'     | | ) | _ __    _ _    __     _     ___    ___       " ,
    "  /'_`\\/\\    | | | )( '__) /'_` ) /'_ `\\ /'_`\\ /' _ `\\/',__)      " ,
    " | (_> ,<`   | |_) || |   ( (_| |( (_) |( (_) )| ( ) |\\__, \\      " ,
    " `\\___/\\/'   (____/'(_)   `\\__,_)`\\__  |`\\___/'(_) (_)(____/      " ,
    "                                 ( )_) |                          " ,
    "                                  \\___/'                          " ,
    "                                                                  " ,
    "                                                                  " ,
    "  ______  ______  ______  ______  ______  ______  ______  ______  " ,
    " (______)(______)(______)(______)(______)(______)(______)(______) " ,
    "                                                                  " ,
    "                                                                                             " ,
    "                                                                                             " ,
    "   *   )      )                          (                                                   " ,
    " ` )  /(   ( /(     (        )     (     )\\ )     (            (  (       )      )       (   " ,
    "  ( )(_))  )\\())   ))\\      /((    )\\   (()/(    ))\\    (      )\\))(   ( /(     (       ))\\  " ,
    " (_(_())  ((_)\\   /((_)    (_))\\  ((_)   ((_))  /((_)   )\\    ((_))\\   )(_))    )\\  '  /((_) " ,
    " |_   _|  | |(_) (_))      _)((_)  (_)   _| |  (_))    ((_)    (()(_) ((_)_   _((_))  (_))   " ,
    "   | |    | ' \\  / -_)     \\ V /   | | / _` |  / -_)  / _ \\   / _` |  / _` | | '  \\() / -_)  " ,
    "   |_|    |_||_| \\___|      \\_/    |_| \\__,_|  \\___|  \\___/   \\__, |  \\__,_| |_|_|_|  \\___|  " ,
    "                                                              |___/                          " ,
    "  " ,
    "  " ,
    "  " ,
    "    ___         _      ___ ____  ______                    __ " ,
    "   / _ )__ __  | | /| / (_) / / /_  __/______ __ _  __ _  / / " ,
    "  / _  / // /  | |/ |/ / / / /   / / / __/ -_)  ' \\/  ' \\/ /  " ,
    " /____/\\_, /   |__/|__/_/_/_/ _ /_/ /_/  \\__/_/_/_/_/_/_/_/   " ,
    "  ___ /___/ ___/ / / __/_ _  (_) /_ __  / ___/ /  ___ ____    " ,
    " / _ `/ _ \\/ _  / / _//  ' \\/ / / // / / /__/ _ \\/ _ `/ _ \\   " ,
    " \\_,_/_//_/\\_,_/ /___/_/_/_/_/_/\\_, /  \\___/_//_/\\_,_/\\___/   " ,
    "                               /___/                          " ,
    "  " ,
    " Press an arrow key to begin " ,
    " Press 'q' to quit "};

  for(i=0;i<45;i++){
    mvprintw((row-45)/2+i,(col-strlen(img[30]))/2,"%s",img[i]);
  }

  //printw("Press an arrow key to begin");

  refresh();
  getch();
  erase();
}


char* Name(int row, int col){
  	char* _name;
  	_name = new char[40];

  	char welcome[] = "Welcome traveler. You seem to be a bit lost?";
  	char tell[] = "Tell me? What is your name?";

  
	mvprintw((row)/2,(col-strlen(welcome))/2,"%s", welcome);
	refresh();

	sleep(2);
	erase();

	mvprintw((row)/2,(col-strlen(welcome))/2,"%s", tell);
	refresh();

	move( (row)/2+4,(col-strlen(welcome))/2 );
	getnstr(_name, 40);
	erase();

	mvprintw((row)/2,(col-strlen(welcome))/2,"Very well, %s. Press any key to continue.", _name);
	refresh();
	getch();
	erase();

	return(_name);

}

int Magic(int row, int col){
	int i;
	int ch = 0;

	char wiz[26][40] = { "   ",
	"     ",
	"	   	      _,._         ",
	"	  .||,       /_ _\\\\        ",
	"	 \\.`',/      |'L'| |       ",
	"	 = ,. =      | -,| L       ",
	"	 / || \\    ,-'\\\"/,'`.      ",
	"	   ||     ,'   `,,. `.     ",
	"	   ,|____,' , ,;' \\| |     ",
	"	  (3|\\    _/|/'   _| |     ",
	"	   ||/,-''  | >-'' _,\\    ",
	"	   ||'      ==\\ ,-'  ,'    ",
	"	   ||       |  V \\ ,|      ",
	"	   ||       |    |` |      ",
	"	   ||       |    |   \\     ",
	"	   ||       |    \\    \\    ",
	"	   ||       |     |    \\   ",
	"	   ||       |      \\_,-'   ",
	"	   ||       |___,,--\")_\\   ",
	"	   ||         |_|   ccc/   ",
	"	   ||        ccc/          ",
	"	   ||                   ",
	"     ",
	"     ",
	"    Wizard (1)   ",
	"     " };

	char mini[26][45] = { "   ",
	"        .      .    ",
	"        |\\____/|    ",
	"       (\\|----|/)    ",
	"        \\ 0  0 /    ",
	"         |    |    ",
	"      ___/\\../\\____    ",
	"     /     --       \\    ",
	"    /  \\         /   \\    ",
	"   |    \\___/___/(   |    ",
	"   \\   /|  }{   | \\  )    ",
	"    \\  ||__}{__|  |  |    ",
	"     \\  |;;;;;;;\\  \\ / \\_______    ",
	"      \\ /;;;;;;;;| [,,[|======    ",
	"        |;;;;;;/ |     /    ",
	"        ||;;|\\   |    ",
	"        ||;;/|   /    ",
	"        \\_|:||__|    ",
	"         \\ ;||  /    ",
	"         |= || =|    ",
	"         |= /\\ =|    ",
	"         /_/  \\_\\    ",
	"     ",
	"     ",
	"    Minotaur (2)   ",
	"     "};

	char elf[24][40] = {"     ",
	"      ",
	"  	       .-----.   ",
	"   \\ ' /   _/    )/   ",
	"  - ( ) -('---''--)   ",
	"   / . \\((()\\^_^/)()   ",
	"    \\\\_\\ (()_)-((()()   ",
	"     '- \\ )/\\._./(()   ",
	"       '/\\/( X   ) \\   ",
	"       (___)|___/ ) \\   ",
	"            |.#_|(___)   ",
	"           /\\    \\ ( (_   ",
	"           \\/\\/\\/\\) \\\\   ",
	"           | / \\ |   ",
	"           |(   \\|   ",
	"          _|_)__|_\\_   ",
	"          )...()...(   ",
	"           | (   \\ |        ",
	"        .-'__,)  (  \\   ",
	"                  '\\_-,   ",
	"     ",
	"     ",
	"    Elf (3)   ",
	"     "};

	char mag1[] = "Now you must tell me what you want to be.";
	char mag2[] = "Each type has a different skill, so choose carefully!";

	char A1[] = "You can cast a spell from afar and damage the monster with a monstrous hit!";
  	char A2[] = "You are trained in the arts of war. The enemy may think you are down, but you get right back up.";
  	char A3[] = "Your super speed (and dashing good looks) allow you to make a quick escape!";


  	for(i=0;i<26;i++){
		mvprintw((row-26)/2+i,(col-45)/5,"%s",wiz[i]);
	}
	for(i=0;i<26;i++){
	    mvprintw((row-26)/2+i,(col-45)/1.5,"%s",mini[i]);
	}
	for(i=0;i<24;i++){
	    mvprintw((row-24)/2+i+1,(col-45),"%s",elf[i]);
	}

	mvprintw((row-26)/2 + 28,(col-45)/2,"%s",mag1);
	mvprintw((row-26)/2 + 29,(col-45)/2,"%s",mag2);
	move((row-26)/2 + 31,(col-45)/2);
	refresh();

	while(int(ch)>3+48 || int(ch)<1+48){
		ch = getch();
	}

	if((int(ch)-48) ==1){
		erase();
		mvprintw((row)/2,(col-strlen(A1))/2,"%s", A1);
		mvprintw((row)/2+3,(col-strlen(A1))/2,"p - pickup items you are standing on");
		mvprintw((row)/2+4,(col-strlen(A1))/2,"n - advance to the next level once you have a key");
		mvprintw((row)/2+5,(col-strlen(A1))/2,"q - quit the game at any time (does not save!)");
		mvprintw((row)/2+7,(col-strlen(A1))/2,"Arrows - move your character");
		refresh();

	}else if((int(ch)-48) ==2){
		erase();
		mvprintw((row)/2,(col-strlen(A2))/2,"%s", A2);
		mvprintw((row)/2+3,(col-strlen(A2))/2,"p - pickup items you are standing on");
		mvprintw((row)/2+4,(col-strlen(A2))/2,"n - advance to the next level once you have a key");
		mvprintw((row)/2+5,(col-strlen(A2))/2,"q - quite the game at any time (does not save!)");
		mvprintw((row)/2+7,(col-strlen(A2))/2,"Arrows - move your character");
		refresh();

	}else {
		erase();
		mvprintw((row)/2,(col-strlen(A3))/2,"%s", A3);
		mvprintw((row)/2+3,(col-strlen(A3))/2,"p - pickup items you are standing on");
		mvprintw((row)/2+4,(col-strlen(A3))/2,"n - advance to the next level once you have a key");
		mvprintw((row)/2+5,(col-strlen(A3))/2,"q - quite the game at any time (does not save!)");
		mvprintw((row)/2+7,(col-strlen(A3))/2,"Arrows - move your character");
		refresh();
	}
	

	getch();
	erase();
	
	return(int(ch)-48);

}





#endif





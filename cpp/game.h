/********************************
             game.h
 ********************************/

#ifndef GAME_H
#define GAME_H 1

#include<iostream>
#include<stdlib.h>
#include<typeinfo>
#include <string>
#include "printer.h"

#include "item.h"

#include "player.h"
#include "room.h"
#include "troll.h"



//The game will be run by creating an instance of this class and passing it commands in the "turn" function
class Game {
private:
	Troll* troll;
	void Update();
	int numrooms;
	int numitems;
	Room** room; //Holds a list of pointers to each room.
	//items will be accessed by the room that they're in.
	Player* me; //Points to the instance of the Player class
	Game (const Game&);
	Game& operator=(const Game&);
	int turn; //just a counter for how many turns have been taken (some commands do not count as a turn)
	int score; //Maybe some kind of scoring?
	bool Move(Room* moveto);
	void MoveTroll(Room* moveto);
	void Look();
	bool Examine(std::string name);
	bool Smash();
	bool Battle(std::string name);
	bool Take(std::string name);
	bool Drop(std::string name);
	bool Open(std::string name);
	bool Close(std::string name);
	bool dead;
public:

	Game(); //This will create rooms and items and populate them in the initial setup of the game
	//will probably have its own file.
	~Game(); //will deallocate all rooms and items etc.
	void Turn(std::string command); //This is what will be called repeatedly by the main function
	
	//Restart(); //This will reset the game to it’s original state (Taken care of by main)
};

#endif // #ifndef GAME_H
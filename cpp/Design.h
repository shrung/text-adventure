/********************************
        ADVENTURE DESIGN 
 ********************************/
// Andrew Miller and Adam Simpson

/********************************
             game.h
 ********************************/

#ifndef GAME_H
#define GAME_H 1

#include<iostream>
#include<typeinfo>
#include <string>

#include "Item.h"
#include "Room.h"
#include "Player.h"



//The game will be run by creating an instance of this class and passing it commands in the "turn" function
class Game {
private:
	Room** room; //Holds a list of pointers to each room.
	//items will be accessed by the room that they're in.
	Player* me; //Points to the instance of the Player class
	Game (const Game&);
	Game& operator=(const Game&);
	int turn; //just a counter for how many turns have been taken (some commands do not count as a turn)
	int score; //Maybe some kind of scoring?
public:
	Game(); //This will create rooms and items and populate them in the initial setup of the game
	//will probably have its own file.
	~Game(); //will deallocate all rooms and items etc.

	Load(string FileName); //This will load a file from FileName
	Save(string FileName); //This will save a file to FileName
	Turn(string command); //This is what will be called repeatedly by the main function

	Restart(); //This will reset the game to it’s original state
};

#endif // #ifndef SHAPES_H


/********************************
             Room.h
 ********************************/

#ifndef ROOM_H
#define ROOM_H 1

// This class will contain items and will change in response to commands
class Room{
protected:
	_numItems;
	Room* N,W,S,E; // Pointers to different directions that can be traveled
	Item** inventory; // Each room has an inventory of items
	int _numItems;
	string description;

public:
	Room();
	Room(Room* N, Room* S, Room* E, Room* W, string description)
	int numItems();
	Item* getItem(int i);
	//These will need to call the functions in Player to have/give items
	//When asked to take, if it is successful, the Take function will call “have” on the player
	//Likewise for placing, if the room accepts an item, it will call “give” on the player.
	void Take(string name, Player* player); takes the named item
	void Place(Item * newitem, Player* player); //adds an item to the room

	void Describe(); //prints out the room description, and describes all items in the room.
	int numItems(); //tells how many items are in the room
	virtual Item* getItem(int i); 
	virtual void Update(); //Each room might want to do something each turn, and it will call update for all items in the room
};

class SpinningRoom: public Room{
private:
	int speed; //how fast the room spins (probably -2 to +2)
public:
void Update(); //This will shift the mapping of N,W,S,E by speed each turn
//There may be a special lever item with friend properties so that it can change the speed of the room.
};

#endif // #ifndef ROOM_H


/********************************
             Item.h
 ********************************/

#ifndef ITEM_H
#define ITEM_H 1

#include<string>
//This class is the basic item class
class Item{
private:
	string name; //Every item will have a unique name (this name may be changed by the item if it is used or broken though)
	string description;

public:
	bool canTake();
	bool canPlace();
	string Name();
	virtual void Update(); //Everything might want to do something each turn
	virtual void Describe(); //Prints out the description (this will be looped over for all the items in a room, etc.)
};

//This class will be for things like a box or treasure chest
class Crate : public Item{
private:
	Item ** stuff; //List of the items inside of it.
	int _numItems;
	bool open;
public:
	void Describe();//this will describe all items inside if it’s open
	int numItems();
	Item* getItem(int i);
	
	//These will need to call the functions in Player to have/give items
	//When asked to take, if it is successful, the Take function will call “have” on the player
	//Likewise for placing, if the crate accepts an item and the item can be taken, it will call "give" on the player.
	void Take(string name, Player* player); takes the named item
	void Place(Item * newitem, Player* player); //adds an item to the box
	Open(); //This will try to open the box
	Close();
	isOpen();
	Description(); //if it’s open. this will print "The box contains:" and then ask for the description of each item inside.
	virtual void Update(); //Everything might want to do something each turn, so this will call update on pieces inside too.
};
#endif // #ifndef ITEM_H


/********************************
             Player.h
 ********************************/

#ifndef PLAYER_H
#define PLAYER_H 1

//This is the player class. The player is very open to the control of outside influences.
//The player will take items it is given, and give up items it is asked for willingly
class Player{
private:
	Room* room; //this keeps track of the current room the player is in.
	Item **Inventory; //this keeps track of all the items in the players inventory
	int _numItems;
	int weight; //the current weight you are holding. Move will check this before letting you go anywhere
public:
	Item* getItem(int i);
	int numItems();
	void Update(); will update, and call update on all items.
	Room* GetRoom();
	void Take(string name);
	void Place(string name);
	void have(Item* newitem); //This will add an item to the inventory. Rooms and crates will call this when a player asks to take an item.
	Item* give(string name); //The player will relinquish an object from its inventory. 
	void SetRoom(Room* newroom); //will move the player to a room.

#endif // #ifndef PLAYER_H
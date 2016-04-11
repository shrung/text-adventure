/********************************
             player.h
 ********************************/

#ifndef PLAYER_H
#define PLAYER_H 1
class Player;

#include "room.h"
#include "item.h"
#include <string.h>
#include <iostream>
#include "printer.h"

#define MAXITEMS 10

//This is the player class. The player is very open to the control of outside influences.
//The player will take items it is given, and give up items it is asked for willingly
class Player{
protected:
	Item* myself;
	Room* room; //this keeps track of the current room the player is in.
	//Item* Inventory[MAX_ITEMS]; //this keeps track of all the items in the players inventory
	//Crate Inventory;
//	int _numitems;
	int maxweight;
	
public:
	Inventory inv;
	Player();
	Player(Room* start);
	void MyInv();
	Item* MyItem(){return myself;};
	int numItems(){return inv.getSize();};
	int GetWeight(){return (inv.Weight());};
	virtual void Update(){}; //will update, and call update on all items.
	bool CanMove(){if(GetWeight()>maxweight){
						Print("You are carrying too much weight to move!");
						return false;} 
					return true;};
	Room* GetRoom(){return room;};
	void Take(std::string name);
	void Place(std::string name);
	virtual void SetRoom(Room* newroom){room=newroom;};//will move the player to a room.
	Item * getItem(std::string name){return inv.getItem(name);};
};
#endif // #ifndef PLAYER_H
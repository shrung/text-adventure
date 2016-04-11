/********************************
             player.cpp
 ********************************/

#include "player.h"

Player::Player(){
	maxweight = 50;
	//for(int i = 0;i<MAXITEMS;i++)
		//Inventory[i] = NULL;
}

Player::Player(Room* start){
	maxweight=50;
	myself = new Item("PLAYER","the user",49,true,false);
	room=start;
	start->inv.AddItem(myself);
}

void Player::MyInv(){
	if(inv.getSize()==0)
		Print("You are not carrying anything");
	else{
		Print("You are carrying:");
		inv.List();
	}
}
/*
void Player::Take(std::string name){
	if(room->inv.getItem(name){
		Item* thing = room->Take(name);
		Inventory.Place(thing);
	}
	else
		Print(name+ " is nowhere to be found.");
}

void Place(std::string name){
	if(Inventory.CanFind(name)){
		Item* thing = Inventory.Take(name);
		room->Place(thing);
	}
}
*/
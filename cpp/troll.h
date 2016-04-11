/********************************
             troll.h
 ********************************/
 
#ifndef TROLL_H
#define TROLL_H 1

#include <iostream>
#include <stdlib.h>
#include "printer.h"
#include "item.h"
#include "player.h"
#include "room.h"


class Troll:public Player{
private:
	bool attack;
	bool chase;
	Item* myself;
public:
	void Die();
	bool ShouldAttack(){return attack;};
	Troll();
	Troll(Room* start);
	~Troll(){};
	
	Room* Move();
	void SetRoom(Room* newroom){room->inv.RemoveItem("troll");
								room=newroom;
								room->inv.AddItem(myself);};
	void Update();
};


#endif //ifndef TROLL_H
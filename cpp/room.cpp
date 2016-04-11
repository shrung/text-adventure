/********************************
             room.cpp
 ********************************/
#include "room.h"
#include <iostream>

Room::Room(){
	SetDesc("This room has not been configured!");
	SetN(NULL);
	SetS(NULL);
	SetE(NULL);
	SetW(NULL);
	SetUp(NULL);
	SetDown(NULL);
	//inventory = Crate(RmItems, "");
}

Room::~Room(){
}

bool Room::Enter(Player* player, bool silent){
	Item* lock = inv.getItem("LOCK");
	if(player->GetRoom() == GetN() ||
		player->GetRoom() == GetS() ||
		player->GetRoom() == GetE() ||
		player->GetRoom() == GetW() ||
		player->GetRoom() == GetUp() ||
		player->GetRoom() == GetDown()){
		if(lock!=NULL)
			if(player->getItem(lock->Description())!=NULL){
				if(!silent)Print("You unlock the door with the "+lock->Description());
				inv.getItem("LOCK")->SetName("UNLOCKED");
				return Enter(player,silent);
			}
			else{
				if(!silent)Print("That room is locked!");
				return false;
			}
		else 
			return true;
	}
	else{
		if(!silent)Print("You can't go that way!");
		return false;
	}
}

void Room::Describe(){
	Print(description);
	if(inv.visItems()){
		Print("The room contains:");
		inv.List();
	}
	//Need to describe item in the room here.
}

void Room::Update(){
	inv.Update();
}

SpinningRoom::SpinningRoom(){
	state=false;
	ew="East and West.";
	ns="North and South.";
}
bool SpinningRoom::Enter(Player* player, bool silent){
	Item* lock = inv.getItem("LOCK");
	if(
		state&&(player->GetRoom() == GetN() ||
		player->GetRoom() == GetS()) ||
		!state&&(player->GetRoom() == GetE() ||
		player->GetRoom() == GetW()) ||
		player->GetRoom() == GetUp() ||
		player->GetRoom() == GetDown()){
		if(lock!=NULL)
			if(player->getItem(lock->Description())!=NULL){
				if(!silent)Print("You unlock the door with the "+lock->Description());
				inv.getItem("LOCK")->SetName("UNLOCKED");
				return Enter(player,silent);
			}
			else{
				if(!silent)Print("That room is locked!");
				return false;
			}
		else 
			return true;
	}
	else{
		if(!silent)Print("The door isn't there right now!");
		return false;
	}
}

void SpinningRoom::Describe(){
	//std::cout<<state<<std::endl;
	Print(description+((state) ? ew: ns));
	if(inv.visItems()){
		Print("The room contains:");
		inv.List();
	}
	//Need to describe item in the room here.
}
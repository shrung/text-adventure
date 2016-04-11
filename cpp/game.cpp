/********************************
             game.cpp
 ********************************/
 #include "game.h"
 #include "room.h"
 #include "player.h"
 #include <iostream>
 #include <sstream>
 #include <string.h>
 

 Game::Game(){
	dead=false;
	turn =0;
	score =0;
	numrooms = 21;
	int N[21] =    { 1, 3,17,-1,-1,-1,-1,-1,-1, 8, 9,-1,10,18,-1,-1,-1, 5,19,20,14};
	int S[21] =    {-1, 0,-1, 1,-1,17,-1,-1, 9,10,12,-1,-1,-1,20,-1,-1, 2,13,18,19};
	int E[21] =    {-1, 2,-1,17,-1,-1,-1, 8,-1,-1,11,-1,-1,-1,-1,-1,-1, 4,-1,-1,-1};
	int W[21] =    {-1,-1, 1,-1,17,-1,-1,-1, 7,-1,-1,10,-1,-1,-1,-1,-1, 3,-1,-1,-1};
	int Up[21] =   {-1,-1,-1,-1, 6,-1,-1,-1,-1,-1,-1, 1,-1,12,15,16,-1,-1,-1,-1,-1};
	int Down[21] = {-1,11,-1,-1,-1,-1, 4,-1,-1,-1,-1,-1,13,-1,-1,14,15,-1,-1,-1,-1};
	
	std::string description[] = {
/*1*/"You are in a boring, unimaginative, nondescript, plain, old, ugly, room. There is a door leading to the North. Nothing else.",
/*2*/"You are standing in a large room. There is a hole in the ground that looks large enough to climb Down. There are also two corridors. One leading North, and one leading East.",
/*3*/"This passageway has an exit to the West and a door to the North. The door seems to come and go, but it is moving slow enough to enter safely.",
/*4*/"This winding passageway has an exit to the South and a door to the East. The door seems to come and go, but it is moving slow enough to enter safely.",
/*5*/"At the end of this corridor a trap door is hanging open on the ceiling, and a ladder leads Up through it. There is a door to the West which seems to be moving by the wall.",
/*6*/"This room is a dead end. It is elaborately decorated and the inscription on the far wall seems to be calling to you. There is a door to the South.",
/*7*/"You are in a high tower room. There is a hole in the ground with a ladder leading Down.",
/*8*/"Congratulations! You have made it to the treasure room! (That means you win) There is treasure all around. Congratulations.",
/*9*/"The space seems to open up here. There is a small, dirty looking tunnel to the South, and a door to the West. It has a complex looking locking system with a single small keyhole.",
/*10*/"You find yourself crawling through what appears to be a filthy mud puddle. You can go North or South.",
/*11*/"The tunnel makes a 'T' here, and you can crawl North, South, or East.",
/*12*/"You are in a hole in the ground. There is a tunnel leading off to the West, and with a little effort, you may be able to climb back Up.",
/*13*/"The tunnel leads North, and there is a much nastier looking hole here leading Down. It smells pretty bad.",
/*14*/"The smell down here is pretty bad. A hole leads Upwards to fresher air, and a long, creaky looking, walkway leads to the North.",
/*15*/"The smell here is nearly unbearable, and it seems to emanate from above. A ladder leads Up, and a creaky walkway leads to the South.",
/*16*/"You are on a ladder in a vertical tunnel. A fowl stench seems to wash downwards over you from the room above. You can go Up or Down.",
/*17*/"By the smell, you know that you are in the Troll's Lair. There are piles of old bones, and some not so old. You shudder at the thought that you might be added to one of these piles. There is a ladder leading Down a hole in the ground.",
/*18*/"This room seems to make you dizzy... If you didn't have such a wonderful internal compass, it would be impossible to know which way is which now. The room is a hallway with exits to the ",
/*19*/"You are on a creaky walkway. It continues to the North, and there is solid ground to the South.",
/*20*/"You are on a creaky walkway. It continues to the North and South.",
/*21*/"You are on a creaky walkway. There is solid ground to the North, and more walkway to the South."};
	
	room = new Room*[numrooms];
	for(int i=0;i<17;i++)
		room[i] = new Room;
	room[17]= new SpinningRoom;
	for(int i=18;i<numrooms;i++)
		room[i] = new Room;
	//BoxPrint("CREATED ROOMS!");
	for(int i =0;i<numrooms;i++){
		room[i]->SetN((N[i]<0) ? NULL: room[N[i]]);
		room[i]->SetS((S[i]<0) ? NULL: room[S[i]]);
		room[i]->SetE((E[i]<0) ? NULL: room[E[i]]);
		room[i]->SetW((W[i]<0) ? NULL: room[W[i]]);
		room[i]->SetUp((Up[i]<0) ? NULL: room[Up[i]]);
		room[i]->SetDown((Down[i]<0) ? NULL: room[Down[i]]);
		room[i]->SetDesc(description[i]);
	}
	//BoxPrint("DONE WITH ROOMS!");
	
/********
ITEMS!!!!
********/
	room[1]->inv.AddItem(new Item("broken ladder", "The remains of a ladder lead down the hole. It is firmly fastened to the ground.",0,false,false));
	room[4]->inv.AddItem(new Item("ladder", "The ladder leads up through the trap door. It appears solid.",1,false,false));
	room[5]->inv.AddItem(new Item("inscription", "This mysterious inscription reads: \"Only the weak may obtain the Sword in the Stone.\"",100,false,false));
	room[5]->inv.AddItem(new Item("brick","This is a very heavy looking cinderblock.",45,false,true));
	room[7]->inv.AddItem(new Item("LOCK", "tiny key", 100, true, false));
	room[8]->inv.AddItem(new Item("lock", "This intricate mechanical system looks like it needs a tiny key to open it.",100,false,false));
	room[16]->inv.AddItem(new Crate("wooden box", "A small, inexpensive looking box. It seems glued to the floor."));
	static_cast<Crate*>(room[16]->inv.getItem("wooden box"))->inv.AddItem(new Item("tiny key", "A small, expensive looking key.",1,false,true));
	room[6]->inv.AddItem(new LockedCrate("stone crate", "A massive crate made of stone. There is a rusty, weak-looking lock fastened to it."));
	static_cast<Crate*>(room[6]->inv.getItem("stone crate"))->inv.AddItem(new Item("LOCK", "the weak lock",1,true,false));
	room[6]->inv.AddItem(new Item("weak lock", "A rusty, weak looking lock",100,false,false));
	static_cast<Crate*>(room[6]->inv.getItem("stone crate"))->inv.AddItem(new Item("adventure sword", "A beautiful sword, it fits perfectly in your hand.",6,false,true));
	

	room[12]->inv.AddItem(new Item("sign", "This poorly written sign says: \"DONE'T ENTUR.\"",100,false,false));
	
	
	room[rand()%20+1]->inv.AddItem(new Item("rock", "A boring rock. It looks like it has a little weight to it.",15,false, true));
	room[rand()%20+1]->inv.AddItem(new Item("rock", "A boring rock. It looks like it has a little weight to it.",15,false, true));
	room[rand()%20+1]->inv.AddItem(new Item("rock", "A boring rock. It looks like it has a little weight to it.",15,false, true));

	troll = new Troll(room[rand()%13+8]);
	
	//BoxPrint("CREATED TROLL");
	
	me = new Player(room[0]);
	Look();
}

Game::~Game(){
	for(int i=0;i<numrooms;i++)
		delete room[i];
	delete [] room;
	delete me;
}

bool Game::Move(Room* moveto){
	if(moveto!=NULL){
		if(moveto->Enter(me, false)){
			me->GetRoom()->inv.RemoveItem("PLAYER");
			me->SetRoom(moveto);
			me->GetRoom()->inv.AddItem(me->MyItem());
			
			Look();
			return true;
		}
	}
	else
		Print("You can't go that way!");
	return false;
}

void Game::Look(){
	me->GetRoom()->Describe();
}

bool Game::Examine(std::string name){
	Item* item = me->getItem(name);
	if(item==NULL)
		item = me->GetRoom()->getItem(name);
	if(item == NULL){
		Print("There is no "+name+" here.");
		return false;
	}
	else{
		if(!item->Hidden()){
			item->Describe();
			return true;
		}
		else{
			Print("There is no "+name+" here.");
			return false;
		}
	}
}

void Game::MoveTroll(Room* moveto){
	if(moveto!=NULL){
		if(moveto->Enter(troll, true)){
			troll->SetRoom(moveto);
			//BoxPrint("TrollSees: ");
			//troll->GetRoom()->Describe();
		}
	}
	//else
		//BoxPrint("Troll doesn't move");
}

void Game::Update(){
	me->Update();
	for(int i=0;i<numrooms;i++)
		room[i]->Update();
	if(troll)
		MoveTroll(troll->Move());
	if(troll){
		//std::cout<<troll->ShouldAttack();
		if(troll->ShouldAttack()){
			Battle("troll");
				return;
		}
	}
	if(troll)
		troll->Update();
	turn++;
}

bool Game::Battle(std::string name){
	Item* item  = me->GetRoom()->getItem(name);
	if(item){
		if(!item->Hidden()){
			if(name!="troll"){
				Print("You can't fight the "+name+".");
				return false;
			}
			else{
				Print("The Troll lunges forward at you!");
				if(me->inv.getItem("adventure sword")){
					Print("You swing the mighty adventure sword and slay the troll!");
					troll->Die();
					delete troll;
					troll=0;
				}
				else{
					Print("You are no match for this Troll without a weapon. He violently kills you and begins to prepare you as a meal.");
					dead=true;
				}
			}
		}
	}
	else{
		Print("There is no "+name+" here.");
		return false;
	}
}


void Game::Turn(std::string command){
	std::stringstream Command(command);
	std::string action;
	std::string item;
	std::string junk;
	if(dead){
		Print("You are dead.");
		return;
	}
	if (command == "look"){
		Look();
		Update();
	}
	else if (command == "n"|| command =="north"){
		if(me->CanMove())
			if(Move(me->GetRoom()->GetN()))
				Update();
	}
	else if (command == "s"||command=="south"){
		if(me->CanMove())
			if(Move(me->GetRoom()->GetS()))
				Update();
	}
	else if (command == "e"||command == "east"){
		if(me->CanMove())
			if(Move(me->GetRoom()->GetE()))
				Update();
	}
	else if (command == "w"|| command =="west"){
		if(me->CanMove())
			if(Move(me->GetRoom()->GetW()))
				Update();
	}
	else if (command == "up"|| command =="u"){
		if(me->CanMove())
			if(Move(me->GetRoom()->GetUp()))
				Update();
	}
	else if (command == "down"||command=="d"){
		if(me->CanMove())
			if(Move(me->GetRoom()->GetDown()))
				Update();
	}
	else if(command == "inventory")
		me->MyInv();
	else { 
		std::getline(Command,action,' ');
		if(action=="examine"){
			std::getline(Command,item);
			Examine(item);
		}
		else if(action == "take"){
			std::getline(Command, item);
			if(Take(item))
				Update();
		}
		else if(action == "drop"){
			std::getline(Command, item);
			if(Drop(item))
				Update();
		}
		else if(action == "open"){
			std::getline(Command, item);
			if(Open(item))
				Update();
		}
		else if(action=="close"){
			std::getline(Command, item);
			if(Close(item))
				Update();
		}
		else if(action=="fight"){
			std::getline(Command, item);
			if(Battle(item))
				Update();
		}
		else if(command=="smash weak lock with rock"){
			if(Smash())
				Update();
		}
		else
			Print("Unknown command!");
	}
}

bool Game::Smash(){
	Item* item = me->GetRoom()->inv.getItem("weak lock");
	if (item != NULL){
		Item* item2 = me->inv.getItem("rock");
		if (item2 != NULL){
			item->SetName("smashed lock");
			static_cast<Crate*>(me->GetRoom()->inv.getItem("stone crate"))->inv.getItem("LOCK")->SetName("UNLOCKED");
			Print("The lock breaks apart easily");
			return true;
		}
		else{
			Print("There is no rock here");
			return false;
		}
	}
	else{
		Print("There is no weak lock here");
		return false;
	}
}

bool Game::Take(std::string name){
	Item* item = me->GetRoom()->inv.getItem(name);
	if(item != NULL)
		if(!item->Hidden()){
			if(item->Movable()){
				me->GetRoom()->inv.RemoveItem(name);
				me->inv.AddItem(item);
				Print("You are now carrying the " +name);
				return true;
			}
			else{
				Print("That item is immovable");
				return false;
			}
		}
	Print("There is no "+name+" here");
	return false;
}

bool Game::Drop(std::string name){
	Item* item = me->inv.getItem(name);
	if(item != NULL)
		if(!item->Hidden()){
			if(item->Movable()){
				me->inv.RemoveItem(name);
				me->GetRoom()->inv.AddItem(item);
				Print("You drop the "+name+" to the floor");
				return true;
			}
			else{
				Print("You can't drop the "+name+" here");
				return false;
			}
		}
	Print("You don't have a "+name+" to drop");
	return false;
}

bool Game::Open(std::string name){
	Item* item = me->GetRoom()->inv.getItem(name);
	if(item != NULL)
		if(!item->Hidden()){
			if(item->Open())
				return true;
			return false;
		}
	Print("There is no "+name+" here");
	return false;
}

bool Game::Close(std::string name){
	Item* item = me->GetRoom()->inv.getItem(name);
	if(item != NULL)
		if(!item->Hidden()){
			if(item->Close())
				return true;
			return false;
		}
	Print("There is no "+name+" here");
	return false;
}



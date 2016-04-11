/********************************
             troll.cpp
 ********************************/
 #include "troll.h"
 
 Troll::Troll(){
	chase=false;
	attack=false;
	maxweight=50;
	myself = new Item("troll","A very smelly troll. He also looks quite mean. You should probably be running...",49,false,false);
};

Troll::Troll(Room* start){
	chase=false;
	attack=false;
	maxweight=50;
	myself = new Item("troll","A very smelly troll. He also looks quite mean. You should probably be running...",49,false,false);
	room=start;
	start->inv.AddItem(myself);
}

Room* Troll::Move(){//The heart of the Troll's AS (Artificial Stupidity)
	if(chase){
		if(GetRoom()->inv.getItem("PLAYER")){
			attack=true;
			return GetRoom();
		}
		if(GetRoom()->GetN())
			if(GetRoom()->GetN()->inv.getItem("PLAYER"))
				return GetRoom()->GetN();
		if(GetRoom()->GetS())
			if(GetRoom()->GetS()->inv.getItem("PLAYER"))
				return GetRoom()->GetS();
		if(GetRoom()->GetE())
			if(GetRoom()->GetE()->inv.getItem("PLAYER"))
				return GetRoom()->GetE();
		if(GetRoom()->GetW())
			if(GetRoom()->GetW()->inv.getItem("PLAYER"))
				return GetRoom()->GetW();
		if(GetRoom()->GetUp())
			if(GetRoom()->GetUp()->inv.getItem("PLAYER"))
				return GetRoom()->GetUp();
		if(GetRoom()->GetDown())
			if(GetRoom()->GetDown()->inv.getItem("PLAYER"))
				return GetRoom()->GetDown();
	}
	int dir=rand()%6;
	if(dir==0)
		return GetRoom()->GetN();
	if(dir==1)
		return GetRoom()->GetS();
	if(dir==2)
		return GetRoom()->GetE();
	if(dir==3)
		return GetRoom()->GetW();
	if(dir==4)
		return GetRoom()->GetUp();
	if(dir==5)
		return GetRoom()->GetDown();
	else
		return NULL;
}

void Troll::Update(){
	if(!chase){
		if(GetRoom()->inv.getItem("PLAYER")){
			Print("The Troll has spotted you!");
			chase=true;
		}
	}
	else{
		if(GetRoom()->inv.getItem("PLAYER"))
			Print("The Troll is chasing you!");
		else{
			chase=false;
			attack=false;
			Print("The Troll has lost you!");
		}
	}
}

void Troll::Die(){
	myself->SetName("troll carcass");
	myself->SetDesc("A filthy looking troll carcass. He smells worse now, if that's possible...");
	myself=0;
}


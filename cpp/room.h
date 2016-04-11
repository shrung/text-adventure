/********************************
             room.h
 ********************************/

#ifndef ROOM_H
#define ROOM_H 1
class Room;
#include "player.h"
#include "item.h"
#include "printer.h"

// This class will contain items and will change in response to commands
class Room{
protected:
	Room *N;
	Room *W;
	Room *S;
	Room *E;
	Room *Up;
	Room *Down; // Pointers to different directions that can be traveled
	//Item** inventory; // Each room has an inventory of items
	//Crate inventory;
	
	std::string description;

public:
	Inventory inv;
	Room();
	virtual ~Room();
	//Room(Room* N, Room* S, Room* E, Room* W, string description);
	void SetN(Room* n){N = n;};
	void SetS(Room* s){S = s;};
	void SetE(Room* e){E = e;};
	void SetW(Room* w){W = w;};
	void SetUp(Room* up){Up = up;};
	void SetDown(Room* down){Down = down;};
	virtual Room* GetN(){return N;};
	virtual Room* GetS(){return S;};
	virtual Room* GetE(){return E;};
	virtual Room* GetW(){return W;};
	virtual Room* GetUp(){return Up;};
	virtual Room* GetDown(){return Down;};
	
	void SetDesc(std::string desc){description = desc;};
	
	virtual bool Enter(Player* player,bool silent);
	
	//Item* getItem(int i);
	//These will need to call the functions in Player to have/give items
	//When asked to take, if it is successful, the Take function will call “have” on the player
	//Likewise for placing, if the room accepts an item, it will call “give” on the player.
	//void Take(string name, Player* player); takes the named item
	//void Place(Item * newitem, Player* player); //adds an item to the room
	
	//Item* Take(std::string name){return inventory.Take(name);}
	//void Place(Item* thing){inv.Place(thing);}

	virtual void Describe(); //prints out the room description, and describes all items in the room.
	Item * getItem(std::string name){return inv.getItem(name);};//will move the player to a room.

	int numItems(){return inv.getSize();}; //tells how many items are in the room
	//virtual Item* getItem(int i); 
	virtual void Update(); //Each room might want to do something each turn, and it will call update for all items in the room
};

class SpinningRoom:public Room{
private:
	bool state;
	std::string ew;
	std::string ns;
public:
	SpinningRoom();
	void Describe();
	bool Enter(Player* player,bool silent);
	void Update(){state=!state;inv.Update();};
	Room* GetN(){return (state ? N: NULL);};
	Room* GetS(){return (state ? S: NULL);};
	Room* GetE(){return (state ? NULL: E);};
	Room* GetW(){return (state ? NULL: W);};
};
#endif //ifndef ROOM_H
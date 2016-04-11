/********************************
             Item.h
 ********************************/

#ifndef ITEM_H
#define ITEM_H 1

#include<string>
#include "printer.h"

//This class is the basic item class
class Item{
protected:
	std::string name; //Every item will have a unique name (this name may be changed by the item if it is used or broken though)
	std::string description;
	int weight;
	//int lifetime;
	//bool works;
	bool invis;
	bool movable;

public:
	virtual bool isOpen()const{return false;};
	virtual bool Open(){Print("The "+name+" doesn't open");return false;};
	virtual bool Close(){Print("The "+name+" doesn't close");return false;};
	virtual bool Hidden(){return invis;};
	Item();
	virtual void setHidden(bool hid){invis = hid;};
	Item(std::string nom, std::string desc, int wt, bool hide, bool canmove);
	virtual ~Item();
	
	virtual int GetWeight(){return weight;};
	virtual void SetWeight(int w){weight = w;};
	//int GetLifetime(){return lifetime;};
	//void SetLifetime(int life){lifetime = life;};
	virtual bool Movable(){return movable;};
	std::string Name(){return name;};
	void SetName(std::string newname){name = newname;};
	void SetDesc(std::string newdesc){description=newdesc;};
	virtual void Update(); //Everything might want to do something each turn
	virtual std::string Description(){return description;}; 
	//Prints out the description (this will be looped over for all the items in a room, etc.)
	virtual void Describe(){Print(description);};
	//void Broken();
	//bool Works(){return works;}
};

//This class will facilitate a container for items. It is for things like a box or treasure chest or an inventory, etc.
class Inventory{
private:
	Item** data;
	int size;
	int numitems;
	void grow();
public:
	Inventory();
	~Inventory();
	void AddItem(Item* item);
	Item* getItem(std::string name);
	Item* RemoveItem(std::string name);
	int getSize(){return numitems;};
	bool visItems();
	int Weight();
	void List(int spaces=0);
	void Update();
};

class Crate : public Item{
protected:
	bool open;
public:
	void List(int spaces=0);
	bool isOpen()const{return open;};
	virtual bool Open(){Print("The "+name+" is now open");open=true;return true;};
	bool Close(){Print("The "+name+" is now closed");open = false;return true;};
	bool Movable(){return false;};
	Inventory inv;
	Crate();
	Crate(std::string nm, std::string desc);
	~Crate();
	void Describe();//this will describe all items inside if it’s openn
	//void Open(); //This will try to open the box
	//void Close();
//Description(); //if it’s open. this will print "The box contains:" and then ask for the description of each item inside.
	virtual void Update(); //Everything might want to do something each turn, so this will call update on pieces inside too.
};

class LockedCrate : public Crate{
	public:
		LockedCrate();
		LockedCrate(std::string nm, std::string desc);
		~LockedCrate(){};
		bool Open();
};



#endif // #ifndef ITEM_H
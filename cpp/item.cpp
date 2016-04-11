/********************************
             item.cpp
 ********************************/
#include "item.h"
#include <iostream>
#include <string.h>
#include <typeinfo>


Item::Item(){};

Item::Item(std::string nom, std::string desc, int wt, bool hide, bool canmove){
	name = nom;
	description = desc;
	weight = wt;
	invis = hide;
	movable = canmove;
	//lifetime = -1;
	//works = true;
}

Item::~Item(){};

/*
void Item::ChangeDesc(std::string desc){
	description == desc;
}
*/

void Item::Update(){
	//lifetime--;
	//if (lifetime == 0)
	//	Broken();
}

Crate::Crate(){
	open = false;
	invis=false;
	movable=false;
	name="crate_name";
	description="crate_description";
}

Crate::Crate(std::string nm, std::string desc){
	open=false;
	invis=false;
	movable=false;
	name = nm;
	description=desc;
}

Crate::~Crate(){
}

void Crate::Describe(){
	Print(Description());
	if (open){
		if(!inv.visItems())
			Print("The "+name+" appears to be empty.");
		else{
			Print("The "+name+" contains:");
			inv.List(4);
		}
	}
	else
		Print("The "+name+" is closed.");
}

void Crate::List(int spaces){
	if (open){
		if(!inv.visItems())
			Print("The "+name+" appears to be empty.");
		else{
			Print("The "+name+" contains:");
			inv.List(spaces+4);
		}
	}
	else
		Print("The "+name+" is closed.");
}

void Crate::Update(){
	inv.Update();
}

Inventory::Inventory(){
	size = 1;
	data = new Item* [size];
	for(int i = 0;i<size;i++)
		data[i] = NULL;
	numitems = 0;
}
Inventory::~Inventory(){
	for(int i = 0;i<size;i++)
		if(data[i]!=NULL)
			delete data[i];
	delete [] data;
}

void Inventory::AddItem(Item* item){
	if(numitems == size)
		grow();
	for(int i=0;i<size; i++)
		if(data[i] == NULL){
			data[i] = item;
			numitems++;
			break;
		}
}

bool Inventory::visItems(){
	for(int i=0;i<size;i++)
		if(data[i]!=NULL)
			if(!data[i]->Hidden())
				return true;
	return false;
}

Item* Inventory::RemoveItem(std::string name){
	Item* ret = NULL;
	for(int i = 0;i<size;i++){
		if(data[i]!=NULL){
			if(data[i]->isOpen())
				if(static_cast<Crate*>(data[i])->inv.getItem(name)!=NULL){
					ret=static_cast<Crate*>(data[i])->inv.getItem(name);
					static_cast<Crate*>(data[i])->inv.RemoveItem(name);
				}
			if(data[i]->Name()==name){
				ret = data[i];
				data[i] = NULL;
				numitems--;
				break;
			}
		}
	}
	return ret;
}

Item* Inventory::getItem(std::string name){
	for(int i = 0;i<size;i++)
		if(data[i]!=NULL){
			if(data[i]->isOpen())
				if(static_cast<Crate*>(data[i])->inv.getItem(name)!=NULL)
					return static_cast<Crate*>(data[i])->inv.getItem(name);
			if(data[i]->Name()==name)
				return data[i];
		}
	return NULL;
}

void Inventory::grow(){
	Item** newdata = new Item* [size*2];
	for(int i = 0;i<size; i++){
		newdata[i] = data[i];
		newdata[i+size] = NULL;
	}
	size = size*2;
	delete [] data;
	data = newdata;
}

int Inventory::Weight(){
	int w =0;
	for(int i =0;i<size;i++)
		if(data[i]!=NULL)
			w+= data[i]->GetWeight();
	return w;
}

void Inventory::List(int spaces){
	std::string pad="";
	for(int i=0;i<spaces;i++)
		pad=pad+" ";
	
	for(int i =0;i<size;i++)
		if(data[i]!=NULL)
			if(!(data[i]->Hidden())){
				Print(pad+data[i]->Name());
				if(data[i]->isOpen())
					static_cast<Crate*>(data[i])->List(spaces);
			}
}

void Inventory::Update(){
	for(int i =0;i<size;i++)
		if(data[i]!=NULL)
			data[i]->Update();
}
LockedCrate::LockedCrate(std::string nm, std::string desc){
	open=false;
	invis=false;
	movable=false;
	name = nm;
	description=desc;
}


bool LockedCrate::Open(){
	Item* item = inv.getItem("LOCK");
	if (item != NULL){
		Print("The "+name+" is locked");
		return false;
	}
	else{
		Print("The "+name+" is open");
		open=true;
		return true;
	}
}
	

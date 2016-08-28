# player.py

from printer import *
from room import *
from item import *

MAXITEMS = 10

class Player:
    def __init__(self,start = None):
        self._myself = Item(name="PLAYER",description = "the user",weight = 49,hidden = True, movable = False)
        if start == None:
            self._room  = Room()
        else:
            self._room = start
            start.inv.AddItem(self._myself)        
        self._maxweight = 50
        self.inv=Inventory()
    def MyInv(self):
        if self.inv.visItems():
            Print("You are carrying:")
            self.inv.List()
        else:
            Print("You are not carrying anything")
    def MyItem(self):
        return self._myself
    def numItems(self):
        return self.inv.getSize()
    def GetWeight(self):
        return self.inv.Weight()
    def Update(self):
        pass
    def CanMove(self):
        if self.GetWeight() > self._maxweight:
            Print("You are carrying too much weight to move!")
            return False
        else:
            return True
    def GetRoom(self):
        return self._room
    #def Take(name):
     #   pass
    #def Place(name):
     #   pass
    def SetRoom(self,newroom):
        self._room = newroom
    def getItem(self,name):
        return self.inv.getItem(name)

        
        
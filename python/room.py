# -*- coding: utf-8 -*-
"""
Created on Sat Aug 27 14:31:12 2016

@author: Roy
"""

from player import *
from item import *
from printer import *

class Room:
#protected variables
#public variables and functions
#defines adjoining rooms and such
    def __init__(self):
        self._description = "this room has not been configured."
        self.inv = Inventory()
    def SetN(self,n):
        self._N = n
    def SetS(self,s):
        self._S = s
    def SetE(self,e):
        self._E = e
    def SetW(self,w):
        self._W = w
    def SetUp(self,up):
        self._Up = up
    def SetDown(self,down):
        self._Down = down
    def GetN(self):
        return self._N
    def GetS(self):
        return self._S
    def GetE(self):
        return self._E
    def GetW(self):
        return self._W
    def GetUp(self):
        return self._Up
    def GetDown(self):
        return self._Down
    def SetDesc(self,desc):
        self._description = desc
    
    def Enter(self,player,silent):
        lock = self.inv.getItem("LOCK")
        if(player.GetRoom == self.GetN() or
           player.GetRoom == self.GetS() or
           player.GetRoom == self.GetE() or
           player.GetRoom == self.GetS() or
           player.GetRoom == self.GetUp() or
           player.GetRoom == self.GetDown()):
            if lock != None:
                if player.getItem(lock.self._description()) != None:
                    if not silent:
                        Print("You unlock the door with the",lock.self._description)
                    self.inv.getItem("LOCK").SetName("UNLOCKED")
                    return(Enter(self,player,silent))
                elif not silent:
                    Print("That room is locked!")
                    return False
            else:
                return True
        elif not silent:
            Print("You can't go that way!")
            return False
        
    def Describe(self):
        Print(self._description)
        if self.inv.visItems():
            Print("The room contains:")
            self.inv.List()
    def getItem(self,name):
        return self.inv.getItem(name)
    def numItems(self):
        return self.inv.getSize()
    def Update(self):
        self.inv.Update()
class SpinningRoom(Room):
#protected variables
#public variables
    
    def __init__(self):
        self._state = False
        self._ew = "East and West."
        self._ns = "North and South."
        self.inv = Inventory()
    def Describe(self):
        if self._state:
            Print(self._description+self._ew)
        else: 
            Print(self._description+self._ns)
        if self.inv.visItems():
            Print("The room contains:")
            inv.List()
    def Enter(self,player,silent):
        lock = self.inv.getItem("LOCK")
        if((_state and player.getRoom() == getN())
           or player.getRoom() == getS() 
           or(not state and player.getRoom() == getE())
           or player.getRoom() == getW()
           or player.getRoom() == getUp()
           or player.getRoom() == getDown()
           ):
            if lock != None:
                if player.getItem(lock.Description()) != None:
                    if not silent:
                        Print("You unlock the door with the " + lock.Description())
                    self.inv.getItem("LOCK").SetName("UNLOCKED")
                    return Enter(player,silent)
                elif not silent:
                    Print("That room is locked!")
                    return False
            else:
                return True
        elif not silent:
            Print("The door isn't there right now!")
            return False
    
    def Update(self):
        self._state = not self._state
        self.inv.Update()
        
    def getN(self):
        if self._state == True:
            return self._N
        else:
            return None
    def getS(self):
        if self._state == True:
            return self._S
        else:
            return None
    def getE(self):
        if self._state == True:
            return self._E
        else:
            return None
    def getW(self):
        if self._state == True:
            return self._W
        else:
            return None
    
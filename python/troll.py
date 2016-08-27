# troll.py

from printer import *
from item import *
from player import *
from room import *
import random

class Troll(Player):
    _attack
    _chase
    _myself
    def __init__(self,start = None):
        self._chase = False
        self._attack = False
        self._maxweight = 50
        self._myself = Item(name = "troll",description = "A very smelly troll. He also looks quite mean. You should probably be running...",weight = 49,hidden = false, movable = false)
        if start == None:
            self._room  = Room()
        else:
            self._room = start
            start.inv.AddItem(self._myself)
    def Die(self):
        self._room.inv.RemoveItem("troll")
        self._myself.SetName("troll carcass")
        self._myself.SetDesc("A filthy looking troll carcass. He smells worse now, if that's possible...")
        self._room.inv.AddItem(self._myself)
        self._myself= None
    def ShouldAttack(self):
        return self._attack
    def Move(self):
        if self._chase:
            if self.GetRoom().inv.getItem("PLAYER"):
                self._attack=True
                return self.GetRoom()
			if self.GetRoom().GetN():
                if self.GetRoom().GetN().inv.getItem("PLAYER"):
                    return self.GetRoom().GetN()
            if self.GetRoom().GetS():
                if self.GetRoom().GetS().inv.getItem("PLAYER"):
                    return self.GetRoom().GetS()
            if self.GetRoom().GetE():
                if self.GetRoom().GetE().inv.getItem("PLAYER"):
                    return self.GetRoom().GetE()
            if self.GetRoom().GetW():
                if self.GetRoom().GetW().inv.getItem("PLAYER"):
                    return self.GetRoom().GetW()
            if self.GetRoom().GetUp():
                if self.GetRoom().GetUp().inv.getItem("PLAYER"):
                    return self.GetRoom().GetUp()
            if self.GetRoom().GetDown():
                if self.GetRoom().GetDown().inv.getItem("PLAYER"):
                    return self.GetRoom().GetDown()

        dir=random.randint(0,5)
        if dir==0:
            return self.GetRoom().GetN()
        if dir==1:
            return self.GetRoom().GetS()
        if dir==2:
            return self.GetRoom().GetE()
        if dir==3:
            return self.GetRoom().GetW()
        if dir==4:
            return self.GetRoom().GetUp()
        if dir==5:
            return self.GetRoom().GetDown()
        else:
            return None
    def SetRoom(self,newroom):
        self._room.inv.RemoveItem("troll")
        self._room = newroom
        self._room.inv.AddItem(self._myself)
    def Update(self):
        if not self._chase:
            if self.GetRoom().inv.getItem("PLAYER"):
                Print("The Troll has spotted you!")
                self._chase = True
        else:
            if self.GetRoom().inv.getItem("PLAYER"):
                Print("The Troll is chasing you!")
            else:
                self._chase = False
                self._attack = False
                Print("The Troll has lost you!")
    
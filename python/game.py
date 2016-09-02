#game.py

from printer import *
from item import *
from player import *
from room import *
from troll import *

class Game:
    def _MoveTroll(self,moveto):
        if moveto != None:
            if moveto.Enter(self._troll,True):
                self._troll.SetRoom(moveto)
    def _Look(self):
        self._rooms[self._me.GetRoom()].Describe()
    def _Examine(self,name):
        item = self._me.getItem(name)
        if item == None:
            item = self._rooms[self._me.GetRoom()].getItem(name)
        if item == None:
            Print("There is no "+name+" here.")
            return False
        else:
            if not item.Hidden():
                item.Describe()
                return True
            else:
                Print("There is no "+name+" here.")
                return False
    def _Smash(self):
        item = self._rooms[self._me.GetRoom()].inv.getItem("weak lock")
        if item != None:
            item2 = self._me.inv.getItem("rock")
            if item2 != None:
                item.SetName("smashed lock");
                self._rooms[self._me.GetRoom()].inv.getItem("stone crate").inv.getItem("LOCK").SetName("UNLOCKED")
                Print("The lock breaks apart easily")
                return True
            else:
                Print("There is no rock here")
                return False
        else:
            Print("There is no weak lock here")
            return False
    def _Battle(self,name):
        item  = self._rooms[self._me.GetRoom()].getItem(name);
        if item != None:
            if not item.Hidden():
                if name != "troll":
                    Print("You can't fight the "+name+".")
                    return False
                
                else:
                    Print("The Troll lunges forward at you!")
                    if self._me.inv.getItem("adventure sword"):
                        Print("You swing the mighty adventure sword and slay the troll!")
                        self._troll.Die()
                        del self._troll
                    else:
                        Print("You are no match for this Troll without a weapon. He violently kills you and begins to prepare you as a meal.")
                        self._dead= True;
        else:
            Print("There is no "+name+" here.")
            return False
    def _Take(self, name):
        item = self._rooms[self._me.GetRoom()].inv.getItem(name)
        if item != None:
            if not item.Hidden():
                if item.Movable():
                    self._rooms[self._me.GetRoom()].inv.RemoveItem(name)
                    self._me.inv.AddItem(item)
                    Print("You are now carrying the "+name)
                    return True
                else:
                    Print("That item is immovable")
                    return False
        Print("There is no "+name+" here")
        return False
    def _Drop(self, name):
        item = self._me.inv.getItem(name)
        if item != None:
            if not item.Hidden():
                if item.Movable():
                    self._me.inv.RemoveItem(name)
                    self._rooms[self._me.GetRoom()].inv.AddItem(item)
                    Print("You drop the "+name+" to the floor")
                    return True
                else:
                    Print("You can't drop the "+name+" here")
                    return False
        Print("You don't have a "+name+" to drop")
        return False
    def _Open(self, name):
        item = self._rooms[self._me.GetRoom()].inv.getItem(name)
        if item != None:
            if not item.Hidden():
                if item.Open():
                    return True
                return False
        Print("There is no "+name+" here")
        return False
    def _Close(self, name):
        item = self._rooms[self._me.GetRoom()].inv.getItem(name)
        if item != None:
            if not item.Hidden():
                if item.Close():
                    return True
                return False
        Print("There is no "+name+" here");
        return False
    def _Update(self):
        self._me.Update()
        for room in self._rooms:
            room.Update()
        if self._troll:
            newroom = self._troll.Move()
            if newroom != None:
                self._MoveTroll(self._rooms[newroom])
        if self._troll:
            if self._troll.ShouldAttack():
                self._Battle("troll")
                return
        if self._troll:
            self._troll.Update()
        self._turn=self._turn+1
    def _Move(self,moveto):
        #print(moveto)
        if moveto != None:
            if self._rooms[moveto].Enter(self._me, False):
                self._rooms[self._me.GetRoom()].inv.RemoveItem("PLAYER")
                self._me.SetRoom(moveto)
                self._rooms[self._me.GetRoom()].inv.AddItem(self._me.MyItem())
                self._Look()
                return True
        else:
            Print("You can't go that way!")
        return False
    def Turn(self, command):
        wordlist = command.split(sep = " ",maxsplit = 1)
        action = wordlist[0]
        if len(wordlist)>1:
            item = wordlist[1]
        else:
            item = ""
        if self._dead:
            Print("You are dead.")
            return
        if command == "look":
            self._Look()
            self._Update()
        elif command == "n" or command == "north":
            if self._me.CanMove():
                if self._Move(self._rooms[self._me.GetRoom()].GetN()):
                    self._Update()
        elif command == "s" or command == "south":
            if self._me.CanMove():
                if self._Move(self._rooms[self._me.GetRoom()].GetS()):
                    self._Update()
        elif command == "e" or command == "east":
            if self._me.CanMove():
                if self._Move(self._rooms[self._me.GetRoom()].GetE()):
                    self._Update()
        elif command == "w" or command == "west":
            if self._me.CanMove():
                if self._Move(self._rooms[self._me.GetRoom()].GetW()):
                    self._Update()
        elif command == "u" or command == "up":
            if self._me.CanMove():
                if self._Move(self._rooms[self._me.GetRoom()].GetUp()):
                    self._Update()
        elif command == "d" or command == "down":
            if self._me.CanMove():
                if self._Move(self._rooms[self._me.GetRoom()].GetDown()):
                    self._Update()
        elif command == "inventory":
            self._me.MyInv()
        else: 
            if action=="examine":
                self._Examine(item)
            elif action == "take":
                if self._Take(item):
                    self._Update()
            elif action == "drop":
                if self._Drop(item):
                    self._Update()
            elif action == "open":
                if self._Open(item):
                    self._Update()
            elif action=="close":
                if self._Close(item):
                    self._Update()
            elif action=="fight":
                if self._Battle(item):
                    self._Update()
            elif command=="smash weak lock with rock":
                if self._Smash():
                    self._Update()
            else:
                Print("Unknown command!")
    def __init__(self):
        self._dead=False
        self._turn = 0
        self._score = 0
        self._numrooms = 21
        N =    [ 1, 3,17,None,None,None,None,None,None, 8, 9,None,10,18,None,None,None, 5,19,20,14]
        S =    [None, 0,None, 1,None,17,None,None, 9,10,12,None,None,None,20,None,None, 2,13,18,19]
        E =    [None, 2,None,17,None,None,None, 8,None,None,11,None,None,None,None,None,None, 4,None,None,None]
        W =    [None,None, 1,None,17,None,None,None, 7,None,None,10,None,None,None,None,None, 3,None,None,None]
        Up =   [None,None,None,None, 6,None,None,None,None,None,None, 1,None,12,15,16,None,None,None,None,None]
        Down = [None,11,None,None,None,None, 4,None,None,None,None,None,13,None,None,14,15,None,None,None,None]
        
        description = [
    "You are in a boring, unimaginative, nondescript, plain, old, ugly, room. There is a door leading to the North. Nothing else.",
    "You are standing in a large room. There is a hole in the ground that looks large enough to climb Down. There are also two corridors. One leading North, and one leading East.",
    "This passageway has an exit to the West and a door to the North. The door seems to come and go, but it is moving slow enough to enter safely.",
    "This winding passageway has an exit to the South and a door to the East. The door seems to come and go, but it is moving slow enough to enter safely.",
    "At the end of this corridor a trap door is hanging open on the ceiling, and a ladder leads Up through it. There is a door to the West which seems to be moving by the wall.",
    "This room is a dead end. It is elaborately decorated and the inscription on the far wall seems to be calling to you. There is a door to the South.",
    "You are in a high tower room. There is a hole in the ground with a ladder leading Down.",
    "Congratulations! You have made it to the treasure room! (That means you win) There is treasure all around. Congratulations.",
    "The space seems to open up here. There is a small, dirty looking tunnel to the South, and a door to the West. It has a complex looking locking system with a single small keyhole.",
    "You find yourself crawling through what appears to be a filthy mud puddle. You can go North or South.",
    "The tunnel makes a 'T' here, and you can crawl North, South, or East.",
    "You are in a hole in the ground. There is a tunnel leading off to the West, and with a little effort, you may be able to climb back Up.",
    "The tunnel leads North, and there is a much nastier looking hole here leading Down. It smells pretty bad.",
    "The smell down here is pretty bad. A hole leads Upwards to fresher air, and a long, creaky looking, walkway leads to the North.",
    "The smell here is nearly unbearable, and it seems to emanate from above. A ladder leads Up, and a creaky walkway leads to the South.",
    "You are on a ladder in a vertical tunnel. A fowl stench seems to wash downwards over you from the room above. You can go Up or Down.",
    "By the smell, you know that you are in the Troll's Lair. There are piles of old bones, and some not so old. You shudder at the thought that you might be added to one of these piles. There is a ladder leading Down a hole in the ground.",
    "This room seems to make you dizzy... If you didn't have such a wonderful internal compass, it would be impossible to know which way is which now. The room is a hallway with exits to the ",
    "You are on a creaky walkway. It continues to the North, and there is solid ground to the South.",
    "You are on a creaky walkway. It continues to the North and South.",
    "You are on a creaky walkway. There is solid ground to the North, and more walkway to the South."]
        
        self._rooms = []
        for i in range(0,17):
            temproom = Room()
            self._rooms.append(temproom)
        temproom = SpinningRoom()
        self._rooms.append(temproom)
        for i in range(18,self._numrooms):
            temproom = Room()
            self._rooms.append(temproom)
        #BoxPrint("CREATED ROOMS!");
        for i in range(0,self._numrooms):
            self._rooms[i].SetHere(i)
            self._rooms[i].SetN(N[i])
            #print(str(self._rooms[i].GetN())+ " is north of room "+str(i))
            self._rooms[i].SetS(S[i])
            self._rooms[i].SetE(E[i])
            self._rooms[i].SetW(W[i])
            self._rooms[i].SetUp(Up[i])
            self._rooms[i].SetDown(Down[i])
            self._rooms[i].SetDesc(description[i])
        #BoxPrint("DONE WITH ROOMS!");
        
    #/********
    #ITEMS!!!!
    #********/
        self._rooms[1].inv.AddItem(Item("broken ladder", "The remains of a ladder lead down the hole. It is firmly fastened to the ground.",0,False,False))
        self._rooms[4].inv.AddItem(Item("ladder", "The ladder leads up through the trap door. It appears solid.",1,False,False))
        self._rooms[5].inv.AddItem(Item("inscription", "This mysterious inscription reads: \"Only the weak may obtain the Sword in the Stone.\"",100,False,False))
        self._rooms[5].inv.AddItem(Item("brick","This is a very heavy looking cinderblock.",45,False,True))
        self._rooms[7].inv.AddItem(Item("LOCK", "tiny key", 100, True, False))
        self._rooms[8].inv.AddItem(Item("lock", "This intricate mechanical system looks like it needs a tiny key to open it.",100,False,False))
        self._rooms[16].inv.AddItem(Crate("wooden box", "A small, inexpensive looking box. It seems glued to the floor."))
        self._rooms[16].inv.getItem("wooden box").inv.AddItem(Item("tiny key", "A small, expensive looking key.",1,False,True))
        self._rooms[6].inv.AddItem(LockedCrate("stone crate", "A massive crate made of stone. There is a rusty, weak-looking lock fastened to it."))
        self._rooms[6].inv.getItem("stone crate").inv.AddItem(Item("LOCK", "the weak lock",1,True,False))
        self._rooms[6].inv.AddItem(Item("weak lock", "A rusty, weak looking lock",100,False,False))
        self._rooms[6].inv.getItem("stone crate").inv.AddItem(Item("adventure sword", "A beautiful sword, it fits perfectly in your hand.",6,False,True))
        

        self._rooms[12].inv.AddItem(Item("sign", "This poorly written sign says: \"DONE'T ENTUR.\"",100,False,False))
        
        
        self._rooms[random.randint(1,20)].inv.AddItem(Item("rock", "A boring rock. It looks like it has a little weight to it.",15,False, True))
        self._rooms[random.randint(1,20)].inv.AddItem(Item("rock", "A boring rock. It looks like it has a little weight to it.",15,False, True))
        self._rooms[random.randint(1,20)].inv.AddItem(Item("rock", "A boring rock. It looks like it has a little weight to it.",15,False, True))

        self._troll = Troll(self._rooms[random.randint(8,20)])
        
        #//BoxPrint("CREATED TROLL");
        
        self._me = Player(0)
        self._rooms[0].inv.AddItem(self._me.MyItem())
        #print(self._rooms[self._me.GetRoom()].GetN())
        self._Look()

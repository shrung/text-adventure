#game.py

from printer import *
from item import *
from player import *
from room import *
from troll import *

class Game:
    _troll
    _numrooms
    _numitems
    _rooms
    _me
    _turn
    _score
    _dead
    def _MoveTroll(self,moveto):
        if moveto != None:
            if moveto.Enter(self._troll,true):
                self._troll.SetRoom(moveto)
    def _Look(self):
        self._me.GetRoom().Describe()
    def _Examine(self,name):
        item = self._me.getItem(name)
        if item == None:
            item = self._me.GetRoom().getItem(name)
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
        item = self._me.GetRoom().inv.getItem("weak lock")
        if item != None:
            item2 = self._me.inv.getItem("rock")
            if item2 != None:
                item.SetName("smashed lock");
                self._me.GetRoom().inv.getItem("stone crate").inv.getItem("LOCK").SetName("UNLOCKED")
                Print("The lock breaks apart easily")
                return True
            else:
                Print("There is no rock here")
                return False
        else:
            Print("There is no weak lock here")
            return False
    def _Battle(self,name):
        item  = self._me.GetRoom().getItem(name);
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
        item = self._me.GetRoom().inv.getItem(name)
        if item != None:
            if not item.Hidden():
                if item.Movable():
                    self._me.GetRoom().inv.RemoveItem(name)
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
                    self._me.GetRoom().inv.AddItem(item)
                    Print("You drop the "+name+" to the floor")
                    return True
                else:
                    Print("You can't drop the "+name+" here")
                    return False
        Print("You don't have a "+name+" to drop")
        return False
    def _Open(self, name):
        item = self._me.GetRoom().inv.getItem(name)
        if item != None:
            if not item.Hidden():
                if item.Open():
                    return True
                return False
        Print("There is no "+name+" here")
        return False
    def _Close(self, name):
        item = self._me.GetRoom().inv.getItem(name)
        if item != None:
            if not item.Hidden():
                if item.Close():
                    return True
                return False
        Print("There is no "+name+" here");
        return False
    def _Update():
        self._me.Update()
        for room in self._rooms
            room.Update()
        if self._troll:
            self._MoveTroll(self._troll.Move())
        if self._troll:
            if self._troll.ShouldAttack():
                self._Battle("troll")
                return
        if self._troll:
            self._troll.Update()
        self._turn++
    def _Move(moveto):
        if moveto != None:
            if moveto.Enter(self._me, False):
                self._me.GetRoom().inv.RemoveItem("PLAYER")
                self._me.SetRoom(moveto)
                self._me.GetRoom().inv.AddItem(self._me.MyItem())
                self._Look()
                return True
        else:
            Print("You can't go that way!")
        return False
    def Turn(self, command):
        wordlist = command.split(sep = " ",maxsplit = 1)
        action = wordlist[0]
        item = wordlist[1]
        if self._dead:
            Print("You are dead.")
            return
        if command == "look":
            self._Look()
            self._Update()
        elif command == "n" or command == "north":
            if self._me.CanMove():
                if self._Move(self._me.GetRoom().GetN()):
                    self._Update()
        elif command == "s" or command == "south":
            if self._me.CanMove():
                if self._Move(self._me.GetRoom().GetS()):
                    self._Update()
        elif command == "e" or command == "east":
            if self._me.CanMove():
                if self._Move(self._me.GetRoom().GetE()):
                    self._Update()
        elif command == "w" or command == "west":
            if self._me.CanMove():
                if self._Move(self._me.GetRoom().GetW()):
                    self._Update()
         elif command == "u" or command == "up":
            if self._me.CanMove():
                if self._Move(self._me.GetRoom().GetUp()):
                    self._Update()
        elif command == "d" or command == "down":
            if self._me.CanMove():
                if self._Move(self._me.GetRoom().GetDown()):
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
        N =    [ 1, 3,17,-1,-1,-1,-1,-1,-1, 8, 9,-1,10,18,-1,-1,-1, 5,19,20,14]
        S =    [-1, 0,-1, 1,-1,17,-1,-1, 9,10,12,-1,-1,-1,20,-1,-1, 2,13,18,19]
        E =    [-1, 2,-1,17,-1,-1,-1, 8,-1,-1,11,-1,-1,-1,-1,-1,-1, 4,-1,-1,-1]
        W =    [-1,-1, 1,-1,17,-1,-1,-1, 7,-1,-1,10,-1,-1,-1,-1,-1, 3,-1,-1,-1]
        Up =   [-1,-1,-1,-1, 6,-1,-1,-1,-1,-1,-1, 1,-1,12,15,16,-1,-1,-1,-1,-1]
        Down = [-1,11,-1,-1,-1,-1, 4,-1,-1,-1,-1,-1,13,-1,-1,14,15,-1,-1,-1,-1]
        
        description[] = [
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
            self._rooms.SetN((N[i]<0) ? NULL: room[N[i]]);
            room[i]->SetS((S[i]<0) ? NULL: room[S[i]]);
            room[i]->SetE((E[i]<0) ? NULL: room[E[i]]);
            room[i]->SetW((W[i]<0) ? NULL: room[W[i]]);
            room[i]->SetUp((Up[i]<0) ? NULL: room[Up[i]]);
            room[i]->SetDown((Down[i]<0) ? NULL: room[Down[i]]);
            room[i]->SetDesc(description[i]);
        }
        #BoxPrint("DONE WITH ROOMS!");
        
    #/********
    #ITEMS!!!!
    #********/
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

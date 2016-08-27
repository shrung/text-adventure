# item.py

from printer import *

class Item:
    _name
    _description
    _weight
    _invis
    _movable
    def isOpen(self):
        return False
    def Open(self):
        Print("The "+self._name+" doesn't open")
    def Close(self):
        Print("The "+self._name+" doesn't close")
        return False
	def Hidden(self):
        return self._invis
	def __init__(self,name="",description="",weight=0,hidden=False,movable=True):
        self._name=name
        self._description=description
        self._weight = weight
        self._invis = hidden
        self._movable = movable
	def setHidden(self,hid):
        self._invis = hid
	
	def GetWeight(self):
        return self._weight
	def SetWeight(self,w)
        self._weight = w
	#int GetLifetime(){return lifetime;};
	#void SetLifetime(int life){lifetime = life;};
	def Movable(self):
        return self._movable
	def Name(self):
        return self._name
	def SetName(self,newname):
        self._name = newname
	def SetDesc(self,newdesc):
        self._description=newdesc
	def Update(self):
        pass
	def Description(self):
        return self._description 
	#Prints out the description (this will be looped over for all the items in a room, etc.)
	def Describe(self):
        Print(self._description)
	#void Broken();
	#bool Works(){return works;}
class Inventory:
    _data
    def __init__(self):
        self._data=[]
    def AddItem(self,item):
       self._data.append(item)
    def getItem(self,name):
        for i in self._data:
            if i.isOpen():
                return i.inv.getItem(name)
            if i.GetName() == name:
                return i
        return None
    def RemoveItem(self,name):
        ret = self._data.getItem(name)
        self._data.remove(ret)
        for i in _data:
            if i.isOpen():
                i.inv.RemoveItem(name)            
        return ret
    def getSize(self):
        return len(self._data)
    def visItems(self):
        for i in self._data:
            if not i.Hidden()
                return True
        return False
    def Weight(self):
        w = 0
        for i in self._data:
            w += i.GetWeight()
        return w
    def List(self,spaces=0):
        pad = ""
        for i in Range(0,spaces):
            pad = pad+ ' '
        for i in self._data:
            if not i.Hidden():
                Print(pad+i.Name())
                if i.isOpen():
                    i.List(spaces)
    def Update(self):
        for i in self._data:
            i.Update()

class Crate(Item):
    _open
    inv
    def List(self,spaces=0):
        if self._open:
            if not self.inv.visItems():
                Print("The "+self._name+" appears to be empty.")
            else:
                Print("The "+self._name+" contains:");
                self.inv.List(spaces+4)
    def isOpen(self):
        return self._open
    def Open(self):
        Print("The "+self._name+" is now open")
        self._open = True
        return True
    def Close(self):
        Print("The "+self._name+" is now closed")
        self._open= False
        return True
    def Movable(self):
        return False
    def __init__(self, name="",description = ""):
        self.inv = Inventory()
        self._open = False
        self._invis = False
        self._movable = False
        self._name = name
        self._description = description
    def Describe(self):
        Print(Description())
        if self._open:
            if not self.inv.visItems():
                Print("The "+self._name+" appears to be empty.")
            else:
                Print("The "+self._name+" contains:")
                self.inv.List(4)
        else:
            Print("The "+self._name+" is closed.")
    def Update(self):
        self.inv.Update()
class LockedCrate(Crate):
    def __init__(self, name = "", description = ""):
        self.inv = Inventory()
        self._open = False
        self._invis=False
        self._movable =False
        self._name = name
        self._description = description
    def Open(self):
        item = self.inv.getItem("LOCK")
        if item != None:
            Print("The "+self._name+" is locked")
            return False
        else:
            Print("The "+self._name+" is open")
            self._open = True
            return True

        
        
    
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
	_N
	_W
	_S
	_E
	_Up
	_Down
	_description

#public variables and functions
#defines adjoining rooms and such
	inv
	def __init__(self):
		_description = "this room has not been configured."
	def SetN(n):
		_N = n
	def SetS(s):
		_S = s
	def SetE(e):
		_E = e
	def SetW(w):
		_W = w
	def Up(up):
		_Up = up
	def Down(down):
		_Down = down
	def GetN():
		return _N
	def GetS():
		return _S
	def GetE():
		return _E
	def GetW():
		return _W
	def GetUp():
		return _Up
	def GetDown():
		return _Down
	def SetDesc(desc):
		_description = desc
	
	def Enter(player,silent):
		lock = inv.getItem("LOCK")
		if(player.GetRoom == GetN() or
		   player.GetRoom == GetS() or
		   player.GetRoom == GetE() or
		   player.GetRoom == GetS() or
		   player.GetRoom == GetUp() or
		   player.GetRoom == GetDown()):
			if lock != None:
				if player.getItem(lock._description()) != None:
					if not silent:
						Print("You unlock the door with the",lock._description)
					inv.getItem("LOCK").SetName("UNLOCKED")
					return(Enter(player,silent))
				elif not silent:
					Print("That room is locked!")
					return False
			else:
				return True
		elif not silent:
			Print("You can't go that way!")
			return False
		
				
		
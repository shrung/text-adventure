# printer.py

import textwrap

WRAP = 49

def PrintAdventure():
    lines=[
    "             _                 _                  _ ",
    "    /\\      | |               | |                | |",
    "   /  \\   __| |_   _____ _ __ | |_ _   _ _ __ ___| |",
    "  / /\\ \\ / _` \\ \\ / / _ \\ '_ \\| __| | | | '__/ _ \\ |",
    " / ____ \\ (_| |\\ V /  __/ | | | |_| |_| | | |  __/_|",
    "/_/    \\_\\__,_| \\_/ \\___|_| |_|\\__|\\__,_|_|  \\___(_)"]

    for line in lines:
        print(line)

# Constrains lines to 'WRAP' characters. Pay attention Miller, this is called
# COMMENTING.This is good coding practice. You should comment! It's really
# HELPFUL.
def Print(words):
	lines = textwrap.wrap(words,WRAP)
	for line in lines:
		print(line)

#Constrains lines to 'WRAP' characters and puts em in a nice lil box.	
def BoxPrint(words):
	for i in range(0,WRAP):
		print("-", end = "") #this creates our horizontal line
	print("")
	edge = WRAP-4
	lines = textwrap.wrap(words,edge)		
	for line in lines:
		pad = edge-len(line) #define the number of spaces to line up '|'
		print("|",line, end = "") #our vertical line
		for j in range(0,pad):
			print(" ",end = "")
		print(" |")
	for i in range(0,WRAP):
		print("-", end = "")
	print("")
	
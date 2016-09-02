from printer import *
from game import *
import random
import time

def main():
    seed = time.time()
    random.seed(seed)
    command = ""
    
    PrintAdventure()
    BoxPrint("Hello, and welcome to the greatest text based game ever experienced by anyone in history. Type \"Help\" for a list of commands. Type \"q\" to quit.")
    quit = False
    restart = False
    mygame = Game()
    save = ""
    fname = ""
    while True:
        command = input(">>").lower()
        Print("")

        if restart or quit:
            if command == "y" or command == "yes":
                if quit:
                    break
                else:
                    del mygame
                    mygame = Game()
                    save = ""
                    restart = False
            else:
                quit = False
                restart = False
        else:
            quit = False
            restart = False
            if command == "q" or command=="quit":
                BoxPrint("Aren't you having fun?! Are you sure you absolutely have to exit? (yes or no?)")
                quit = True
            elif command == "restart":
                    BoxPrint("Are you sure you want to restart? (yes or no?)")
                    restart = True
            elif command =="save":
                BoxPrint("Enter filename for save:")
                fname = input()
                try:
                    with open(fname,'w') as Save:
                        Save.write(str(seed)+"\n")
                        Save.write(save)
                except IOError:
                    BoxPrint("Error opening file. Your game is not saved.")
            elif command == "load":
                BoxPrint("Enter filename to load:")
                fname = input()
                try:
                    with open(fname,'r') as Load:
                        save = "";
                        seed = float(Load.readline())
                        random.seed(seed)
                        del mygame;
                        mygame = Game();
                        for line in Load:
                            command = line.rstrip()
                            if command != "":
                                Print(">>"+command)
                                mygame.Turn(command);
                                save = save+"\n"+command
                except IOError:
                    BoxPrint("Error opening file. Unable to load game.")
            elif command == "help":
                BoxPrint("\"n\" or \"north\" --- Moves to the north. The other directions are similar.")
                BoxPrint("\"look\" --- Looks around the room you are in. (Takes time...)")
                BoxPrint("\"inventory\" --- Lists the items you are currently carrying.")
                BoxPrint("\"examine <item>\" --- Gives a description of <item>.")
                BoxPrint("\"take <item>\" --- Pick up <item>.")
                BoxPrint("\"drop <item>\" --- Drop <item>.")
                BoxPrint("\"open <item>\" --- Opens <item>.")
                BoxPrint("\"close <item>\" --- Closes <item>.")
                BoxPrint("\"smash <item> with <item>\" --- Works for some specific items...")
                BoxPrint("\"fight <item>\" --- Fight with <item>.")
            else:
                mygame.Turn(command)
                save = save+command+"\n"
    del mygame
    end = "Thanks for playing! We hope you enjoyed this game enough to give it a grade of A+ or better! In the unlikely event that you were dissapointed by this game, please use the following coupon code to receive a $20 cash refund: "
    code = ""
    for i in range(0,10):
        code = code+chr(random.randint(33,126))
    BoxPrint(end+code)
if __name__ == '__main__':
    main()





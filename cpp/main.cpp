#include <stdlib.h>
#include <time.h>
#include<fstream>
#include <iostream>
#include <string>


using namespace std;
#include "game.h"
#include "printer.h"


int main(){
	int seed = time(NULL);
	srand(seed);
	string in;
	PrintAdventure();
	BoxPrint("Hello, and welcome to the greatest text based game ever experienced by anyone in history. Type \"Help\" for a list of commands. Type \"q\" to quit.");
	bool quit = false;
	bool restart = false;
	Game* mygame = new Game;
	string save = "";
	string fname;
	while(true){
		cout<<">>";
		getline(cin,in);
		cout<<endl;
		for(int i=0;i<in.length();i++)
			in[i]=tolower(in[i]);
		if(restart||quit){
			if(in == "y" || in == "yes"){
				if(quit)
					break;
				else {
					delete mygame;
					mygame = new Game;
					save = "";
					restart = false;
				}
			}
			else{
				quit = false;
				restart = false;
			}
		}
		else{
			quit = false;
			restart = false;
			if(in == "q" || in=="quit"){
				BoxPrint("Aren't you having fun?! Are you sure you absolutely have to exit? (yes or no?)");
				quit = true;
			}
			else if(in == "restart"){
					BoxPrint("Are you sure you want to restart? (yes or no?)");
					restart = true;
				}
			else if(in =="save"){
				BoxPrint("Enter filename for save:");
				getline(cin,fname);
				ofstream Save;
				Save.open(fname.c_str(),ios::trunc);
				if(!Save)
					BoxPrint("Error opening file. Your game is not saved.");
				else{
					Save<<seed<<endl;
					Save<<save;
					Save.close();
				}
			}
			else if(in == "load"){
				BoxPrint("Enter filename to load:");
				getline(cin,fname);
				ifstream Load;
				Load.open(fname.c_str(), fstream::in);
				if(!Load)
					BoxPrint("Error opening file. Unable to load game.");
				else{
					save = "";
					Load>>seed;
					srand(seed);
					delete mygame;
					mygame = new Game;
					getline(Load,in);
					while(Load){
						getline(Load, in);
						if(in!=""){
							cout<<">>"+in<<endl;
							mygame->Turn(in);
							save = save+"\n"+in;
						}
					}
					Load.close();
				}
			}
			else if(in == "help"){
				BoxPrint("\"n\" or \"north\" --- Moves to the north. The other directions are similar.");
				BoxPrint("\"look\" --- Looks around the room you are in. (Takes time...)");
				BoxPrint("\"inventory\" --- Lists the items you are currently carrying.");
				BoxPrint("\"examine <item>\" --- Gives a description of <item>.");
				BoxPrint("\"take <item>\" --- Pick up <item>.");
				BoxPrint("\"drop <item>\" --- Drop <item>.");
				BoxPrint("\"open <item>\" --- Opens <item>.");
				BoxPrint("\"close <item>\" --- Closes <item>.");
				BoxPrint("\"smash <item> with <item>\" --- Works for some specific items...");
				BoxPrint("\"fight <item>\" --- Fight with <item>.");
			}
			else{
				mygame->Turn(in);
				save = save+in+"\n";
			}
		}
		
	}
	
	delete mygame;
	string end = "Thanks for playing! We hope you enjoyed this game enough to give it a grade of A+ or better! In the unlikely event that you were dissapointed by this game, please use the following coupon code to receive a $20 cash refund: ";
	string code = "---------------";
	for(int i=0;i<code.length();i++)
		code[i] = rand() % 93 + 33;
	BoxPrint(end+code);
}

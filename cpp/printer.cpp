#include "printer.h"

void PrintAdventure(){
std::string line[6]={
"             _                 _                  _ ",
"    /\\      | |               | |                | |",
"   /  \\   __| |_   _____ _ __ | |_ _   _ _ __ ___| |",
"  / /\\ \\ / _` \\ \\ / / _ \\ '_ \\| __| | | | '__/ _ \\ |",
" / ____ \\ (_| |\\ V /  __/ | | | |_| |_| | | |  __/_|",
"/_/    \\_\\__,_| \\_/ \\___|_| |_|\\__|\\__,_|_|  \\___(_)"};

for(int i=0;i<6;i++)
	std::cout<<line[i].substr(0,WRAP)<<std::endl;
}

void Print(std::string words){
	int printed =0;
	
	while(printed < words.length()){
		int space = printed+WRAP;
		if(space>words.length())
			space = words.length()+1;
		else
			for(int i = printed+WRAP;i>printed;i--)
				if(i<words.length())
					if(words[i]==' '){
						space = i+1;
						break;
					}
		while(printed<space){
			if(printed<space-1)
				std::cout<<words[printed];
			printed++;
		}
		std::cout<<std::endl;
	}
}

 void BoxPrint(std::string words){
	int printed =0;
	std::cout<<char(201);
	for(int i=0;i<WRAP-2;i++)
		std::cout<<char(205);
	std::cout<<char(187)<<std::endl;
		
	while(printed < words.length()){
		int linecount=0;
		std::cout<<char(186)<<" ";
		int space = printed+WRAP-4;
		if(space>words.length())
			space = words.length()+1;
		else
			for(int i = printed+WRAP-4;i>printed;i--)
				if(i<words.length())
					if(words[i]==' '||words[i]=='\n'){
						space = i+1;
						break;
					}
		while(printed<space){
			if(printed<space-1){
				if(words[printed]!='\n')
					std::cout<<words[printed];
				else
					std::cout<<" ";
			}
			printed++;
			linecount++;
		}
		for(int i =linecount;i<WRAP-2;i++)
			std::cout<<" ";
		std::cout<<char(186)<<std::endl;
	}
	std::cout<<char(200);
	for(int i=0;i<WRAP-2;i++)
		std::cout<<char(205);
	std::cout<<char(188)<<std::endl;
}
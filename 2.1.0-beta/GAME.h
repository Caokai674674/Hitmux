#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>

#include "MINE-CLEARANCE.h"
#include "MINE-CLEARANCE-2.1.3.h"

using namespace std;

inline void game_f(){
	while(1){
		system("cls");
		cout<<"Game Menu in Hitmux (C) 2024 CaoKai,All right reserved.\n";
		cout<<"Game Menu in Hitmux (C) 2024 CaoKai,All right reserved.\n";
		cout<<"Game Menu in Hitmux (C) 2024 CaoKai,All right reserved.\n";
		cout<<"*******************************************************\n";
		cout<<"Please select a game:\n";
		cout<<"1. Mine Clearance 1.0.0-bate(Not recommended)\n";
		cout<<"2. Mine Clearance 2.1.3-bate(Recommended version)\n";
		cout<<"0. Exit\n";
		cout<<"*******************************************************\n";
		cout<<"Stay tuned for more games!\n";
		string a;
		cin>>a;
		if(a=="1") game1_f();
		else if(a=="2") game2_f();
		else if(a=="0"){
			getchar();
			return;
		}
		else{
			getchar();
			cout<<"Error!\nPress any key to continue";
		}
		getchar();
	}
}

#endif
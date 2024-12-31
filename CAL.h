#ifndef CAL_H
#define CAL_H

#include <cmath>
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

inline void calc_f(string a1,string a2,string a3){
	cout<<"Powerful NB calculator 1.0-stable (C) 2024-2025 CaoKai,All right reserved.\n";
	if((a2=="-sin"||a2=="-cos"||a2=="-tan")||(a1=="\0"||a2=="\0"||a3=="\0")){
		cout<<"Error!";
		return;
	}
	long double n1=atof(a1.c_str()),n2=atof(a3.c_str()),ans;
	if(a2=="+") ans=n1+n2;
	else if(a2=="-") ans=n1-n2;
	else if(a2=="*") ans=n1*n2;
	else if(a2=="/"){
		if(n2!=0)
			ans=n1/n2;
		else{
			cout<<"Error!";
			return;
		}
	}
	else if(a2=="^") ans=pow(n1,n2);
	else if(a2=="-log") ans=(log(n2)/log(n1));
	else if(a2=="-sin") ans=sin(n1);
	else if(a2=="-cos") ans=cos(n1);
	else if(a2=="-tan") ans=tan(n1);
	cout<<"Calculation result:   "<<fixed<<setprecision(15)<<ans<<"\n";
}

#endif

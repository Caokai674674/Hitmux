#include <bits/stdc++.h>
using namespace std;
const int L=1000;
int main(){
	int keyx[L],key;
	char be[L];
	cin.getline(be,L-1);
	srand(be[strlen(be)%3+be[strlen(be)%5]]);
	for(int i=0;i<strlen(be);i++)keyx[i]=rand();
	for(int i=0;i<strlen(be);i++)key+=be[i]+keyx[i];
	srand(key);
	for(int i=0;i<strlen(be);i++){
		int k=(rand()*keyx[strlen(be)-i-1])%95;
		be[i]=int(be[i])+k<=126?int(be[i])+k:int(be[i])+k-95;
	}
	for(int i=0;i<strlen(be);i++)cout<<be[i];
	return 0;
}
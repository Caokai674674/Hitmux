#include<bits/stdc++.h>
using namespace std;
const int L=1000;
int main(){
    int keyx[L],key=0,n;
    char be[L];
    cin.getline(be,L-1);
    cin>>n;
    srand(n);
    for(int i=0;i<strlen(be);i++)keyx[i]=rand();
    for(int i=0;i<strlen(be);i++)key+=be[i]-keyx[i];
    srand(key);
    for(int i=0;i<strlen(be);i++){
        int k=(rand()*keyx[strlen(be)-i-1])%95;
        be[i]=int(be[i])-k>=32?int(be[i])-k:int(be[i])-k+95;
    }
    for(int i=0;i<strlen(be);i++)cout<<be[i];
    return 0;
    //PmKUibC:}b0%09|lHLVC0n6iD9dV\FU:Ef}MuMYy
    //123321456
}

#ifndef MINE_ClEARANCE_h
#define MINE_ClEARANCE_h

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

#include "UI.h"

using namespace std;
inline int f(int a){
    int b=rand()%a;
    return b==0?1:0;
}
inline void p(int a,int b,string ll[99][99]){
    cout<<"\n   ";
    for(int i=0;i<=b;i++){
        if(i+1<10)
            cout<<i+1<<"  ";
        else cout<<i+1<<" ";
    }
    cout<<"\n";
    for(int i=0;i<=a;i++){
        if(i+1<10) cout<<i+1<<"  ";
        else cout<<i+1<<" ";
        for(int j=0;j<=b;j++){
            cout<<ll[i][j]<<"  ";
        }
        cout<<"\n";
    }
}
inline int mm(int m){
    if(m<100) return 5;
    else if(m<1000) return 7;
    return 9;
}
void aut(int x,int y,int a,int b,int l[99][99],string ll[99][99]){
    if(x<0||x>a||y<0||y>b)return;
    if(ll[x][y]!="#"||l[x][y]!=0)return;
    int sum=0;
    for(int i=-1;i<=1;i++){
        for(int j=-1;j<=1;j++){
            if(x+i>=0&&x+i<=a&&y+j>=0&&y+j<=b&&!(i==0&&j==0)){
                sum+=l[x+i][y+j];
            }
        }
    }
    ll[x][y]=to_string(sum);
    if(sum==0){
        for(int i=-1;i<=1;i++){
            for(int j=-1;j<=1;j++){
                if(x+i>=0&&x+i<=a&&y+j>=0&&y+j<=b&&!(i==0&&j==0)){
                    aut(x+i,y+j,a,b,l,ll);
                }
            }
        }
    }
}
void game1_f(){
	string temp[4]={"This version has been","discontinued for maintenance"," ","Please use the latest version."};
	text_long(temp,2,4);
	text_ui("This version has serious flaws",1);
    srand(time(0));
    cout<<"Mine Clearance 1.0.0-bate (C) 2024 CaoKai,All right reserved\n";
    cout<<"Mine Clearance 1.0.0-bate (C) 2024 CaoKai,All right reserved\n";
    cout<<"Mine Clearance 1.0.0-bate (C) 2024 CaoKai,All right reserved\n\n";
    cout<<"Line   "<<"Column   "<<"Reciprocal of mine ratio(usually 3~4)"<<endl; 
    int a,b,c,x,y,de,total=0,t=0,m;
    cin>>a>>b>>c;
    m=a*b;
    if(a>=100||b>=100||a<=0||b<=0){
        cout<<"Error!";
        return;
    }
    int l[99][99],x1[5],y1[5];
    string ll[99][99];
    a--; b--;
    for(int i=0;i<=a;i++){
        for(int j=0;j<=b;j++){
            l[i][j]=f(c);
            if(l[i][j]==1) total++;
        }
    }
    for(int i=0;i<=a;i++){
        for(int j=0;j<=b;j++)
            ll[i][j]="#";
    }
    p(a,b,ll);
    cout<<"Input "<<mm(m)<<" places,I can make sure that there aren't landmien."<<endl;
    for(int i=0;i<mm(m);i++){
        cin>>x1[i]>>y1[i];
        x1[i]--;
        y1[i]--;
        if(l[x1[i]][y1[i]]==1) total--;
        l[x1[i]][y1[i]]=0;
    }
    for(int q=0;q<mm(m);q++){
        int summ=0;
        for(int i=-1;i<=1;i++){
            for(int j=-1;j<=1;j++){
                if(x1[q]+i>=0 && x1[q]+i<=a && y1[q]+j>=0 && y1[q]+j<=b && !(i==0 && j==0)){
                    summ+=l[x1[q]+i][y1[q]+j];
                }
            }
        }
        ll[x1[q]][y1[q]]=to_string(summ);
        if(summ==0) aut(x1[q],y1[q],a,b,l,ll);
    }
    p(a,b,ll);
    while(true){
        cout<<"Line "<<"Column "<<"Choose(\"0\"marking,\"1\"confirm,\"2\"unmarking)\n"<<endl;
        cin>>x>>y>>de;
        x--; y--;
        if(x>a||y>b||x<0||y<0){
            cout<<"Error!";
            continue;
        }
        cout<<"There's "<<total<<" landmine.\n";
        cout<<"You have marked "<<t<<" places.\n";
        if(l[x][y]==1 && de==1){
            cout<<"boom!! You stepped on a landmine.";
            break;
        }
        else if(de==0){
            if(ll[x][y]=="#"){
                ll[x][y]="*";
                t++;
                if(l[x][y]==1) total--;
            }
        }
        else if(de==2){
            if(ll[x][y] == "*"){
                ll[x][y] = "#";
                t--;
                if(l[x][y] == 1) total++;
            }
        }
        else if(de==1){
            int sum=0;
            for(int i=-1;i<=1;i++){
                for(int j=-1;j<=1;j++){
                    if(x+i>=0 && x+i<=a && y+j>=0 && y+j<=b && !(i==0 && j==0)){
                        sum+=l[x+i][y+j];
                    }
                }
            }
            ll[x][y]=to_string(sum);
            if(sum==0) aut(x,y,a,b,l,ll);
        }
        if(t>=total){
            int sum1=0;
            for(int i=0;i<=a;i++){
                for(int j=0;j<=b;j++){
                    if(l[i][j]==1&&ll[i][j]!="*") sum1++;
                    if(l[i][j]==0&&ll[i][j]=="#") sum1++;
                }
            }
            if(sum1==0){
                cout<<"You win!!!!";
                return;
            }
        }
        p(a,b,ll);
    }
}

#endif
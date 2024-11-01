#ifndef GAME_2_H
#define GAME_2_H

#include<iostream>
#include<vector>
#include<ctime>
#include<cstdlib>

using namespace std;

class MineSweeper{
private:
    vector<vector<int>>board;
    vector<vector<bool>>revealed;
    int rows,cols,mines;
    time_t startTime;

    void placeMines(int firstX,int firstY){
        int count=0;
        while(count<mines){
            int x=rand()%rows,y=rand()%cols;
            if(board[x][y]==-1||(x==firstX&&y==firstY))continue;
            board[x][y]=-1;
            for(int i=-1;i<=1;i++)
                for(int j=-1;j<=1;j++)
                    if(x+i>=0&&x+i<rows&&y+j>=0&&y+j<cols&&board[x+i][y+j]!=-1)
                        board[x+i][y+j]++;
            count++;
        }
    }

    void reveal(int x,int y){
        if(x<0||x>=rows||y<0||y>=cols||revealed[x][y])return;
        revealed[x][y]=true;
        if(board[x][y]==0){
            for(int i=-1;i<=1;i++)
                for(int j=-1;j<=1;j++)
                    reveal(x+i,y+j);
        }
    }

public:
    MineSweeper(int r,int c,int p){
        rows=r;cols=c;
        mines=(r*c*p)/100;
        board.resize(rows,vector<int>(cols,0));
        revealed.resize(rows,vector<bool>(cols,false));
    }

    void start(int firstX,int firstY){
        srand(time(0));
        placeMines(firstX,firstY);
        startTime=time(0);
        reveal(firstX,firstY);
    }

    void revealPosition(int x,int y){
        reveal(x,y);
    }

    void display(){
        for(int i=0;i<rows;i++){
            for(int j=0;j<cols;j++){
                if(revealed[i][j]){
                    if(board[i][j]==-1)cout<<"* ";
                    else cout<<board[i][j]<<" ";
                }else cout<<"# ";
            }
            cout<<endl;
        }
        cout<<"Time: "<<difftime(time(0),startTime)<<" seconds"<<endl;
    }

    bool isGameOver(int x,int y){
        return board[x][y]==-1;
    }
};

void game2_f(){
	cout<<"Mine Clearance 2.1.3-bate (C) 2024 CaoKai,All right reserved\n";
	cout<<"Mine Clearance 2.1.3-bate (C) 2024 CaoKai,All right reserved\n";
	cout<<"Mine Clearance 2.1.3-bate (C) 2024 CaoKai,All right reserved\n";
    int r,c,p;
    cout<<"Enter rows, columns and mine percentage: ";
    cin>>r>>c>>p;
    MineSweeper game(r,c,p);
    int x,y;
    cout<<"Enter first reveal position (x y): ";
    cin>>x>>y;
    game.start(x,y);

    while(true){
        game.display();
        cout<<"Enter position to reveal (x y): ";
        cin>>x>>y;
        if(game.isGameOver(x,y)){
            cout<<"Game Over!"<<endl;
            break;
        }
        game.revealPosition(x,y);
    }
    return;
}
#endif

#include<stdio.h>

typedef struct ox{
    int a[9];
    int remain;
    int sugpos;
} ox;

int connect(int,int,int,ox*);
int Con(int,ox*);
//1 win 2 win 3 tie 4 unknow
int main(){
    ox Game;
    int N,M=1,e=0,temp,w,type;//1:player 2:computer
//初始化
    for(int i=0;i<9;i++) Game.a[i]=0;
    Game.remain=9;
//輸入
    scanf("%d %d",&M,&N);
    if(M!=1 && M!=2) e=1;
    N*=2;
    while(N--){
        scanf("%d",&temp);
        if(w==1 || w==2) continue; //已分勝負
        temp--;
        if(Game.a[temp]!=0 || (temp<0 || temp>8)){ //error input
            e=1;
            N++;
            continue;
        }
        Game.a[temp]=M;
        Game.remain--;
        w=Con(M,&Game);//return winer
        type=w;
        if(Game.remain==1 && w!=4) type=3;
        M=2-M+1;//next
    }

    if(e) printf("Error\n");
    else printf("OK\n");

    for(int i=0;i<9;i++){ //輸出棋盤
        printf("%d ",Game.a[i]);
        if(i%3==2) printf("\n");
    }

    printf("%d",type);
    if(type==4) printf("\n%d",Game.sugpos);
}

int Con(int play,ox *game){//回傳有無連線，是誰連線
    int c;
    for(int i=0;i<3;i++){
        if(connect(i*3,1,play,game)) c=connect(i*3,1,play,game);
        if(connect(i,3,play,game)) c=connect(i,3,play,game);
    }
    if(connect(0,4,play,game)) c=connect(0,4,play,game);
    if(connect(2,2,play,game)) c=connect(2,2,play,game);
    if(c) return c;
    else return 0;
}

int connect(int a,int d,int play,ox *game){//回傳有無連線，是誰連線
    int p,c=0,y=1;
    for(int i=0;i<3;i++){
        if(game->a[a]==0){
            c++;
            y=0; //不連線
        }
        else if(game->a[a]!=play){
            y=0;
            c=0;
            break;
        }
        a+=d;
    }
    if(y) return play; //回傳誰連線
    else if(c==1){ //差一連線
        for(int i=0;i<3;i++){
            if(game->a[a]==0) game->sugpos=a+1;
            a-=d;
            return 4; //有人差一連線
        }
    }
    else{
        for(int i=0;i<8;i++){
            if(game->a[i]==0) {
                game->sugpos=i+1; //隨便下
                return 0;
            }
        }
    }
}
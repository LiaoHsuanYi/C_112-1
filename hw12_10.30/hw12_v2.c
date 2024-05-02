#include<stdio.h>
float score(char,float);
int main(){
    int N;
    int P[4]={0};//c 1 2 3 下注數
    char e;//YN
    float point[4]={0};//分數
    int hand[4]={0};//手牌數
    char card;
    int count=1;//從第一位玩家開始要牌
    int f[4]={0};//最後賺賠
    int b[4]={0};//有沒分勝負
    int c=0;
    float min;
    float s;

    //開始
        //輸入人數N
    scanf("%d",&N);
        //輸入下注數P
    for(int i=1;i<=N;i++) scanf("%d",&P[i]);
    scanf("\n",&e);
        //輸入第一張牌
    for(int i=0;i<=N;i++){
        scanf("%c",&card);
        point[i]=score(card,point[i]);
        if(card=='1') scanf("%c",&e);
        if(i!=N) scanf(" ",&e);
        hand[i]++;
    }
    scanf("\n",&e);
    //模擬
    while(count<=N){
        //if輸入要不要要牌YN
        scanf("%c",&e);
        //要:輸入拿到的牌
        if(e=='Y') scanf(" %c",&card);
        //不要:換下一個人要牌
        else {
            scanf("\n",&e);
            count++;
            continue;
        }
        hand[count]++;
        point[count]=score(card,point[count]);
        if(card=='1') scanf("%c",&e);
        scanf("\n",&e);
        //if判斷有沒有爆||達到10.5
        //爆:賠下注數且換下一個人要牌
        if(point[count]>10.5){
            f[count]-=P[count];
            f[0]+=P[count];
            b[count]=1;
            count++;
            continue;
        }
        //10.5:賺下注數 換下一個人要牌
        else if(point[count]==10.5){
            f[count]+=P[count];
            f[0]-=P[count];
            b[count]=1;
            count++;
            continue;
        }
        //if手牌=5不再要牌
        else if(hand[count]==5){
            count++;
            continue;
        }
    }
    min=11;
    for(int i=1;i<=N;i++){
        if(!b[i]){//還有未分勝負
            c=1;
            if(min>point[i]) min=point[i];
        }
    }
    //computer
    if(c){
        //若點數小於player最低點數:輸入要牌
        while(point[0]<min){
            scanf("%c",&card);
            point[0]=score(card,point[0]);
            if(card=='1') scanf("%c",&e);
            hand[0]++;
            //爆了停牌
            if(point[0]>10.5){
                b[0]=1;
                break;
            }
            //手牌五張停牌
            else if(hand[0]==5) break;
            scanf("\n",&e);
        }
        //結算
        if(b[0]){//如果電腦爆 未分勝負玩家賺
            for(int i=1;i<=N;i++){
                if(!b[i]){
                    f[i]+=P[i];
                    f[0]-=P[i];
                }
            }
        }
        else{
            for(int i=0;i<=N;i++){
                if(!b[i]){
                    s=10.5-point[i];
                    min=s;
                    count=i;
                    break;
                }
            }
            //判斷最靠近10.5的贏
            for(int i=0;i<=N;i++){
                if(!b[i]){
                    s=10.5-point[i];
                    if(s<min) {
                        min=s;
                        count=i;
                    }
                }
            }
            //贏家贏得賭注
            if(count==0){
                for(int j=1;j<=N;j++){
                    if(!b[j]){
                        f[0]+=P[j];
                        f[j]-=P[j];
                    }
                }
            }
            else{
                f[0]-=P[count];
                f[count]+=P[count];
                for(int j=1;j<=N;j++){
                    if(!b[j]&&j!=count){
                        f[j]-=P[j];//其他人賠
                        f[0]+=P[j];
                    }
                }
            }
        }
    }

//輸出
    //輸出每人賺賠
    for(int i=1;i<=N;i++){
        printf("Player%d ",i);
        if(f[i]>0) printf("+");
        printf("%d\n",f[i]);
    }
    printf("Computer ");
    if(f[0]>0) printf("+");
    printf("%d",f[0]);
}

float score(char card,float p){
    if(card=='J'||(card=='Q'||card=='K')) p+=0.5;
    else if(card=='A') p+=1;
    else if(card=='1') p+=10;
    else p+=card-'0';
    return p;
}
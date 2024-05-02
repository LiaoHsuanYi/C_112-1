#include <stdio.h>
#include <stdlib.h>
 
#define MAX_PATH_CNT 100
 
typedef struct Path_struct{
  int path[MAX_PATH_CNT][MAX_PATH_CNT];//紀錄原始路徑
  int visit[MAX_PATH_CNT];  //是否已被加入最短路徑樹
  int parent[MAX_PATH_CNT]; //紀錄路徑的上一步是哪個城市
  int last_pt;              //最後一個城市編號
} Path_s;

//找出最短路徑
void dijkstra(Path_s *ps,int start){
  int distance[MAX_PATH_CNT];//從起點開始到各城市的距離
  int i,j,idx,min_dist,next,dist;
 
  //初始化
  for (i=0;i<=ps->last_pt;i++){
    distance[i]=ps->path[start][i];
    ps->visit[i]=0;
    if (distance[i]==1) //代表相鄰
      ps->parent[i]=start;
    else
      ps->parent[i]=0; //0為未確認父節點
  }
  ps->visit[start]=1; //將起點設為已拜訪，加入最短路徑樹
  ps->parent[start]=-1; //起點沒有父節點
 
  for (i=0;i<ps->last_pt;i++){
    //尋找一個目前不在最短路徑樹上
    //且離起點最近的點
    min_dist=1e9;
    idx=-1;  //紀錄要找的點
    for (j=0;j<=ps->last_pt;j++){
      if (!ps->visit[j] && distance[j]<min_dist){
        min_dist=distance[j];
        idx=j;  //暫時將該節點視為要加入最短路徑樹的點
      }
    }
    if (idx==-1) //已完成最短路徑樹
      break;
    
    ps->visit[idx]=1; //將該點加入最短路徑樹
    //從起點到idx，再到其他點，查看是否能更新起點到其他點的最短路徑
    for (next=0;next<=ps->last_pt;next++){
      dist=distance[idx]+ps->path[idx][next]; //從起點到idx，再到其他點
      if (!ps->visit[next] && dist<distance[next]){
        distance[next]=dist;
        ps->parent[next]=idx;
      }
    }
  }
}

//透過ps->parent找出最短路徑走法
void findPath(Path_s *ps, int current, int *p, int *p_size){
  if (ps->parent[current]==-1){ //回溯到起點
    p[(*p_size)++]=current;
    return;
  }
  findPath(ps,ps->parent[current],p,p_size);
  p[(*p_size)++]=current; //從起點開始，依序紀錄路徑
}


	
int main(){
  //宣告變數
  Path_s *ps;
  char buffer;
  int i, j, N, X, Z, Y, from, to, p_size;
  int p[MAX_PATH_CNT]; //儲存最終路徑
  
  //配置記憶體&初始化
  ps=(Path_s *)malloc(sizeof(Path_s));
  for (i=0;i<MAX_PATH_CNT;i++){
    for (j=0;j<MAX_PATH_CNT;j++)
      if (i==j)
        ps->path[i][j]=0; 
      else
        ps->path[i][j]=1e9; //預設此路不通
  }
  
  //處理輸入
  Y=-1; //預設無中途點
  scanf("%d %d %d%c",&N,&X,&Z,&buffer);
  if (buffer==' ') //有中途點
    scanf("%d",&Y);
  
  ps->last_pt=-1; //最後一個城市節點預設為-1
  while (N--){  
    scanf("%d %d",&from,&to);
    ps->path[from][to]=1;
    ps->path[to][from]=1;
    if (ps->last_pt<from)
      ps->last_pt=from;
    if (ps->last_pt<to)
      ps->last_pt=to;
  }
 
  dijkstra(ps,X);  //從X開始走，找出最短路徑
  if (Y==-1){ //起點(X)~終點(Z)  
    if (!ps->visit[Z]){
      printf("NO");
      return 0;
    }
    //從Z往前面追溯，找出X~Z的最短路徑
    p_size=0;
    findPath(ps,Z,p,&p_size);
    //輸出
    printf("%d\n",p_size-1); 
    for (i=0;i<p_size;i++)
      printf("%d ",p[i]);
  }
  else{ 
    //起點(X)~中途點(Y)
    if (!ps->visit[Y]){ //不會到Y
      printf("NO");
      return 0;
    }
    p_size=0;
    findPath(ps,Y,p,&p_size); //從Y開始追溯到X
 
    //中途點(Y)~終點(Z)
    dijkstra(ps,Y); //從Y開始找最短路徑
    if (!ps->visit[Z]){ //不會到Z
      printf("NO");
      return 0;
    }
 
    findPath(ps,Z,p,&p_size); //從Z開始往前追溯到Y
 
    //輸出
    printf("%d\n",p_size-2);//Y會重複(X~Y,Y~Z)，所以p_size-2
    for (i=0;i<p_size;i++){
      printf("%d ",p[i]);
      if (p[i]==Y)
        i++;
    }
  }
  free(ps); //釋放先前配置給Path_s的記憶體
  return 0;
}
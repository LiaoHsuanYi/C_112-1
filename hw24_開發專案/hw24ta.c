#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
typedef struct TN {
  int num;		//節點編號(1~N)
  int time;		//所需時間
  struct TN *next;	//下一節點
  struct TP *path;	//隸屬的路徑
} TaskNode;
 
typedef struct TP {
  TaskNode *first;	//第一個節點的指標 
  struct TP *next_path;//下一個路徑
  int from_t;		//路徑起始時間(截至該路徑的前一個節點)
} TaskPath;

//取得最後一條path
//因為不知道總共有幾條path，故使用link list管理
TaskPath* getLast(TaskPath *path)	{
  while (path->next_path != NULL)
    path = path->next_path;
  return path;
}

//取得整條path(截至to_node)花費的時間
int getPathTime(TaskPath *p_ptr, TaskNode *to_node) {
  TaskNode *n_ptr;
  int rtn = p_ptr->from_t;	//記錄總時
 
  n_ptr = p_ptr->first;	//初始化指向node的指標
  while (n_ptr != NULL && n_ptr != to_node) {
    rtn += n_ptr->time;
    n_ptr = n_ptr->next;
  }
 
  //如果該path的最後一個節點非末端節點
  //需額外加上該節點的時間(while迴圈沒加到)
  if (to_node != NULL)
    rtn += to_node->time;
 
  return rtn;
}

//取得截至該node為止，路徑上花費的總時
//如果該node尚不屬於任何路徑，直接回傳該node的時間
int getEndTime(TaskNode *node) {
  if (node->path == NULL)
    return node->time;
  return getPathTime(node->path, node);
}
	
//新增一條路徑
TaskPath* newPath(TaskPath *root, TaskNode *n_ptr, TaskNode *from_node) {
  TaskPath* p_ptr;
  //root沒有任何節點，把root視為新增的路徑
  if (root->first == NULL) 
    p_ptr = root;
  else {
    p_ptr = malloc(sizeof(TaskPath));
    //該path前面仍有node，須加上截至上一個節點的時間
    if (from_node != NULL) 
      p_ptr->from_t = getEndTime(from_node);
    else
      p_ptr->from_t = 0;
    p_ptr->next_path = NULL; 
    getLast(root)->next_path = p_ptr; //新路徑設為最後一條路徑
  }
  p_ptr->first = n_ptr;
  n_ptr->path = p_ptr;
  return p_ptr;
}

	
int main() {
  char buf[256], *p;
  TaskNode *node_ary, *n_ptr, *n_ptr1;
  TaskPath root_path, *p_ptr, *tmp_path;
  int N, n_cnt, k, t , longest;
 
  //root_path只有一個，代表最一開始產生的path
  memset(&root_path, 0, sizeof(root_path));
 
  scanf("%d\n", &N);	//讀入node個數
  node_ary = malloc(N * sizeof(TaskNode)); //配置好所有的node
  memset(node_ary, 0, N*sizeof(TaskNode)); //初始化
 
  for (int i = 0; i < N; i++) {
    gets(buf);		//time, n, t1..tn
    p = strtok(buf, " ");
    n_ptr = &node_ary[i];	//指向我們要編輯的node
    n_ptr->num = i + 1;
    n_ptr->time = atoi(p);
 
    if (n_ptr->path == NULL) //該節點尚未加入任何path
      newPath(&root_path, n_ptr, NULL);
 
    p = strtok(NULL, " ");
    n_cnt = atoi(p);	//取得該node後面還有幾個node
    for(k=0; k<n_cnt; k++)	{
      p = strtok(NULL, " ");
      t = atoi(p);		//子節點的編號
      n_ptr1 = &node_ary[t - 1]; //子節點的指標
      if (n_ptr->next == NULL) { //父節點目前無後繼者
        n_ptr->next = n_ptr1;
        n_ptr1->path = n_ptr->path;	//隸屬同一路徑
      }
      else { //父節點已有後繼者，新增路徑並將n_ptr1設為路徑的起點
        //該新路徑基於父節點的時間，故參數from_node傳的是父節點n_ptr
        newPath(&root_path, n_ptr1, n_ptr);	
      }
    }
  }
  //必須全部task都完成，故需找出最耗時的路徑，輸出該路徑花費時間
  longest = 0;
  p_ptr = &root_path;
  while (p_ptr != NULL) {
    t = getPathTime(p_ptr, NULL);
    if (t > longest)
      longest = t;
    p_ptr = p_ptr->next_path;
  }
  printf("%d\n", longest);
 
  //釋放先前配置的記憶體
  p_ptr = root_path.next_path;
  while (p_ptr != NULL) {
    tmp_path = p_ptr;
    p_ptr = p_ptr->next_path;
    free(tmp_path);
  }
  free(node_ary);
  return 0;
}
#include <stdio.h>
#include <stdlib.h>
 
typedef struct node_s{ //題目指定struct
  char data;
  struct node_s *right,*left;
} tree_t;
 
typedef tree_t *btree;

	
btree newNode(char data){
  btree new_node=malloc(sizeof(tree_t));
  new_node->data = data;
  new_node->right = NULL;
  new_node->left = NULL;
  return new_node;
}

void output(btree root){
  int count=1,c=0;
  btree temp1[100],temp2[100];
  temp1[0]=root;
  while(count>0){ //該層尚有節點
    for(int i=0; i<count; i++){
      printf("%c",temp1[i]->data);
      if(temp1[i]->left!=NULL)
        temp2[c++]=temp1[i]->left;
      if(temp1[i]->right!=NULL)
        temp2[c++]=temp1[i]->right;
    }
    for(int i=0; i<c; i++) 
      temp1[i]=temp2[i];	//將下一層的節點往上搬
    count=c; //count為新搬上來這層節點數
    c=0;
  }
}

int main(){
  int n,x,y,index=0;
  char c,input1[100],input2[100],s;
  char aim;
  btree root=NULL,temp;
  scanf("%d\n",&n); //讀入節點總數 
  scanf("%c\n",&s); //讀入前、中、後序
  if(s=='P'|| s=='O'){ //前 or 後序
    for(int i=0; i<n; i++) scanf("%c",&input1[i]);
    scanf("\n%c\n",&c);	//必為中序，吃掉輸入
    for(int i=0; i<n; i++) scanf("%c",&input2[i]); //中序
    scanf("%c",&c); //吃掉換行
  }
  else{ //中序
    for(int i=0; i<n; i++) scanf("%c",&input2[i]);
    scanf("\n%c\n",&s); //必為前/後序，讀入前or後
    for(int i=0; i<n; i++) scanf("%c",&input1[i]); //前/後序
    scanf("%c",&c); //吃掉換行
  }
  if(s=='O'){ //後序(左、右、根節點)
    //沿著中間左右反轉(變為根節點、右、左)
    for(int i=0; i<n/2; i++){ 
      c = input1[i];
      input1[i] = input1[n-i-1];
      input1[n-i-1] = c;
    }
  }
  root=newNode(input1[0]); //input1[0]為root
  while(index<n-1){ 
    index++; //index=0~n-1
    temp = root; //temp初始為root
    aim = input1[index]; //依序前/後序的順序
    for(int i=0; i<n; i++)
      if(input2[i]==aim) x=i; //在中序找到aim，標註該位置
    while(1){ //無窮迴圈，直到新增一個node至正確位置
      for(int i=0; i<n; i++)
        if(input2[i]==temp->data) y=i; //在中序找到temp，標註位置
        //比較aim跟temp的位置
      if(x>y){ //aim的位置在temp的右邊
        if(temp->right==NULL){
          temp->right=newNode(aim);
          break;
        }
        else temp=temp->right;
      }
      else{ //aim的位置在temp的左邊
        if(temp->left==NULL){
          temp->left=newNode(aim);
          break;
        }
        else temp=temp->left;
      }
    }
  }
  output(root);
  return 0;
}
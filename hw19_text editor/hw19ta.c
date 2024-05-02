	
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#define BUFFER_SIZE 256
 
typedef struct Sentences{
  int line_cnt;
  char **lines;
} Sentences; 

void cmd_aw(Sentences *sen_p,int i,int n,char *word,int front){
  char *insert_p;
  int word_cnt=1; 
  i--;  //i從1開始，但儲存時index從0開始，故減1
  insert_p=sen_p->lines[i];
  if (!front) //插入在第n+1個字的位置
    n++;
  if (n!=1){  //n如果是1就插入在開頭
    while (*insert_p!='\0'){
      if (*insert_p==' ')
        word_cnt++;
      if (word_cnt==n){
        insert_p++; //空格的下一位為插入位置
        break;
      }
      insert_p++;
    }
  }
  if (*insert_p=='\0'){
    //先塞空格，後塞word
    *insert_p=' ';
    insert_p++;
    strcpy(insert_p,word); //於指定位置插入word
  }
  else{
    //將原文挪出足夠空間插入word(word長度+1空格)
    //移動的是insert_p開始起算一直到\0的字串(\0要一起移動)
    memmove(insert_p+(strlen(word)+1),insert_p,(strlen(insert_p)+1));
    strcpy(insert_p,word); //於指定位置插入word
    insert_p+=strlen(word);
    *insert_p=' '; //word後填空格
  }
}

void cmd_as(Sentences *sen_p,int i,char *sentence,int front){
  char *insert_p;
 
  i--;  //i從1開始，但儲存時index從0開始，故減1
  if (front){ //先加句子，再加空格
    insert_p=sen_p->lines[i];
    //將原文挪出足夠空間插入sentence(sentence長度+1空格)
    //移動的是insert_p開始起算一直到\0的字串(\0要一起移動)
    memmove(insert_p+(strlen(sentence)+1),insert_p,(strlen(insert_p)+1));
    strcpy(insert_p,sentence);
    insert_p+=strlen(sentence);
    *insert_p=' '; //sentence後填空格
  }
  else{     //先加空格，再加句子
    insert_p=sen_p->lines[i]+strlen(sen_p->lines[i]);
    *insert_p=' ';
    insert_p++;
    strcpy(insert_p,sentence);
  }
}

void cmd_i(Sentences *sen_p,char *key,char *word,int front){
  char *insert_p;
  for (int i=0;i<sen_p->line_cnt;i++){
    insert_p=strstr(sen_p->lines[i],key);
    while (insert_p!=NULL){
      if (!front){
        insert_p+=strlen(key);
        if (*insert_p=='\0'){ //句子末端，先加空格再加word
          *insert_p=' ';
          insert_p++;
          strcpy(insert_p,word);
          break;
        }
        insert_p++; //key的下一個字的開頭
      }
      //空出word的長度+一空格
      memmove(insert_p+(strlen(word)+1),insert_p,(strlen(insert_p)+1));
      strcpy(insert_p,word); //於指定位置插入word
      insert_p+=strlen(word);
      *insert_p=' '; //word後填空格
 
      //用strstr找下一個key所在位置
      //若插入位置在key前面(if)，需要加上key的長度，避免重複找
      //同一個key；
      //若插入位置在key後面(ia)，insert_p指向空格或\0，
      //不需要再做處理
      if (front)
        insert_p=strstr(insert_p+strlen(key),key); 
      else
        insert_p=strstr(insert_p,key);
    }
  }
}

	
void cmd_dw(Sentences *sen_p,int i,int n){
  char *start_p, *end_p, *p;
  int word_cnt=1;
  i--;  //i從1開始，但儲存時index從0開始，故減1
 
  //尋找欲刪除word的起始
  p=sen_p->lines[i];
  while (*p!='\0'){
    if (word_cnt==n)
      break;
    if (*p==' ')
      word_cnt++;
    p++;
  }
  start_p=p;
  while (*p!=' ' && *p!='\0')
    p++;
  if (*p==' ')
    end_p=p+1; //後方空格要一併刪除
  else{
    start_p--;//前方空格要一併刪除
    end_p=p;  //end_p=='\0'
  }
  memmove(start_p,end_p,strlen(end_p)+1);//移動含\0
}

	
void cmd_dl(Sentences *sen_p,int i){
  i--;//i從1開始，但儲存時index從0開始，故減1
  free(sen_p->lines[i]);  //釋放儲存該行文字的記憶體
  sen_p->line_cnt--;  
  //將後面的文句往前挪，移動的是指向句子的指標
  for (int j=i;j<sen_p->line_cnt;j++)
    sen_p->lines[j]=sen_p->lines[j+1];
}

	
void cmd_rp(Sentences *sen_p,char *old,char *new){
  char *p,*src;
  cmd_i(sen_p,old,new,0); //先在所有old後面加上new
  //再刪除所有old+空格*1
  for (int i=0;i<sen_p->line_cnt;i++){
    p=strstr(sen_p->lines[i],old);
    while(p!=NULL){
      src=p+strlen(old)+1;//src指向new的開始
      memmove(p,src,strlen(src)+1);//搬移長度為new開始到\0
      p=strstr(p,old);  //找下一個要刪除的old位置
    }
  }
}

	
int cmd_c(Sentences *sen_p){
  char *p;
  int word_cnt=0; 
  for (int i=0;i<sen_p->line_cnt;i++){
    //逐行看有幾個字
    p=sen_p->lines[i];
    word_cnt++; //一行裡一定至少有一個字
    while(*p!='\0'){
      if (*p==' ')//碰到空格代表接下來會有一個詞
        word_cnt++;
      p++;
    }
  }
  return word_cnt;
}

int main(){
  //宣告
  int N,i,j;
  char buffer[BUFFER_SIZE];
  char *param[3];
  char *p;
  Sentences sen;
 
  //初始化
  sen.line_cnt=0;
 
  //輸入
  scanf("%d %d\n",&sen.line_cnt,&N);
  sen.lines=malloc(sen.line_cnt*sizeof(char *));
  for (i=0;i<sen.line_cnt;i++){  //動態配置記憶體放置原文
    gets(buffer);
    sen.lines[i]=(char *)malloc(BUFFER_SIZE);
    strcpy(sen.lines[i],buffer);
  }
  for (i=0;i<N;i++){  //逐行處理指令
    gets(buffer);
    p=strtok(buffer," ");
    if (strcmp(p,"awf")==0){
      for (j=0;j<3;j++)  //依序取得三個參數
        param[j]=strtok(NULL," ");
      cmd_aw(&sen,atoi(param[0]),atoi(param[1]),param[2],1);
    }
    else if (strcmp(p,"awa")==0){
      for (j=0;j<3;j++)  //依序取得三個參數
        param[j]=strtok(NULL," ");
      cmd_aw(&sen,atoi(param[0]),atoi(param[1]),param[2],0);
    }
    else if (strcmp(p,"asf")==0){
      param[0]=strtok(NULL," ");
      param[1]=strtok(NULL,"\0");
      cmd_as(&sen,atoi(param[0]),param[1],1);
    }
    else if (strcmp(p,"asa")==0){
      param[0]=strtok(NULL," ");
      param[1]=strtok(NULL,"\0");
      cmd_as(&sen,atoi(param[0]),param[1],0);
    }
    else if (strcmp(p,"if")==0){
      for (j=0;j<2;j++)  //key, word
        param[j]=strtok(NULL," ");
      cmd_i(&sen,param[0],param[1],1);
    }
    else if (strcmp(p,"ia")==0){
      for (j=0;j<2;j++)  //key, word
        param[j]=strtok(NULL," ");
      cmd_i(&sen,param[0],param[1],0);
    }
    else if (strcmp(p,"dw")==0){
      for (j=0;j<2;j++)  //i,n
        param[j]=strtok(NULL," ");
      cmd_dw(&sen,atoi(param[0]),atoi(param[1]));
    }
    else if (strcmp(p,"dl")==0){
      param[0]=strtok(NULL,"\n");//只有一個參數，以換行當分隔符
      cmd_dl(&sen,atoi(param[0]));
    }    
    else if (strcmp(p,"rp")==0){
      for (j=0;j<2;j++)
        param[j]=strtok(NULL," ");
      cmd_rp(&sen,param[0],param[1]);
    } 
    else if (strcmp(p,"c")==0)
      printf("%d\n",cmd_c(&sen));
  }
 
  //輸出文章
  for (i=0;i<sen.line_cnt;i++)
    printf("%s\n",sen.lines[i]);
  
  for (i=0;i<sen.line_cnt;i++) //釋放先前配置的記憶體
    free(sen.lines[i]);
  free(sen.lines);
  return 0;
}
#include <stdio.h>
#include <string.h>
 
#define	PROP_CNT	8
#define	MAX_UNIVERSITY	10
 
typedef struct u {
  char name[11];	//名稱(最多10字母)
  int props;		//屬性(透過8個bit來表示8種屬性是否擁有)
  int match_cnt;	//符合次數(根據mode不同定義不同)
} University;
 
typedef struct q {
  int flags[9]; //每組or條件用一個int表示，最多9組
  int cnt;			//實際有幾組or條件
} Query;

int getPropIdx(char* name) {  //-1 or 0 to PROP_CNT-1
  const char prop_names[PROP_CNT][2]={"GF","BC","NC","CT","NS","NM","HL","NL"};
  for (int idx=0; idx<PROP_CNT; idx++)
    if (name[0]==prop_names[idx][0] && name[1]==prop_names[idx][1])
      return idx;	//找到該屬性，回傳該屬性對應索引值
  return -1;	//找不到該屬性
}

	
int matchPropCnt(int flags) {   //每符合一個屬性則加1
  int rtn=0, mask=1;
  for (int i=0; i<PROP_CNT; i++) {
    if (flags & mask)
      rtn++;
    mask=mask << 1;
  }
  return rtn;
}

	
//mode=0要全部符合, mode=1時部分符合即可
void match(University *u_ptr, int u_cnt, Query *q_ptr, int mode) {
  int i, j, best_cnt=0, m_flags;
 
  for(i=0; i<u_cnt; i++) //初始化每個大學的符合條件數
    u_ptr[i].match_cnt=0;//在mode不同時，符合條件數的定義稍有不同
 
  for (j=0; j<q_ptr->cnt; j++) {	//針對每一組or條件判斷屬性符合數
    int q_flags=q_ptr->flags[j];  //一組or條件(例如GF BC+NC為兩組or條件)
    for (i=0; i<u_cnt; i++) {
      m_flags=u_ptr[i].props & q_flags;	//該大學屬性和一組or條件相同的部分
      if (m_flags!=0) {  //!=0表示至少有一屬性符合
        if(mode==0) {
          if (m_flags==q_flags) {   //所有bit(屬性)均符合
            if (u_ptr[i].match_cnt==0)
              printf("%s ", u_ptr[i].name);
            u_ptr[i].match_cnt=1;	//match_cnt用來判斷是否印過該大學
          }
        }
        else {  //mode=1，需紀錄目前最大符合數
          u_ptr[i].match_cnt+=matchPropCnt(m_flags);
          if (best_cnt<u_ptr[i].match_cnt)	
            best_cnt=u_ptr[i].match_cnt;	//更新最大符合數
        }
      }
    }
  }
  if (mode==1) {   //印出符合屬性數最多的學校(可能多個)
    for (i=0; i<u_cnt; i++) {
      if (u_ptr[i].match_cnt==best_cnt)
        printf("%s ", u_ptr[i].name);
    }
  }
  //已根據該查詢條件輸出大學，若有下一個查詢條件，則換行繼續輸出
  printf("\n"); 
}

int main() {
  int i, M, N, mode, idx;
  char buf[256], *p;
  University universities[MAX_UNIVERSITY];
  Query queries[10];   //最多10個query(By題目)
 
  scanf("%d\n",&N);	//有N所大學
  for (i=0; i<N; i++) {
    gets(buf);
    p=strtok(buf, " ");
    strcpy(universities[i].name,p);
    universities[i].props=0; //初始化該大學擁有的屬性
 
    p=strtok(NULL, " ");
    while(p!=NULL) {
      idx=getPropIdx(p);
      if (idx>=0)  //合法屬性
        universities[i].props |= (1 << idx);
      p=strtok(NULL, " ");
    }
  }
 
  memset(queries, 0, sizeof(queries));//初始化query的所有內容
  scanf("%d\n", &M);  //有M筆查詢
  for (int i=0; i<M; i++) {
    gets(buf);
    p=strtok(buf, " ");
    while (p != NULL) {
      if (*p=='+')
        queries[i].cnt++; //結算至加號前一個屬性
      else {	//p指向的內容為屬性
        idx=getPropIdx(p);
        if (idx>=0) {	//合法屬性
          queries[i].flags[queries[i].cnt] |= (1 << idx);
        }
      }
      p = strtok(NULL, " ");
    }
    queries[i].cnt++; //加上最後一個屬性
  }
 
  scanf("%d", &mode);
  //輸出符合情況：
  //mode=0時輸出全部符合的有哪些學校；
  //mode=1時輸出部分符合中符合最多的學校
  for (int i=0; i<M; i++) 
    match(universities, N, &queries[i], mode);
 
  return 0;
}
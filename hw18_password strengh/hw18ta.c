	
#include <stdio.h>
#include <string.h>
 
float calcStrength(char* s){
  const char *spc_chars = "~!@#$%^&*<>_+=";
  float strength=0;
  int digit_cnt=0, grp_cnt=0;
 
  while (*s) {
    if (*s >= '0' && *s <= '9') { //數字0-9
      strength += 2;	//Y個數字+2*Y分，一個數字+2分
      grp_cnt++;
      if (grp_cnt == 1)       //每群數字的第一個
        digit_cnt++;
      else if (grp_cnt == 2)  //每群數字的第二個
        digit_cnt--; //複數個數字相鄰，不計入五個不相鄰數字
    }
    else {
      grp_cnt = 0;
      if (*s >= 'A' && *s <= 'Z') //大寫字母
        strength += 3;
      else if (*s >= 'a' && *s <= 'z')    //小寫字母
        strength += 1;
      else if (strchr(spc_chars, *s) != NULL) //特殊符號
        strength += 4.5;
    }
    s++;
  }
  if (digit_cnt >= 5)
    strength += 10;
  return strength;
}

int main(){
  char buf[80],max_pwd[80],min_pwd[80];
  float score, max_score=0, min_score=9999;
 
  while (gets(buf)) {	//每次讀入一整行輸入
    if (strcmp(buf, "-1") == 0)	//讀到-1結束輸入
      break;
    score = calcStrength(buf);
    if (score < min_score) {
      strcpy(min_pwd, buf);
      min_score = score;
    }
    if (score > max_score) {
      strcpy(max_pwd, buf);
      max_score = score;
    }
  }
  printf("%s %.1f\n", max_pwd, max_score);
  printf("%s %.1f\n", min_pwd, min_score);
 
  return 0;
}
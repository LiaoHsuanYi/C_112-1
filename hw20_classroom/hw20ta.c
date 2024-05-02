#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
typedef struct Classroom{
  int num;
  int size;
  int used[24];
} Classroom;
 
typedef struct Course{
  int num;
  int people;
  int start;
  int end;
  int room;  
  int ans_room;
} Course;

	
//檢查在該課程的所有時段內，該教室是否皆可用
int check_used(Classroom room, Course crs){ 
  for (int i = crs.start; i < crs.end; i++)
    if (room.used[i])
      return 0;
  return 1;
}

void schedule(Classroom *room, Course *crs, int M, int N, int hours, int courses, int *max_hours, int *max_courses, int mode){
  if (*max_hours < hours){  //該排課情形能更新最大時數
    *max_hours = hours;
    *max_courses = courses;
 
    for (int i = 0; i < N; i++) //更新每一門課的教室使用情形
      crs[i].ans_room = crs[i].room;  
  }
  //依序檢查每一門課程，並嘗試排課
  for (int i = 0; i < N; i++){ 
    //只排還沒有教室的課程(已經排過的不重複排)
    if (crs[i].room != 0)
      continue;
    for (int j = 0; j < M; j++){ //針對還沒排的課，檢查各教室
      //若該時段該教室已被使用，則不可排該教室
      if (!check_used(room[j], crs[i])) 
        continue;
      //若mode為0，不考慮教室容量；否則須人數<教室容量
      if (mode == 0 || (crs[i].people <= room[j].size)){ 
        crs[i].room = room[j].num;  //教室編號放入該課程目前排的課程
        //針對該教室以小時為單位標註使用情形(crs[i]這門課使用)
        for (int k = crs[i].start; k < crs[i].end; k++)
          room[j].used[k] = crs[i].num;
 
        //排完一門課，再排下一門
        schedule(room, crs, M, N, hours+crs[i].end-crs[i].start, courses+1, max_hours, max_courses, mode);
        //將該排課情形還原，嘗試將該課排下一間教室or排下一門課
        crs[i].room = 0;
        for (int k = crs[i].start; k < crs[i].end; k++)
          room[j].used[k] = 0;
      }
    }
  }
}

int main(){
  //輸入&配置記憶體&初始化
  int M, N, b;
  scanf("%d %d", &M, &N);
 
  //根據教室數量動態配置記憶體
  Classroom *room = (Classroom *)malloc(M * sizeof(Classroom));
  for (int i = 0; i < M; i++)
    scanf("%d %d", &room[i].num, &room[i].size);
  Course *crs = (Course *)malloc(N * sizeof(Course));
  for (int i = 0; i < N; i++)
    scanf("%d %d %d %d", &crs[i].num, &crs[i].people, &crs[i].start, &crs[i].end);
 
  scanf("%d", &b); //模式：b=0不考慮容量；b=1考慮容量；b=2考慮容量且輸出課程編號和教室編號
 
  for (int i = 0; i < M; i++) //初始化教室為皆未被使用
    memset(room[i].used, 0, sizeof(room[i].used));
 
  for (int i = 0; i < N; i++){
    crs[i].room = 0;
    crs[i].ans_room = 0;
  }
 
  //開始排課
  int max_hours = 0, max_courses = 0;
  schedule(room, crs, M, N, 0, 0, &max_hours, &max_courses, b);
    
  //根據課程編號小到大來排序
  int last = N, check = 0;
  while (last > 1){
    while (check < last - 1){
      if (crs[check].num > crs[check + 1].num){
        Course tmp = crs[check];
        crs[check] = crs[check + 1];
        crs[check + 1] = tmp;
      }
      check++;
    }
    check = 0;
    last--;
  }
  
  //輸出
  printf("max hours %d\nmax courses %d\n", max_hours, max_courses);
  if (b == 2) //需再印出哪一門課對應哪間教室
    for (int i = 0; i < N; i++)
      if (crs[i].ans_room != 0)
        printf("%d %d\n", crs[i].num, crs[i].ans_room);
 
  //釋放先前配置的記憶體
  free(room);
  free(crs);
 
  return 0;
}
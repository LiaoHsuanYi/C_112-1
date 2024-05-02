#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Classroom
{
    int num;
    int size;
    int used[24];
} Classroom;

typedef struct Course
{
    int num;
    int people;
    int start;
    int end;
    int room;
    int ans_room;
} Course;

int check_used(Classroom room, Course crs)
{
    for (int i = crs.start; i < crs.end; i++)
    {
        if (room.used[i])
        {
            return 0;
        }
    }
    return 1;
}

void schedule(Classroom *room, Course *crs, int M, int N, int hours, int courses, int *max_hour, int *max_course, int mode)
{
    if (*max_hour < hours)
    {
        *max_hour = hours;
        *max_course = courses;

        for (int i = 0; i < N; i++)
        {
            crs[i].ans_room = crs[i].room;
        }
        
    }
    
    for (int i = 0; i < N; i++)
    {
        if (crs[i].room != 0)
        {
            continue;
        }
        for (int j = 0; j < M; j++)
        {
            if (!check_used(room[j], crs[i]))
            {
                continue;
            }
            if (mode == 0 || (crs[i].people <= room[j].size))
            {
                crs[i].room = room[j].num;
                for (int k = crs[i].start; k < crs[i].end; k++)
                {
                    room[j].used[k] = crs[i].num;
                }
                
                schedule(room, crs, M, N, hours + crs[i].end - crs[i].start, courses + 1, max_hour, max_course, mode);
                crs[i].room = 0;
                for (int k = crs[i].start; k < crs[i].end; k++)
                {
                    room[j].used[k] = 0;
                }
                
            }
            
        }
        
    }
    
}

int main()
{
    //initialize
    int M, N, b;
    scanf("%d %d", &M, &N);

    //allocate the memory
    Classroom *room = (Classroom *)malloc(M * sizeof(Classroom));
    for (int i = 0; i < M; i++)
    {
        scanf("%d %d", &room[i].num, &room[i].size);
    }
    Course *crs = (Course *)malloc(N * sizeof(Course));
    for (int i = 0; i < N; i++)
    {
        scanf("%d %d %d %d", &crs[i].num, &crs[i].people, &crs[i].start, &crs[i].end);
    }
    
    scanf("%d", &b);

    for (int i = 0; i < M; i++)
    {
        memset(room[i].used, 0, sizeof(room[i].used));
    }
    
    for (int i = 0; i < N; i++)
    {
        crs[i].room = 0;
        crs[i].ans_room = 0;
    }
    
    //arrange the course
    int max_hour = 0, max_course = 0;
    schedule(room, crs, M, N, 0, 0, &max_hour, &max_course, b);

    //sort by course num
    int last = N, check = 0;
    while (last > 1)
    {
        while (check < last - 1)
        {
            if (crs[check].num > crs[check + 1].num)
            {
                Course tmp = crs[check];
                crs[check] = crs[check + 1];
                crs[check + 1] = tmp;
            }
            check++;
        }
        check = 0;
        last--;
    }
    
    //output
    printf("max hours %d\nmax courses %d\n", max_hour, max_course);
    if (b == 2)
    {
        for (int i = 0; i < N; i++)
        {
            if (crs[i].ans_room != 0)
            {
                printf("%d %d\n", crs[i].num, crs[i].ans_room);
            }
            
        }
        
    }
    
    free(room);
    free(crs);

    return 0;

}
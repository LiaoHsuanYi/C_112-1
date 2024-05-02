#include <stdio.h>
#include <stdlib.h>
#define MAX_PATH_CNT 100

typedef struct Path_struct{
    int path[MAX_PATH_CNT][MAX_PATH_CNT]; //original path
    int visit[MAX_PATH_CNT]; //added or not
    int parent[MAX_PATH_CNT]; //previous one city
    int last_pt; //last city num
}Path_s;

void dijkstra(Path_s *ps, int start)
{
    int distance[MAX_PATH_CNT];
    int i, j, idx, min_dist, next, dist;

    //initialize
    for ( i = 0; i <= ps->last_pt; i++)
    {
        distance[i] = ps->path[start][i];
        ps->visit[i] = 0;
        if (distance[i] == 1)
        {
            ps->parent[i] = start;
        }
        else
        {
            ps->parent[i] = 0;
        }
    }
    ps->visit[start] = 1;
    ps->parent[start] = -1;

    for ( i = 0; i < ps->last_pt; i++)
    {
        min_dist = 1e9;
        idx = -1;
        for ( j = 0; j <= ps->last_pt; j++)
        {
            if (!ps->visit[j] && distance[j] < min_dist)
            {
                min_dist = distance[j];
                idx = j;
            }
            
        }
        if (idx == -1)
        {
            break;
        }
        
        ps->visit[idx] = 1;

        for (next = 0; next <= ps->last_pt; next++)
        {
            dist = distance[idx] + ps->path[idx][next];
            if (!ps->visit[next] && dist < distance[next])
            {
                distance[next] = dist;
                ps->parent[next] = idx;
            }
            
        }
        
    }
    
}


void findPath(Path_s *ps, int current, int *p, int *p_size)
{
    if (ps->parent[current] == -1)//back to origin
    {
        p[(*p_size)++] = current;
        return;
    }
    findPath(ps, ps->parent[current], p, p_size);
    p[(*p_size)++] = current;
}

int main()
{
    //declaration
    Path_s *ps;
    char buffer;
    int i, j, n, x, z, y, from, to, p_size;
    int p[MAX_PATH_CNT];

    //initalize
    ps = (Path_s *)malloc(sizeof(Path_s));
    for ( i = 0; i < MAX_PATH_CNT; i++)
    {
        for ( j = 0; j < MAX_PATH_CNT; j++)
        {
            if (i == j)
            {
                ps->path[i][j] = 0;
            }
            else
            {
                ps->path[i][j] = 1e9;
            }
        }
    }    

    //compute
    y = -1;
    scanf("%d %d %d%c", &n, &x, &z, &buffer);
    if (buffer == ' ')
    {
        scanf("%d", &y);
    }

    ps->last_pt = -1;
    while (n--)
    {
        scanf("%d %d", &from, &to);
        ps->path[from][to] = 1;
        ps->path[to][from] = 1;
        if (ps->last_pt < from)
        {
            ps->last_pt = from;
        }
        if (ps->last_pt < to)
        {
            ps->last_pt = to;
        }
    }
    
    dijkstra(ps, x);
    if (y == -1)
    {
        if(!ps->visit[z])
        {
            printf("NO");
            return 0;
        }
        p_size = 0;
        findPath(ps, z, p, &p_size);

        //output
        printf("%d\n", p_size - 1);
        for ( i = 0; i < p_size; i++)
        {
            printf("%d ", p[i]);
        }
        
    }
    else
    {
        if (!ps->visit[y])
        {
            printf("NO");
            return 0;
        }
        p_size = 0;
        findPath(ps, y, p, &p_size);

        dijkstra(ps, y);
        if (!ps->visit[z])
        {
            printf("NO");
            return 0;
        }

        findPath(ps, z, p, &p_size);

        //output
        printf("%d\n", p_size - 2);
        for ( i = 0; i < p_size; i++)
        {
            printf("%d ", p[i]);
            if (p[i] == y)
            {
                i++;
            }
            
        }
        
    }
    free(ps);
    return 0;    
}
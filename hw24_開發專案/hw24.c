#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TN
{
    int num; 
    int time; 
    struct TN *next;
    struct TP *path;
}TaskNode;

typedef struct TP
{
    TaskNode *first;
    struct TP *next_path;
    int from_t; //started time
}TaskPath;

TaskPath* getLast(TaskPath *path)
{
    while (path->next_path != NULL)
    {
        path = path->next_path;
    }
    return path;
}

int getPathTime(TaskPath *p_ptr, TaskNode *to_node)
{
    TaskNode *n_ptr;
    int rtn = p_ptr->from_t;

    n_ptr = p_ptr->first;
    while (n_ptr != NULL && n_ptr != to_node)
    {
        rtn += n_ptr->time;
        n_ptr = n_ptr->next;
    }

    if (to_node != NULL)
    {
        rtn += to_node->time;
    }
    
    return rtn;
}

int getEndTime(TaskNode *node)
{
    if (node->path == NULL)
    {
        return node->time;
    }
    return getPathTime(node->path, node);
}

//add new path
TaskPath *newPath(TaskPath *root, TaskNode *n_ptr, TaskNode *from_node)
{
    TaskPath *p_ptr;
    if (root->first == NULL)
    {
        p_ptr = root;
    }
    else
    {
        p_ptr = malloc(sizeof(TaskPath));
        if (from_node != NULL)
        {
            p_ptr->from_t = getEndTime(from_node);
        }
        else
        {
            p_ptr->next_path = NULL;
        }
        p_ptr->next_path = NULL;
        getLast(root)->next_path = p_ptr;
    }
    p_ptr->first = n_ptr;
    n_ptr->path = p_ptr;
    return p_ptr;
}

int main()
{
    //initialize
    char buf[256], *p;
    TaskNode *node_ary, *n_ptr, *n_ptr1;
    TaskPath root_path, *p_ptr, *tmp_path;
    int N, n_cnt, k, t, longest;

    //memset
    memset(&root_path, 0, sizeof(root_path));

    //input, allocate, memset
    scanf("%d\n", &N);
    node_ary = malloc(N * sizeof(TaskNode));
    memset(node_ary, 0, N * sizeof(TaskNode));

    for (int i = 0; i < N; i++)
    {
        gets(buf);
        p = strtok(buf, " ");
        n_ptr = &node_ary[i];
        n_ptr->num = i + 1;
        n_ptr->time = atoi(p);

        if (n_ptr->path == NULL)
        {
            newPath(&root_path, n_ptr, NULL);
        }
        
        p = strtok(NULL, " ");
        n_cnt = atoi(p);
        for ( k = 0; k < n_cnt; k++)
        {
            p = strtok(NULL, " ");
            t = atoi(p);
            n_ptr1 = &node_ary[t - 1];
            if (n_ptr->next == NULL)
            {
                n_ptr->next = n_ptr1;
                n_ptr1->path = n_ptr->path;
            }
            else
            {
                newPath(&root_path, n_ptr1, n_ptr);
            }
            
        }
        
    }
    
    longest = 0;
    p_ptr = &root_path;
    while (p_ptr != NULL)
    {
        t = getPathTime(p_ptr, NULL);
        if (t > longest)
        {
            longest = t;
        }
        p_ptr = p_ptr->next_path;
    }
    printf("%d\n", longest);

    p_ptr = root_path.next_path;
    while (p_ptr != NULL)
    {
        tmp_path = p_ptr;
        p_ptr = p_ptr->next_path;
        free(tmp_path);
    }
    free(node_ary);
    return 0;
    
}
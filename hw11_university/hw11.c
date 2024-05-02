#include <stdio.h>
#include <string.h>

#define PROP_CNT 8
#define MAX_UNIVERSITY 10

typedef struct u
{
    char name[11];
    int props;
    int match_count;
} University;

typedef struct q
{
    int flags[9];
    int count;
} Query;

int getPropIndex(char *name)
{
    const char prop_names[PROP_CNT][2] = {"GF", "BC", "NC", "CT", "NS", "NM", "HL", "NL"};
    for (int index = 0; index < PROP_CNT; index++)
    {
        if (name[0] == prop_names[index][0] && name[1] == prop_names[index][1])
        {
            return index;
        }
    } 
    return -1;
}

int matchPropCount(int flags)
{
    int rtn = 0, mask = 1;
    for (int i = 0; i < PROP_CNT; i++)
    {
        if (flags & mask)
        {
            rtn++;        
        }
        mask = mask << 1;
    }
    return rtn;
}

void match(University *u_ptr, int u_cnt, Query *q_ptr, int mode)
{
    int best_count = 0, m_flags;
    for (int i = 0; i < u_cnt; i++)
    {
        u_ptr[i].match_count = 0;
    }
    for (int j = 0; j < q_ptr -> count; j++)
    {
        int q_flags = q_ptr -> flags[j];
        for (int i = 0; i < u_cnt; i++)
        {
            m_flags = u_ptr[i].props & q_flags;
            if (m_flags != 0)
            {
                if (mode == 0)
                {
                    if (m_flags == q_flags)
                    {
                        if (u_ptr[i].match_count == 0)
                        {
                            printf("%s ", u_ptr[i].name);
                        }
                        u_ptr[i].match_count = 1;
                    }
                    
                }
                else
                {
                    u_ptr[i].match_count += matchPropCount(m_flags);
                    if (best_count < u_ptr[i].match_count)
                    {
                        best_count = u_ptr[i].match_count;
                    }
                    
                }
            }
            
        }
        
    }
    
    if (mode == 1)
    {
        for (int i = 0; i < u_cnt; i++)
        {
            if (u_ptr[i].match_count == best_count)
            {
                printf("%s ", u_ptr[i].name);
            }
            
        }
    }
    printf("\n");
}

int main()
{
    int m, n, mode, index;
    char buf[256], *p;
    University universities[MAX_UNIVERSITY];
    Query queries[10];

    scanf("%d\n", &n);
    for (int i = 0; i < n; i++)
    {
        gets(buf);
        p = strtok(buf, " ");
        strcpy(universities[i].name, p);
        universities[i].props = 0;

        p = strtok(NULL, " ");
        while (p != NULL)
        {
            index = getPropIndex(p);
            if (index >= 0)
            {
                universities[i].props |= (1 << index);
            }
            p = strtok(NULL, " ");
        }
    }

    memset(queries, 0, sizeof(queries));
    scanf("%d\n", &m);
    for (int i = 0; i < m; i++)
    {
        gets(buf);
        p = strtok(buf, " ");
        while (p != NULL)
        {
            if (*p == '+')
            {
                queries[i].count++;
            }
            else
            {
                index = getPropIndex(p);
                if (index >= 0)
                {
                    queries[i].flags[queries[i].count] |= (1 << index);
                }
                
            }
            p = strtok(NULL, " ");
        }
        queries[i].count++;
    }

    scanf("%d", &mode);

    for (int i = 0; i < m; i++)
    {
        match(universities, n, &queries[i], mode);
    }
    
    return 0;
    
}
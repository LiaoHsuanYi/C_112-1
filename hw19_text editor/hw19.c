#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 256

typedef struct Sentences
{
    int line_cnt;
    char **lines;
}Sentences;

void cmd_aw(Sentences * sen_p, int i, int n , char * word, int front)
{
    char *insert_p;
    int word_cnt = 1;
    i--;
    insert_p = sen_p->lines[i];
    if (!front)
    {
        n++;
    }
    if (n != 1)
    {
        while (*insert_p != '\0')
        {
            if (*insert_p == ' ')
            {
                word_cnt++;
            }
            if (word_cnt == n)
            {
                insert_p++;
                break;
            }
            insert_p++;
        }
        
    }
    if (*insert_p == '\0')
    {
        *insert_p = ' ';
        insert_p++;
        strcpy(insert_p, word);
    }
    else
    {
        memmove(insert_p + (strlen(word) + 1), insert_p, (strlen(insert_p)+ 1));
        strcpy(insert_p, word);
        insert_p += strlen(word);
        *insert_p = ' ';
    }
}

void cmd_as(Sentences *sen_p, int i , char *sentence, int front)
{
    char *insert_p;
    i--;
    if(front)
    {
        insert_p = sen_p->lines[i];

        memmove(insert_p + (strlen(sentence) + 1), insert_p, (strlen(insert_p) + 1));
        strcpy(insert_p, sentence);
        insert_p += strlen(sentence);
        *insert_p = ' ';
    }
    else
    {
        insert_p = sen_p->lines[i] + strlen(sen_p->lines[i]);
        *insert_p = ' ';
        insert_p++;
        strcpy(insert_p, sentence);
    }
}

void cmd_i(Sentences * sen_p, char *key, char *word, int front)
{
    char *insert_p;
    for (int i = 0; i < sen_p->line_cnt; i++)
    {
        insert_p = strstr(sen_p->lines[i], key);
        while (insert_p != NULL)
        {
            if(!front)
            {
                insert_p += strlen(key);
                if (*insert_p == '\0')
                {
                    *insert_p = ' ';
                    insert_p++;
                    strcpy(insert_p, word);
                    break;
                }
                insert_p++;
            }

            memmove(insert_p + (strlen(word)+1), insert_p, (strlen(insert_p) + 1));
            strcpy(insert_p, word);
            insert_p += strlen(word);
            *insert_p = ' ';

            if(front)
            {
                insert_p = strstr(insert_p + strlen(key), key);
            }
            else
            {
                insert_p = strstr(insert_p, key);
            }
        }
        
    }
    
}

void cmd_dw(Sentences *sen_p, int i, int n)
{
    char *start_p, *end_p, *p;
    int word_cnt = 1;
    i--;

    p = sen_p->lines[i];
    while (*p != '\0')
    {
        if (word_cnt == n)
        {
            break;
        }
        if (*p == ' ')
        {
            word_cnt++;
        }
        p++;
    }
    start_p = p;
    while (*p != ' ' && *p != '\0')
    {
        p++;
    }
    if (*p == ' ')
    {
        end_p = p + 1;
    }
    else
    {
        start_p--;
        end_p = p;
    }
    memmove(start_p, end_p, strlen(end_p) + 1);
}

void cmd_dl(Sentences *sen_p, int i)
{
    i--;
    free(sen_p->lines[i]);
    sen_p->line_cnt--;

    for (int j = i; j < sen_p->line_cnt; j++)
    {
        sen_p->lines[j] = sen_p->lines[j+1];
    }
    
}

void cmd_rp(Sentences *sen_p, char *old, char *new)
{
    char *p, *src;
    cmd_i(sen_p, old, new, 0);

    for (int i = 0; i < sen_p->line_cnt; i++)
    {
        p = strstr(sen_p->lines[i], old);
        while (p != NULL)
        {
            src = p + strlen(old) + 1;
            memmove(p, src, strlen(src) + 1);
            p = strstr(p, old);
        }
        
    }
    
}

int cmd_c(Sentences * sen_p)
{
    char *p;
    int word_cnt = 0;
    for (int i = 0; i < sen_p->line_cnt; i++)
    {
        p = sen_p->lines[i];
        word_cnt++;
        while (*p != '\0')
        {
            if (*p == ' ')
            {
                word_cnt++;
            }
            p++;
        }
        
    }
    return word_cnt;
}

int main()
{
    //declaration
    int N, i, j;
    char buffer[BUFFER_SIZE];
    char *param[3];
    char *p;
    Sentences sen;

    //initailize
    sen.line_cnt = 0;

    //input
    scanf("%d %d\n", &sen.line_cnt, &N);
    sen.lines = malloc(sen.line_cnt *sizeof(char *));
    for ( i = 0; i < sen.line_cnt; i++)
    {
        gets(buffer);
        sen.lines[i] = (char *)malloc(BUFFER_SIZE);
        strcpy(sen.lines[i], buffer);
    }
    for ( i = 0; i < N; i++)
    {
        gets(buffer);
        p = strtok(buffer, " ");
        if (strcmp(p, "awf") == 0)
        {
            for ( j = 0; j < 3; j++)
            {
                param[j] = strtok(NULL, " ");
            }
            cmd_aw(&sen, atoi(param[0]), atoi(param[1]), param[2], 1);

        }
        else if (strcmp(p, "awa") == 0)
        {
            for ( j = 0; j < 3; j++)
            {
                param[j] = strtok(NULL, " ");
            }
            cmd_aw(&sen, atoi(param[0]), atoi(param[1]), param[2], 0);
            
        }
        else if (strcmp(p, "asf") == 0)
        {
           param[0] = strtok(NULL, " ");
           param[1] = strtok(NULL, "\0");
           cmd_as(&sen, atoi(param[0]), param[1], 1);
            
        }
        else if (strcmp(p, "asa") == 0)
        {
           param[0] = strtok(NULL, " ");
           param[1] = strtok(NULL, "\0");
           cmd_as(&sen, atoi(param[0]), param[1], 0);
            
        }
        else if (strcmp(p, "if") == 0)
        {
            for ( j = 0; j < 2; j++)
            {
                param[j] = strtok(NULL, " ");
            }
            cmd_i(&sen, param[0], param[1], 1);

        }
        else if (strcmp(p, "ia") == 0)
        {
            for ( j = 0; j < 2; j++)
            {
                param[j] = strtok(NULL, " ");
            }
            cmd_i(&sen, param[0], param[1], 0);

        }
        else if (strcmp(p, "dw") == 0)
        {
            for ( j = 0; j < 2; j++)
            {
                param[j] = strtok(NULL, " ");
            }
            cmd_dw(&sen, atoi(param[0]), atoi(param[1]));
        }
        else if (strcmp(p, "dl") == 0)
        {
            param[0] = strtok(NULL, "\n");
            cmd_dl(&sen, atoi(param[0]));
        }
        else if (strcmp(p, "rp") == 0)
        {
            for ( j = 0; j < 2; j++)
            {
                param[j] = strtok(NULL, " ");
            }
            cmd_rp(&sen, param[0], param[1]);
        }
        else if (strcmp(p, "c") == 0)
        {
            printf("%d\n", cmd_c(&sen));
        }
    }   


    //output
    for ( i = 0; i < sen.line_cnt; i++)
    {
        printf("%s\n", sen.lines[i]);
    }
    for ( i = 0; i < sen.line_cnt; i++)
    {
        free(sen.lines[i]);
    }
    free(sen.lines);

    return 0;
    
}
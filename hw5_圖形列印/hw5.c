#include <stdio.h>

void f1_1(int);
void f1_2(int);
void f2_1(int, int);
void f2_2(int, int);
void f3_1(int);
void f3_2(int);

int main()
{
    int num, x;
    scanf("%d", &num);

    if (num < 1 || num > 3)
    {
        printf("ERROR");
    }
    else
    {
        scanf("%d", &x);

        if (num == 1)
        {
            f1_1(x);
            f1_2(x);
        }
        else if (num == 2)
        {
            for (int i = 1; i <= x - 1; i++)
            {
                f2_1(x, i);
                f2_2(x, i);
                printf("\n");
            }
            for (int i = x - 1; i >= 1; i--)
            {
                f2_1(x, i);
                f2_2(x, i);
                printf("\n");
            }
            
            
        }
        else
        {
            for (int i = 1; i <= x; i++)
            {
                f3_1(i);
                f3_2(i);
                printf("\n");
            }
            
        }
        
    }
    return 0;
    
}

void f1_1(int a)
{
    for (int i = 1; i <= a; i++)
    {
        for (int j = 1; j <= i; j++)
        {
            printf("%d", j);
        }
        printf("\n");
        if (i == a)
        {
            break;
        }
        
    }
    
}

void f1_2(int a)
{
    for (int i = a; i >= 1; i--)
    {
        for (int j = i; j >= 1; j--)
        {
            printf("%d", j);
        }
        printf("\n");
        if (i == 1)
        {
            break;
        }
    }
    
}

void f2_1(int a, int b)
{
    for (int i = a - 1; i >= 1 ; i--)
    {
        if (b < i)
        {
            printf("_");
        }
        else
        {
            printf("%d", i);
        }
        
    }
    
}

void f2_2(int a, int b)
{
    for (int i = 2; i < a; i++)
    {
        if (b < i)
        {
            printf("_");
        }
        else
        {
            printf("%d", i);
        }
        
    }
    
}

void f3_1(int a)
{
    for (int i = 1; i <= a; i++)
    {
        printf("%d", i);
    }
    
}
void f3_2(int a)
{
    for (int i = a - 1; i >= 1; i--)
    {
        printf("%d", i);
    }
    
}


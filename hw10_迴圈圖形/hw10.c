#include <stdio.h>

void f1(int);
void f2(int, int);

int main()
{
    int choose, n, m;

    while(1)
    {
        scanf("%d", &choose);
        if (choose == 0)
        {
            break;
        }
        else if (choose != 1 && choose != 2)
        {
            printf("Error\n");
            break;
        }
        else if (choose == 1)
        {
            scanf("%d", &n);
            f1(n);
        }
        else
        {
            scanf("%d\n%d", &n, &m);
            f2(n, m);
        }
        
    }
    
    return 0;

}

void f1(int a)
{
    if (a < 1 || a > 30)
    {
        printf("Error\n");
        return;
    }
    for (int i = 1; i <= a; i++)
    {
        for (int j = 1; j <= i; j++)
        {
            printf("*");
        }
        for (int j = a - i + 1; j > 0; j--)
        {
            if (j <= 9)
            {
                printf("%d", j);
            }
            else
            {
                printf("%c", (j - 10) + 'a');
            }
        }
        printf("\n");

    }
    
}
void f2(int a, int b)
{
    if (a < 1 || a > 3)
    {
        printf("Error\n");
        return;
    }
    else if (b < 1 || b > 29 || b % 2 == 0)
    {
        printf("Error\n");
        return;
    }
    
    if (a == 1)
    {
        for (int i = 1; i <= b / 2; i++)
        {
            for (int j = 1; j <= i; j++)
            {
                printf("*");
            }
            printf("\n");
        }
        for (int i = b / 2 + 1; i >= 1; i--)
        {
            for (int j = 1; j <= i; j++)
            {
                printf("*");
            }
            printf("\n");
        }
    }

    else if (a == 2)
    {
        for (int i = 1; i <= b / 2; i++)
        {
            for (int j = b / 2 + 1; j >= 1; j--)
            {
                if (j > i)
                {
                    printf("#");
                }
                else
                {
                    printf("*");
                }
                
            }
            printf("\n");
        }

        for (int i = b / 2 + 1; i >= 1; i--)
        {
            for (int j = b / 2 + 1; j >= 1; j--)
            {
                if (j > i)
                {
                    printf("#");
                }
                else
                {
                    printf("*");
                }
                
            }
            printf("\n");
        }
    }

    else
    {

        for (int i = 1; i <= b / 2; i++)
        {
            for (int j = 1; j <= b / 2 + 1 - i; j++)
            {
                printf("#");
            }

            for (int j = 1; j <= i * 2 - 1; j++)
            {
                printf("*");
            }
            printf("\n");
        }
        
        for (int i = b / 2 + 1; i >= 1; i--)
        {
            for (int j = 1; j <= b / 2 + 1 - i; j++)
            {
                printf("#");
            }

            for (int j = 1; j <= i * 2 - 1; j++)
            {
                printf("*");
            }
            printf("\n");
        }
        
    }
    
}
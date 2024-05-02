#include <stdio.h>
#include <stdlib.h>

int get_gcd (int, int);

int main()
{
    //initialize
    int a1, a2, b1, b2, c, d, e, gcd, sign; 
    char operator, stat;        
    do
    {   
        //input
        scanf("%d/%d\n %d/%d\n", &a1, &a2, &b1, &b2);
        scanf("%c\n %c", &operator, &stat);

        if (a2 == 0 || b2 == 0)
        {
            printf("ERROR\n");
            continue;
        }
        
        //compute
        if (operator == '+' || operator == '-')
        {
            d = a2 * b2 / get_gcd(a2, b2);
            if (operator == '+')
            {
                c = a1 * (d / a2) + b1 * (d / b2);
            }
            else
            {
                c = a1 * (d / a2) - b1 * (d / b2);
            }
            sign = c >= 0 ? 1 : -1;
            if (sign == -1)
            {
                c = -c;
            }
        }
        else
        {
            sign = a1 * b1 >= 0 ? 1 : -1;
            a1 = abs(a1);
            b1 = abs(b1);
            if (operator == '*')
            {
                c = a1 * b1;
                d = a2 * b2;
            }
            else
            {
                c = a1 * b2;
                d = a2 * b1;

            }
        }

        //approximation
        gcd = get_gcd(c, d);
        c /= gcd;
        d /= gcd;
       
        if (c % d == 0) //integer
        {
            printf("%d\n", sign * (c/d));
        }
        else if (c > d) //mixed fraction
        {
            e = c / d;
            c %= d;
            printf("%d(%d/%d)\n", sign * e, c, d);
        }
        else //proper fraction
        {
            printf("%d/%d\n", sign * c, d);
        }

    } while(stat == 'y');

    return 0;

}   

int get_gcd(int a, int b)
{
    int temp;
    while (b != 0)
    {
        temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}



#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int main()
{
    char dividend[40], divisor[40], divisor_copy[40], quotient[40];
    int a = 0, k = 0, a_k, a_k_copy;
    int index = 0, count = 0;
    int mode = 0;
    bool start = false;
    bool sign1 = false, sign2 = false, sign3 = false;
    bool zero = true;

    scanf("%s", dividend);
    scanf("%s", divisor);

    a = strlen(dividend) - 1;
    k = strlen(divisor) - 1;

    if (dividend[0] == '-')
    {
        sign1 = true;
        for (int i = 0; i < a; i++)
        {
            dividend[i] = dividend[i + 1];
        }
        dividend[a] = '\0';
        a--;
    }
    if (divisor[0] == '-')
    {
        sign2 = true;
        for (int i = 0; i < k; i++)
        {
            divisor[i] = divisor[i + 1];
        }
        divisor[k] = '\0';
        k--;
    }

    if ((sign1 == true && sign2 == false) || (sign1 == false && sign2 == true))
    {
        sign3 = true;
    }
    
    a_k = a - k;
    a_k_copy = a_k;

    //copy divisor
    for (int i = a; i >= a - k; i--)
    {
        divisor_copy[i] = divisor[i - (a - k)];
    }
    for (int i = a - k - 1; i >= 0; i--)
    {
        divisor_copy[i] = '0';
    }
    for (int i = k + 1; i <= a; i++)
    {
        divisor[i] = '0';
    }
    
    //minus
    while(1)
    {
        for (int i = 0; i <= a; i++)
        {
            if (dividend[i] > divisor[i])
            {
                mode = 1;
                break;
            }
            else if (dividend[i] < divisor[i])
            {
                mode = 2;
                break;
            }
            else{}          
            
        }
        if (mode == 0)
        {
            count++;
            for (int i = 0; i < a_k; i++)
            {
                count = count * 10;
            }
            if (sign3 == true)
            {
                printf("-");
            }
            printf("%d", count);
            printf("\n0");

            return 0;
        }
        else if(mode == 1)
        {
            index = a;
            while (1)
            {
                if (dividend[index] >= divisor[index])
                {
                    dividend[index] = dividend[index] - divisor[index] + '0';
                }
                else
                {
                    int borrow = index - 1;
                    while (1)
                    {
                        if (dividend[borrow] > 0)
                        {
                            dividend[borrow] = dividend[borrow] - 1;
                            for (int i = borrow + 1; i < index; i++)
                            {
                                dividend[i] = '9';
                            }
                            dividend[index] = 10 + '0' - divisor[index] + dividend[index];
                            break;
                        }
                        else
                        {
                            borrow--;
                        }
                        
                    }
                    
                }
                index--;
                if (index < 0)
                {
                    break;
                }
                
            }
            count++;
        }
        else
        {
            if (strncmp(divisor_copy, divisor, a + 1) == 0)
            {
                quotient[a_k] = count + '0';
                break;
            }
            else
            {
                for (int i = a; i > 0; i--)
                {
                    divisor[i] = divisor[i - 1];
                }
                divisor[0] = '0';
                quotient[a_k] = count + '0';
                count = 0;
                a_k--;
            }
        }
    }              
    if ((sign1 == true && sign2 == true) || (sign1 == true && sign2 == false))
    {
        for (int i = 0; i <= a; i++)
        {
            if (dividend[i] != '0')
            {
                zero = false;
                break;
            }
            
        }
        if (zero == false)
        {
            quotient[0] += 1;

            index = a;
            while (1)
            {
                if (divisor[index] >= dividend[index])
                {
                    dividend[index] = divisor[index] - dividend[index] + '0';
                }
                else
                {
                    int borrow = index - 1;
                    while (1)
                    {
                        if (divisor[borrow] > 0)
                        {
                            divisor[borrow] = divisor[borrow] - 1;
                            for (int i = borrow + 1; i < index; i++)
                            {
                                divisor[i] = '9';
                            }
                            dividend[index] = 10 + '0' - dividend[index] + divisor[index];
                            break;
                        }
                        else
                        {
                            borrow--;
                        }
                        
                    }
                    
                }
                index--;

                if (index < 0)
                {
                    break;
                }
                
            }
            
        }
        
    }
    if (sign3 == true)
    {
        printf("-");
    }
    for (int i = a_k_copy; i >= 0; i--)
    {
        if (quotient[i] != '0')
        {
            start = true;
        }
        if (start == true)
        {
            printf("%c", quotient[i]);
        }
    }
    printf("\n");

    start = false;

    //output
    for (int i = 0; i <= a; i++)
    {
        if (dividend[i] != '0')
        {
            start = true;
        }
        if (start == true)
        {
            printf("%c", dividend[i]);
        }
        
    }
    if (start == false)
    {
        printf("0");
    }
    
    return 0;
}


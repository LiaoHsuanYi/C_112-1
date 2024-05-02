#include <stdio.h>
#include <string.h>
#define MID_POS 60
#define LAST_POS 120

typedef struct LongNumAry
{
    int digits[LAST_POS + 1];
} LongNum;

void negate(LongNum *ln)
{
    int i, carry, n;
    carry = 1;
    for ( i = LAST_POS; i >= 0; i--)
    {
        n = 9 - ln -> digits[i] + carry;
        if (n > 9)
        {
            n -= 10;
            carry = 1;
        }
        else
        {
            carry = 0;
            ln -> digits[i] = n;
        }
    }
}

void fillNum(char *c, LongNum *ln)
{
    int i, neg, fillTo;
    char *p;

    memset(ln ->digits, 0, sizeof(LongNum));
    if (*c == '-')
    {
        neg = 1;
        c++;
    }
    else
    {
        neg = 0;
    }
    
    p = strchr(c, '.');
    if (p == NULL)
    {
        p = c + strlen(c);
    }
    
    fillTo = MID_POS - (p - c) + 1;
    while (*c && fillTo <= LAST_POS)
    {
        if (c != p)
        {
            ln ->digits[fillTo++] = *c - '0';
        }
        c++;
    }
    if (neg)
    {
        negate(ln);
    }
}


void fillStr(LongNum *ln, char *buffer)
{
    int neg, i, n;
    neg = (ln ->digits[0] != 0);
    if (neg)
    {
        *buffer++ = '-';
        negate(ln);
    }
    
    i = 1;
    n = 0;
    while (i <= MID_POS)
    {
        if (ln ->digits[i] == 0 && n == 0)
        {
            i++;
            continue;
        }
        *buffer++ = ln ->digits[i++] + '0';
        n++;
    }
    if (n == 0)
    {
        *buffer++ = '0';
    }
    
    n = 0;
    i = LAST_POS;
    while (i > MID_POS)
    {
        if (ln ->digits[i] == 0 && n == 0)
        {
            i--;
            continue;
        }
        n++;
        i--;
    }
    if (n > 0)
    {
        *buffer++ = '.';
        for ( i = 0; i < n; i++)
        {
            *buffer++ = ln ->digits[i + MID_POS + 1] + '0';
        }
        
    }
    *buffer++ = '\0';
    if (neg)
    {
        negate(ln);
    }
    
}

void add(LongNum *ln1, LongNum *ln2, LongNum *rtn)
{
    int carry, i, n;
    carry = 0;
    for ( i = LAST_POS; i >= 0; i--)
    {
        n = ln1 ->digits[i] + ln2 ->digits[i] + carry;
        if (n > 9)
        {
            n -= 10;
            carry = 1;
        }
        else
        {
            carry = 0;
        }
        rtn ->digits[i] = n;
    }
    
}

void multiple(LongNum *ln1, LongNum *ln2, LongNum *rtn)
{
    int neg1, neg2, i, j, carry, n, m;
    neg1 = ln1 ->digits[0] != 0;
    neg2 = ln2 ->digits[0] != 0;

    for ( i = 0; i <= LAST_POS; i++)
    {
        rtn ->digits[i] = 0;
    }
    
    if (neg1)
    {
        negate(ln1);
    }
    if (neg2)
    {
        negate(ln2);
    }

    for ( i = LAST_POS; i >= 1; i--)
    {
        if (ln1 ->digits[i] == 0)
        {
            continue;
        }
        n = MID_POS - i;
        if (n < 1)
        {
            n = 1;
        }
        m = LAST_POS + MID_POS - i;
        if (m > LAST_POS)
        {
            m = LAST_POS;
        }
        for (j = m; j >= n; j--)
        {
            if (ln2 ->digits[j] == 0)
            {
                continue;
            }
            rtn ->digits[i + j - MID_POS] += ln1 ->digits[i] * ln2 ->digits[j];
        }
        
    }
    carry = 0;
    for ( i = LAST_POS; i >= 1; i--)
    {
        rtn ->digits[i] += carry;
        if (rtn ->digits[i] >= 10)
        {
            carry = rtn ->digits[i] / 10;
            rtn ->digits[i] %= 10;
        }
        else
        {
            carry = 0;
        }
    }
    if (neg1)
    {
        negate(ln1);
    }
    if (neg2)
    {
        negate(ln2);
    }
    if (neg1 ^ neg2)
    {
        negate(rtn);
    }
    
}

int main()
{
    LongNum num1, num2, num3;
    char s1[LAST_POS + 1];
    char s2[LAST_POS + 1];
    char buffer[LAST_POS + 1];
    scanf("%s", s1);
    scanf("%s", s2);
    fillNum(s1, &num1);
    fillNum(s2, &num2);

    //add
    add(&num1, &num2, &num3);
    fillStr(&num3, buffer);
    printf("%s\n", buffer);

    //minus
    negate(&num2);
    add(&num1, &num2, &num3);
    negate(&num2);
    fillStr(&num3, buffer);
    printf("%s\n", buffer);

    //multiple
    multiple(&num1, &num2, &num3);
    fillStr(&num3, buffer);
    printf("%s", buffer);

    
    return 0;


}
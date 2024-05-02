#include <stdio.h>
#include <stdbool.h>

int main()
{
    char num[16];
    char converted_num[30];
    int before_r, after_r;
    int count = 0;
    unsigned long long num1 = 0;
    bool err = false;
    char table[17] = "0123456789ABCDEF"; //output setting

    //input
    scanf("%s", num);
    scanf("%d", &before_r);
    scanf("%d", &after_r);

    if (before_r > 16 || before_r < 2 || after_r > 16 || after_r < 2)
    {
        err = true;
    }
    
    //convert to 10 
    for (int i = 0; num[i] != '\0' ; i++)
    {
        //number
        if (num[i] >= '0' && num[i] <= '9')
        {
            if (num[i] - '0' >= before_r)
            {
                err = true;
                break;
            }
            else
                num1 = num1 * before_r + num[i] - '0';
        }
        //letter
        else
            if (num[i] - 'A' + 10 >= before_r)
            {
                err = true;
                break;
            }
            else
            num1 = num1 * before_r + num[i] - 'A' + 10;
    }


    //transform to converted number
    do
    {
        converted_num[count] = num1 % after_r;
        count++;
        num1 = num1 / after_r;
       
    } while (num1 != 0);

    //print output
    if (err == true)
    {
        printf("ERROR\n");
    }
    else
    {
        for (int i = count - 1; i >= 0 ; i--)
        {
            if (converted_num[i] == '0')
            {
                printf("0");
            }
            else
                printf("%c", table[converted_num[i]]);
        }
    }
    return 0;

}
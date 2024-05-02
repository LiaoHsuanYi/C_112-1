#include <stdio.h>
#include <string.h>

float calcStrength(char *s)
{
    const char *spc_chars = "~!@#$%^&*<>_+=";
    float strength = 0;
    int total_count = 0, group_count = 0;

    while (*s)
    {
        if (*s >= '0' && *s <= '9')
        {
            strength += 2;
            group_count++;
            if (group_count == 1) //first num
            {
                total_count++;
            }
            else if (group_count == 2) //second num
            {
                total_count--; //didn't include to not adjacent
            }
            
        }
        else
        {
            group_count = 0;
            if (*s >= 'a' && *s <= 'z')
            {
                strength += 1;
            }
            else if (*s >= 'A' && *s <= 'Z')
            {
                strength += 3;
            }
            else if (strchr(spc_chars, *s) != NULL)
            {
                strength += 4.5;
            }
            
        }
        s++;
    }
    if (total_count >= 5)
    {
        strength += 10;
    }
    
    return strength;

}

int main()
{
    char buf[80], max_pwd[80], min_pwd[80];
    float score, max_score = 0, min_score = 9999;

    while (gets(buf))
    {
        if (strcmp(buf, "-1") == 0)
        {
            break;
        }
        score = calcStrength(buf);
        if (score < min_score)
        {
            strcpy(min_pwd, buf);
            min_score = score;
        }
        if (score > max_score)
        {
            strcpy(max_pwd, buf);
            max_score = score;
        } 
    }
    printf("%s %.1f\n", max_pwd, max_score);
    printf("%s %.1f\n", min_pwd, min_score);

    return 0;

}
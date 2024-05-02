#include <stdio.h>
#include <stdbool.h>

int card_type(int arr[]);

int main()
{
    char face[] = {'2', '3', '4', '5', '6', '7', '8', '9', ' ', 'J', 'Q', 'K', 'A'};
    char suit[] = {'C', 'D', 'H', 'S'};
    char set[10][5];
    int set_int[10] = {0}; //change char to int
    int set1_int[5], set2_int[5]; 
    bool is_duplicate = false;
    int type1 = 0, type2 = 0;

    scanf("%s %s %s %s %s", set[0], set[1], set[2], set[3], set[4]);
    scanf("%s %s %s %s %s", set[5], set[6], set[7], set[8], set[9]);

    // face * 10 + suit
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 13; j++)
        {
            if (set[i][0] == face[j]) // judge face
            {
                for (int k = 0; k < 4; k++) // judge suit
                {
                    if (set[i][1] == suit[k])
                    {
                        set_int[i] = (j + 2) * 10 + k; //change to number
                    }
                }
                if (set[i][2] != '\0')
                {
                    printf("Error input");
                    return 0;
                }
                
            }
            else if (set[i][0] == '1' && set[i][1] == '0') //is 10?
            {
                for (int k = 0; k < 4; k++) // judge suit
                {
                    if (set[i][2] == suit[k])
                    {
                        set_int[i] = 10 * 10 + k;
                    }
                    
                }
                
            }
        }
        if (set_int[i] == 0)
        {
            printf("Error input");
            return 0;
        }
        else
        {
            for (int j = 0; j < i; j++)
            {
                if (set_int[i] == set_int[j])
                {
                    is_duplicate = true;
                }
                
            }
            
        }
    }
    if (is_duplicate == true)
    {
        printf("Duplicate deal");
        return 0;
    }
    for (int i = 0; i < 10; i++) //separated to set1 and set2
    {
        if (i < 5)
        {
            set1_int[i] = set_int[i];
        }
        else
        {
            set2_int[i - 5] = set_int[i];
        }
    }
    
    //order
    int temp;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4 - i; j++)
        {
            if (set1_int[j] > set1_int[j + 1])
            {
                temp = set1_int[j];
                set1_int[j] = set1_int[j + 1];
                set1_int[j + 1] = temp;
            }
            if (set2_int[j] > set2_int[j + 1])
            {
                temp = set2_int[j];
                set2_int[j] = set2_int[j + 1];
                set2_int[j + 1] = temp;
            }
            
        }
        
    }

    //obtain max
    type1 = card_type(set1_int);
    type2 = card_type(set2_int);

    //compare and output the max of two sets
    if (type1 > type2)
    {
        printf("%d", type1);
    }
    else
    {
        printf("%d", type2);
    }

    return 0;
}

int card_type(int arr[])
{
    int set[5];
    bool is_type[10] = {false};
    int same_num[4] = {0};

    is_type[1] = true;

    for (int i = 0; i < 5; i++)
    {
        set[i] = arr[i];
    }

    //straight
    for (int i = 0; i < 4; i++)
    {
        //nornal or segmented
        if ((set[i] / 10 + 1) != (set[i + 1] / 10 ) && (set[i] / 10 + 9) != (set[i + 1] / 10))
        {
            is_type[5] = false;
            break;
        }
        is_type[5] = true;
    }

    //flush
    for (int i = 0; i < 4; i++)
    {
        int r1, r2;
        r1 = set[i] % 10;
        r2 = set[i + 1] % 10;
        if (r1 != r2)
        {
            is_type[6] = false;
            break;
        }
        is_type[6] = true;
    }
    
    //straight flush
    if (is_type[5] == true && is_type[6] == true)
    {
        return 9;
    }

    //compute the same points card
    for (int i = 0; i < 4; i++)
    {
        for (int j = i + 1; j <= 4; j++)
        {
            if (set[i] / 10 == set[j] / 10)
            {
                same_num[i]++;
            }
        }
        i += same_num[i];
    }

    int pair = 0;
    for (int i = 0; i < 4; i++)
    {
        if (same_num[i] > 0)
        {
            pair++;
            if (same_num[i] == 3)
            {
                return 8;
            }
            else if (same_num[i] == 2)
            {
                is_type[4] = true;
            }
            else if (same_num[i] == 1)
            {
                is_type[2] = true;
            }
        }
        
    }

    //pair
    if (pair == 2)
    {
        is_type[3] = true;
    }

    //full house
    if (is_type[4] == true && is_type[2] == true)
    {
        return 7;
    }

    //check
    for (int i = 6; i > 0 ; i--)
    {
        if(is_type[i] == true)
        {
            return i;
        }
    }
    
    
}
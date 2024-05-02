#include <stdio.h>
#include <stdbool.h>

int card_type(int arr[]);

int main()
{
    //initialize
    char face[] = {'2', '3', '4', '5', '6', '7', '8', '9', ' ', 'J', 'Q', 'K', 'A'};
    char suit[] = {'C', 'D', 'H', 'S'};
    char set[20][5];
    char winner;
    int round;
    int set_int[20] = {0};
    int set4_int[4][5]; //4 set card
    bool error, duplicate, is_suit, is_face;

    //input
    scanf("%d", &round);
    while (round > 0)
    {
        error = false;
        duplicate = false;

        for (int i = 0; i < 20; i += 5)
        {
            scanf("%s %s %s %s %s", set[i], set[i+1], set[i+2], set[i+3], set[i+4]);
        }

        //convert to integer
        //face * 10 + suit
        for (int i = 0; i < 20; i++)
        {
            is_face = false;
            is_suit = false;
            for (int j = 0; j < 13; j++)
            {
                if (set[i][0] == face[j])
                {
                    is_face = true; //have face
                    for (int k = 0; k < 4; k++)
                    {
                        if (set[i][1] == suit[k])
                        {
                            is_suit = true; //have suit
                            set_int[i] = (j + 2) * 10 + k;
                        }
                    }
                    if (set[i][2] != '\0')
                    {
                        error = true;
                        break;
                    }
                    if (is_suit == false)
                    {
                        error = true;
                        break;
                    }
                }
                else if (set[i][0] == '1' && set[i][1] == '0')
                {
                    for (int k = 0; k < 4; k++)
                    {
                        if (set[i][2] == suit[k])
                        {
                            is_suit = true;
                            set_int[i] = 10 * 10 + k;
                        }
                        
                    }
                    
                }
                    
            }

            if (error == true)
            {
                break;
            }
            
            if (set_int[i] == 0)
            {
                error = true;
                break; 
            }
            else
            {
                for (int j = 0; j < i; j++)
                {
                    if (set_int[i] == set_int[j])
                    {
                        duplicate = true;
                        break;
                    }
                    
                }
                
            }
            if (duplicate == true)
            {
                break;
            }

        }
        
        if (error == true)
        {
            printf("Error input\n");
            round--;
            continue;
        }

        if (duplicate == true)
        {
            printf("Duplicate deal\n");
            round--;
            continue;
        }

        for (int i = 0; i < 4; i++)
        {
            for (int j = i * 5; j < i * 5 + 5; j++)
            {
                set4_int[i][j % 5] = set_int[j];
            }
            
        }

        int temp;
        for (int x = 0; x < 5; x++)
        {
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4 - i; j++)
                {
                    if (set4_int[x][j] > set4_int[x][j+1])
                    {
                        temp = set4_int[x][j];
                        set4_int[x][j] = set4_int[x][j+1];
                        set4_int[x][j+1] = temp;
                    }
                    
                }
                
            }
            
        }
        
        int max_type = 0;
        int max_player = 0;
        int type = 0;
        for (int i = 0; i < 4; i++)
        {
            type = card_type(set4_int[i]);

            if (type > max_type)
            {
                max_type = type;
                max_player = i;
            }
            
        }
        
        winner = 'A' + max_player;
        printf("%c\n", winner);

        round--;

    }

    
    return 0;
    
    
}

int card_type(int arr[])
{
    int set[5];
    bool is_type[9] = {false};
    int same_num[4] = {0};
    int face[5], suit[5];
    int Face, Suit, temp;

    is_type[0] = true;

    for (int i = 0; i < 5; i++)
    {
        set[i] = arr[i];
        face[i] = arr[i];
        suit[i] = arr[i];
    }

    //straight
    for (int i = 0; i < 4; i++)
    {
        if (set[i] / 10 + 1 != set[i+1] / 10 && set[i] / 10 + 9 != set[i+1] / 10)
        {
            is_type[4] = false;
            break;
        }
        is_type[4] = true;
    }
    if (is_type[4])
    {
        if (set[0] / 10 == 2 && set[4] / 10 == 14)
        {
            Face = 1;
            Suit = set[4] % 10;
        }
        else
        {
            Face = set[0] / 10;
            Suit = set[4] % 10;
        }
    }
    

    //flush
    for (int i = 0; i < 4; i++)
    {
        int r1 = set[i] % 10;
        int r2 = set[i+1] % 10;
        if (r1 != r2)
        {
            is_type[5] = false;
            break;
        }
        if (suit[i] > suit[i+1])
        {
            if (face[i] > face[i+1])
            {
                suit[0] = suit[i];
                face[0] = face[i];
            }
        }
        
        is_type[5] = true;
    }

    if (is_type[5])
    {
        Suit = set[0] % 10;
    }
    
    
    //flush straight
    if (is_type[4] == true && is_type[5] == true)
    {
        return 8 * 1000 + Face * 10 + Suit;
    }

    //same point card
    for (int i = 0; i < 4; i++)
    {
        for (int j = i + 1; j < 5; j++)
        {
            if (set[i] / 10 == set[j] / 10)
            {
                same_num[i]++;
            }
            
        }
        i += same_num[i];
    }
    
    int pair = 0; //quantity of pairs
    

    for (int i = 0; i < 4; i++)
    {
        if (same_num[i] > 0)
        {
            pair++;
            if (same_num[i] == 3) //four of kind
            {
                i += 3;
                Face = set[i] / 10;
                Suit = set[i] % 10;
                return 7 * 1000 + Face * 10 + Suit;
            }
            else if (same_num[i] == 2) // three of kind
            {
                is_type[3] = true;
                Face = set[i+2] / 10;
                Suit = set[i+2] % 10;
            }
            else if (same_num[i] == 1) //pair
            {
                is_type[1] = true;
            }
            
            
        }
        
    }
    
    //two pairs
    if (pair == 2)
    {
        is_type[2] = true;
    }
    
    //full house
    if (is_type[3] == true && is_type[1] == true)
    {
        return 6 * 1000 + Face * 10 + Suit;
    }
    
    //check 0 ~ 5
    for (int i = 5; i >= 0; i--)
    {
        if (is_type[i] == true)
        {
            for (int i = 5; i >= 0; i--)
            {
                if (i == 2 || i == 1) //pair & two pair
                {
                    for (int i = 3; i >= 0; i--)
                    {
                        if (same_num[i] != 0)
                        {
                            Face = set[i+1] / 10;
                            Suit = set[i+1] % 10;
                        }
                        
                    }
                    
                }
                if(i == 0) //one of card
                {
                    Face = set[4] / 10;
                    Suit = set[4] % 10;
                }
                return i * 1000 + Face * 10 + Suit;
            }
            
        }
        
    }
    
    
}
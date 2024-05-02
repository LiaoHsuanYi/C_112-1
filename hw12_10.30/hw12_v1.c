#include <stdio.h>
#include <stdbool.h>

float deal(char, char);

int main()
{
    //initialize
    float points[4] = {0}; //c & p1~p3's points
    int output[4] = {0}; 
    int bets[3] = {0}; 
    bool burst[3] = {false}; //burst or not
    bool stop[3] = {false}; //win or lose
    bool end = false; //game finished or not
    int players, p = 0, count = 1, handcards = 0;
    float min_point;
    char str[15] = {'\0'};

    char ch;
    int i = 0;

    //input players
    scanf("%d", &players);

    //input bets
    while (i < players)
    {
        scanf("%d", &bets[i]);
        i++;
    }
    i = 0;

    ch = getchar();

    //c & p1~p3 all get 1 card
    fgets(str, 15, stdin);

    //save to points[4]
    do
    {
        points[p] = deal(str[i], str[i + 1]);
        if (points[p] == 10)
        {
            i++;
        }

        i += 2;
        p++;
        
    } while (p != players + 1);
    i = 0;

    while (count <= players)
    {
        handcards = 1;

        for (int j = 0; j < 15; j++)
        {
            str[j] = '\0';
        }

        while ((ch = getchar()) != '\n')
        {
            str[i] = ch;
            i++;
        }
        i = 0;

        while (str[0] == 'Y')
        {
            handcards++;
            float r = deal(str[2], str[3]);
            points[count] += r;

            if (points[count] > 10.5)
            {
                burst[count - 1] = true;
                stop[count - 1] = true;
                output[count - 1] -= bets[count - 1]; //player lose money
                output[players] += bets[count - 1]; //computer earn player's bets
                break;
            }
            
            else if (points[count] == 10.5)
            {
                stop[count - 1] = true;
                output[count - 1] += bets[count - 1]; //player earn money
                output[players] -= bets[count - 1]; //computer lose player's bets
                break;
            }
            
            //player got 5 cards, computer lose player's bets
            if (handcards == 5)
            {
                stop[count - 1] = true;
                output[count - 1] += bets[count - 1];
                output[players] -= bets[count - 1];
                break;
            }

            //whether computer give player cards or not
            while ((ch = getchar()) != '\n')
            {
                str[i] = ch;
                i++;
            }
            i = 0;
            
        }
        count++;
        
    }
    
    min_point = points[1];
    for (int k = 1; k < players + 1; k++)
    {
        if (min_point > points[k])
        {
            min_point = points[k];
        }
    }
    
    //whether the game ended or not
    for (int k = 0; k < players; k++)
    {
        if (stop[k] == false)
        {
            end = false;
            break;
        }
        end = true;
    }
    
    if (end == false)
    {
        //if computer's points < all players's minimun points
        while (points[0] < min_point)
        {
            while ((ch = getchar()) != '\n')
            {
                str[i] = ch;
                i++;
            }
            i = 0;

            float r = deal(str[0], str[1]);
            points[0] += r;

            //if computer burst
            if (points[0] > 10.5)
            {
                for (int k = 0; k < players; k++)
                {
                    if (stop[k] == false)
                    {
                        output[k] += bets[k]; //all players earn
                        output[players] -= bets[k]; //computer lose
                    }
                    
                }
                break;
            }
        
        }
        
        //computer compare points with players
        if (points[0] <= 10.5)
        {
            for (int k = 0; k < players; k++)
            {
                if (stop[k] == false)
                {
                    if (points[0] >= points[k + 1])
                    {
                        output[k] -= bets[k];
                        output[players] += bets[k];
                    }
                    else
                    {
                        output[k] += bets[k];
                        output[players] -= bets[k];
                    }

                }
                
            }
            
        }  

    }
    
    //players output
    for (int k = 0; k < players; k++)
    {
        if (output[k] > 0)
        {
            printf("Player%d +%d\n", k + 1, output[k]);
        }
        else
        {
            printf("Player%d %d\n", k + 1, output[k]);
        }
    }
    
    //computer output
    if (output[players] > 0)
    {
        printf("Computer +%d\n", output[players]);
    }
    else
    {
        printf("Computer %d\n", output[players]);
    }
    

    return 0;

}

float deal(char face, char face1)
{
    if (face == 'A')
    {
        return 1;
    }
    else if (face >= '2' && face <= '9')
    {
        return face - '0';
    }
    else if (face == '1' && face1 == '0')
    {
        return 10;
    }
    else if (face == 'J' || face == 'Q' || face == 'K')
    {
        return 0.5;
    }
    else
    {
        printf("Input Error");
        return -1;
    }

}

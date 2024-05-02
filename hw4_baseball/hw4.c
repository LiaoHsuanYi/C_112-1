#include <stdio.h>

int main()
{
    char player[9][5];
    int hits[9][3];
    int base[3];
    int to_outs = 0;
    int curr_outs = 0;
    int score = 0;
    int a;
    int b;
    int temp;

    //initialize
    for (int i = 0; i < 3; i++)
    {
        base[i] = -1;
    }
    
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            player[i][j] = 0;
        }
    }
    
    for (int i = 0; i < 9; i++)
    {
        hits[i][0] = i + 1; //player number
        for (int j = 1; j < 3; j++)
        {
            hits[i][j] = 0;
        }
    }

    //input
    for (int i = 0; i < 9; i++)
    {
        scanf("%d", &a);
        for (int j = 0; j < a; j++)
        {
            scanf(" %c", &player[i][j]);
        }
        scanf("\n", &temp);
    }
    
    scanf("%d", &b);

    //calculate
    for (int i = 0; i < 5; i++) // 5 rounds
    {
        for (int j = 0; j < 9; j++) // 9 players
        {
            if (player[j][i] == 'O')
            {
                to_outs += 1;
                if (to_outs == b)
                {
                    break;
                }
                curr_outs += 1;
                if (curr_outs == 3) // clear base
                {
                    base[0] = -1;
                    base[1] = -1;
                    base[2] = -1;
                    curr_outs = 0;
                }
                continue;
            }

            hits[j][1] += 1;

            if (player[j][i] == '1')
            {
                if(base[2] != -1)
                {
                    hits[base[2]][2] += 1;
                    score += 1;
                    base[2] = -1;
                }
                base[2] = base[1];
                base[1] = base[0];
                base[0] = j;
            }
            else if (player[j][i] == '2')
            {
                for (int k = 1; k < 3; k++)
                {
                    if (base[k] != -1)
                    {
                        hits[base[k]][2] += 1;
                        score += 1;
                        base[k] = -1;
                    }
                }
                base[2] = base[0];
                base[1] = j;
                base[0] = -1;
            }
            else if (player[j][i] == '3')
            {
                for (int k = 0; k < 3; k++)
                {
                    if (base[k] != -1)
                    {
                        hits[base[k]][2] += 1;
                        score += 1;
                        base[k] = -1;
                    }
                }
                base[2] = j;
                
            }
            else if (player[j][i] == 'H')
            {
                for (int k = 0; k < 3; k++)
                {
                    if (base[k] != -1)
                    {
                        hits[base[k]][2] += 1;
                        score += 1;
                        base[k] = -1;
                    }
                }
                hits[j][2] += 1;
                score += 1;
            }
        }    
        if (to_outs == b)
        {
            break;
        }
    }
    
    
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8 - i; j++)
        {
            if(hits[j][2] < hits[j+1][2])
            {
                //0
                temp = hits[j+1][0];
                hits[j+1][0] = hits[j][0];
                hits[j][0] = temp;
                //1
                temp = hits[j+1][1];
                hits[j+1][1] = hits[j][1];
                hits[j][1] = temp;
                //2
                temp = hits[j+1][2];
                hits[j+1][2] = hits[j][2];
                hits[j][2] = temp;
            }
        }
    }

    for (int i = 0; i < 8; i++)
    {
        if (hits[i][2] == hits[i+1][2])
        {
            if(hits[i][0] > hits[i+1][0])
            {
                //0
                temp = hits[i+1][0];
                hits[i+1][0] = hits[i][0];
                hits[i][0] = temp;
                //1
                temp = hits[i+1][1];
                hits[i+1][1] = hits[i][1];
                hits[i][1] = temp;
                //2
                temp = hits[i+1][2];
                hits[i+1][2] = hits[i][2];
                hits[i][2] = temp;
            }
        }
    }

    //output
    printf("%d\n", score);
    for (int i = 0; i < 3; i++)
    {
        printf("%d %d %d\n", hits[i][0], hits[i][1], hits[i][2]);
    }
    
    return 0;
}
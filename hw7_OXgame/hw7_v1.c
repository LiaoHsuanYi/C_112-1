#include <stdio.h>
#include <string.h>

typedef struct OXgame
{
    int board[9];
    int remain;
    int sugg;
} OX;

int sumOne(int index, int delta, int player, OX *game)
{
    int count = 0;
    for (int i = 0; i < 3; i++)
    {
        if (game -> board[index] == 0)
        {
            count++;
        }
        else if (game -> board[index] != player)
        {
            return -1;
        }
        index += delta;
    }
    if (count == 1)
    {
        for (int i = 0; i < 3; i++)
        {
            index -= delta;
            if (game -> board[index] == 0)
            {
                game -> sugg = index;
                break;
            }
            
        }
        
    }
    return count;
}

// n = 0 means already be line. n = 1 means will be line soon.
int FindWinPos(int player, int n, OX *game)
{
    int count = 0;
    for (int i = 0; i < 3; i++)
    {
        //level
        if (sumOne(i * 3, 1, player, game) == n)
        {
            count++;
        }
        //vertical
        if (sumOne(i, 3, player, game) == n)
        {
            count++;
        }
    }
    //1, 5, 9
    if (sumOne(0, 4, player, game) == n)
    {
        count++;
    }
    //3, 5, 7
    if (sumOne(2, 2, player, game) == n)
    {
        count++;
    }
    
    return count;
}

int CheckWin(OX *game)
{
    for (int i = 1; i < 3; i++)
    {
        if (FindWinPos(i, 0, game) > 0)
        {
            return i;
        }
    }
    if (game -> remain == 1)
    {
        if (FindWinPos(1, 1, game) == 0 && FindWinPos(2, 1, game) == 0) //tie
        {
            return 3;
        }
    }
    return 4; //no winner and loser
}

int SuggPos(OX *game)
{
    if (FindWinPos(2, 1, game) > 0) //if computer can win
    {
        return game -> sugg + 1;
    }
    if (FindWinPos(1, 1, game) > 0) //if player can win
    {
        return game -> sugg + 1;
    }
    for (int i = 0; i < 9; i++)
    {
        if (game -> board[i] == 0)
        {
            return i + 1;
        }
        
    }
    
}

int main()
{
    OX game;
    int a, b, i, error, curr_player, curr_pos, winstate;
    game.remain = 9;
    memset(game.board, 0, sizeof(game.board)); //initialize
    scanf("%d %d", &a, &b);

    error = 0;
    if(a != 1 && a != 2)
    {
        error = 1;
    }
    curr_player = a;
    winstate = 4;
    b *= 2;
    while (b--)
    {
        scanf("%d", &curr_pos);
        curr_pos--;
        if (winstate != 4)
        {
            continue;
        }
        else if (curr_pos < 0 || curr_pos > 8)
        {
            error = 1;
            b++;
        }
        else if (game.board[curr_pos] != 0)
        {
            error = 1;
            b++;
        }
        else
        {
            game.board[curr_pos] = curr_player;
            game.remain--;
            winstate = CheckWin(&game);
            curr_player = 2 - curr_player + 1;
        }
    }
    if (error)
    {
        printf("Error\n");
    }
    else
    {
        printf("OK\n");
    }

    // print board situation
    for (int i = 0; i < 9; i++)
    {
        printf("%d ", game.board[i]);
        if (i % 3 == 2)
        {
            printf("\n");
        }
    }

    // print win state
    printf("%d\n", winstate);
    if (winstate == 4)
    {
        printf("%d\n", SuggPos(&game));
    }

    return 0;

}
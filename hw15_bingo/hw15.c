#include <stdio.h>
#include <stdlib.h>

typedef struct bingo
{
    int *boardA;
    int *boardB;
    int N;
    int N2;
}Bingo;

int checkLine(int x, int y, int dx, int dy, int *board, int N)
{
    for (int i = 0; i < N; i++)
    {
        int idx = y * N + x;
        if (board[idx] >= 0)
        {
            return 0; //didn't connect
        }
        x += dx;
        y += dy;
    }
    return 1;//connected
}

int checkBoard(int *board, int N)
{
    for (int i = 0; i < N; i++)
    {
        if (checkLine(0, i, 1, 0, board, N)) //horizontal
        {
            return 1;
        }
        if (checkLine(i, 0, 0, 1, board, N)) //vertical
        {
            return 1;
        }
    }
    if (checkLine(0, 0, 1, 1, board, N)) //upper left to lower right
    {
        return 1;
    }
    return checkLine(N - 1, 0, -1, 1, board, N); //upper right to lower left
}

//0:A win, 1:B win, 2:tie, 3:no loss no win
int checkWin(Bingo *bingo)
{
    int winA, winB;
    winA = checkBoard(bingo->boardA, bingo->N);
    winB = checkBoard(bingo->boardB, bingo->N);
    if (winA && !winB)
    {
        return 0;
    }
    if (!winA && winB)
    {
        return 1;
    }
    if (winA && winB)
    {
        return 2;
    }
    return 3;
}

void mark(Bingo *bingo, int num)
{
    for (int i = 0; i < bingo->N2; i++)
    {
        if (bingo->boardA[i] == num)
        {
            bingo->boardA[i] = -1;
        }
        if (bingo->boardB[i] == num)
        {
            bingo->boardB[i] = -1;
        }
        
    }
    
}

int main()
{
    Bingo bingo;
    int M, i, cur_num, status, finished;
    const char *result[3] = {"A Win", "B Win", "Tie"};

    //input
    scanf("%d %d", &bingo.N, &M); //board = N * N, M = choosed num
    bingo.N2 = bingo.N * bingo.N;
    bingo.boardA = malloc(sizeof(int) * bingo.N2);
    bingo.boardB = malloc(sizeof(int) * bingo.N2);
    for (i = 0; i < bingo.N2; i++)
    {
        scanf("%d", &bingo.boardA[i]);
    }
    for (i = 0; i < bingo.N2; i++)
    {
        scanf("%d", &bingo.boardB[i]);
    }
    
    finished = 0; //keep going
    
    for (i = 0; i < M; i++)
    {
        scanf("%d", &cur_num);
        if(finished) //need to complete the input
        {
            continue;
        }
        mark(&bingo, cur_num);

        status = checkWin(&bingo); //win and loss status

        if (status < 3) // 0:A win, 1:B win, 2:Tie 
        {
            printf("%s", result[status]);
            finished = 1;
        }
        
    }
    if (!finished) // no win no loss
    {
        printf("Tie");
    }
    
    free(bingo.boardA);
    free(bingo.boardB);

    return 0;
}
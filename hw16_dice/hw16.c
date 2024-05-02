#include <stdio.h>

void modify_dice(int dice_[][6], int modify_num, int modify_[][2]);
int modify_mode(int modify_[][2], int round, int dice_num);

void roll_forward_1(int dice_[][6], int dice_num);
void roll_right_2(int dice_[][6], int dice_num);

void print_dice(int dice_[][6]);

int main()
{
    //initialize
    int modify_num_A, modify_num_B;
    int modify_A[10][2], modify_B[10][2];
    int dice_A[2][6] = {{3, 1, 4, 6, 2, 5}, {3, 1, 4, 6, 2, 5}}, dice_B[2][6] = {{3, 1, 4, 6, 2, 5}, {3, 1, 4, 6, 2, 5}};
    int points[2] = {0};

    //input A
    scanf("%d", &modify_num_A);

    for (int i = 0; i < modify_num_A; i++)
    {
        scanf("%d %d", &modify_A[i][0], &modify_A[i][1]);
    }

    //modified A
    modify_dice(dice_A, modify_num_A, modify_A);

    //input B
    scanf("%d", &modify_num_B);

    for (int i = 0; i < modify_num_B; i++)
    {
        scanf("%d %d", &modify_B[i][0], &modify_B[i][1]);
    }
    
    //modified B
    modify_dice(dice_B, modify_num_B, modify_B);

    //output
    print_dice(dice_A);
    print_dice(dice_B);

    //compute score
    if (dice_A[0][1] == dice_A[1][1])
    {
        points[0] = 0;
    }
    else
    {
        points[0] = dice_A[0][1] + dice_A[1][1];
    }

    if (dice_B[0][1] == dice_B[1][1])
    {
        points[1] = 0;
    }
    else
    {
        points[1] = dice_B[0][1] + dice_B[1][1];
    }


    //compare
    if (points[0] > points[1])
    {
        printf("A win");
    }
    else if (points[0] < points[1])
    {
        printf("B win");
    }
    else
    {
        printf("Tie");
    }
    
    return 0;

}

void modify_dice(int dice_[][6], int modify_num, int modify_[][2])
{
    int dice_num;
    int mode;
    
    for (int i = 0; i < modify_num; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            dice_num = j;
            mode = modify_mode(modify_, i, j);

            if (mode == 1)
            {
                roll_forward_1(dice_, dice_num);
            }
            else if (mode == 2)
            {
                roll_right_2(dice_, dice_num);
            }

        }
        
    }
    
}

int modify_mode(int modify_[][2], int round, int dice_num)
{
    if (modify_[round][dice_num] == 1)
    {
        return 1;
    }
    else if (modify_[round][dice_num] == 2)
    {
        return 2;
    }
    else
    {
        return 0;
    }
    
}

void roll_forward_1(int dice_[][6], int dice_num)
{
    int temp = dice_[dice_num][0];

    for (int i = 0; i < 3; i++)
    {
        dice_[dice_num][i] = dice_[dice_num][i + 1];
    }
    
    dice_[dice_num][3] = temp;
}

void roll_right_2(int dice_[][6], int dice_num)
{
    int temp = dice_[dice_num][1];
    dice_[dice_num][1] = dice_[dice_num][5];
    dice_[dice_num][5] = dice_[dice_num][3];
    dice_[dice_num][3] = dice_[dice_num][4];
    dice_[dice_num][4] = temp;

}

void print_dice(int dice_[][6])
{
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            printf("%d ", dice_[i][j]);
        }
        printf("\n");
    }
    
}
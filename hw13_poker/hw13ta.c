#include <stdio.h>
#include <stdbool.h>

int card_type(int arr[]); // 找出該組牌的最大牌型

int main()
{
    char Face[] = {'2','3','4','5','6','7','8','9',' ','J','Q','K','A'}; // 把10略過可以讓陣列保持一維，另外作判斷看數字是否為10
    char Suit[] = {'C','D','H','S'};
    char win_player;
    char set[20][5]; // 以字串方式儲存牌組
    int round;
    int set_int[20] = {0}; // 把牌組存成整數
    int set_int_4[4][5]; // 第一組牌, 第二組牌, 第三組牌, 第四組牌
    bool is_Error; // 輸入是否錯誤
    bool is_Duplicate; // 輸入是否重複發牌
    bool is_Suit; // 是否存在撲克花色
    bool is_Face; // 是否存在撲克點數

    scanf("%d",&round);

    while (round > 0)
    {
        is_Error = false;
        is_Duplicate = false;
        // 將使用者輸入的牌面分別存進字元陣列 set[i], ..., set[i+4] ，共 4 組牌 20 張
        for(int i = 0; i < 20; i += 5)
        {
            scanf("%s %s %s %s %s",set[i],set[i+1],set[i+2],set[i+3],set[i+4]);
        }

                    
        // 把牌組轉換成對應數字 Face * 10 + Suit 
        for(int i = 0; i < 20; i++)
        {
            is_Face = false;
            is_Suit = false;
            for(int j = 0; j < 13; j++ ) // 迴圈判斷當前字串的第1個字元是否等於 '2', '3','4', ... , '9', 'A', 'J', 'Q', 'K' 其中一個字元
            {
                if (set[i][0] == Face[j]) // 判斷當前字串的第1個字元是否等於字元陣列 Face 中的某個字元
                {
                    is_Face = true; // 存在點數
                    for (int k = 0; k < 4; k++) // 迴圈判斷當前牌面字串的第二個字元是否等於 'C', 'D', 'H', 'S' 其中一個字元
                    {
                        if (set[i][1] == Suit[k])
                        {
                            is_Suit = true; // 存在花色
        
                            // 利用陣列 Face 與陣列 Suit 的索引值將牌面轉為對應數字
                            set_int[i] = (j + 2) * 10 + k; // 將陣列 Face 的索引值加二進行計算，因為陣列 Face 的索引值會與其對應的點數數值相差二
                        }
        
                    }
                    if (set[i][2] != '\0') // 若當前牌面字串的第3個字元不是結束符號則判斷輸入錯誤
                    {
                        is_Error = true;
                        break;
                    }
                    if (is_Suit == false) // 若當前牌面字串中不存在花色則判斷輸入錯誤
                    {
                        is_Error = true;
                        break;
                    }
                }
                else if (set[i][0] == '1' && set[i][1] == '0') // 判斷牌面字串前兩字元是否為'10'
                {
                    for (int k = 0; k < 4; k++)
                    {
                        if (set[i][2] == Suit[k])
                        {
                            is_Suit = true; // 判斷存在花色
        
                            set_int[i] = 10 * 10 + k; // 將牌面轉換成對應數字 Face * 10 + Suit 
                        }
                    }
                }
            }

            if(is_Error == true) 
            {
                break;
            }
        
            if(set_int[i] == 0)
            {
                is_Error = true;
                break;
            }
            else
            {
                for(int j = 0; j < i; j++)
                {
                    if(set_int[i] == set_int[j])
                    {
                        is_Duplicate = true;
                        break;
                    }
                }
            }
        
            if(is_Duplicate == true)
            {
                break;
            }
        }
        if(is_Error == true)
        {
            printf("Error input\n");
            round--; // 回合數減1
            continue; // 結束本次迴圈，表示結束本局
        }

        if(is_Duplicate == true)
        {
            printf("Duplicate deal\n");
            round--; // 回合數減1
            continue; // 結束本次迴圈，表示結束本局
        }

        // 沒有錯誤或重複發牌則將四組牌轉換後的數字分別存進四個一維陣列
        for(int i = 0; i < 4; i++) // 存進第幾組牌
        {
            for(int j = i*5; j < i * 5 + 5 ; j++)
            {
                set_int_4[i][j%5] = set_int[j];
            }
        }

        // 用泡泡排序法把四個牌組由小到大排序
        int temp;
        for(int x = 0; x < 5; x++)
        {
            for (int i = 0; i < 4; i++)   //循環N-1次
            {      
                for (int j = 0; j < 4 - i; j++) //每次循環要比較的次數
                { 
                    if (set_int_4[x][j] > set_int_4[x][j + 1])       //比大小後交換
                    {
                        temp = set_int_4[x][j];
                        set_int_4[x][j] = set_int_4[x][j + 1];
                        set_int_4[x][j + 1] = temp;
                    }
                }
            }
        }

        // 把set_int_4丟到card_type，取得各自的最大牌型編號
        int max_type = 0;
        int max_player = 0;
        int type = 0;
        for(int i = 0; i < 4;i++)
        {

            type = card_type(set_int_4[i]);

            // 比較哪個牌型較大，輸出最大牌型編號
            if(type > max_type)
            {
                max_type = type;
                max_player = i;
            }
        }

        win_player = 'A' + max_player;
        printf("%c\n",win_player);

        round--;
    } //while迴圈
  
  return 0;
}

int card_type(int arr[])
{
    int set[5]; // 儲存傳入的陣列
    bool is_type[9] = {false}; // 牌組是否形成牌型
    int same_num[4] = {0}; // 從index後面算有幾張是相同的數字
    
    is_type[0] = true; // 無牌型為散牌
    
    for(int i = 0; i < 5; i++)
    {
        set[i] = arr[i];
    }
    // 判斷是否為 順子(4)
    for(int i = 0; i < 4; i++)
    {
        if(set[i] / 10 + 1 != set[i+1] / 10 && set[i] / 10 + 9 != set[i+1] / 10)
        {
            is_type[4] = false;
            break;
        }
        is_type[4] = true;
    }
    // 判斷是否為 同花(5)
    for(int i = 0; i < 4; i++)
    {           
        int r1 = set[i] % 10;
        int r2 = set[i+1] % 10;
        if( r1 != r2)
        {
            is_type[5] = false;
            break;
        }
        is_type[5] = true;
    }
    // 判斷是否為 同花順(8) = 同花(5) + 順子(4)
    if(is_type[4] == true && is_type[5] == true)
    {
        return 8 * 1000;
    }
    // 計算牌組中有多少張點數一樣的牌, 例如: 2D 2H 5C 5H 8D, same_num[] = {1,0,1,0}
    for(int i = 0; i < 4; i++)
    {
        for(int j = i + 1; j <= 4; j++)
        {
            if(set[i] / 10 == set[j] / 10)
            {
                same_num[i]++;
            }
        }
        i += same_num[i];
    }

    // 根據same_num可以判斷是否為四條(7)、三條(3)、兩對(2)、一對(1)
    int pair = 0; // Pair的數量

    for (int i = 0; i < 4; i++)
    {
        if(same_num[i] > 0)
        {
            pair++;
            if(same_num[i] == 3) //與其他 3 張牌重複，確定是四條(8)，回傳牌組編號
            {
                return 7 * 1000;
            }
            else if(same_num[i] == 2) //判斷是否為三條(4)
            {
                is_type[3] = true;
            }
            else if(same_num[i] == 1) //判斷是否為一對(2)
            {
                is_type[1] = true;
            }
        }
    }

    // 判斷是否為兩對(2)
    if(pair == 2)
    {
        is_type[2] = true;
    }

    // 判斷是否為 葫蘆(6) = 三條(3) + 一對(1)
    if(is_type[3] == true && is_type[1] == true)
    {
        return 6 * 1000;
    }
    // 若是牌型 6、7、8 前面已return，且要輸出最大牌型，所以從牌型5開始由大到小檢查是否符合
    for(int i = 5; i >= 0; i--)
    {
        if(is_type[i] == true)
        {
            return i * 1000;
        }
    }
}
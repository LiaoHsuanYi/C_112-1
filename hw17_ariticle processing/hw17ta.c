#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void count_freq(int A_len, char A_str[], int *word_num,char words[][15], int freq[]); // 計算單字頻率
void find_max_position(int word_num,int freq[],int *max_p, char words[][15]); // 找出頻率最高的單字位置  
void delete_word(int A_len, int P_len, char A_str[], char P_str[], char A_substr[]); // 刪除單字

int main()
{
    char A_str[150] = {'\0'};
    char A_substr[10] = {'\0'}; // 記錄 A_str 的子字串
    char P_str[10] = {'\0'};
    char Q_str[10] = {'\0'};
    int n, c;

    int p = 0; // 當 A_str 的index
    int A_len, P_len, Q_len; // 字串長度
    int max_p = 0;  // 出現頻率最高的單字index
    int word_num = 0;   // 計算words陣列裡已存的單字數量
    char words[30][15] = {'\0'}; // 出現過的單字 (30個1x15的一維陣列組成的二維陣列，設單字不超過 14 個英文字)
    char low_feq_words[30][15] = {'\0'}; // 出現頻率小於 N 的單字 (30個1x15的一維陣列組成的二維陣列，設單字不超過 14 個英文字)
    int freq[30] = {0}; // 單字出現頻率

    scanf("%[^\n]", A_str); // 直到讀到換行鍵才會結束讀取，將讀到的字串存入 A_str
    A_len = strlen(A_str);

    scanf("%s", P_str);
    P_len = strlen(P_str);
    scanf("%s", Q_str);
    Q_len = strlen(Q_str);
    scanf("%d", &n);
    scanf("%d", &c);

    	
    if(c == 1 || c == 2) // C=1, 將文句 A 中 P 字串以 Q 字串取代。 // C=2, 在文句 A 中 P 字串前插入 Q 字串。
    {
        while ( p < A_len) // 重複確認直到文句 A 結束
        {
            if(A_str[p] == P_str[0]) // 判斷當前字元是否與 P 字串的第 1 個字元相同
            {
                // 判斷 是否當字元是其他單字的一部分 或是 是否單字的長度不一致 (任一條件達成則非相同詞)
                // 判斷 是否索引值不在句首跟前一格非空格 或是 是否加了 P 字串長度的索引值後一格非空格跟不在句尾
                if((p != 0 && A_str[p-1] != ' ' )|| (A_str[p + P_len] != ' ' && A_str[p + P_len] != '\0'))
                {
                    p++; // 若不可能自成單字則令索引值 p 加 1
                    continue; // 結束本次迴圈
                }
    
                // 將同樣長度的字串存進字串 A_substr (還不確定單字是否一致)
                for (int i = 0; i < P_len; i++)
                {
                    A_substr[i] = A_str[p+i];
                }
    
                // 用 strcmp 確認字串 A_substr 與 P 字串是否一致
                if(strcmp(A_substr, P_str) == 0) // 返回值等於 0，則表示 str1 等於 str2。
                {
                    // 將文句 A 從尾開始往後移動 Q 字串長度，索引值 i 是 A_len + Q_len，現在字串索引值是 0 ~ ( A_len + Q_len )
                    for (int i = A_len + Q_len; i > p; i--) // 在 A_str 中，若找到 P 字串，在 A_str 中，把 P 字串(包含 P )以後的值都往後移動 Q_len + 1 個位置
                    {
                        A_str[i] = A_str[i - Q_len -1];
                    }
                    for (int i = 0; i < Q_len; i++) // 將 Q 字串存進原本跟 P 字串一致的詞的位置
                    {
                        A_str[p] = Q_str[i];
                        p++;
                    }
                    A_len += Q_len + 1; // 加 Q 字串長度再加 1 個空格長度
                    p += Q_len; // 加 Q 字串長度防止重複計算
                }
            }
            p++; // 比對下一個字元
        }
        if(c == 1) // 加完 Q 字串後, 如果是 C=1 要將 P 字串刪除, 達成 P 字串以 Q 字串取代
        {
            delete_word(A_len, P_len, A_str, P_str, A_substr);
        }
        printf("%s",A_str);
    }

    else if(c == 3) // C=3, 將文句 A 中 P 字串刪除。
    {
        delete_word(A_len, P_len, A_str, P_str, A_substr); // 用函式 delete_word 刪除單字
        printf("%s",A_str);
    }

    else if(c == 4) // C=4, 統計文句 A 中英文字出現頻率前 2 高
    {
        count_freq(A_len, A_str, &word_num, words, freq); // 用函式 count_freq 計算單字出現次數，需使用 & 運算子傳址才能更動主函式變數

        find_max_position(word_num, freq, &max_p, words); // 用函式 find_max_position 找出出現次數最高的單字位置  

        freq[max_p] = 0; // 將最高的出現次數清除為零, 準備統計出現次數第二高的單字
        printf("\n");

        find_max_position(word_num, freq, &max_p , words); // 用函式 find_max_position 找出出現次數最高的單字位置 (實際為全部單字中次高)
    }

    else if(c == 5) // C=5,將文句中,出現頻率小於 N 的英文字刪除。
    {
        count_freq(A_len, A_str, &word_num, words, freq); // 用函式 count_freq 計算單字出現次數
        
        int count = 0; // 計算有幾個出現次數低於 N 的單字
        for (int i = 0; i < word_num; i++) // 將出現次數低於 N 的單字存在 low_feq_words
        {
            if(freq[i] < n) // 判斷第 i 種單字的出現次數是否小於 n
            {
                for(int j = 0; j < 15; j++) // 重複存字元直到當前單字陣列結束
                {
                    low_feq_words[count][j] = words[i][j];
                }
                count++;
            }
        }
 
        for (int i = 0; i < count; i++) // 刪除出現次數低於 N 的單字
        {
            A_len = strlen(A_str);
            P_len = strlen(low_feq_words[i]);
 
            delete_word(A_len, P_len, A_str, low_feq_words[i], A_substr); // 用函式 delete_word 刪除單字
            
            for(int j = 0; j < 10; j++) // 刪除完當前單字初始化 A_substr
            {
                A_substr[j] = '\0';
            }
        }
        printf("%s",A_str);
    }
    return 0;
}

void delete_word(int A_len, int P_len, char A_str[], char P_str[], char A_substr[])
{
    int p = 0 ; // 當 A_str 的index
    
    while ( p < A_len)
    {
        if(A_str[p] == P_str[0]) // 判斷當前字元是否與 P 字串的第 1 個字元相同
        {
            if((p != 0 && A_str[p-1] != ' ' )|| (A_str[p + P_len] != ' ' && A_str[p + P_len] != '\0'))
            {
                p++;
                continue;
            }
            for (int i = 0; i < P_len; i++) // 將同樣長度的字串存進字串 A_substr
            {
                A_substr[i] = A_str[p+i];
            }
            if(strcmp(A_substr, P_str) == 0) // 返回值等於 0，則表示 str1 等於 str2。
            {
                if(A_len - P_len == p)
                {
                    A_str[p-1] = '\0'; // 若剛好要刪除最後一個詞, 直接將前一格空白設為結束符號即可
                }
                else
                {
                    for (int i = p; i < A_len - P_len; i++)
                    {
                        if(A_str[i + P_len] == '\0')
                        {
                            A_str[i-1] = '\0';
                            break;
                        }
                        else
                        {
                            A_str[i] = A_str[i + P_len + 1];
                        }
                    }
                    A_len -= P_len; // 減掉刪除掉的單字的長度
                }
            }
        }
        p++; // 比對下一個字元
    }
}

void find_max_position(int word_num, int freq[], int *max_p, char words[][15]) // 找出單字出現次數最高的單字位置
{
    for (int i = 0; i < word_num; i++) // 當 i 小於單字總數迴圈持續執行，每執行一次 i 加 1
    {
        if(freq[i] > freq[*max_p]) // 判斷當前單字出現次數是否大於目前最高單字出現次數
        {
            *max_p = i; // 將當前單字索引值存為目前出現次數最高的單字索引值
        }
    }
    printf("%s:%d",words[*max_p] ,freq[*max_p]);
}

	
void count_freq(int A_len, char A_str[], int *word_num, char words[][15], int freq[]) // 分別存放出現過的單字, 計算單字出現頻率
{
    int p = 0;
    int p_copy; // 記錄 p
    bool same = 0;// 當下的單字是否與 words 陣列裡有一樣的
 
    while ( p < A_len)
    {
        same = 0;
        p_copy = p; // 存放 p 當前位置
        if(A_str[p] != ' ') // 判斷 p 位置的字元是否不為空白
        {
            for (int i = 0; i < *word_num; i++) // 跟 words 陣列已存單字比對是否為相同詞
            {
                for (int j = 0; j < 15; j++)
                {
                     // 若 p 位置為空白或結束符號且 words 陣列為結束符號則判斷為相同單字並跳出迴圈
                    if((A_str[p] == ' ' || A_str[p] == '\0') && words[i][j] =='\0')
                    {
                        same = 1;
                        break;
                    }
                    if(A_str[p] == words[i][j]) // 若當下字元與 words 陣列當下單字對應的字元一樣
                    {
                        same = 1; // 先設定布林值 same 為 1 (true)
                        p++; // 再繼續檢查下一個字元
                    }
                    else // 有字元不相同則判斷單字不相同並跳出迴圈
                    {
                        same = 0;
                        break;
                    }
                }
 
                if(same == 1) // 與 words 陣列內已存字詞相同時
                {
                    freq[i]++; // 當前單字出現次數加 1
                    break; // 已經確定為相同單字, 跳出迴圈
                }
 
                p = p_copy; // 設定 p 回到原本的位置, 再比較是否與下一個 words 陣列內的已存單字為相同單字
            }
            if(same == 0) // 表示 此單字為新單字(尚未出現過)，則要加入 words 陣列中
            {
                for (int j = 0; j < 15; j++)
                {
                    if(A_str[p] == ' ' || A_str[p] == '\0') // 若新單字已結束
                    {
                        words[*word_num][j] = '\0';
                        break;
                    }
                    words[*word_num][j] = A_str[p]; // 將文句 A 中的當前字元 p 加進當前 words 陣列的最後一個一維陣列
                    p++; // 準備存進下一個字元
                }
                freq[*word_num]++; // 當前單字出現次數加 1 (預設為 0 )
                *word_num += 1 ; // 總單字數量加 1
            }
        }
        p++; // 比對下一個字元
    }
}
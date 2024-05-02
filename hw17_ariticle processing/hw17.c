#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void count_freq(int A_len, char A_str[], int *word_num, char words[][15], int freq[]); //count words frequent
void find_max_position(int word_num, int freq[], int *max_p, char words[][15]); //find the highest frequent words position
void delete_word(int A_len, int P_len, char A_str[], char P_str[], char A_substr[]); //delete words

int main()
{
    char A_str[150] = {'\0'};
    char A_substr[10] = {'\0'}; 
    char P_str[10] = {'\0'};
    char Q_str[10] = {'\0'};
    int n, c;

    int p = 0; // A_str's index
    int A_len, P_len, Q_len; //string's length
    int max_p = 0; // the highest frequency word
    int word_num = 0;
    char words[30][15] = {'\0'};
    char low_feq_words[30][15] = {'\0'};
    int freq[30] = {0};

    //input
    scanf("%[^\n]", A_str);
    A_len = strlen(A_str);

    scanf("%s", P_str);
    P_len = strlen(P_str);
    scanf("%s", Q_str);
    Q_len = strlen(Q_str);
    scanf("%d", &n);
    scanf("%d", &c);

    if (c == 1 || c == 2) //c = 1 : replace, c = 2 : insert
    {
        while (p < A_len) //loop check
        {
            if (A_str[p] == P_str[0])
            {
                //isn't a word
                if ((p != 0 && A_str[p-1] != ' ') || (A_str[p + P_len] != ' ' && A_str[p + P_len] != '\0'))
                {
                    p++;
                    continue;
                }
                
                for (int i = 0; i < P_len; i++)
                {
                    A_substr[i] = A_str[p + i];
                }

                if (strcmp(A_substr, P_str) == 0) //string compare
                {
                    for (int i = A_len + Q_len; i > p; i--)
                    {
                        A_str[i] = A_str[i - Q_len - 1];
                    }
                    for (int i = 0; i < Q_len; i++)
                    {
                        A_str[p] = Q_str[i];
                        p++;
                    }
                    A_len += Q_len + 1; // +1 space
                    p += Q_len; //prevent repeated calculation
                    
                }
            }
            p++; // compare next char
        }
        if (c == 1)
        {
            delete_word(A_len, P_len, A_str, P_str, A_substr);
        }
        printf("%s", A_str);
    }
    else if (c == 3) // delete
    {
        delete_word(A_len, P_len, A_str, P_str, A_substr);
        printf("%s", A_str);
    }
    else if (c == 4) // find top 2 highest frequency words
    {
        count_freq(A_len, A_str, &word_num, words, freq);
        find_max_position(word_num, freq, &max_p, words);

        freq[max_p] = 0;
        printf("\n");

        find_max_position(word_num, freq, &max_p, words);
    }
    else if (c == 5) // delete the words appear frquency that it < N
    {
        count_freq(A_len, A_str, &word_num, words, freq);

        int count = 0; // compute unqualified words  quantity
        for (int i = 0; i < word_num; i++)
        {
            if(freq[i] < n) // repeat to save the char to string
            {
                for (int j = 0; j < 15; j++)
                {
                    low_feq_words[count][j] = words[i][j];
                }
                count++;
            }
        }
        for (int i = 0; i < count; i++) //delete
        {
            A_len = strlen(A_str);
            P_len = strlen(low_feq_words[i]);

            delete_word(A_len, P_len, A_str, low_feq_words[i], A_substr);

            for (int j = 0; j < 10; j++) // initialize A_substr
            {
                A_substr[j] = '\0';
            }
            
        }
        printf("%s", A_str);
    }
    
    return 0;

}

void delete_word(int A_len, int P_len, char A_str[], char P_str[], char A_substr[])
{
    int p = 0; // A_str's index
    while (p < A_len)
    {
        if (A_str[p] == P_str[0]) // whether it the same
        {
            if ((p != 0 && A_str[p-1] != ' ') || (A_str[p + P_len] != ' ' && A_str[p + P_len] != '\0'))
            {
                p++;
                continue;
            }
            for (int i = 0; i < P_len; i++) // save to A_substr
            {
                A_substr[i] = A_str[p + i];
            }
            if (strcmp(A_substr, P_str) == 0)
            {
                if (A_len - P_len == p)
                {
                    A_str[p - 1] = '\0';
                }
                else
                {
                    for (int i = p; i < A_len - P_len; i++)
                    {
                        if (A_str[i + P_len] == '\0')
                        {
                            A_str[i - 1] = '\0';
                            break;
                        }
                        else
                        {
                            A_str[i] = A_str[i + P_len + 1];
                        }
                    }
                    A_len -= P_len;
                }
            }
            
        }
        p++;// compare next char
    }
    
}

void find_max_position(int word_num, int freq[], int *max_p, char words[][15])
{
    for (int i = 0; i < word_num; i++)
    {
        if (freq[i] > freq[*max_p])
        {
            *max_p = i;
        }   
    }
    printf("%s:%d", words[*max_p], freq[*max_p]);
}

void count_freq(int A_len, char A_str[], int *word_num, char words[][15], int freq[])
{
    int p = 0;
    int p_copy;//record p
    bool same = 0; //Are the words same
    
    while (p < A_len)
    {
        same = 0;
        p_copy = p;
        if (A_str[p] != ' ')
        {
            for (int i = 0; i < *word_num; i++)
            {
                for (int j = 0; j < 15; j++)
                {
                    if ((A_str[p] == ' ' || A_str[p] == '\0') && words[i][j] == '\0')
                    {
                        same = 1;
                        break;
                    }
                    if (A_str[p] == words[i][j])
                    {
                        same = 1;
                        p++;
                    }
                    else //isn't the same, break
                    {
                        same = 0;
                        break;
                    }
                    
                }
                if (same == 1)
                {
                    freq[i]++; //frequency +1
                    break;
                }
                p = p_copy;
            }
            if (same == 0) // add to words array
            {
                for (int j = 0; j < 15; j++)
                {
                    if (A_str[p] == ' ' || A_str[p] == '\0')
                    {
                        words[*word_num][j] = '\0';
                        break;
                    }
                    words[*word_num][j] = A_str[p];
                    p++;
                }
                freq[*word_num]++;
                *word_num += 1; // total words +1
            }
            
        }
        p++;
    }
    
}
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int main()
{
    //   106  /   3  =  35 + 1
    //   106  / (-3) = -35 + 1 
    // (-106) /   3  = -36 + 2
    // (-106) / (-3) =  36 + 2
    char Dividend[40], Divisor[40],Divisor_copy[40],Quotient[40]; // 被除數(餘數), 除數, 除數副本, 商數
    int a = 0, k = 0, a_k, a_k_copy; // 被除數的個位數index, 除數的個位數index, 被除數與除數相差值(a-k), 被除數與除數相差值副本
    int  index = 0, count = 0; // 被除數與除數相減的index, 計算共減了幾次
    int mode = 0; // 0 表示相除為10的倍數, 1 表示可繼續作除法, 2 表示無法繼續作除法
    bool start = false; // 商數前面的0不顯示,直到遇到非0數字開始輸出
    bool signed_1 = false, signed_2 = false, signed_Q = false; // false 表示正數, true 表示負數
    bool is_zero = true; // true 表示餘數為0

    scanf("%s", Dividend);
    scanf("%s", Divisor);

    // 找出被除數和除數個位數的index
    a = strlen(Dividend) - 1;
    k = strlen(Divisor) - 1;

    // 如果被除數或除數為負數，則記錄其為負數，只取數字(i.e. index都往前一格)，ex: -125 儲存成 125(變成 正數除以正數)
 
    if(Dividend[0] == '-')
    {
        signed_1 = true;
    
        for(int i = 0; i < a; i++)
        {
            Dividend[i] = Dividend[i+1];
        }
        Dividend[a] = '\0';
        a--;
    }
    
    if(Divisor[0] == '-')
    {
        signed_2 = true;
    
        for(int i = 0; i < k; i++)
        {
            Divisor[i] = Divisor[i+1];
        }
        Divisor[k] = '\0';
        k--;
    }
    
    // 負數除以正數 或是 正數除以負數，商為負數
    if((signed_1 == true && signed_2 == false)||(signed_1 == false && signed_2 == true))
        signed_Q = true;

    a_k = a - k; // 被除數和除數相差的位數
    a_k_copy = a_k;

    // copy除數
    for(int i = a; i >= a-k ; i--)
    {
        Divisor_copy[i] = Divisor[i-(a-k)];
    }
    for(int i = a-k-1; i >= 0 ; i--)
    {
        Divisor_copy[i] = '0';
    }

    // 除數放大10的(a-k)次方倍，這樣程式執行時間能大幅減少 (長除法補零)
    // 除法過程中被除數和除數不斷相減，而一次減十倍比減十次快很多，以此類推
    for(int i = k+1; i <= a; i++)
    {
        Divisor[i] = '0';
    }
    // 開始進行相減
    while (1)
    {
        // 判斷被除數與除數間的大小，若每一位都一樣 mode 會保持零
        for(int i = 0; i <= a; i++)
        {
            if(Dividend[i] > Divisor[i])
            {
                mode = 1; 
                break;
            }
            else if (Dividend[i] < Divisor[i])
            {
                mode = 2;
                break;
            }
            else{}
        }
        if(mode == 0) // 表示 被除數 = 除數 * 10的(a_k)次方
        {
            count++; // 初始值 0，加一後變為 1
            for(int i = 0; i < a_k;i++)
            {
                count = count * 10;
            }

            if(signed_Q == true)
                printf("-");
            printf("%d",count);

            printf("\n0");

            return 0;
        }
        	
        else if(mode == 1) // 被除數 > 除數
        {
            index = a; // 從個位數開始做減法
            while (1)
            {
                if(Dividend[index] >= Divisor[index]) // 被除數當下的位大於除數的位，則直接相減
                {
                    Dividend[index] = Dividend[index] - Divisor[index] +'0';
                }
                else // 不夠減，向前借位
                {
                    int borrow = index-1;
                    while(1)
                    {
                        if(Dividend[borrow] > 0)
                        {
                            Dividend[borrow] = Dividend[borrow] - 1 ; // 前一位減一
                            for(int i = borrow + 1; i < index; i++) // 借的不是前一位時，補上 '9' 直到前一位為止
                            {
                                Dividend[i] = '9';
                            }
                            Dividend[index] = 10 +'0' - Divisor[index] + Dividend[index]; // '10' 減除數當下數字後加上被除數當下數字
                            break;
                        }
                        else
                            borrow--; // 不夠借則再往前借
                    }
                }
                index--; // 往前一位繼續相減
        
                if(index < 0)
                    break;
            }
            count++; // 被除數每減完一次除數，則 count = count + 1
        } 
         else // 被除數 < 除數
        {
            // 判斷除數是否已變回原先的除數，若成立，表示已經無法再做減法，結束除法;若不成立，則除數 / 10後，繼續做減法
            if(strncmp(Divisor_copy, Divisor, a+1) == 0) // 因為 Divisor 已經放大10的(a-k)次方倍，所以需要比到第 a+1 個元素才可以確定是否一致
            {
                Quotient[a_k] = count + '0'; // 將 count 的值加上字元 '0' 存進存放商數的字元陣列 Quotient
                break; // 已經無法再做減法，結束除法
            }
            else
            {
                for(int i = a; i > 0; i--) // 除數 / 10
                {
                    Divisor[i] = Divisor[i-1]; // 將陣列數字往右移一位
                }
                Divisor[0] = '0'; // 將第一位歸零
                Quotient[a_k] = count + '0'; // 將 count 作為字元存進存放商數的陣列 Quotient
                count = 0; // 將 count 歸零
                a_k--; // 被除數和除數相差的位數減 1
            }
        }
    }
    // 若被除數為負數，且餘數不等於0，則 |商| + 1，且餘數 = |除數| - 餘數
    if((signed_1 == true && signed_2 == true) || (signed_1 == true && signed_2 == false))
    {   
        for(int i = 0; i <= a; i++) // 檢查餘數 (除完的被除數 Dividend) 是否在長度內皆為 '0' 
        {
            if(Dividend[i] != '0' )
            {
                is_zero = false;
                break;
            }
        }
        if(is_zero == false) // 餘數不等於0
        {
            Quotient[0] += 1; // 被除數為負數所以 |商| + 1 ，例：-10/3 = -4 ... 2 
    
            index = a;
            while (1)
            {
                if(Divisor[index] >= Dividend[index]) // 若除數當下的數字大於等於餘數當下的數字，餘數 = |除數| - 餘數
                {
                    Dividend[index] = Divisor[index] - Dividend[index] +'0';
                }
                else // 若除數當下的數字小於餘數當下的數字，借前一位達成 餘數 = |除數| - 餘數
                {
                    int borrow = index-1;
                    while(1)
                    {
                        if(Divisor[borrow] > 0) // 當前一位大於零時，借一當十；否則繼續往前借
                        {
                            Divisor[borrow] = Divisor[borrow] - 1 ;
                            for(int i = borrow + 1; i < index; i++) // 如果是向前一位以前的位數借一當十會進入此迴圈
                            {
                                Divisor[i] = '9';
                            }
                            Dividend[index] = 10 +'0' - Dividend[index] + Divisor[index]; // '10' 減除數當下數字後加上被除數當下數字
                            break;
                            }
                        else
                            borrow--; // 往前找大於零的位數
                    }
                }
                index--; // 持續往前相減
    
                if(index < 0) // 索引值小於零不屬於陣列範圍，表示減法結束，離開迴圈
                    break;
            }
        }
    }
    // 輸出商數
    if(signed_Q == true) // 商為負數加負號
        printf("-");
 
    for(int i = a_k_copy; i >= 0; i--) // 找到商的非零位置後輸出
    {
        if(Quotient[i] != '0' )
            start = true;
 
        if(start == true)
            printf("%c",Quotient[i]);
    }
    printf("\n");
 
    start = false;
 
    // 輸出餘數
    for(int i = 0; i <= a; i++) // 找到餘數的非零位置後輸出
    {
        if(Dividend[i] != '0' )
            start = true;
 
        if(start == true)
            printf("%c",Dividend[i]);
    }
 
    // 餘數為0時，輸出0
    if(start == false)
        printf("0");
 
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node_s {
    int coef;
    int exp;
    struct node_s * next;
} node_t; 

typedef node_t * nodep_t; // 此行重新命名node_t*，之後nodep_t 都代表node_t*

typedef struct pol_s {
    nodep_t root;
} pol_t; // pol_t 是指Linked list的第一個node。

void add(pol_t* X, pol_t* Y, pol_t* Z); //兩個多項式 X, Y 相加,Z 是結果
void sub(pol_t* X, pol_t* Y, pol_t* Z); //兩個多項式 X, Y 相減,Z 是結果
void mul(pol_t* X, pol_t* Y, pol_t* Z); //兩個多項式 X, Y 相減,Z 是結果

nodep_t createList(int); // 串列建立函數
void printList(nodep_t);  // 串列列印函數

int main()
{
    int x_node_num, y_node_num;
    nodep_t x_first, y_first, z_first, new_node; // 4個指標，分別指向第一、第二個多項式，結果多項式，以及新的節點
    pol_t *x, *y ,*z;
    x = (pol_t *) malloc(sizeof(pol_t));
    y = (pol_t *) malloc(sizeof(pol_t));
    z = (pol_t *) malloc(sizeof(pol_t));
     scanf("%d",&x_node_num);
    x_first = createList(x_node_num);
    x->root = x_first;

    scanf("%d",&y_node_num);
    y_first = createList(y_node_num);
    y->root = y_first;

    new_node=(nodep_t) malloc(sizeof(node_t));
    new_node->exp = 100;
    z_first = new_node;
    z->root = z_first;

    add(x, y, z);
    z_first->next = NULL;
    sub(x, y, z);
    z_first->next = NULL;
    mul(x, y, z);
    return 0;
}

// 串列建立函數
nodep_t createList(int len){
    nodep_t first, current, previous; // 3個指標，分別指向第一個節點、當前節點、前一個節點
    for(int i=0;i < len;i++){
        current=(nodep_t) malloc(sizeof(node_t)); // 建立新節點並令 current 指向新節點
        scanf("%d",&(current->coef));  // 設定節點的資料成員(係數)
        current->exp = len - 1 - i; // 設定節點的資料成員(次方)，次方 = 項數個數 - 1 - 已跑迴圈數
        if(i==0){
            first=current;  // 如果是第一個成員令指標 frist 指向目前的節點 
        }
        else{
            previous->next=current; // 令前一個節點的 next 指向目前的節點 
        }
        current->next=NULL; // 令目前節點的 next 設為 NULL
        previous=current; // 令指向前一個節點的指標指向目前節點 
    }
    return first;
}

//串列列印函數
void printList(nodep_t first){
	nodep_t node = first -> next, p = NULL; // 將node指向第一個節點(跳過z最前面的節點)，p 指向將釋放的節點
	if(node == NULL){
		printf("None\n");
	}
    else{
		while(node != NULL){
			printf("%d %d ", node->coef, node->exp); // 輸出係數和次方
			node = node->next;
		}
		printf("\n");
	}
    
    if(first -> next != NULL){
        node = first -> next;
        while(node != NULL){ // 釋放動態記憶體空間
            p = node;
            node = node->next;
            free(p);
        }
    }
} 

void sub(pol_t* X, pol_t* Y, pol_t* Z)
{
    nodep_t x_current, y_current, z_current, z_root, new_node;
    // 5個指標，分別指向 x, y, z 的當前節點， z 的第一個節點，以及新的節點

    x_current = X->root;
    y_current = Y->root;
    z_current = Z->root;
    z_root = Z->root;
    while (1)
    {
        if(x_current == NULL || y_current == NULL)
            break;
        if( x_current->exp > y_current->exp ) // 若當前多項式 x 的項次方大於多項式 y 的項次方
        {
            new_node=(nodep_t) malloc(sizeof(node_t)); // 建立新節點，存進當前多項式 x 的項
            new_node->coef = x_current->coef;
            new_node->exp = x_current->exp;
            x_current = x_current->next;
        }
        else if( x_current->exp < y_current->exp ) // 若當前多項式 x 的項次方小於多項式 y 的項次方
        {
            new_node=(nodep_t) malloc(sizeof(node_t)); // 建立新節點，存進加上負號的當前多項式 y 的項
            new_node->coef = -y_current->coef;
            new_node->exp = y_current->exp;
            y_current = y_current->next;
        }
        else // 若兩者的項次方相等
        {
            new_node=(nodep_t) malloc(sizeof(node_t)); // 建立新節點
            new_node->coef = x_current->coef - y_current->coef; // 存進當前多項式 x 的項係數減當前多項式 y 的項係數
            new_node->exp = x_current->exp; // 存進當前多項式 x 的項次方
            x_current = x_current->next;
            y_current = y_current->next;
        }
            z_current->next = new_node; // 將當前 z 的指標 next 指向新的節點
            z_current = z_current->next; // 把後一個節點設成當前節點 
            z_current->next = NULL; // 把當前節點(本輪的新節點)的指標 next 設為 NULL
    }
    printList(z_root); // 做完減法即列印多項式 z
}

void add(pol_t* X, pol_t* Y, pol_t* Z)
{
    nodep_t x_current, y_current, z_current, z_root, new_node;
    // 5個指標，分別指向 x, y, z 的當前節點， z 的第一個節點， 以及新的節點

    x_current = X->root;
    y_current = Y->root;
    z_current = Z->root;
    z_root = Z->root;
    while (1)
    {
        if(x_current == NULL || y_current == NULL)
            break;
        if( x_current->exp > y_current->exp ) // 若當前多項式 x 的項次方大於多項式 y 的項次方
        {
            new_node=(nodep_t) malloc(sizeof(node_t)); // 建立新節點，存進當前多項式 x 的項
            new_node->coef = x_current->coef;
            new_node->exp = x_current->exp;
            x_current = x_current->next;
        }
        else if( x_current->exp < y_current->exp ) // 若當前多項式 x 的項次方小於多項式 y 的項次方
        {
            new_node=(nodep_t) malloc(sizeof(node_t)); // 建立新節點，存進當前多項式 y 的項
            new_node->coef = y_current->coef;
            new_node->exp = y_current->exp;
            y_current = y_current->next;
        }
        else // 若兩者的項次方相等
        {
            new_node=(nodep_t) malloc(sizeof(node_t));
            new_node->coef = x_current->coef + y_current->coef; // 存進當前多項式 x 的項係數加當前多項式 y 的項係數
            new_node->exp = x_current->exp; // 存進當前多項式 x 的項次方
            x_current = x_current->next;
            y_current = y_current->next;
        }
        z_current->next = new_node;
        z_current = z_current->next;
        z_current->next = NULL;
    }
    printList(z_root); // 做完加法即列印多項式 z
}


void mul(pol_t* X, pol_t* Y, pol_t* Z)
{
    int product_exp; // x * y的次方項
    bool exp_exist = false; // 看 z 的 Linked list 中是否已經出現過 x * y 的次方 , false 表示未出現
    nodep_t x_current, y_current, z_current, z_root, new_node;

    x_current = X->root;
    y_current = Y->root;
    z_current = Z->root;
    z_root = Z->root;

    while (1)   // 讓 y 的每一項去 * x 每一項
    {
        exp_exist = false;
        z_current = Z->root;
 
        if(x_current == NULL) // y 的當前項已經乘上 x 的每一項
        {
            y_current = y_current->next; // 到 y 的下一項
            x_current = X->root; // 從頭開始乘上 x 的每一項
        }
        if(y_current == NULL) // y 的每個項已經乘上 x 的每一項
            break;
        
        product_exp = x_current->exp + y_current->exp; // 次方項相乘結果為相加
 
        while (z_current != NULL) // 判斷 z 是否為空串列
        {
            if(z_current->exp == product_exp) // 看 z 的 Linked list 中是否已經出現過 x * y 的次方
            {
                exp_exist = true;
                break;
            }
            if(z_current->next != NULL)
                z_current = z_current->next; // 檢查 z 的下一項
            else
                break;
        }
        
        if(exp_exist == false) // x * y 的次方項不在 z 中，則建立新節點
        {
            new_node=(nodep_t) malloc(sizeof(node_t)); // 建立新節點
            new_node->coef = x_current->coef * y_current->coef; // 存進係數相乘結果
            new_node->exp = product_exp; // 存進次方項相乘結果
            z_current->next = new_node;
            z_current = z_current->next;
            z_current->next = NULL;
        }
        else // x * y 的次方項在 z 中，則直接更新該系數
        {
            z_current->coef += x_current->coef * y_current->coef; // 加進係數相乘結果
        }
        x_current = x_current->next;
    }
    printList(z_root); // 做完乘法即列印多項式 z
}
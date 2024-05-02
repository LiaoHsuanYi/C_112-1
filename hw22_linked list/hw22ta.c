#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node_s{
    int data;
    struct node_s *next; // 指向下一個節點
}node_t;

node_t *createList(int); // 串列建立函數

node_t *add_Node(node_t *,int); // 1.從最後面加入資料 x 

node_t *delete_the_front(node_t *); // 2.刪除最前面節點，若 List 無節點，則不必刪除。
node_t *delete_the_back(node_t *); // 3.刪除最後面節點，若 List 已無節點，則不必刪除。
node_t *delete_x_node(node_t *, int); // 4.刪除 List 內資料為 x 的節點；若 x 不存在則不刪除任何節點。

node_t *add_y_node(node_t *, int, int); // 5.搜尋 List 內資料為 x 的節點，並在其後加入數值 y 的新節點。若 x 不在 List 中，則不必加入 y 。

node_t *Reverse(node_t *); // 6. 反轉 Linked List。
node_t *Change_position(node_t *, int, int); // 7. 交換數值為 x 和 y 節點的位置，若 x 或 y 不在 List中，則不必交換。

void printList(node_t *);  // 串列列印函數 

int main()
{
    int node_num, op_num, x, y;
    node_t *first;
    scanf("%d",&node_num); // 讓使用者輸入節點數
    first = createList(node_num); // 使用函式 createList 創建節點
    scanf("%d",&op_num); // 讓使用者輸入操作指令的數量 
    while (op_num > 0)
    {
        int op;
        scanf("%d",&op); // 讓使用者輸入操作指令
        switch (op)
        {
        case 1: // 1.從最後面加入資料 x 
            scanf("%d",&x);
            first = add_Node(first,x);
            break;
 
        case 2: // 2.刪除最前面節點，若 List 無節點，則不必刪除。
            if(first != NULL)
                first = delete_the_front(first);
            break;
 
        case 3: // 3.刪除最後面節點，若 List 已無節點，則不必刪除。
            if(first != NULL)
                first = delete_the_back(first);
            break;
        case 4: // 4.刪除 List 內資料為 x 的節點；若 x 不存在則不刪除任何節點。
            scanf("%d",&x);
            first = delete_x_node(first, x);
            break;
 
        case 5: // 5.搜尋 List 內資料為 x 的節點，並在其後加入數值 y 的新節點。若 x 不在 List 中，則不必加入 y 。
            scanf("%d %d",&x,&y);
            first = add_y_node(first, x, y);
            break;
 
        case 6: // 6. 反轉 Linked List。
            first = Reverse(first);
            break;
 
        case 7: // 7. 交換數值為 x 和 y 節點的位置，若 x 或 y 不在 List中，則不必交換
            scanf("%d %d",&x,&y);
            first = Change_position(first, x, y);//
            break;
 
        default:
            break;
        }
        op_num--;
    }
    printList(first);
    return 0;
}  

//串列建立函數 
node_t *createList(int len){
    node_t *first, *current, *previous; // 指向第一個節點、當前節點、先前節點的三個指標
    for(int i = 0; i < len; i++){
        current = (node_t *) malloc(sizeof(node_t)); // 建立新節點
        scanf("%d",&(current->data));  // 設定節點的資料成員
        if(i == 0){
            first = current;  // 如果是第一個成員把指標frist指向目前的節點 
        }
        else{
            previous->next = current; // 把前一個的next指向目前的節點 
        }
        current->next = NULL; // 把目前的節點的next指向NULL
        previous = current; // 把前一個節點設成目前的節點，最初 previous 會是 first
    }
    return first;
}

//從最後面加入資料 x 
node_t *add_Node(node_t *first,int data){
    node_t *new_node,*current;
    current = first;
    new_node = malloc(sizeof(struct node_s)); // 建立新節點

    if(first!=NULL){ // 判斷串列是否存在
        while (current->next != NULL) // 判斷目前是否為最後一個節點
        {
            current = current->next;
        }
        current -> next = new_node; // 是最後一個節點則指向新節點
    }
    else
    {
        first = new_node;
    }
    new_node->data = data;
    new_node->next = NULL;

    return first;
}

//刪除最前面節點，若 List 無節點，則不必刪除。
node_t *delete_the_front(node_t *first){
    node_t *p=NULL;
    if(first!=NULL){
        p = first;
        first = first -> next;
    }
    free(p);

    return first;
}

//刪除最後面節點，若 List 已無節點，則不必刪除。
node_t *delete_the_back(node_t *first){
    node_t *current, *p=NULL;
    current = first;

    if(first!=NULL){ // 判斷串列是否存在
        if(current->next!=NULL) // 判斷目前是否為最後一個節點
        {
            while (current->next->next != NULL) // 判斷下一個節點是否為最後一個節點
            {
                current = current->next;
            }
            p = current->next; // 將指標 p 指向下一個節點
            current -> next = NULL; // 將當前節點設為串列最後一個節點
        }
        else{
            p = first;
            first = NULL;
        }   
    }
    free(p);

    return first;
}

//刪除 List 內資料為 x 的節點；若 x 不存在則不刪除任何節點。
node_t *delete_x_node(node_t *first, int x){
    node_t *current, *follow, *p=NULL; // 指向當前節點、先前節點、被刪除節點的三個指標
    current = first;
    bool find = true;
 
    if(current->data == x ) // 判斷第一個節點的資料是否為 x
    {
        first = delete_the_front(first); // 是則用刪除第一個節點的函式 delete_the_front 進行刪除
        return first;
    }
    while (current->data != x ) // 這種作法一次只能刪一個
    {
        follow = current; // 指向當前節點
        current = current->next; // 指向下一個節點檢查
        if(current == NULL)
        {
            find = false;
            break;
        }
    }
    if(find == true)
    {
        p = current;
        follow->next = current->next; // 前一個節點指向下一個節點
        free(p);
    }
 
    return first;
}

//搜尋 List 內資料為 x 的節點，並在其後加入數值 y 的新節點。若 x 不在 List 中，則不必加入 y 。
node_t *add_y_node(node_t *first,int x, int y){
    node_t *current, *new_node;
    current = first;
    bool find = true;
    while (current->data != x ) // 這種作法一次只能加一個
    {
        current = current->next;
        if(current == NULL)
        {
            find = false;
            break;
        }
    }
    if(find == true)
    {
        new_node = malloc(sizeof(struct node_s)); // 建立新節點
        new_node->data = y;
        new_node->next = current->next; // 新節點指向當前節點的下一個節點
        current->next = new_node; // 當前節點指向新節點
    }
    return first;
}

// 反轉 Linked List。
node_t *Reverse(node_t *first)
{
    node_t *previous = NULL, *current = first, *preceding = first->next; // 指向新串列的下一個節點、當前節點、舊串列的下一個節點的三個指標
  
    // new:{NULL}, old:{1, 2, 3, 4, 5, NULL} -> {1, NULL}, {2, 3, 4, 5, NULL} 
    // -> {2, 1, NULL}, {3, 4, 5, NULL} > ... -> {5, 4, 3, 2, 1, NULL}, {NULL}
    while (preceding != NULL) {
        current->next = previous;      // 把current->next轉向（第一次操作會讓原本的 first -> next 指向 NULL）
        previous = current;            // previous指向新串列的第一個節點
        current = preceding;           // current指向舊串列剩下的第一個節點（當前要處理的節點）
        preceding = preceding->next;   // preceding指向舊串列的下一個節點
    }                                  // preceding更新成NULL即跳出while loop

    current->next = previous;          // 此時current位於最後一個node, 將current->next轉向
    first = current;

    return first;
}

	
// 交換數值為 x 和 y 節點的位置，若 x 或 y 不在 List中，則不必交換。
node_t *Change_position(node_t *first, int x, int y)
{   
    node_t *current, *x_current, *x_previous = NULL, *y_current, *y_previous = NULL,*temp,*temp1;
    current = first; // 用於尋找 x 節點和 y 節點的位置
    bool find_x = true, find_y = true, x_front = false, y_back = false;
 
    if(current->data == x ) // 判斷 x 節點是否為第一個節點
    {
        x_current = current;
        x_front = true;
    }
    else
    {
        while (current->data != x )
        {
            x_previous = current;
            current = current->next;
            x_current = current;
            if(current == NULL)
            {
                find_x = false;
                break;
            }
        }
    }
 
    current = first; // 回復成初始值
    while (current->data != y )
    {
        y_previous = current;
        current = current->next;
        y_current = current;
        if(current == NULL)
        {
            find_y = false;
            break;
        }
    }
    if(find_y == true && current->next == NULL) // 判斷 y 節點是否為最後一個節點
    {
        y_back = true;
    }

    if(find_x == true && find_y == true)
    {
        if(x_front == true && y_back == false) // 當 x 節點為第一個節點且 y 節點不為最後一個節點
        {
            x_current->next = y_current->next; // 將 x 節點指向 y 節點的下一個節點
            y_current->next = x_current; // 將 y 節點指向原本 x 節點的下一個節點
            first = y_current; // 設定 first 節點為 y 節點
        }
        else if(x_front == false && y_back == true) // 當 x 節點不為第一個節點且 y 節點為最後一個節點
        {
            x_previous->next = y_current; // 將 x 節點前面的節點指向 y 節點
            y_current->next = x_current; // 將 y 節點的下一個節點指向原本的 x 節點的下一個節點
            x_current->next = NULL; // 將 x 節點指向 NULL
        }
        else if(x_front == true && y_back == true) // 當 x 節點為第一個節點且 y 節點為最後一個節點
        {
            y_current->next = x_current->next;// 將 y 節點的下一個節點指向原本的 x 節點的下一個節點
            y_previous->next = x_current; // 將 y 節點的前一個節點指向 x 節點
            first = y_current; // 將 first 指向 y 節點
            x_current->next = NULL; // 將 x 節點指向 NULL
        }
        else // 當 x 節點不為第一個節點且 y 節點不為最後一個節點
        {
            temp = x_current->next; // 將 temp 指向原本的 x 節點的下一個節點
            temp1 = y_current->next; // 將 temp1 指向原本的 y 節點的下一個節點
            x_previous->next = y_current; // 將原本的 x 節點前面的節點指向 y 節點
            y_previous->next = x_current; // 將原本的 y 節點前面的節點指向 x 節點
            x_current->next = temp1; // 將 x 節點指向原本的 y 節點的下一個節點
            y_current->next = temp; // 將 y 節點指向原本的 x 節點的下一個節點
        }
    }
    return first;   
}

//串列列印函數
void printList(node_t *first){
    node_t *node = first; //將node指向第一個節點
    node_t *p = NULL;
    if(first == NULL){
        printf("None\n");
    }
    else{
        while(node != NULL){
            printf("%d ",node->data);
            node = node->next;
        }
        printf("\n");
    }

    node = first;
    while(node != NULL){ // 釋放動態記憶體空間
        p = node;
        node = node->next;
        free(p);
    }
}
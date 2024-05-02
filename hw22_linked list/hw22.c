#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node_s{
    int data;
    struct node_s *next;
}node_t;

node_t *createList(int);

node_t *add_Node(node_t *, int);

node_t *delete_the_front(node_t *);
node_t *delete_the_back(node_t *);
node_t *delete_x_node(node_t *, int);

node_t *add_y_node(node_t *, int, int);

node_t *Reverse(node_t *);
node_t *Change_position(node_t *, int, int);

void printList(node_t *);

int main()
{
    int node_num, op_num, x, y;
    node_t *first;
    scanf("%d", &node_num);
    first = createList(node_num);
    scanf("%d", &op_num);

    while (op_num > 0)
    {
        int op;
        scanf("%d", &op);
        switch(op)
        {
            case 1:
                scanf("%d", &x);
                first = add_Node(first, x);
                break;

            case 2:
                if (first != NULL)
                {
                    first = delete_the_front(first);
                }
                break;

            case 3:
                if (first != NULL)
                {
                    first = delete_the_back(first);
                }
                break;

            case 4:
                scanf("%d", &x);
                first = delete_x_node(first, x);
                break;

            case 5:
                scanf("%d %d", &x, &y);
                first = add_y_node(first, x, y);
                break;

            case 6:
                first = Reverse(first);
                break;
                
            case 7:
                scanf("%d %d", &x, &y);
                first = Change_position(first, x, y);
                break;

            default:
                break;   
        }
        op_num--;
    }
    printList(first);
    return 0;
    
}

node_t *createList(int len)
{
    node_t *first, *current, *previous;
    for (int i = 0; i < len; i++)
    {
        current = (node_t *)malloc(sizeof(node_t));
        scanf("%d", &(current->data));
        if (i == 0)
        {
            first = current;
        }
        else
        {
            previous->next = current;
        }
        current->next = NULL;
        previous = current;
    }
    return first;
}

node_t *add_Node(node_t *first, int data)
{
    node_t *new_node, *current;
    current = first;
    new_node = malloc(sizeof(struct node_s));

    if (first != NULL)
    {
        while (current->next != NULL)
        {
            current = current->next;
        }
        current -> next = new_node;
    }
    else
    {
        first = new_node;
    }
    new_node->data = data;
    new_node->next = NULL;

    return first;
}

node_t *delete_the_front(node_t *first)
{
    node_t *p = NULL;
    if (first != NULL)
    {
        p = first;
        first = first->next;
    }
    free(p);

    return first;
    
}

node_t *delete_the_back(node_t * first)
{
    node_t *current, *p = NULL;
    current = first;

    if (first != NULL)
    {
        if (current->next != NULL)
        {
            while (current->next->next != NULL)
            {
                current = current->next;
            }
            p = current->next;
            current->next = NULL;
        }
        else
        {
            p = first;
            first = NULL;
        }
    }

    free(p);

    return first;
    
}

node_t *delete_x_node(node_t *first, int x)
{
    node_t *current, *follow, *p = NULL;
    current = first;
    bool find = true;

    if (current->data == x)
    {
        first = delete_the_front(first);
        return first;
    }
    while (current->data != x)
    {
        follow = current;
        current = current->next;
        if (current == NULL)
        {
            find = false;
            break;
        }
        
    }
    if (find == true)
    {
        p = current;
        follow->next = current->next;
        free(p);
    }
    return first;
}

node_t *add_y_node(node_t *first, int x, int y)
{
    node_t *current, *new_node;
    current = first;
    bool find = true;
    while (current->data != x)
    {
        current = current->next;
        if (current == NULL)
        {
            find = false;
            break;
        }
        
    }
    if (find == true)
    {
        new_node = malloc(sizeof(struct node_s));
        new_node->data = y;
        new_node->next = current->next;
        current->next = new_node;
    }
    return first;
}

node_t *Reverse(node_t *first)
{
    node_t *previous = NULL, *current = first, *preceding = first->next;

    while (preceding != NULL)
    {
        current->next = previous;
        previous = current;
        current = preceding;
        preceding = preceding->next;
    }
    
    current->next = previous;
    first = current;

    return first;
}

node_t *Change_position(node_t *first, int x, int y)
{
    node_t *current, *x_current, *x_previous = NULL, *y_current, *y_previous = NULL, *temp, *temp1;
    current = first;
    bool find_x = true, find_y = true, x_front = false, y_back = false;

    if (current->data == x)
    {
        x_current = current;
        x_front = true;
    }
    else
    {
        while (current->data != x)
        {
            x_previous = current;
            current = current->next;
            x_current = current;
            if (current == NULL)
            {
                find_x = false;
                break;
            }
            
        }
        
    }

    current = first;
    while (current->data != y)
    {
        y_previous = current;
        current = current->next;
        y_current = current;
        if (current == NULL)
        {
            find_y = false;
            break;
        }
        
    }
    if (find_y == true && current->next == NULL)
    {
        y_back = true;
    }
    
    if (find_x == true && find_y == true)
    {
        if (x_front == true && y_back == false)
        {
            x_current->next = y_current->next;
            y_current->next = x_current;
            first = y_current;
        }
        else if (x_front == false && y_back == true)
        {
            x_previous->next = y_current;
            y_current->next = x_current;
            x_current->next = NULL;
        }
        else if (x_front == true && y_back == true)
        {
            y_current->next = x_current->next;
            y_previous->next = x_current;
            first = y_current;
            x_current->next = NULL;
        }
        else
        {
            temp = x_current->next;
            temp1 = y_current->next;
            x_previous->next = y_current;
            y_previous->next = x_current;
            x_current->next = temp1;
            y_current->next = temp;
        }
    }
    return first;
}

void printList(node_t *first)
{
    node_t *node = first;
    node_t *p = NULL;
    if (first == NULL)
    {
        printf("None\n");
    }
    else
    {
        while (node != NULL)
        {
            printf("%d ", node->data);
            node = node->next;
        }
        printf("\n");
    }
    
    node = first;
    while (node != NULL)
    {
        p = node;
        node = node->next;
        free(p);
    }
    
}
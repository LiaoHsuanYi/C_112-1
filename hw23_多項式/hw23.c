#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node_s
{
    int coef;
    int exp;
    struct node_s * next;
}node_t;

typedef node_t * nodep_t; //rename

typedef struct pol_s
{
    nodep_t root;
} pol_t;

void add(pol_t* X, pol_t* Y, pol_t* Z);
void sub(pol_t* X, pol_t* Y, pol_t* Z);
void mul(pol_t* X, pol_t* Y, pol_t* Z);

nodep_t createList(int);
void printList(nodep_t);

int main()
{
    //initialize
    int x_node_num, y_node_num;
    nodep_t x_first, y_first, z_first, new_node;
    pol_t *x, *y, *z;

    //allocate
    x = (pol_t *)malloc(sizeof(pol_t));
    y = (pol_t *)malloc(sizeof(pol_t));
    z = (pol_t *)malloc(sizeof(pol_t));

    //input x
    scanf("%d", &x_node_num);
    x_first = createList(x_node_num);
    x->root = x_first;

    //input y
    scanf("%d", &y_node_num);
    y_first = createList(y_node_num);
    y->root = y_first;

    //compute z
    new_node = (nodep_t)malloc(sizeof(node_t));
    new_node->exp = 100;
    z_first = new_node;
    z->root = z_first;

    //function
    add(x, y, z);
    z_first->next = NULL;
    sub(x, y, z);
    z_first->next = NULL;
    mul(x, y, z);

    return 0;
}

nodep_t createList(int len)
{
    nodep_t first, current, previous;
    for (int i = 0; i < len; i++)
    {
        current = (nodep_t)malloc(sizeof(node_t));
        scanf("%d", &(current->coef));
        current->exp = len - 1 - i;
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

void printList(nodep_t first)
{
    nodep_t node = first->next, p = NULL;

    //node = null
    if (node == NULL)
    {
        printf("None\n");
    }
    else
    {
        while (node != NULL)
        {
            printf("%d %d ", node->coef, node->exp);
            node = node->next;
        }
        printf("\n");
    }
    if (first->next != NULL)
    {
        node = first->next;
        while (node != NULL)
        {
            p = node;
            node = node->next;
            free(p);
        }   
    }
}

void add(pol_t* X, pol_t* Y, pol_t* Z)
{
    nodep_t x_current, y_current, z_current, z_root, new_node;

    x_current = X->root;
    y_current = Y->root;
    z_current = Z->root;
    z_root = Z->root;

    while (1)
    {
        if (x_current == NULL || y_current == NULL)
        {
            break;
        }
        if (x_current->exp > y_current->exp)
        {
            new_node = (nodep_t)malloc(sizeof(node_t));
            new_node->coef = x_current->coef;
            new_node->exp = x_current->exp;
            x_current = x_current->next;
        }
        else if (x_current->exp < y_current->exp)
        {
            new_node = (nodep_t)malloc(sizeof(node_t));
            new_node->coef = y_current->coef;
            new_node->exp = y_current->exp;
            y_current = y_current->next;
        }
        else
        {
            new_node = (nodep_t)malloc(sizeof(node_t));
            new_node->coef = x_current->coef + y_current->coef;
            new_node->exp = x_current->exp;
            x_current = x_current->next;
            y_current = y_current->next;
        }
        z_current->next = new_node;
        z_current = z_current->next;
        z_current->next = NULL;
        
    }
    printList(z_root);
}

void sub(pol_t* X, pol_t* Y, pol_t* Z)
{
    //nodep_t
    nodep_t x_current, y_current, z_current, z_root, new_node;

    //initialize
    x_current = X->root;
    y_current = Y->root;
    z_current = Z->root;
    z_root = Z->root;

    while (1)
    {
        //NULL
        if (x_current == NULL || y_current == NULL)
        {
            break;
        }

        //x > y
        if (x_current->exp > y_current->exp)
        {
            new_node = (nodep_t)malloc(sizeof(node_t));
            new_node->coef = x_current->coef;
            new_node->exp = x_current->exp;
            x_current = x_current->next;
        }

        //x < y
        else if (x_current->exp < y_current->exp)
        {
            new_node = (nodep_t)malloc(sizeof(node_t));
            new_node->coef = -y_current->coef;
            new_node->exp = y_current->exp;
            y_current = y_current->next;
        }

        //x = y
        else
        {
            new_node = (nodep_t)malloc(sizeof(node_t));
            new_node->coef = x_current->coef - y_current->coef;
            new_node->exp = x_current->exp;
            x_current = x_current->next;
            y_current = y_current->next;
        }
        z_current->next = new_node;
        z_current = z_current->next;
        z_current->next = NULL;
    }
    printList(z_root);
}

void mul(pol_t* X, pol_t* Y, pol_t* Z)
{
    int product_exp;
    bool exp_exist = false;
    nodep_t x_current, y_current, z_current, z_root, new_node;

    x_current = X->root;
    y_current = Y->root;
    z_current = Z->root;
    z_root = Z->root;

    while (1)
    {
        exp_exist = false;
        z_current = Z->root;

        //x = null
        if (x_current == NULL)
        {
            y_current = y_current->next;
            x_current = X->root;
        }
        //y = null
        if (y_current == NULL)
        {
            break;
        }

        product_exp = x_current->exp + y_current->exp;

        //z != null
        while (z_current != NULL)
        {
            if (z_current->exp == product_exp)
            {
                exp_exist = true;
                break;
            }
            if(z_current->next != NULL)
            {
                z_current = z_current->next;
            }
            else
            {
                break;
            }
        }

        //exp_exist = false
        if (exp_exist == false)
        {
            new_node = (nodep_t)malloc(sizeof(node_t));
            new_node->coef = x_current->coef * y_current->coef;
            new_node->exp = product_exp;
            z_current->next = new_node;
            z_current = z_current->next;
            z_current->next = NULL;
        }
        else
        {
            z_current->coef += x_current->coef * y_current->coef;
        }
        x_current = x_current->next;
    }
    printList(z_root);
}

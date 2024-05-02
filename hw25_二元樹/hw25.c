#include <stdio.h>
#include <stdlib.h>

typedef struct node_s
{
    char data;
    struct node_s *right, *left;
} tree_t;

typedef tree_t * btree;

btree newNode(char data)
{
    btree new_node = malloc(sizeof(tree_t));
    new_node->data = data;
    new_node->right = NULL;
    new_node->left = NULL;
    return new_node;
}

void output(btree root)
{
    //initialize
    int count = 1, c = 0;
    btree temp1[100], temp2[100];
    temp1[0] = root;
    
    //loop
    while (count > 0)
    {
        for (int i = 0; i < count; i++)
        {
            printf("%c", temp1[i]->data);
            if (temp1[i]->left != NULL)
            {
                temp2[c++] = temp1[i]->left;
            }
            if (temp1[i]->right != NULL)
            {
                temp2[c++] = temp1[i]->right;
            } 
            
        }
        for (int i = 0; i < c; i++)
        {
            temp1[i] = temp2[i];
        }
        count = c;
        c = 0;
    }
}

int main()
{
    //initialize
    int n, x, y, index = 0;
    char c, s, aim, input1[100], input2[100];
    btree root = NULL, temp;

    //input n, s
    scanf("%d\n", &n);
    scanf("%c\n", &s);

    //s = P | s = O
    if (s == 'P' || s == 'O')
    {
        for (int i = 0; i < n; i++)
        {
            scanf("%c", &input1[i]);
        }
        scanf("\n%c\n", &c);
        for (int i = 0; i < n; i++)
        {
            scanf("%c", &input2[i]);
        }
        scanf("%c", &c);
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            scanf("%c", &input2[i]);
        }
        scanf("\n%c\n", &s);
        for (int i = 0; i < n; i++)
        {
            scanf("%c", &input1[i]);
        }
        scanf("%c", &c);
    }

    //s = O
    if (s == 'O')
    {
        for (int i = 0; i < n/2; i++)
        {
            c = input1[i];
            input1[i] = input1[n-i-1];
            input1[n-i-1] = c;
        }
        
    }
    
    //root
    root = newNode(input1[0]);

    //index
    while (index < n-1)
    {
        index++;
        temp = root;
        aim = input1[index];
        for (int i = 0; i < n; i++)
        {
            //find aim
            if (input2[i] == aim)
            {
                x = i;
            }
        }
        while (1)
        {
            //find temp
            for (int i = 0; i < n; i++)
            {
                if (input2[i] == temp->data)
                {
                    y = i;
                }
                
            }

            //x > y
            if (x > y)
            {
                if (temp->right == NULL)
                {
                    temp->right = newNode(aim);
                    break;
                }
                else
                {
                    temp = temp->right;
                }
            }

            //x < y
            else
            {
                if (temp->left == NULL)
                {
                    temp->left = newNode(aim);
                    break;
                }
                else
                {
                    temp = temp->left;
                }
            }
        } 
    }
    output(root);
    return 0;
}
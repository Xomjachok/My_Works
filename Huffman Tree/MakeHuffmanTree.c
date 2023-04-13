#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define SIZE 100

void buff(char buffer[SIZE]);

struct Node 
{
    char world;
    struct Node *left;
    struct Node *right;
};

void logic (struct Node* node, char buffer[SIZE])
{
    if (node == NULL)
    {  
        return;        
    }  
    if (node->left == NULL || node->right == NULL)
    {
        putchar(node->world);
        return 0;
    }

    for (int i = 0; buffer[i] != '\0'; i++)
    {
        if (buffer[i] == '1')
        {
            buffer[i] = ' ';            
            logic(node->right, buffer);
        }
        else if (buffer[i] == '0')
        {
            
            buffer[i] = ' ';
            logic(node->left, buffer);       
        }        
    }
    return;
    
}

void buff(char buffer[SIZE])
{   
    struct Node* node;
    logic(node->right, buffer);
}

struct Node* createNode()
{
    struct Node* newnode = (struct Node*) malloc(sizeof(struct Node));
    char buffer[SIZE];
    memset(buffer, 2, sizeof(buffer));
    char* r = fgets(buffer, SIZE, stdin);
    if(strlen(buffer) == 1)
    {
        printf("Ziadny vstup\n");
        return 0;
    }
    buffer[strlen(buffer) - 1] = '\0';
    if (buffer[0] == '1' || buffer[0] == '0') 
    {
        buff(buffer);
        printf("\n");
        return 0;
    }
    newnode->left = NULL;
    newnode->right = NULL;
    newnode->world = buffer[0];
    if (buffer[0] == '#')
    {        
        newnode->left = createNode(newnode->left);
        newnode->right = createNode(newnode->right);
        createNode(newnode->world);
    }
    return newnode;
};

int main ()
{
    struct Node* node;
    createNode(); 
}

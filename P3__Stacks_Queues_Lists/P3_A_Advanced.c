#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node
{
    char data;
    struct Node *next;
};

struct Node *top = NULL;

void push(char data)
{
    struct Node *link = (struct Node*)malloc(sizeof(struct Node));
    link->data = data;

    // if stack is empty
    if(top == NULL)
    {
        top = link;
        link->next = NULL;
        return;
    }

    // if stack is not empty
    link->next = top;
    top = link;
}

void pop()
{
    if(top == NULL)
    {
        return;
    }

    if(top->next == NULL)
    {
        free(top);
        top = NULL;
        return;
    }

    struct Node *tmp = top;
    top = top->next;
    free(tmp);
}

char getTop()
{
    return top->data;
}

void remove_all()
{
    while(top != NULL)
    {
        pop();
    }
}

int checkSyntax(char x[])
{
    int len = strlen(x);

    for(int i = 0; i < len; i++)
    {
        // opening symbols -> push
        if(x[i] == '(' || x[i] == '[' || x[i] == '{')
        {
            push(x[i]);
        }

        // closing symbols -> check top
        if(x[i] == ')' || x[i] == ']' || x[i] == '}')
        {
            if(top == NULL)
            {
                return 0;
            }

            // check matching pair
            if(x[i] == ')' && getTop() == '(')
            {
                pop();
            }
            else if(x[i] == ']' && getTop() == '[')
            {
                pop();
            }
            else if(x[i] == '}' && getTop() == '{')
            {
                pop();
            }
            else
            {
                return 0;
            }
        }
    }

    // after reading all expression, stack must be empty
    if(top == NULL)
    {
        return 1;
    }
    return 0;
}

int main()
{
    char expr1[] = "[()]{}{[()()]()}";
    char expr2[] = "[(])";

    printf("Expression: %s -> %d\n", expr1, checkSyntax(expr1));
    remove_all();

    printf("Expression: %s -> %d\n", expr2, checkSyntax(expr2));
    remove_all();

    return 0;
}
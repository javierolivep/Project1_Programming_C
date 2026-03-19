#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *next;
};
struct Node *top = NULL;

void push(int data)
{
    //create a link
    struct Node *link=(struct Node*)malloc(sizeof(struct Node));

    link->data = data;
    // If top is empty, create a new stack
    if(top==NULL) {
        top = link;
        link->next = NULL;
        return;
    }
    // If top is not empty, point 'next' to the previous 'top' 
    // and the new 'top' will point to the new created node with its value (link->data = data)
    link->next = top;
    top = link;
}

void pop ()
{
    if(top==NULL) {
        printf("No element to remove. Stack is empty");
        return;
    }
    if(top->next == NULL){
        free (top);
        top = NULL;
        printf("Stack is empty now");
        return;
    }
    //if(top->next != NULL) so there are variables left
    struct Node * tmp=top;
    top = top->next;
    free (tmp);
    return;
}

void print_stack()
{
    struct Node * current = top;
    while (current != NULL)
    {
    printf("%d=>", current->data);
    current = current->next;
    }
    printf ("\n");
}

int count_elements()
{
    int elements = 0;
    struct Node * current = top;
    while (current != NULL)
    {
        current = current->next;
        elements += 1;
    }
    return elements;
}

void remove_all ()
{
   while (top != NULL)
    {
        pop();
    }
}

int main(void)
{
    int len;
    push(1);
    push(2);
    push(3);
    print_stack ();
    len = count_elements();
    printf("num of elements: %d\n", len);
    pop();
    print_stack ();
    len = count_elements();
    printf("num of elements: %d\n", len);
    remove_all();
    print_stack ();
    return 0;
}
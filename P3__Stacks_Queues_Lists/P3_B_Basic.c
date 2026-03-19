#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *next;
};
struct Node *first = NULL;
struct Node *last = NULL;

void addElement (int data)
{
    //create a new element
    struct Node *newElement=(struct Node*)malloc(sizeof(struct Node));
    newElement->data = data;
    if(first==NULL)
    {
        printf("first NULL, creating the queue\n");
        first = last = newElement;
        newElement->next = NULL;
        return;
    }

    newElement->next=NULL;
    last->next=newElement;
    last=newElement;
    return;
}

void removeElement ()
{
    if (first==NULL)
    {
        printf("nothing to remove");
        return;
    }
    // remove the one element
    if (first->next==NULL) 
    {
        printf("...removing data: %d\n", first->data);
        free (first);
        first = last = NULL;
        printf("List is empty now");
        return;
    }
    struct Node * tmp=first;
    printf("...removing data: %d\n", tmp->data);
    first=tmp->next;
    free(tmp);
    return;
}

void print_queue()
{
    struct Node * current = first;
    while (current != NULL)
    {
        printf("%d=>", current->data);
        current = current->next;
    }
    printf ("\n");
}

int countNodes()
{
    int count = 0;
    struct Node * current = first;
    while(current != NULL)
    {
        count++;
        current = current->next;
    }
    return count;
}

void remove_all()
{
    int len = countNodes();
    for (int i = 0; i < len; i++)
    {
        removeElement();
    }
}

int getFirst()
{
    return first->data;
}

int getLast()
{
    return last->data;
}

int main(void)
{
    int len;
    addElement(1);
    addElement(2);
    addElement(3);
    print_queue();
    len = countNodes();
    printf("num of nodes: %d\n", len);
    removeElement();
    print_queue();
    len = countNodes();
    printf("num of nodes: %d\n", len);
    remove_all();
    print_queue();
    return 0;
}
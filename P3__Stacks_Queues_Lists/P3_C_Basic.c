#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *next;
};
struct Node *head = NULL;

void create_list()
{
    int data;
    while (1)
    {
        printf("Input data to insert in the list: ");
        scanf("%d", &data);

        if (data < 0)
            break;

        struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->data = data;
        newNode->next = NULL;
        
        if (head == NULL)
        {
            head = newNode;
        }
        else
        {
            struct Node *current = head;
            while (current->next != NULL)
            {
                current = current->next;
            }
            current->next = newNode;
        }
    }
}

void display_list()
{
    struct Node *current = head;
    printf("Data in the list:\n");
    while (current != NULL)
    {
        printf("%d==>", current->data);
        current = current->next;
    }
    printf("\n");
}

int count_nodes()
{
    int count = 0;
    struct Node *current = head;
    while (current != NULL)
    {
        count++;
        current = current->next;
    }
    return count;
}

void insert_beginning(int data)
{
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = head;
    head = newNode;
}

void insert_end(int data)
{
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;

    if (head == NULL)
    {
        head = newNode;
        return;
    }

    struct Node *current = head;
    while (current->next != NULL)
    {
        current = current->next;
    }
    current->next = newNode;
}

void insert_middle(int data, int afterData)
{
    struct Node *current = head;
    while(current != NULL && current->data != afterData)
    {
        current = current->next;
    }

    if (current == NULL)
    {
        printf("Node with data %d: Not found\n", afterData);
        return;
    }

    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = current->next;
    current->next = newNode;
}

void remove_first()
{
    if (head == NULL)
        return;

    struct Node *tmp = head;
    head = head->next;
    free(tmp);
}

void remove_last()
{
    if (head == NULL)
        return;

    if (head->next == NULL)
    {
        free(head);
        head = NULL;
        return;
    }

    struct Node *current = head;
    while (current->next->next != NULL)
    {
        current = current->next;
    }
    free(current->next);
    current->next = NULL;
}

void remove_middle(int data)
{
    if (head == NULL)
        return;

    if (head->data == data)
    {
        remove_first();
        return;
    }

    struct Node *current = head;
    while(current->next != NULL && current->next->data != data)
    {
        current = current->next;
    }
    
    if(current->next == NULL)
    {
        printf("Node with data %d not found\n\n", data);
        return;
    }

    struct Node *tmp = current->next;
    current->next = tmp->next;
    free(tmp);
}

void search_element(int data)
{
    int position = 1;
    struct Node *current = head;

    while(current != NULL)
    {
        if(current->data == data)
        {
            printf("Element found at node number %d\n\n", position);
            return;
        }
        current = current->next;
        position++;
    }

    printf("Element not found\n\n");
}

int main()
{
    create_list();
    display_list();

    printf("Total number of nodes = %d\n\n", count_nodes());

    printf("Input data to insert at the begginig: 4\n\n");
    insert_beginning(4);
    display_list();

    printf("Input data to insert at the end: 8\n\n");
    insert_end(8);
    display_list();

    printf("Input data to insert in the list: 77\n");
    printf("Input the position after which the new node must be inserted (node data): 7\n\n");
    insert_middle(77, 7);
    display_list();
    printf("\n");

    remove_first();
    display_list();

    remove_last();
    display_list();

    printf("Input the element of the node to remove (node data): 7\n");
    remove_middle(7);
    display_list();

    printf("Input the element to be searched: 6\n");
    search_element(6);

    return 0;
}
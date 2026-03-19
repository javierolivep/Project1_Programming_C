//DELIVERABLE_2 BY JUANMA MACHADON AND JAVIER OLIVÉ
#include <stdio.h>
#include <stdlib.h>

struct Character
{
    char data;
    struct Character *next;
};
struct Character *head = NULL;

//declaration of functions
void InsertCharacter(char character);
struct Character *Search(char character);
void RemoveFirstAndLastCharacter();
void PrintList();

void InsertCharacter(char character)
{
    struct Character *newNode = (struct Character*)malloc(sizeof(struct Character));
    newNode->data = character;
    newNode->next = NULL;

    if (head == NULL)
    {
        head = newNode;
        return;
    }

    struct Character *previous = Search(character);

    // if insert is at the beginning(head)
    if (previous == NULL)
    {
        //duplicate at head
        if (head->data == character)
        {
            printf("Warning: This character has already been in the list\n");
            free(newNode);
            return;
        }
        newNode->next = head;
        head = newNode;
        return;
    }

    //duplicate after previous (except head)
    if (previous->next != NULL && previous->next->data == character)
    {
        printf("Warning: This character has already been in the list\n");
        free(newNode);
        return;
    }
    newNode->next = previous->next;
    previous->next = newNode;
}

struct Character *Search(char newCharacter)
{
    struct Character *current = head;
    struct Character *previous = NULL;

    while (current != NULL && current->data < newCharacter)
    {
        previous = current;
        current = current->next;
    }

    return previous;
}

void RemoveFirstAndLastCharacter()
{
    //if no elements in the list
    if (head == NULL)
        return;

    // remove first
    struct Character *first = head;
    head = head->next;
    free(first);

    // if only one node remains after removing first, remove it too 
    if (head->next == NULL)
    {
        free(head);
        head = NULL;
        return;
    }

    // if >2 elements, remove last
    struct Character *last = head;
    while (last->next->next != NULL)
    {
        last = last->next;
    }
    free(last->next);
    last->next = NULL;
}

void PrintList()
{
    struct Character *current = head;
    printf("Output sorted list -> ");
    while (current != NULL)
    {
        printf("%c ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main()
{
    char newCharacter;

    printf("Welcome to the sorted list!\n");

    while (1)
    {
        printf("Which character would you like to insert? ");
        scanf(" %c", &newCharacter);

        if (newCharacter == '9')
        {
            break;
        }
        else if (newCharacter >= 'a' && newCharacter <= 'z')
        {
            InsertCharacter(newCharacter);
            PrintList();
        }
        else
        {
            printf("Character %c is not between 'a' and 'z'. Try again.\n", newCharacter);
        }
    }

    printf("Removing the first and the last element\n");
    RemoveFirstAndLastCharacter();
    PrintList();

    return 0;
}


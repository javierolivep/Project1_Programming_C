#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node
{
    char name[50];
    int ticketType;
    int numTickets;
    int budget;
    struct Node *next;
};
struct Node *first = NULL;
struct Node *last = NULL;

int availableTickets[5] = {200, 400, 150, 50, 30};
int ticketPrices[5] = {100, 120, 80, 300, 500};
char ticketNames[5][30] = {
                            "General entrance",
                            "Tribune seats",
                            "Balcony seats",
                            "VIP",
                            "Gold VIP"
                          };

void addElement(char name[], int ticketType, int numTickets, int budget)
{
    struct Node *newElement = (struct Node*)malloc(sizeof(struct Node));
    strcpy(newElement->name, name);
    newElement->ticketType = ticketType;
    newElement->numTickets = numTickets;
    newElement->budget = budget;

    if(first == NULL)
    {
        first = last = newElement;
        newElement->next = NULL;
        return;
    }

    newElement->next = NULL;
    last->next = newElement;
    last = newElement;
}

void removeElement()
{
    if(first == NULL)
    {
        return;
    }

    if(first->next == NULL)
    {
        free(first);
        first = last = NULL;
        return;
    }

    struct Node *tmp = first;
    first = tmp->next;
    free(tmp);
}

void processPurchase()
{
    if(first == NULL)
    {
        return;
    }

    int type = first->ticketType;
    int wanted = first->numTickets;
    int totalPrice = wanted * ticketPrices[type];

    printf("Person: %s\n", first->name);
    printf("Ticket type: %s\n", ticketNames[type]);
    printf("Requested tickets: %d\n", wanted);
    printf("Budget: %d\n", first->budget);
    printf("Total price: %d\n", totalPrice);

    if(availableTickets[type] < wanted)
    {
        printf("No enough tickets available\n\n");
        removeElement();
        return;
    }

    if(first->budget < totalPrice)
    {
        printf("No sufficient budget\n\n");
        removeElement();
        return;
    }

    availableTickets[type] = availableTickets[type] - wanted;
    printf("Purchase completed\n\n");
    removeElement();
}

void processAll()
{
    while(first != NULL)
    {
        processPurchase();
    }
}

void printTickets()
{
    for(int i = 0; i < 5; i++)
    {
        printf("%s - available: %d - price: %d\n",
               ticketNames[i], availableTickets[i], ticketPrices[i]);
    }
    printf("\n");
}

int main()
{
    addElement("Jiarui", 0, 2, 250);
    addElement("Marc", 1, 3, 500);
    addElement("Laia", 2, 4, 200);
    addElement("Juanma", 3, 1, 350);
    addElement("Guille", 4, 2, 1200);

    printTickets();
    processAll();
    printTickets();
    return 0;
}
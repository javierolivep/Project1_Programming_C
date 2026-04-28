/* ──────────────────────────────────────────────────────────────────────────────────────────
 * Universitat Autònoma de Barcelona - UAB
 * 	Bachelor's Degree in Artificial Intelligence
 *     	Fundamentals of Programming II
 *         	Practical Project I - Logistics Simulator
 * 			Team:	
 * 				Name          Surname          NIU
 * 				--------------------------------------
 * 				Javier        Olivé Padrós     1794767
 * 				Juanma        Machado Millan   1797427
   ────────────────────────────────────────────────────────────────────────────────────────── */

/* ──────────────────────────────────────────────────────────────────────────────────────────
 * 																					 INCLUDES
   ────────────────────────────────────────────────────────────────────────────────────────── */

/* Import standard libraries and specific project header.  */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "project1.h"

/* ──────────────────────────────────────────────────────────────────────────────────────────
 *  																		UTILITY FUNCTIONS
   ────────────────────────────────────────────────────────────────────────────────────────── */

/* Generate random event type: 0, 1 or 2, corresponding to the next three code sections. */
enum EventType GenerateEventType()
{
	return rand()%3;
}

/* Check whether the program arguments are valid, exit with error message if invalid. */
void CheckArguments (int argc, char ** argv)
{
	if (argc != 2)
	{
		printf("Error: correct usage is ./program #events\n");
		exit(1);
	}
	if (atoi(argv[1]) <= 0)
	{
		printf("Error: Number of events must be an integer grater than 0.\n\n");
		exit(1);
	}
}

/* ──────────────────────────────────────────────────────────────────────────────────────────
 *  															  ROBOT PACKAGES: SORTED LIST
    							   Linked list of packages, sorted alphabetically by supplier
   ────────────────────────────────────────────────────────────────────────────────────────── */
/* Allocate memory for a new RobotPackage, initialize with random attributes and return. */
struct RobotPackage * GenerateRobotPackage()
{
	struct RobotPackage * RobotPackage=malloc(sizeof(struct RobotPackage));
	int RobotPackageNum=rand()%8;
	strcpy (RobotPackage->supplier, suppliers[RobotPackageNum]);
	strcpy (RobotPackage->id, ids[RobotPackageNum]);
	int year=rand()%40+1980;
	RobotPackage->year=year;
	return RobotPackage;
}

/* Print all RobotPackage node data currently stored in the sorted linked list. */
void PrintRobotPackages()
{
    struct RobotPackage *current = RobotPackagesHead;
    printf("Displaying RobotPackages sorted list data...\n");
    char lastSupplier[20] = "";
    while (current != NULL)
    {
        if (strcmp(current->supplier, lastSupplier) != 0)
        {
            printf("\tSupplier: %s\n\tID: %s\n\tYears:\n", current->supplier, current->id);
            strcpy(lastSupplier, current->supplier);
        }
        printf("\t\t%d\n", current->year);
        current = current->next;
    }
    printf("\n");
}

/* Find the position for a new RobotPackage to be placed in, indicated with a pointer to the previous package. */ 
struct RobotPackage *SearchRobotPackage(char *supp)
{
    struct RobotPackage *current = RobotPackagesHead;
    struct RobotPackage *previous = NULL;
	// Move forward until the correct sorted position is found
    while (current != NULL && strcmp(current->supplier, supp) <= 0)
    {
        previous = current;
        current = current->next;
    }
    return previous;
}

/* Insert a RobotPackage into the linked list following the alphabetical order by supplier. */
void SimulateManagingRobotPackages(struct RobotPackage * robot_package)
{
	robot_package->next = NULL;

	// Empty list: new node becomes the head.
    if (RobotPackagesHead == NULL)
    {
        RobotPackagesHead = robot_package;
        return;
    }
	// Insert at the beginning if it should go just before the current head.
    else if (strcmp(robot_package->supplier, RobotPackagesHead->supplier) < 0)
    {
        robot_package->next = RobotPackagesHead;
        RobotPackagesHead = robot_package;
        return;
    }
	// Else, the list is traversed until the correct insertion point is found.
 	struct RobotPackage *previous = SearchRobotPackage(robot_package->supplier);
    struct RobotPackage *after = previous->next;
	// Insert Robotpackage between previous and after:
    previous->next = robot_package;
    robot_package->next = after;
}

/* Free all RobotPackage nodes and set header to NULL to reset the list to empty state. */
void RemoveAllRobotPackages()
{
	struct RobotPackage *current = RobotPackagesHead;
    struct RobotPackage *nextNode;
    while (current != NULL)
    {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }
    RobotPackagesHead = NULL;
}

/* ──────────────────────────────────────────────────────────────────────────────────────────
 *  																		 PACKAGES: STACKS
    											   Array of 3 stacks of packages by size type
   ────────────────────────────────────────────────────────────────────────────────────────── */

/* Allocate and return a new Package with random attributes.*/
struct Package * GeneratePackage()
{
	struct Package * Package=malloc(sizeof(struct Package));
	enum PackageType type=rand()%3;
	enum Colors color=rand()%4;
	Package->type = type;
	Package->color = color;
	return Package;
}

/* Initialize all stacks, headers pointing to NULL and counters being 0.*/
void InitStacks()
{
	for (int i=0; i<NUMBER_OF_STACK; i++)
	{
		Top_ofPackageStacks[i] = NULL;
		CurrentState[i] = 0;
	}
}

/* Print all packages and their attributes from each stack, making use of the enums via switch. */
void PrintPackages()
{
	const char* size;
	const char* color;
	for (int i=0; i<NUMBER_OF_STACK; i++)
	{
		switch ((enum PackageType)i) 
		{
            case small:  size = "small";  break;
            case medium: size = "medium"; break;
            case large:  size = "large";  break;
		}
		printf("\tStack %d: Size %s (%d package/s of %d)\n", i, size, CurrentState[i], MAX_CAPACITY);
		if (Top_ofPackageStacks[i] == NULL)
		{
			printf("\t\tEmpty\n");
		}
		else
		{
			struct Package *current = Top_ofPackageStacks[i];
			printf("\t\tColors: ");
			while (current != NULL)
			{
				switch (current->color) 
				{
					case white:  color = "white";  break;
					case green:  color = "green";  break;
					case yellow: color = "yellow"; break;
					case beige:  color = "beige";  break;
				}
				printf("%s", color);
                if (current->next != NULL) printf(", ");
                current = current->next;
			}
            printf("\n");
        }
    }
    printf("\n");
}

/* Clear stack by freeing nodes, setting header to NULL and returning counter to 0. */
void RemoveStack(int stack_index)
{
	struct Package *current = Top_ofPackageStacks[stack_index];
	while (current != NULL)
	{
		struct Package *temp = current;
		current = current->next;
		free(temp);
	}
	Top_ofPackageStacks[stack_index] = NULL;
	CurrentState[stack_index] = 0;
}

/* Add package to corresponding stack by size, clearing it instantly once it's full. */
void SimulateClassifyPackage(struct Package * package)
{
	int stack_index = package->type;
	package->next = Top_ofPackageStacks[stack_index];
	Top_ofPackageStacks[stack_index] = package;
	CurrentState[stack_index]++;
	if (CurrentState[stack_index]>=MAX_CAPACITY)
	{
		RemoveStack(stack_index); 
	}
}

/* Reset all stacks to the initial state. */
void CleanPackageStacks()
{
	for (int stack_index=0; stack_index<NUMBER_OF_STACK; stack_index++)
	{
		RemoveStack(stack_index);
	}
}

/* ──────────────────────────────────────────────────────────────────────────────────────────
 *  																		  SHOPPING: QUEUE
     		   FIFO queue of robots, waiting to non-simultaneousy execute a number of actions 
   ────────────────────────────────────────────────────────────────────────────────────────── */

/* Allocate and return a new Shopping robot with random attributes.*/
struct Shopping * GenerateShopping()
{
	struct Shopping * shopping=malloc(sizeof(struct Shopping));
	int n=rand()%5+1;
	shopping->numberThingsToBuy = n;
	nextRobotID++;
	shopping->robot_id=nextRobotID;
	return shopping;
}

/* Print all shopping robots in the shopping queue and their attributes. */
void PrintShopping()
{
    struct Shopping *current = queueFirst;
    printf("Displaying Shopping queue data...\n");
    while (current != NULL)
    {
        printf("\tRobot ID: %d, Things to buy: %d\n", current->robot_id, current->numberThingsToBuy);
        current = current->next;
    }
    printf("\n");
}

/* Add a shopping robot to the end of the queue. */
void AddToQueue(struct Shopping * shopping)
{
	shopping->next = NULL;
	// If the queue is empty the new robot is now first and last
	if (queueFirst == NULL)
	{
		queueFirst = shopping;
		queueLast = shopping;
		return;
	}
	// Else, new robot is added at the end and assigned as the last one
	queueLast->next = shopping;
	queueLast = shopping;
	return;
}

/* Remove oldest robot in line and returning the number of actions to perform. */
int Dequeue ()
{
    if (queueFirst == NULL)
    {
        printf("Queue is already empty\n");
        return 0;
    }

    struct Shopping *tmp = queueFirst;
    int things = tmp->numberThingsToBuy;
    if (queueFirst->next == NULL)
    {
        queueFirst = NULL;
        queueLast = NULL;
    }
    else
    {
        queueFirst = queueFirst->next;
    }
    free(tmp);
    return things;
}

/* Advance robot time layer by one unit, dispatching a new robot if none is active, reducing the action count of the working robot by 1 otherwise. */
void UpdateShoppingQueue (int *robot_timer)
{
	if (*robot_timer == 0 && queueFirst != NULL)
	{
		/* No robot currently shopping and more available: deploy next one. */
		*robot_timer = Dequeue();
	}
	if (*robot_timer > 0)
	{
		/* Advancement of one time unit: one shopping action completed. */
		(*robot_timer)--; 
	}
}

/* Add shopping robot to the end of the queue, waiting to be deployed, one at a time. */
void SimulateGoForShopping(struct Shopping * shopping)
{
	AddToQueue(shopping);
}

/* Reset the shopping queue to the initial state by freeing the remaining nodes. */
void CleanShoppingQueue()
{
    while (queueFirst != NULL)
    {
        Dequeue();
    }
}	

/* ──────────────────────────────────────────────────────────────────────────────────────────
 * 																						 MAIN
   ────────────────────────────────────────────────────────────────────────────────────────── */

/* Run a single simulation, corresponding to a time unit or a singular event.
   Simultaneously advances the shopping robot timer.
   Once the main timer runs out, prints info about remaining nodes before resetting the system. */
void SimulationLoop(int EventNumbers)
{
	int robot_timer = 0;
	InitStacks();
	for (int i=0; i<EventNumbers; i++) 
	{
		int event_type = GenerateEventType(); 
		switch(event_type)
		{
			case 0:
			{
				struct RobotPackage *robot_package = GenerateRobotPackage();
				SimulateManagingRobotPackages(robot_package);
				break;
			}
			case 1:
			{
				struct Package *package = GeneratePackage();
				SimulateClassifyPackage(package);
				break;
			}
			case 2:
			{
				struct Shopping *shopping = GenerateShopping();
				SimulateGoForShopping(shopping);
				break;
			}
		}
		UpdateShoppingQueue(&robot_timer);
	}
	printf("program %d\n", EventNumbers);
	printf("STATISTICS WHEN CLEANING THE SIMULATION:\n");

	/* Robot Package List */
	printf("\tRemoving packages...\n");
	int count = 0;
	{
		struct RobotPackage *current = RobotPackagesHead;
		while (current != NULL) {count++; current = current->next;}
	}
	RemoveAllRobotPackages();
	printf("\t\t%d packages have been removed.\n", count);

	/* Package Stacks */
	count = 0;
	printf("\tCleaning all stacks of packages...\n");
	for (int i=0; i<NUMBER_OF_STACK; i++)
	{
		struct Package *current = Top_ofPackageStacks[i];
		while (current != NULL) {count++; current = current->next;}
	}
	CleanPackageStacks();
	printf("\t\t%d packages have been removed\n", count);

	/* Shopping Queue */
	printf("\tCleaning shopping queue...\n");
	count = 0;
	{ 
		struct Shopping *current = queueFirst;
		while (current != NULL) {count++; current = current->next;}
	}
	CleanShoppingQueue();
	printf("\t\t%d robots have been removed\n", count);
}

/* Put all pieces together, validating arguments and running the simulation. */
int main (int argc, char ** argv)
{
	int EventNumbers;
	printf ("Starting... \n");
	CheckArguments(argc, argv);
	EventNumbers = atoi(argv[1]);
	SimulationLoop(EventNumbers);
	return 0;
}
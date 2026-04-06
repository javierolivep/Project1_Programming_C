
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "project1.h"

/* ──────────────────────────────────────────────────────────────────────────────────────────
 * 																			GENERAL FUNCTIONS
   ────────────────────────────────────────────────────────────────────────────────────────── */
enum EventType GenerateEventType()
{
	return rand()%3;
}

void CheckArguments (int argc, char ** argv)
{
	int EventNumbers; 
	if (argc < 2) // if there is no argument assigned (1st one is the name of the program)
	{
		printf("Argument is missing\n");
		exit (1);
	}
	else if (atoi(argv[1]) <= 0) // if argument is negative
    {
        printf("Error: NumberOfEvents must be an integer grater than 0.\n");
        exit(1);
    }
}

/* ──────────────────────────────────────────────────────────────────────────────────────────
 * 																  ROBOT PACKAGES: SORTED LIST
   ────────────────────────────────────────────────────────────────────────────────────────── */
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

void PrintRobotPackages()
{
	struct RobotPackage *current = RobotPackagesHead;
	printf("Data in the list of packages: \n");
	while (current != NULL)
    {
        printf("supplier: %s, ID: %s, year: %d\n", current->supplier, current->id, current->year);
        current = current->next;
    }
    printf("\n");
}

struct RobotPackage *SearchRobotPackage(char *supp, char *id, int year) // TODO: unused function?
{
	int position = 1;
	struct RobotPackage *current = RobotPackagesHead;
	while (current != NULL)
	{
		if (strcmp(current->supplier,supp ) == 0 && 
			strcmp(current->id, id) == 0 && 
			current->year == year)
		{
			printf("Package found at position number %d\n", position);
            return current;
		}
		current = current->next;
		position++;
	}
	printf("Package not found\n");
	return NULL;
}

void SimulateManagingRobotPackages(struct RobotPackage * robot_package)  // TODO What happens when packages share supplier? Order by year or id? Doesnt matter?
{
	robot_package->next = NULL;

    if (RobotPackagesHead == NULL)
    {
        RobotPackagesHead = robot_package;
        return;
    }
    else if (strcmp(robot_package->supplier, RobotPackagesHead->supplier) < 0)
    {
        robot_package->next = RobotPackagesHead;
        RobotPackagesHead = robot_package;
        return;
    }

	struct RobotPackage *current = RobotPackagesHead;
	struct RobotPackage *previous = NULL;
	while (current != NULL &&
           strcmp(current->supplier, robot_package->supplier) <= 0)
	{
		previous = current;
		current = current->next;
	}
	previous->next = robot_package;
	robot_package->next = current;
}

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
 * 																			 PACKAGES: STACKS
   ────────────────────────────────────────────────────────────────────────────────────────── */
struct Package * GeneratePackage()
{
	struct Package * Package=malloc(sizeof(struct Package));
	enum PackageType type=rand()%3;
	enum Colors color=rand()%4;
	Package->type = type;
	Package->color = color;
	return Package;
}

void InitStacks()
{
	for (int i=0; i<NUMBER_OF_STACK; i++)
	{
		Top_ofPackageStacks[i] = NULL;
		CurrentState[i] = 0;
	}
}

void PrintPackages() // TODO also unused
{
	const char* PackageType[] = {"small", "medium", "large"};
	const char* Colors[] = {"white", "green", "yellow", "beige"};
	printf("Displaying stack data...\n");
	for (int i=0; i<NUMBER_OF_STACK; i++)
	{
		printf("Stack %d:\n",  i);
		if (Top_ofPackageStacks[i] == NULL)
		{
			printf("  Empty\n");
		}
		else
		{
			struct Package *current = Top_ofPackageStacks[i];
			printf("    %-15s %-10s\n", "Size",  "Color");
			while (current != NULL)
			{
				printf("    %-15s %-10s\n", PackageType[current->type], Colors[current->color]);
				current = current->next;
			}
		}
	}
	printf("\n");
}

void RemoveStack(int stack_index)
{
	struct Package *current = Top_ofPackageStacks[stack_index];
	struct Package *temp = NULL;
	while (current != NULL)
	{
		temp = current;
		current = current->next;
		free(temp);
	}
	Top_ofPackageStacks[stack_index] = NULL;
	CurrentState[stack_index] = 0;
}

void SimulateClassifyPackage(struct Package * package)
{
	int stack_index = package->type;
	package->next = Top_ofPackageStacks[stack_index];
	Top_ofPackageStacks[stack_index] = package;
	CurrentState[stack_index]++;
	if (CurrentState[stack_index]>=MAX_CAPACITY)
	{
		RemoveStack(stack_index); // TODO stack instantly deleted once full
	}
}

void CleanPackageStacks()
{
	for (int stack_index=0; stack_index<NUMBER_OF_STACK; stack_index++)
	{
		RemoveStack(stack_index);
	}
}

/* ──────────────────────────────────────────────────────────────────────────────────────────
 * 																			  SHOPPING: QUEUE
   ────────────────────────────────────────────────────────────────────────────────────────── */
struct Shopping * GenerateShopping()
{
	struct Shopping * shopping=malloc(sizeof(struct Shopping));
	int n=rand()%5+1;
	shopping->numberThingsToBuy = n;
	nextRobotID++;
	shopping->robot_id=nextRobotID;
	return shopping;
}

void PrintShopping()
{
	struct Shopping *current = queueFirst;
	while (current != NULL)
	{
		printf("things to buy: %d, ID: %d\n", current->numberThingsToBuy, current->robot_id);
        current = current->next;
	}
	printf("\n");
}

void AddToQueue(struct Shopping * shopping)
{
	shopping->next = NULL;
	if (queueFirst == NULL)
	{
		queueFirst = shopping;
		queueLast = shopping;
		return;
	}
	queueLast->next = shopping;
	queueLast = shopping;
	return;
}

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

void UpdateShoppingQueue (int *robot_timer)
{
	if (queueFirst != NULL)
	{
		if (*robot_timer == 0)
		{
			*robot_timer = Dequeue();
		}
		(*robot_timer)--; // TODO Decision: robot can be deployed and take action in the same turn. If not, then the -- goes inside an else
	}
}

void SimulateGoForShopping(struct Shopping * shopping)
{
	AddToQueue(shopping);
}

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
	printf("Removing packages...\n");
	int count = 0;
	{
		struct RobotPackage *current = RobotPackagesHead;
		while (current != NULL) {count++; current = current->next;}
	}
	RemoveAllRobotPackages();
	printf("%d packages have been removed.\n", count);

	/* Package Stacks */
	count = 0;
	printf("Cleaning all stacks of packages...\n");
	for (int i=0; i<NUMBER_OF_STACK; i++)
	{
		struct Package *current = Top_ofPackageStacks[i];
		while (current != NULL) {count++; current = current->next;}
	}
	CleanPackageStacks();
	printf("%d packages have been removed\n", count);

	/* Shopping Queue */
	printf("Cleaning shopping queue...\n");
	count = 0;
	{ // TODO current double declaration: will fail to compile
		struct Shopping *current = queueFirst;
		while (current != NULL) {count++; current = current->next;}
	}
	CleanShoppingQueue();
	printf("%d robots have been removed\n", count);
}

int main (int argc, char ** argv)
{
	int EventNumbers;
	printf ("Starting... \n");
	CheckArguments(argc, argv);
	EventNumbers = atoi(argv[1]);
	SimulationLoop(EventNumbers);
	return 0;
}

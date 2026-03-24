/*
Degree: Artificial Intelligence
Subject: Fundamentals of Programming 2
Practical project: 1

Simulator - main program
*/

#include <stdio.h>
#include <stdlib.h>
#include "project1.h" // header with all data structures

//----------------------------------------------------------General
// WARNING: do not change this function
enum EventType GenerateEventType()
{
	return rand()%3;
}

void CheckArguments (int argc, char ** argv)
{
	if (argc != 2)
	{
		printf("Error: correct usage is ./program #events\n");
		exit(1);
	}
	char *endptr;
	long n = strtol(argv[1], &endptr, 10);
	if (*endptr != '\0')
	{
		printf("Error: #events argument must be a valid integer\n");
		exit(1);
	}
	if (n<=0)
	{
		printf("Error: #events must be a positive integer\n");
		exit(1);
	}
}

//----------------------------------------------------------RobotPackages -> Sorted list
// WARNING: do not change this function
struct RobotPackage * GenerateRobotPackage()
{
	// reserve memory for a RobotPackage
	struct RobotPackage * RobotPackage=malloc(sizeof(struct RobotPackage));
	int RobotPackageNum=rand()%8;
	// initialize the RobotPackage's fields
	strcpy (RobotPackage->supplier, suppliers[RobotPackageNum]);
	strcpy (RobotPackage->id, ids[RobotPackageNum]);
	int year=rand()%40+1980;
	RobotPackage->year=year;
	return RobotPackage;
}

// function to print a list of RobotPackages
void PrintRobotPackages()
{
	
}

// function to search for a RobotPackage
struct RobotPackage * SearchRobotPackage(/*...*/)
{

}

// function to simulate an insertion of RobotPackages in a ordered way (sorted by supplier)
void SimulateManagingRobotPackages(struct RobotPackage * RobotPackage)
{

}

// function to remove all the RobotPackages from the list at the end of the program
void RemoveAllRobotPackages()
{

}

//----------------------------------------------------------Packages -> different Stacks
// WARNING: do not change this function
struct Package * GeneratePackage()
{
	// reserve memory for a Package
	struct Package * Package=malloc(sizeof(struct Package));
	// initialize the Package's fields
	enum PackageType type=rand()%3;
	enum Colors color=rand()%4;
	Package->type = type;
	Package->color = color;
	return Package;
}

// function to initialize all stacks of Packages 
void InitStacks()
{
	for (int i=0; i<NUMBER_OF_STACK; i++)
	{
		Top_ofPackageStacks[i] = NULL;
		CurrentState[i] = 0;
	}
}

// function to print all stacks with all Packages
void PrintPackages()
{
	const char* PackageType[] = {"small", "medium", "large"};
	const char* Colors[] = {"white", "green", "yellow", "beige"};
	for (int i=0; i<NUMBER_OF_STACK; i++)
	{
		printf("Stack %d: (%s)\n", i+1, PackageType[i]);
		if (Top_ofPackageStacks[i] == NULL)
		{
			printf("  Empty\n");
		}
		else
		{
			struct Package* temp = Top_ofPackageStacks[i];
			int j = 1;
			while (temp != NULL)
			{
				printf("  Package %d: size %s - color %s\n", j, PackageType[temp->type], Colors[temp->color]);
				temp = temp-> next;
				j++;
			}
		}
	}
}

// function to remove all packages from a given stack when its MAX_CAPACITY is reached
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

// function to simulate putting a generated Package to a corresponding stack depending on the type (size)
void SimulateClassifyPackage(struct Package * package)
{
	// Put node on top of stack
	int stack_index = package->type;
	package->next = Top_ofPackageStacks[stack_index];
	Top_ofPackageStacks[stack_index] = package;
	CurrentState[stack_index]++;
	if (CurrentState[stack_index]>=MAX_CAPACITY)
	{
		RemoveStack(stack_index);
	}
}

// function to clean all stacks before the end of the program
void CleanPackageStacks()
{
	for (int stack_index=0; stack_index<NUMBER_OF_STACK; stack_index++)
	{
		RemoveStack(stack_index);
	}
}

//----------------------------------------------------------Shopping -> Queue
// WARNING: do not change this function
struct Shopping * GenerateShopping()
{
	// reserve memory for a Shopping
	struct Shopping * shopping=malloc(sizeof(struct Shopping));
	// initialize the shopping's fields
	int n=rand()%5+1;
	shopping->numberThingsToBuy = n;
	nextRobotID++;
	shopping->robot_id=nextRobotID;
	return shopping;
}

// function to print a list of robots in a shopping queue
void PrintShopping()
{

}

// function to add a robot to a shopping queue
void AddToQueue(struct Shopping * shopping)
{

}

// function to remove a robot from the queue and serve it
// it may return the number of things to buy to simulate the time
int Dequeue ()
{

}

// function to simulate the time the robot is in the queue
// function to simulate the time the robot is in the queue
void UpdateShoppingQueue (int *robot_timer)
{
	/// check if queue is empty, then do nothing, checking the pointer queueFirst
	/// if not empty, proceed to another check
	/// check0: if timer is 0, next robot leaves the queue and does first action
	/// check1: timer advances + next robot action happens
	/// timer--
	if (queueFirst != NULL)
	{
		if (*robot_timer == 0)
		{
			*robot_timer = Dequeue();
		}
		(*robot_timer)--; // Decision: robot can be deployed and take action in the same turn. If not, then the -- goes inside an else
	}
}

// function to simulate a robot going for shopping - add to the queue
void SimulateGoForShopping(struct Shopping * shopping)
{

}

// function to clean shopping queue before the end of the program
void CleanShoppingQueue(/*...*/)
{

}

//----------------------------------------------------------main
// This is the main loop of the program. 
// It generates and consumes events.
void SimulationLoop(int EventNumbers)
{
	// declare and initialize necessary variables
	int robot_timer = 0;

	InitStacks();
	
	for (int i=0; i<EventNumbers; i++)    
	{
		// generate event type
		int event_type = GenerateEventType(); 
		// depending on the generated event type:
		switch(event_type)
		{
			// event type 0: 
			// generate RobotPackage 
			// Simulate managing RobotPackages (sorting)
			case 0:
			{
				struct RobotPackage *robot_package = GenerateRobotPackage();
				SimulateManagingRobotPackages(robot_package);
				break;
			}
			// event type 1:
			// generate Package
			// Simulate classifying Packages (putting to a corresponding stack)
			case 1:
			{
				struct Package *package = GeneratePackage();
				SimulateClassifyPackage(package);
				break;
			}
			// event type 2:
			// generate shopping
			// Simulate go for shopping 
			case 2:
			{
				struct Shopping *shopping = GenerateShopping();
				SimulateGoForShopping(shopping);
				break;
			}
		}
		// UpdateShopping
		UpdateShoppingQueue(&robot_timer);
	}
	// CLEANING THE SIMULATION
	printf("program %d", EventNumbers);
	// keep void and count at the end, check stored numbers before removing
	printf("STATISTICS WHEN CLEANING THE SIMULATION:\n");
	// robotPackages
	printf("Removing packages...\n");
	struct RobotPackage *current;
	int count = 0;
	current = RobotPackagesHead;
	while (current != NULL)
	{
		count++;
		current = current->next;
	}
	RemoveAllRobotPackages();
	printf("%d packages have been removed.\n", count);
	// packages
	count = 0;
	printf("Cleaning all stacks of packages...\n");
	for (int i=0; i<NUMBER_OF_STACK; i++)
	{
		struct Package *current = Top_ofPackageStacks[i];
		while (current != NULL) // TODO common function?
		{
			count++;
			current = current->next;
		}
	}
	CleanPackageStacks();
	printf("%d packages have been removed\n", count);
	// shopping
	printf("Cleaning shopping queue...\n");
	struct Shopping *current = queueFirst;
	count = 0;
	while (current != NULL)
	{
		count++;
		current = current->next;
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

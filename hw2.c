#include <stdio.h>
#include <stdlib.h>

typedef struct o_
{
	int ID; //the order number
	int daysInQueue; //the number of days old the order is
	struct o_* nextOrder; //to the next order in the list
} Order;

Order** importLists(char* filename);
void printList(Order* firstOrder);
int updateOrder(int ID, Order** oldList, Order** newList);
int processOldestOrder(Order** firstOrder);
void freeList(Order* list);
int getPriority();

//***********START OF REQUIRED FUNCTIONS***************

Order** importLists(char* filename)
{
	FILE* fp = fopen(filename, "r");
	if(fp == NULL) {
		printf("\nUnable to open input file.");
        return NULL;
	}
    
    // aye made this expandable
    int i = 0, numLists = 4;
    
    // Creating start pointers and intializing the lists

	Order** orders = (Order**)malloc(sizeof(Order)*numLists);
	
	for(i = 0; i < numLists; i++) {
        orders[i] = NULL;
    }
    
    /*
     File format:
     
     <ID> <DAYS IN Q> <LIST INDEX>
     
     */
    
    int id = 0, days = 0, list = 0;
    Order* start = NULL;
    Order* current = NULL;
                                     
    // for loop gets lists 1-4
    for(i = 0; i < numLists; i++) {
        // reset pointers
        start = current = NULL;
        
        // read the list
        while(fscanf(fp, "%d %d %d", &id, &days, &list) == 3) {
            // only add a line if it matches the current list index
            if(list == i) {
                Order* newOrder = (Order*)malloc(sizeof(Order));
                newOrder->ID = id;
                newOrder->daysInQueue = days;
                newOrder->nextOrder = NULL;
                
                if(start == NULL) {
                    current = start = newOrder;
                } else {
                    current = current->nextOrder = newOrder;
                }
            }
        }
        // put it back in our double pointer
        orders[i] = start;
        
        // start the scan over again
        rewind(fp);
    }

	fclose(fp);
    
    return orders;
}

int updateOrder(int ID, Order** oldList, Order** newList)
{
    Order* old = *oldList;
    Order* new = *newList;
    
    // in case lists are empty/null
    if(old == NULL || new == NULL) {
        return -1;
    }
    
    // flag for checking if the ID exists in oldList
    int found = 0;
    
    
    Order* current = old;
    Order* previous = NULL;
    
    // if the order is found in oldList, put it here
    Order* update = NULL;
    
    if(old->ID == ID) {
        found = 1;
        update = old;
        old = (*oldList)->nextOrder->nextOrder;
    }
    
    
    while(old != NULL && found == 0) {
        // match
        if(old->ID == ID) {
            found = 1;
            update = current->nextOrder;
            
            if(previous == NULL) {
                old = current->nextOrder;
            } else {
                // jump over the selected order in the old list.
                current->nextOrder = current->nextOrder->nextOrder;
                
            }
            
            
            break;
        }
        
        previous = current;
        current = old;
        old = old->nextOrder;
        
    }
    // no match found in old list
    if(found == 0) {
        return -1;
    } else if(update->ID == ID){
        current = new;
        while(current->nextOrder != NULL) {
            current = current->nextOrder;
        }
        current->nextOrder = update;
        
        current = current->nextOrder;
        current->nextOrder = NULL;
    }
    
    
    oldList = &old;
    newList = &new;
    
    return update->ID;
}

// 
int processOldestOrder(Order** firstOrder)
{
    Order* list = *firstOrder;
    Order* current = list;
    
    Order* update = current;
    int days = current->daysInQueue;
    
    while(list != NULL) {
        
        if(current->daysInQueue > days) {
            days = current->daysInQueue;
            update = current;
            
        }
        
        current = list;
        list = list->nextOrder;
    }
    
    list = *firstOrder;
    current = list;
    
    while(list != NULL) {
        
        if(current == update) {
            current->nextOrder = current->nextOrder->nextOrder;
        }
        
        
        current = list;
        list = list->nextOrder;
    }
    
    
    return 0;
}

void printList(Order* firstOrder)
{
    if(firstOrder == NULL) {
        printf("\n");
        return;
    }
    
    printf("Order No. %d: %d days in queue.\n", firstOrder->ID, firstOrder->daysInQueue);
    printList(firstOrder->nextOrder);
}

void freeList(Order* list)
{
    Order* current = list;
    while(list != NULL) {
        current = list;
        list = list->nextOrder;
        free(current);
    }
}

//*************END OF REQUIRED FUNCTIONS*************

int main(int argc, char** argv)
{
	if(argc != 2)
	{
		printf("Usage: ./a.out <filename>\n");
		return -2;
	}

	Order** lists = importLists(argv[1]);
	if(lists == NULL)
	{
		printf("Error reading from %s.\n", argv[1]);
		return -1;
	}

	while(1)
	{
		printf("1: print a list\n");
		printf("2: change an order's priority\n");
		printf("3: process oldest order\n");
		printf("4: quit\n>");
		int selection;
		scanf("%d", &selection);
		while(selection < 1 || selection > 4)
		{
			printf("Invalid selection, choose again:\n>");
			scanf("%d", &selection);
		}
	
		if(selection == 1)
		{
			printf("Which list do you want to print out?\n");
			int priority = getPriority();
			printList(lists[priority - 1]);
		}
		else if(selection == 2)
		{
			printf("What is the ID of the order to be changed?\n>");
			int ID;
			scanf("%d", &ID);
			printf("What was the ID's old priority?\n");
			int priority = getPriority();

			printf("What is the ID's new priority?\n");
			int newPriority = getPriority();

			int ret = updateOrder(ID, &lists[priority - 1], &lists[newPriority - 1]);		
			if(ret != ID)
			{
				printf("Error updating order no. %d.\n", ID);
			}
			else
			{
				printf("Order no. %d updated successfully.\n", ID);
			}
		}
		else if(selection == 3)
		{
			printf("Which priority list do you want to process from?\n");
			int priority = getPriority();
			int ret = processOldestOrder(&lists[priority - 1]);
			if(ret != 0)
			{
				printf("Error processing from list %d. Is it empty?\n", priority);
			}
			else
			{
				printf("list %d processed successfully.\n", priority);
			}
		}
		else break;
	}

	int i;
	for(i = 0; i < 4; i++)
	{
		freeList(lists[i]);
	}

	free(lists);
	return 0;
}

int getPriority()
{
	printf("1: Next day\n");
	printf("2: Business\n");
	printf("3: Standard\n");
	printf("4: Long term\n>");
	int priority;
	scanf("%d", &priority);
	while(priority < 1 || priority > 4)
	{
		printf("Invalid selection, choose again:\n>");
		scanf("%d", &priority);
	}

	return priority;
}

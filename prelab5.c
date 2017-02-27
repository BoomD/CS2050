/*
 Alex Gompper
 Prelab 5
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct i_ {
    int value;
    struct i_* nextItem;
} Item;

Item* addItem(Item* start, int toAdd);
void printList(Item* start);
void freeList(Item* start);

int main(void) {
    int input = 0;
    
    Item* start = NULL;
    
    while(1) {
        printf("\nEnter a number (-1 to quit): ");
        scanf("%d", &input);
        switch(input) {
            case -1:
                printf("\nExiting\n\n");
                freeList(start);
                exit(0);
            default:
                start = addItem(start, input);
                printf("\n");
                printList(start);
        }
    }
    
}

Item* addItem(Item* start, int toAdd) {
    if(start == NULL) {
        start = (Item*)malloc(sizeof(Item));
        start->value = toAdd;
        start->nextItem = NULL;
        
        return start;
    }
    Item* ptr = start;
    while(ptr->nextItem != NULL) {
        ptr = ptr->nextItem;
    }
    
    Item* t = (Item*)malloc(sizeof(Item));
    t->value = toAdd;
    t->nextItem = NULL;
    
    ptr->nextItem = t;
    
    return start;
}

void printList(Item* start) {
    if(start == NULL) {
        printf("NULL\n");
        return;
    }
    
    printf("%d -> ", start->value);
    printList(start->nextItem);
}

void freeList(Item* start) {
    Item* t = start;
    while(start != NULL) {
        t = start;
        start = start->nextItem;
        free(t);
    }
    
    
}
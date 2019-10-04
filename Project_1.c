#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>



// ------------------Structures------------------- //

typedef struct node {
    int payload;
    struct node *next;
}unUsedNode;



struct node *high_list;
struct node *med_list;
struct node *low_list;


// ------------------Functions Declared----------- //

int push(struct node *head, int val);
int pop(struct node **head);

int printLinkedList(struct node *head);
int printAllLists(void);

int initializeSimulation(void);
int highToMed(void);
int medToLow(void);
int lowToLow(void);



// ------------------Main------------------------ //

int main(void) {

  initializeSimulation();
  highToMed();
  medToLow();
  lowToLow();
  printf("****Processes Completed****");

  return 0;
}



// ------------------Functions-------------------- //

//  push creates a new node for val and adds to list
int push(struct node *head, int val) {
  struct node* current = head;
  while (current->next != NULL) {
    current = current->next;
  }

  current->next = malloc(sizeof(struct node));
  current->next->payload = val;
  current->next->next = NULL;

  return 0;
}

// must pass in a node with & before the variable name
int pop(struct node **head) {
  int returnVal = -1;
  struct node *next_node = NULL;

  if(*head == NULL) {
    return -1;
  }
  next_node = (*head)->next;
  returnVal = (*head)->payload;
  free(*head);
  *head = next_node;

  return returnVal;
}


int printLinkedList(struct node *head) {
  struct node *current = head;
  current = current->next; //to jump past the listnode

  while(current != NULL) {
    printf("%d ", current->payload);
    current = current->next;
  }

  printf("\n");
  return 0;
}

int printAllLists(void) {
  printf("High Queue: ");
  printLinkedList(high_list);

  printf("Med Queue: ");
  printLinkedList(med_list);

  printf("Low Queue: ");
  printLinkedList(low_list);
  printf("\n");
  return 0;
}


int initializeSimulation(void) {
  //   Create Linked-Lists
  high_list = malloc(sizeof(struct node));
  med_list = malloc(sizeof(struct node));
  low_list = malloc(sizeof(struct node));


  //   Add Nodes with 1-5 to the highest queue
  for(int i = 1; i <= 5; i++) {
    push(high_list, i);
  }

  printf("\nInitializing simulation with process IDs: 1 2 3 4 5\n\n");
  printAllLists();
  sleep(1);
  return 0;
}

int highToMed(void) {

  for(int i = 0; i < 5; i++) {
    int temp = pop(&(high_list->next));
    printf("Executing process %d from High Priority queue\n\n", temp);
    push(med_list, temp);
    printAllLists();
    sleep(1);
  }

  return 0;
}

int medToLow(void) {
  for(int i = 0; i < 5; i++) {
    int temp = pop(&(med_list->next));
    printf("Executing process %d from Med Priority queue\n\n", temp);
    push(low_list, temp);
    printAllLists();
    sleep(1);
  }
  return 0;
}

int lowToLow(void) {
  for (int i = 0; i < 5; i++) {
    int temp = pop(&(low_list->next));
    printf("Executing process %d from Low Priority Queue\n\n", temp);
    push(low_list, temp);
    printAllLists();
    sleep(1);
  }

  return 0;
}

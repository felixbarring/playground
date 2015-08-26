
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

typedef struct node {
  struct node *next;
  int data;
} Node;

typedef struct queue {
  struct node *head, *tail;
} Queue;

// Queue functions
void initialize_queue(void);
void enqueue(int val);
int dequeue(int *extractedValue);

// Auxiliary functions
int isEmpty();
void printContent();
int sumOfAllElements();
void clearQueue();

// Queue variables
static Queue *q;
pthread_mutex_t headLock;
pthread_mutex_t tailLock;

void initialize_queue(void){
  Node *dummyNode = malloc(sizeof(Node));
  q = malloc(sizeof(Queue));
  q->head = dummyNode;
  q->tail = dummyNode;

  pthread_mutex_init(&headLock, NULL);
  pthread_mutex_init(&tailLock, NULL);
}

void enqueue(int val){
  Node *newNode = malloc(sizeof(Node));
  newNode->data = val;
  pthread_mutex_lock(&tailLock);
  q->tail->next = newNode;
  q->tail = newNode;
  pthread_mutex_unlock(&tailLock);
}

int dequeue(int *extractedValue){
  pthread_mutex_lock(&headLock);
  if(isEmpty()){ pthread_mutex_unlock(&headLock); return 1; }
  *extractedValue = q->head->next->data;
  struct node *temp = q->head->next;
  free(q->head);
  q->head = temp;
  pthread_mutex_unlock(&headLock);
  return 0;
}

//----------------------
//---Auxiliary Functions
//----------------------
int isEmpty(){ return q->head == q->tail; }

void printContent(){
  if(isEmpty()) return;
  Node *node = q->head->next;
  while(node != q->tail){
    printf("%i ",  node->data);
    node = node->next;
  }
  printf("%i \n",  node->data);
}

int sumOfAllElements(){
  if(isEmpty()) return 0;
  int sum = 0;
  Node *node = q->head->next;
  while(node != q->tail){
    sum += node->data;
    node = node->next;
  }
  sum += node->data;
  return sum;
}

void clearQueue(){
  int *dummy = malloc(sizeof(int));
  while(!isEmpty()){
    dequeue(dummy);
  }
  free(dummy);
}



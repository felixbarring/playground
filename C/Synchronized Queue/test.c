
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include "synchronizedQueue.c"

typedef struct threadData{
  int operations;                // Used thread functions argument
  int netSum, addOp, removeOp;   // The threadFunction should use these for statistics
} ThreadData;

// Test functions
void testSyncQueue(int numOfThreads, int numOfOperations);
void *threadFunction();
int test1(int threads, int operations);
int test2(int threads, int operations);

// Auxiliary: returns time difference in miliseconds
int diffClock(clock_t clock1, clock_t clock2);
void fillQueue(int size);

main(){
  initialize_queue();

  char command[200];
  int *argument = malloc(sizeof(int));
  printf("\n");
  printf("Type one of the following modes that represets what you want to test \n");
  printf("You will need to provide the following int arguments in order:  \n");
  printf("Initial size of the queue, number of threads, total number of operations \n");
  printf("  test1: Queue with one lock \n");
  printf("  test2: Queue with two locks \n");
  printf("  test3: Compares the performance of test1 and 2 on the same input \n");
  printf("You can also modify the current queue with the following commands \n");
  printf("  add arg : will add the argument to the queue \n");
  printf("  poll: will remove the head of the queue \n");
  printf("  print: will print the queue \n");
  printf("  clear: will clear the queue \n");
  printf("  sum: the sum of all elements in the queue \n \n");

  while(1){
    scanf("%s", command);

    if(!strcmp(command, "test1") || !strcmp(command, "test2") || !strcmp(command, "test3")){
      int startSize;
      int threads;
      int operations;
      scanf("%i", &startSize);
      scanf("%i", &threads);
      scanf("%i", &operations);

      if(!strcmp(command, "test1")){
        fillQueue(startSize);
        printf("Elapsed time for test1: %i \n", test1(threads, operations));
        clearQueue();
      } else if(!strcmp(command, "test2")){
        fillQueue(startSize);
        printf("Elapsed time for test2: %i \n", test2(threads, operations));
        clearQueue();
      } else{
        fillQueue(startSize);
        int t1 = test1(threads, operations);
        clearQueue();
        fillQueue(startSize);
        int t2 = test2(threads, operations);
        clearQueue();
        printf("Time for test1: %i, Time for test2: %i, Difference test1 - 2: %i \n", t1, t2, t1-t2);
      }

    }else if(!strcmp(command, "add")){
      scanf("%i", argument);
      enqueue(*argument);
    } else if(!strcmp(command, "poll")){
      int *arg = malloc(sizeof(int));
      if(!dequeue(arg)){
        printf("Head of list contained: %i \n", *arg);
      } else {
        printf("You can not poll from an empty queue, silly \n");
      }
      free(arg);
    } else if(!strcmp(command, "print")){
      printContent();
    }else if(!strcmp(command, "clear")){
      clearQueue();
    } else if(!strcmp(command, "sum")){
      printf("The sum of all elements is: %i \n", sumOfAllElements());
    } else if(!strcmp(command, "exit")){
      return;
    }else {
      printf("Invalid input \n");
    }
  }
}

// Both dequeue and enqueue uses the same lock
int test1(int threads, int operations){
  clock_t start;
  clock_t end;
  pthread_mutex_t *tmp = &tailLock;
  tailLock = headLock;
  start = clock();
  testSyncQueue(threads, operations);
  end = clock();
  tailLock = *tmp;
  return diffClock(end, start);
}

// Two differentlocks
int test2(int threads, int operations){
  clock_t start;
  clock_t end;
  start = clock();
  testSyncQueue(threads, operations);
  end = clock();
  return diffClock(end, start);
}

void testSyncQueue(int numOfThreads, int numOfOperations){
  if(numOfOperations%numOfThreads != 0){
    printf("Operations must be divisable by the number of threads \n");
  }

  int operationPerThread = numOfOperations/numOfThreads;
  int netSum = 0;
  int totalAddOp = 0;
  int totalRemoveOp = 0;
  int i = 0;
  int initialSum = sumOfAllElements();

  pthread_t threads[numOfThreads];
  ThreadData* dataForEachThread[numOfThreads];
  for(i = 0; i < numOfThreads; i++){
    ThreadData *threadData = malloc(sizeof(ThreadData));
    threadData->operations = operationPerThread;
    dataForEachThread[i] = threadData;
    if(pthread_create(&threads[i], NULL, threadFunction, (void*) threadData) != 0){
      printf("Error occured while creating a thread \n");
    }
  }
  for(i = 0; i < numOfThreads; i++){
    pthread_join(threads[i], NULL);
    netSum +=  dataForEachThread[i]->netSum;
    totalAddOp += dataForEachThread[i]->addOp;
    totalRemoveOp += dataForEachThread[i]->removeOp;
  }
  netSum += initialSum;
  int sum = sumOfAllElements();
  printf("  Netsum: %i Sum of all elements: %i Difference %i \n", netSum, sum, netSum-sum);
  printf("  Add: %i Remove: %i Add+Remove: %i \n    Difference with the specified number of operations %i \n", 
    totalAddOp, totalRemoveOp, totalAddOp+totalRemoveOp, numOfOperations-(totalAddOp+totalRemoveOp));

}

void *threadFunction(void *threadData){
  ThreadData *data = (ThreadData *) threadData;
  int op = data->operations;
  int netSum = 0;
  int add = 0;
  int remove = 0;
  while(op > 0){
    int random = (int)(rand()/1000000);
    if((rand() / (double)RAND_MAX) < 0.5){
      enqueue(random);
      netSum += random;
      add++;      
    } else {
      int ret;
      if (!dequeue(&ret)) netSum -= ret;
      remove++;
    }
    op--;
  }
  data->netSum = netSum;
  data->addOp =  add;
  data->removeOp = remove;
}

int diffClock(clock_t clock1,clock_t clock2){
  double diffTicks = clock1-clock2;
  double diffMs = (diffTicks)/(CLOCKS_PER_SEC/1000);
  return diffMs;
}

void fillQueue(int size){
  int i = 0;
  for(i; i < size; i++){
    enqueue(i);
  }
}



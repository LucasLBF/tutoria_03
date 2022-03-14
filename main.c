#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define N_THREADS 3
#define INT_MIN -2147483647
#define INT_MAX 2147483647

void *calculateAvg(void *args);
void *calculateMax(void *args);
void *calculateMin(void *args);

int numQty = 0;
int *numbers;
int global_max = 0;
int global_min = 0;
int avg = 0;

int main()
{
  pthread_t workerThreads[N_THREADS];
  int numBuffer = 0;

  scanf("%d", &numQty);
  numbers = (int *) malloc(sizeof(int) * numQty);

  for (int i = 0; i < numQty; i++) {
    scanf("%d", &numBuffer);
    numbers[i] = numBuffer;
  }
  
  // create all threads
  pthread_create(&(workerThreads[0]), NULL, calculateAvg, NULL);
  pthread_create(&(workerThreads[1]), NULL, calculateMax, NULL);
  pthread_create(&(workerThreads[2]), NULL, calculateMin, NULL);

  // wait for each thread to finish execution
  for (int i = 0; i < N_THREADS; i++) {
    pthread_join(workerThreads[i], NULL);
  }

  // show results
  printf("Average: %d\n", avg);
  printf("Maximum: %d\n", global_max);
  printf("Minimum: %d\n", global_min);

  return 0;
}

void *calculateAvg(void *args)
{
  int total = 0;
  for (int i = 0; i < numQty; i++) {
    total += numbers[i];
  }
  avg = total / numQty;
  return NULL;
}

void *calculateMax(void *args)
{
  int max = INT_MIN;
  for (int i = 0; i < numQty; i++) {
    if (max == INT_MIN || numbers[i] > max) {
      max = numbers[i];
    }
  }  
  global_max = max;
  return NULL;
}

void *calculateMin(void *args)
{
  int min = INT_MAX;
  for (int i = 0; i < numQty; i++) {
    if (min == INT_MAX || numbers[i] < min) {
      min = numbers[i];
    }
  }
  global_min = min;
  return NULL;
}


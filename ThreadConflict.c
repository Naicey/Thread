/*Thread.c 
  Author: Slem Zhang
  Create: 03/05/2017
*/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <assert.h>
#include <unistd.h>

int x = 0;

//declare a spinlock for global variable
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;


//Asset x = 0;

void * Producer(void*)
{
    int i = 0;
   for(i =0; i<10000; i++)
   {
    // pthread_mutex_lock(&mutex);
     x++;
     //usleep(1000);
     //pthread_mutex_unlock(&mutex);
   }  
}


void  TestMultiThread(void)
{
  int ret = 0;
  pthread_t thread1;
  pthread_t thread2;
  
  ret = pthread_create(&thread1, NULL, Producer, NULL);
  assert(ret == 0);
  
  ret = pthread_create(&thread2, NULL, Producer, NULL);
  assert(ret == 0);
  
  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);
  printf("x=%d\n", x);
}


int main(void)
{
  TestMultiThread();
  return 0;
}

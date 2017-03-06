/*Thread.c 
  Author: Slem Zhang
  Create: 03/05/2017
*/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <assert.h>
#include <unistd.h>

/*
 * Now the Producer will plus x with 1; and Consumer subtract the x with 1;
 * Question Consumer thread start first, so it need to wait Procuder has alread plux x  then subtract x;
 * Refer pthread_cond_wait to complete this code,  Comsuemr wait Producer had done something.
 */

int x = 0;

pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;

void * Producer(void*)
{
    printf("Producer called\n");
    int i = 0;
    x++;
    //TODO: send a signal to Consumer, refer https://linux.die.net/man/3/pthread_cond_signal 
    
   //for(i =0; i<10000; i++)
   //{
   //  pthread_mutex_lock(&mutex);
   //  x++;
   //  pthread_mutex_unlock(&mutex);
   //}  
}

void* Consumer(void*) 
{
    //TODO: wait signal from Produer, refer https://linux.die.net/man/3/pthread_cond_signal 
    printf("Consumer called\n");
    if(x > 0) x--;
    
    //while(1){
    // pthread_mutex_lock(&mutex);
     //if(x> 0) x--;
    // pthread_mutex_unlock(&mutex);
    //}
    
}


void  TestMultiThread(void)
{
  int ret = 0;
  pthread_t thread1;
  pthread_t thread2;
  
  ret = pthread_create(&thread1, NULL, Consumer, NULL);
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

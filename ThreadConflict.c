/*Thread.c 
  Author: Slem Zhang
  Create: 03/05/2017
*/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int x = 0;
pthread_t thread_ctl;
pthread_t thread1;
pthread_t thread2;

//declare a spinlock for global variable
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;


//Asset x = 0;

void * CreateOneWorker(void)
{
   while(x <= 20000)
   {
     pthread_mutex_lock(&mutex);
     
     x++;
     
     pthread_mutex_unlock(&mutex);
     sleep(1);
   }  
}


void * TriggerallStart(void)
{
  int ret = 0;
  
  ret = pthread_create(&thread1, NULL, CreateOneWorker, NULL);
  if( ret !=0 )
     printf("can't create thread1");
    
  ret = pthread_create(&thread2, NULL, CreateOneWorker, NULL);
  if( ret !=0 )
     printf("can't create thread2");
  
  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);
}


int main(void)
{
  pthread_create(&thread_ctl,NULL,TriggerallStart,NULL);
  
  pthread_join(thread_ctl,NULL);
  
  return 0;
}

/*Thread.c 
  Author: Slem Zhang
  Create: 03/05/2017
*/

#include <stdio.h>
#include <pthread.h>
#include <spinlock.h> 
#include <sys/signal.h>

#define  spin_lock(lock)       _spin_lock(lock)
#define  spin_unlock(lock)     _spin_unlock(lock)

int x = 0;
pthread_t thread_ctl;
pthread_t thread1;
pthread_t thread2;

//declare a spinlock for global variable
spinlock_t glb_var = SPIN_LOCK_UNLOCKED;

sigset_t set;

Asset x = 0;

void CreateOneWorker()
{
   while(x <= 20000)
   {
     spin_lock(&glb_var);
     
     x++;
     
     spin_unlock(&glb_var);
     sleep(1);
   }  
}


void TriggerallStart()
{
  int ret = 0;
  
  ret = pthread_create(&thread1, NULL, (void *)CreateOneWorker, NULL);
  if( ret !=0 )
     printf("can't create thread1");
    
  ret = pthread_create(&thread2, NULL, (void *)CreateOneWorker, NULL);
  if( ret !=0 )
     printf("can't create thread2");
  
  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);
}

void WaitAllDone()
{
    int signum;
    while(1)
    {
       if(SIGUSR1==signum)
       {  
          printf("x is 20000");
          break;
       }
    }
       
}

Assert x = 20000;


int main(void)
{
  spinlock_t spin_lock_init(&glb_var);
  
  sigemptyset(&set);
  sigaddset(&set,SIGUSR1);
  sigprocmask(SIG_SETMASK, &set, NULL);
  
  pthread_create(&thread_ctl,NULL,TriggerallStart,NULL);
  
  WaitAllDone();
  
  pthread_kill(thread_ctl,SIGUSR1);
  pthread_join(thread_ctl,NULL);
  
  return 0;
}

#include <stdio.h>   // printf
#include <pthread.h> // pthread
#include <unistd.h>  // sleep
#include <stdlib.h>  // srand
#include <time.h>    // time

#include<stdbool.h>

#include"thread.h"


bool collision_T1=false;
bool collision_T2=false;
bool collision_T3=false;



/** fonction qui va gerer les deplacements du premier train*/

void deplacement_T1() {
  int i,j;
  for(j=0;j<2;j++){
    for (i = 0; i < 4; i++) {
  
      prochain_pas_T1();
    
	pthread_rwlock_wrlock(&lock);
      
    
      printf("Train 1 est sur la voie %c %c \n",T1.liaison1,T1.liaison2);
        
      time_train_T1();
      sleep(time_T1); // on simule un traitement long
    
      pthread_rwlock_unlock(&lock);
      collision_T1=false;
    
      printf("Train 1 sort de la voie %c %c \n", T1.liaison1,T1.liaison2);
    
      
    }
    t1_i=0;
  }
  printf("Train 1 a fini\n");
}




void deplacement_T2() {
  int i,j;
  for(j=0;j<2;j++){
    for (i = 0; i < 5; i++) {
  
      prochain_pas_T2();
    
    
      pthread_rwlock_wrlock(&lock);
      
    
      printf("Train 2 est sur la voie %c %c \n",T2.liaison1,T2.liaison2);
    
      time_train_T2();
      sleep(time_T2); // on simule un traitement long
    
    
      pthread_rwlock_unlock(&lock);
      collision_T2=false;
    
      printf("Train 2 sort de la voie %c %c \n", T2.liaison1,T2.liaison2);
    
      
    }
    t2_i=0;
  }
  printf("Train 2 a fini\n");
  
}




void deplacement_T3() {
  int i,j;

  for(j=0;j<2;j++){
    for (i = 0; i < 5; i++) {
    
      prochain_pas_T3();
    
    
      pthread_rwlock_wrlock(&lock);
      
    
      printf("Train 3 est sur la voie %c %c \n",T3.liaison1,T3.liaison2);
    
      time_train_T3();
      sleep(time_T3); // on simule un traitement long
        
      pthread_rwlock_unlock(&lock);
      collision_T3=false;
    
      printf("Train 3 sort de la voie %c %c \n", T3.liaison1,T3.liaison2);
    
      
    }
    t3_i=0;
  }
  printf("Train 3 a fini\n");
  
}

/**fonction qui va gerer tous les deplacements de tous les trains*/
void* deplacement(void *arg) {
  int id = *((int*) arg);
  
  
  if(id==0)
    deplacement_T1();
  if(id==1)
    deplacement_T2();
  if(id==2)
    deplacement_T3();
	  
  return NULL;
}


int main() {
  int i, nb[3];
  pthread_t tid[3];
  
  initialise();

  pthread_rwlock_init(&lock, NULL);
    
  for(i=0;i<3;i++){
    nb[i]=i;
    pthread_create(&tid[i], NULL, deplacement,  (void*) &nb[i]);
  }
  

  for (i = 0; i < 3; i++) {
    pthread_join(tid[i], NULL);
  }

  pthread_rwlock_destroy(&lock);
  return 0;
}







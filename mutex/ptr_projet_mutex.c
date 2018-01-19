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
void deplacement_T1(){

  int i,j;
  for(j=0;j<2;j++){
    for (i = 0; i < 4; i++) {
      prochain_pas_T1();
		
		
      if(T1.liaison1==T2.liaison2 && T1.liaison2==T2.liaison1){
	collision_T1=true;
	collision_T2=true;
	printf("collision eviter\n");
      }
  
      if(T1.liaison1==T3.liaison2 && T1.liaison2==T3.liaison1){
	collision_T1=true;
	collision_T3=true;
	printf("collision eviter\n");
      }
				
      if(collision_T1==false){
		
	pthread_mutex_lock(&fifo);
	pthread_mutex_lock(&verrou_t1);
		
	pthread_mutex_unlock(&verrou_t1);
	pthread_mutex_unlock(&fifo);
		
	printf("Train 1 est sur la voie %c %c \n",T1.liaison1,T1.liaison2);
		
	time_train_T1();
	sleep(time_T1); // on simule un traitement long
		
	pthread_mutex_lock(&verrou_t1);
		
	printf("Train 1 sort de la voie %c %c \n", T1.liaison1,T1.liaison2);
		
    	pthread_mutex_unlock(&verrou_t1);
    	
		
      }
		
      else{
		
	collision_T1=false;
	
	pthread_mutex_lock(&fifo);
	pthread_mutex_lock(&verrou_t1);
	pthread_mutex_unlock(&fifo);
		
	printf("Train 1 est sur la voie %c %c \n",T1.liaison1,T1.liaison2);
	
	time_train_T1();	
	sleep(time_T1); // on simule un traitement long
		
	printf("Train 1 sort de la voie %c %c \n", T1.liaison1,T1.liaison2);
		
	pthread_mutex_unlock(&verrou_t1);
		
		
      }
		
    }
    t1_i=0;
  }
  printf("Train 1 & fini\n");
}




void deplacement_T2(){

  int i,j;
  for(j=0;j<2;j++){
    for (i = 0; i < 5; i++) {
      prochain_pas_T2();
		
		
		
		
      if(T1.liaison1==T2.liaison2 && T1.liaison2==T2.liaison1){
	collision_T1=true;
	collision_T2=true;
	printf("collision eviter\n");
      }
  
      if(T2.liaison1==T3.liaison2 && T2.liaison2==T3.liaison1){
	collision_T2=true;
	collision_T3=true;
	printf("collision eviter\n");
      }
		
		
		
		
		
      if(collision_T2==false){
		
	pthread_mutex_lock(&fifo);
	pthread_mutex_lock(&verrou_t2);
		
	pthread_mutex_unlock(&verrou_t2);
	pthread_mutex_unlock(&fifo);
		
	printf("Train 2 est sur la voie %c %c \n",T2.liaison1,T2.liaison2);
		
	time_train_T2();
	sleep(time_T2); // on simule un traitement long
		
	pthread_mutex_lock(&verrou_t2);
		
	printf("Train 2 sort de la voie %c %c \n", T2.liaison1,T2.liaison2);
		
    	pthread_mutex_unlock(&verrou_t2);
    	
		
      }
		
      else{
		
	collision_T2=false;
		
	pthread_mutex_lock(&fifo);
	pthread_mutex_lock(&verrou_t2);
	pthread_mutex_unlock(&fifo);
		
	printf("Train 2 est sur la voie %c %c \n",T2.liaison1,T2.liaison2);
		
	time_train_T2();
	sleep(time_T2); // on simule un traitement long
		
	printf("Train 2 sort de la voie %c %c \n", T2.liaison1,T2.liaison2);
		
	pthread_mutex_unlock(&verrou_t2);
		
		
      }
		
    }
    t2_i=0;
  }
  printf("Train 2 a fini\n");
}




void deplacement_T3(){

  int i,j;
  for(j=0;j<2;j++){
    for (i = 0; i < 5; i++) {
      prochain_pas_T3();
		
		
		
      if(T1.liaison1==T3.liaison2 && T1.liaison2==T3.liaison1){
	collision_T1=true;
	collision_T3=true;
	printf("collision eviter\n");
      }
  
      if(T2.liaison1==T3.liaison2 && T2.liaison2==T3.liaison1){
	collision_T2=true;
	collision_T3=true;
	printf("collision eviter\n");
      }
		
		
      if(collision_T3==false){
		
	pthread_mutex_lock(&fifo);
	pthread_mutex_lock(&verrou_t3);
		
	pthread_mutex_unlock(&verrou_t3);
	pthread_mutex_unlock(&fifo);
		
	printf("Train 3 est sur la voie %c %c \n",T3.liaison1,T3.liaison2);
		
	time_train_T3();
	sleep(time_T3); // on simule un traitement long
		
	pthread_mutex_lock(&verrou_t3);
		
	printf("Train 3 sort de la voie %c %c \n", T3.liaison1,T3.liaison2);
		
    	pthread_mutex_unlock(&verrou_t3);
    	
		
      }
		
      else{
		
	collision_T3=false;
	
	pthread_mutex_lock(&fifo);
	pthread_mutex_lock(&verrou_t3);
	pthread_mutex_unlock(&fifo);
		
	printf("Train 3 est sur la voie %c %c \n",T3.liaison1,T3.liaison2);
		
	time_train_T3();
	sleep(time_T3); // on simule un traitement long
		
	printf("Train 3 sort de la voie %c %c \n", T3.liaison1,T3.liaison2);
		
	pthread_mutex_unlock(&verrou_t3);
		
		
      }
		
    }
    t3_i=0;
  }
  printf("Train3 s'en va\n");
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
  initialise();
  pthread_t tid[3];

  for (i = 0; i < 3; i++) {
    nb[i] = i;
    pthread_create(&tid[i], NULL, deplacement, (void*) &nb[i]);
  }

  for (i = 0; i < 3; i++) {
    pthread_join(tid[i], NULL);
  }
  puts("terminé");

  pthread_mutex_destroy(&verrou_t1);
  pthread_mutex_destroy(&verrou_t2);
  pthread_mutex_destroy(&verrou_t3);
	
  pthread_mutex_destroy(&fifo);
  return 0;
}




#include <stdio.h>   // printf
#include <pthread.h> // pthread
#include <unistd.h>  // sleep
#include <stdlib.h>  // srand
#include <time.h>    // time

#include<stdbool.h>



struct train {
  char liaison1;
  char liaison2;
};

typedef struct train train;

train T1;
train T2;
train T3;

char tabT1[4][2];

char tabT2[5][2];

char tabT3[5][2];

void initialise(){

  tabT1[0][0]='A';
  tabT1[0][1]='B';

  tabT1[1][0]='B';
  tabT1[1][1]='C';

  tabT1[2][0]='C';
  tabT1[2][1]='B';

  tabT1[3][0]='B';
  tabT1[3][1]='A';



  tabT2[0][0]='A';
  tabT2[0][1]='B';

  tabT2[1][0]='B';
  tabT2[1][1]='D';

  tabT2[2][0]='D';
  tabT2[2][1]='C';

  tabT2[3][0]='C';
  tabT2[3][1]='B';

  tabT2[4][0]='B';
  tabT2[4][1]='A';



  tabT3[0][0]='A';
  tabT3[0][1]='B';

  tabT3[1][0]='B';
  tabT3[1][1]='D';

  tabT3[2][0]='D';
  tabT3[2][1]='C';

  tabT3[3][0]='C';
  tabT3[3][1]='E';

  tabT3[4][0]='E';
  tabT3[4][1]='A';


  T1.liaison1=tabT1[0][0];
  T1.liaison2=tabT1[0][1];


  T2.liaison1=tabT2[0][0];
  T2.liaison2=tabT2[0][1];


  T3.liaison1=tabT3[0][0];
  T3.liaison2=tabT3[0][1];

}



int t1_i=0;
int t1_j=0;

int t2_i=0;
int t2_j=0;

int t3_i=0;
int t3_j=0;



void prochain_pas_T1(){

  T1.liaison1=tabT1[t1_i][t1_j];
  t1_j++;
  T1.liaison2=tabT1[t1_i][t1_j];
  t1_j=t1_j-1;
    
  t1_i=t1_i+1;

}

void prochain_pas_T2(){

  T2.liaison1=tabT2[t2_i][t2_j];
  t2_j++;
  T2.liaison2=tabT2[t2_i][t2_j];
  t2_j=t2_j-1;
    
  t2_i=t2_i+1;

}

void prochain_pas_T3(){
    
  T3.liaison1=tabT3[t3_i][t3_j];
  t3_j++;
  T3.liaison2=tabT3[t3_i][t3_j];
  t3_j=t3_j-1;
    
  t3_i=t3_i+1;
}


int time_T1=0;
int time_T2=0;
int time_T3=0;

int nb_srand=0;

int time_train_T1(){

  srand(nb_srand);
  time_T1=((rand() % 3)+1);
  nb_srand=nb_srand+1;

  return 0;

}


int time_train_T2(){

  srand(nb_srand);
  time_T2=((rand() % 3)+1);
  nb_srand=nb_srand+1;

  return 0;
}



int time_train_T3(){

  srand(nb_srand);
  time_T3=((rand() % 3)+1);
  nb_srand=nb_srand+1;

  return 0;
}



pthread_mutex_t verrou_t1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t verrou_t2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t verrou_t3 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t fifo = PTHREAD_MUTEX_INITIALIZER;



bool collision_T1=false;
bool collision_T2=false;
bool collision_T3=false;


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




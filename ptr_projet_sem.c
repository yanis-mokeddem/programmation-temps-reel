#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h> // pour les semaphores

#include <unistd.h>  // sleep
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


sem_t turnT1;
sem_t turnT2;
sem_t turnT3;


void* deplacement_T1() {
  int i,j;
    	
  for(j=0;j<2;j++){
    for(i = 0; i < 4; i++) {
      prochain_pas_T1();
      
      if(T1.liaison1==T2.liaison2 && T1.liaison2==T2.liaison1){
    	printf("on evite la collision en laissant passer le 1er train qui s'engage sur la voie et en stopant le 2eme train\n");
    	sem_post(&turnT1);
    	sem_wait(&turnT2);
      }
    
    if(T1.liaison1==T3.liaison2 && T1.liaison2==T3.liaison1){
    	printf("on evite la collision en laissant passer le 1er train qui s'engage sur la voie et en stopant le 2eme train\n");
    	sem_post(&turnT1);
    	sem_wait(&turnT2);
      }
    
    
      printf("Train 1 est sur la voie %c %c \n",T1.liaison1,T1.liaison2);
      fflush(stdout);
    
    
      if(i==0&&j==0){// pour etre sur que le train 1 commence en premier
	sem_post(&turnT2);
      }
    
      if(i>=1)//parce que sinon y a plus de jeton pour T1 des le premier tour
    	sem_post(&turnT2);
    	
    
      sem_wait(&turnT1);
    
      time_train_T1();
      sleep(time_T1);
        
      printf("Train 1 sort de la voie %c %c \n", T1.liaison1,T1.liaison2);
      fflush(stdout);
    
      sem_post(&turnT2);
    
    
      sem_wait(&turnT1);
    
    
      if(i==3)//parce que T2 a une voie de plus a faire que T1 donc il doit lui donner la main
	sem_post(&turnT2);
    
    }
    t1_i=0;
  }
  printf("Train1 a fini\n");
  fflush(stdout);
  return NULL;
}


void* deplacement_T2() {
  int i,j;
    	
  sem_wait(&turnT2);// pour etre sur que le train 1 commence en premier
    
  for(j=0;j<2;j++){
    for(i = 0; i < 5; i++) {
      prochain_pas_T2();
    
      if(T1.liaison1==T2.liaison2 && T1.liaison2==T2.liaison1){
    	printf("on évite la collision en laissant passer le 1er train qui s'engage sur la voie et en stopant le 2eme train\n");
    	sem_post(&turnT1);
    	sem_wait(&turnT2);
      }
        
      if(T3.liaison1==T2.liaison2 && T3.liaison2==T2.liaison1){
    	printf("on évite la collision en laissant passer le 1er train qui s'engage sur la voie et en stopant le 2eme train\n");
    	sem_post(&turnT1);
    	sem_wait(&turnT2);
      }
        
      printf("Train 2 est sur la voie %c %c \n",T2.liaison1,T2.liaison2);
      fflush(stdout);
        
      if(i==0&&j==0){// pour etre sur que le train 2 soit tjr en 2eme position
	sem_post(&turnT3);
      }
        
      if(i>=1||j>=1)
	sem_post(&turnT3);
        
        
      sem_wait(&turnT2);
    
      time_train_T2();
      sleep(time_T2);
        
      printf("Train 2 sort de la voie %c %c \n", T2.liaison1,T2.liaison2);
      fflush(stdout);
        
      sem_post(&turnT3);
        
      if(i==4&&j==1)//si on est a la fin et qu'il ne reste plus que T2 et T3
	sem_post(&turnT2);
        	
      sem_wait(&turnT2);
    }
    t2_i=0;
  }
  printf("Train2 a fini\n");
  fflush(stdout);
  return NULL;
}

void* deplacement_T3() {
  int i,j;
    
  sem_wait(&turnT3);// pour etre sur que le train 1 commence en premier
    
  for(j=0;j<2;j++){
    for(i = 0; i < 5; i++) {
      prochain_pas_T3();
      
      if(T3.liaison1==T2.liaison2 && T3.liaison2==T2.liaison1){
    	printf("on évite la collision en laissant passer le 1er train qui s'engage sur la voie et en stopant le 2eme train\n");
    	sem_post(&turnT1);
    	sem_wait(&turnT2);
      }
      
      if(T3.liaison1==T1.liaison2 && T3.liaison2==T1.liaison1){
    	printf("on évite la collision en laissant passer le 1er train qui s'engage sur la voie et en stopant le 2eme train\n");
    	sem_post(&turnT1);
    	sem_wait(&turnT2);
      }
    
        
      printf("Train 3 est sur la voie %c %c \n",T3.liaison1,T3.liaison2);
      fflush(stdout);
        
      if(i>=3&&j==1){//quand j'arrive au dernier chemin je dois plus donner a T1 mais a T2	
        sem_post(&turnT2);
        
      }else{
        
        sem_post(&turnT1);
      }
        
      sem_wait(&turnT3);
        
      time_train_T3();
      sleep(time_T3);
        
	
      printf("Train 3 sort de la voie %c %c \n\n", T3.liaison1,T3.liaison2);
      fflush(stdout);
        
      if((i==2||i==3)&&j==1){//quand j'arrive au dernier chemin je ne dois plus donner a T1 mais a T2, a chaque fois que t1 entre puis sort direct a cause de AB BA il faut diminuer le i c'est pour ca que j'ai passer de i==3 a i==2||i==3
        sem_post(&turnT2);
        
      }else{
        sem_post(&turnT1);
      }
        
      if(i==4&&j==1)//si on est a la fin et qu'il ne reste plus que T2 et T3
	sem_post(&turnT3);
      fflush(stdout);
      sem_wait(&turnT3);
    }
    t3_i=0;
  }
  printf("Train3 a fini\n");
  fflush(stdout);
  return NULL;
}


int main() {

  initialise();

  pthread_t ID[3];
    
    
  sem_init(&turnT1, 0, 0);
  sem_init(&turnT2, 0, 0);
  sem_init(&turnT3, 0, 0);
    
    
  pthread_create(&ID[0], NULL, deplacement_T1, NULL);
  pthread_create(&ID[1], NULL, deplacement_T2, NULL);
  pthread_create(&ID[2], NULL, deplacement_T3, NULL);

  pthread_join(ID[0], NULL);
  pthread_join(ID[1], NULL);
  pthread_join(ID[2], NULL);
    
  sem_destroy(&turnT1);
  sem_destroy(&turnT2);
  sem_destroy(&turnT3);

  return 0;
}

pthread_rwlock_t lock;


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


/**fonction qui initialise le parcours dans un tableau a 2 dimensions*/

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


/** prochain pas du train 1*/
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

/** temps du train 1*/
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


void deplacement_T1();
void deplacement_T2();
void deplacement_T3();



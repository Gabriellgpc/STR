#include <BlackGPIO.h>
#include <Adc.h>
#include <unistd.h> //sleep
#include <pthread.h>
#include <stdio.h>

// #define DEBUG

using namespace BlackLib;

BlackLib::BlackGPIO trilhos_gpios[] = {BlackGPIO(GPIO_67,output), BlackGPIO(GPIO_68 ,output),
                                       BlackGPIO(GPIO_44,output), BlackGPIO(GPIO_26 ,output),
                                       BlackGPIO(GPIO_46,output), BlackGPIO(GPIO_65 ,output),
                                       BlackGPIO(GPIO_61,output), BlackGPIO(GPIO_66 ,output),
                                       BlackGPIO(GPIO_69,output), BlackGPIO(GPIO_45 ,output),
                                       BlackGPIO(GPIO_47,output), BlackGPIO(GPIO_27 ,output),
                                       BlackGPIO(GPIO_49,output), BlackGPIO(GPIO_20,output)};
ADC tremADC[] = {ADC(AINx::AIN0),
                 ADC(AINx::AIN1),
                 ADC(AINx::AIN2),
                 ADC(AINx::AIN3)};

void MoveTrem(int tremID, int trilho);
void *trem1_function(void *arg);
void *trem2_function(void *arg);
void *trem3_function(void *arg);
void *trem4_function(void *arg);
pthread_mutex_t m[5];

int main() {
    pthread_t th_trem1, th_trem2, th_trem3, th_trem4;
    int res = 0;

    for(int i = 0; i < 5; i++)
    {
      res = pthread_mutex_init(&m[i], NULL);
      if (res != 0) {
        printf("Iniciação do Mutex %d falhou", i);
        exit(EXIT_FAILURE);
      }
    }

    res = pthread_create(&th_trem1, NULL, trem1_function, NULL);
    if (res != 0) {
        perror("Criação da Thread falhou");
        exit(EXIT_FAILURE);
    }

    res = pthread_create(&th_trem2, NULL, trem2_function, NULL);
    if (res != 0) {
        perror("Criação da Thread falhou");
        exit(EXIT_FAILURE);
    }
    //
    res = pthread_create(&th_trem3, NULL, trem3_function, NULL);
    if (res != 0) {
        perror("Criação da Thread falhou");
        exit(EXIT_FAILURE);
    }

    res = pthread_create(&th_trem4, NULL, trem4_function, NULL);
    if (res != 0) {
        perror("Criação da Thread falhou");
        exit(EXIT_FAILURE);
    }


    system("clear");

    printf("\nMAIN() --> Esperando a thread terminar...\n");

    while(1){
      system("clear");
      for(int trem = 0; trem < 4; trem++)
        printf("Trem %d \t Velocidade %.2f %% \n", trem+1, tremADC[trem].getPercentValue()+1);
      sleep(1);
    }

    res = pthread_join(th_trem1, NULL);
    if (res != 0) {
        perror("Join da Thread 1 falhou");
        exit(EXIT_FAILURE);
    }

    res = pthread_join(th_trem2, NULL);
    if (res != 0) {
        perror("Join da Thread 2 falhou");
        exit(EXIT_FAILURE);
    }

    res = pthread_join(th_trem3, NULL);
    if (res != 0) {
        perror("Join da Thread 3 falhou");
        exit(EXIT_FAILURE);
    }

    res = pthread_join(th_trem4, NULL);
    if (res != 0) {
        perror("Join da Thread 4 falhou");
        exit(EXIT_FAILURE);
    }


    printf("MAIN() --> Thread foi juntada com sucesso\n");
    for(int i = 0; i < 5; i++)
      pthread_mutex_destroy(&m[i]);

    exit(EXIT_SUCCESS);
}


void
MoveTrem(int tremID, int trilho)
{
   //ascende led do trilho "trilho"
   int index;
   int index_trilho_ant;
   int trilho_anterior;

   //...
   switch (tremID) {
   case 1:
     index = trilho - tremID;
     trilho_anterior = (trilho+1)%3 + 1;
     index_trilho_ant = trilho_anterior - tremID;
     break;
   case 2:
     index = tremID + trilho;
     trilho_anterior = (trilho+2)%4 + 1;
     index_trilho_ant = tremID + trilho_anterior;
     break;
   case 3:
     index = 2*tremID + trilho;
     trilho_anterior = (trilho+1)%3 + 1;
     index_trilho_ant = 2*tremID + trilho_anterior;
     break;
   case 4:
     index = 2*tremID + trilho + 1;
     trilho_anterior = (trilho+2)%4 + 1;
     index_trilho_ant =  2*tremID + trilho_anterior + 1;
     break;
   default://ignora
     break;
   }

   trilhos_gpios[index_trilho_ant].setValue(low);
   trilhos_gpios[index].setValue(high);
#ifndef DEBUG
   usleep( ( 5000*(tremADC[tremID - 1].getPercentValue()/100.0) + 200)*1000 ); //200ms to 5000ms
#else
   sleep(1);
#endif
   // trilhos_gpios[index].setValue(low);
}

void *trem1_function(void *arg){
 while(true)
 {
   pthread_mutex_unlock(&m[4]);
   MoveTrem(1,1);
   pthread_mutex_lock(&m[0]);
   MoveTrem(1,2);
   pthread_mutex_lock(&m[4]);

   pthread_mutex_unlock(&m[0]);
   MoveTrem(1,3);
 }
}

void *trem2_function(void *arg){
while(true)
{
  pthread_mutex_unlock(&m[0]);
  MoveTrem(2,1);

  pthread_mutex_lock(&m[1]);
  MoveTrem(2,2);

  pthread_mutex_lock(&m[3]);
  pthread_mutex_unlock(&m[1]);
  MoveTrem(2,3);

  pthread_mutex_lock(&m[0]);
  pthread_mutex_unlock(&m[3]);
  MoveTrem(2,4);
}
}

void *trem3_function(void *arg){
while(true)
{
  MoveTrem(3,1);
  pthread_mutex_lock(&m[1]);

  pthread_mutex_unlock(&m[1]);
  pthread_mutex_lock(&m[2]);
  MoveTrem(3,2);

  pthread_mutex_unlock(&m[2]);
  MoveTrem(3,3);
}
}

void *trem4_function(void *arg){
  while(true)
  {
    pthread_mutex_unlock(&m[2]);
    MoveTrem(4,1);
    pthread_mutex_lock(&m[3]);
    pthread_mutex_lock(&m[4]);

    pthread_mutex_lock(&m[2]);
    MoveTrem(4,2);

    pthread_mutex_unlock(&m[4]);
    MoveTrem(4,3);

    pthread_mutex_unlock(&m[3]);
    MoveTrem(4,4);
  }
}

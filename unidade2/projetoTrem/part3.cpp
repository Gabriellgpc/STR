#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <ctime>
#include <string.h>

void L(int tremID, int trilho);
void *trem1_function(void *arg);
void *trem2_function(void *arg);
void *trem3_function(void *arg);
pthread_mutex_t m1; /*Protecao para L */
pthread_mutex_t m2;
pthread_mutex_t m3;

int main() {
    pthread_t th_trem1, th_trem2,th_trem3;
    int res = 0;

    res = pthread_mutex_init(&m1, NULL);
    if (res != 0) {
        perror("Iniciação do Mutex 1 falhou");
        exit(EXIT_FAILURE);
    }

    res = pthread_mutex_init(&m2, NULL);
    if (res != 0) {
        perror("Iniciação do Mutex 2 falhou");
        exit(EXIT_FAILURE);
    }

    res = pthread_mutex_init(&m3, NULL);
    if (res != 0) {
        perror("Iniciação do Mutex 3 falhou");
        exit(EXIT_FAILURE);
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

    res = pthread_create(&th_trem3, NULL, trem3_function, NULL);
    if (res != 0) {
        perror("Criação da Thread falhou");
        exit(EXIT_FAILURE);
    }


    system("clear");

    printf("\nMAIN() --> Esperando a thread terminar...\n");
    res = pthread_join(th_trem1, NULL);
    if (res != 0) {
        perror("Jun��o da Thread 1 falhou");
        exit(EXIT_FAILURE);
    }

    res = pthread_join(th_trem2, NULL);
    if (res != 0) {
        perror("Jun��o da Thread 2 falhou");
        exit(EXIT_FAILURE);
    }

    printf("MAIN() --> Thread foi juntada com sucesso\n");
    pthread_mutex_destroy(&m1);
    exit(EXIT_SUCCESS);
}


void L(int tremID, int trilho){
   printf("Sou o trem %d e estou no trilho %d\n", tremID, trilho);
   fflush(stdout);
}

void *trem1_function(void *arg){
 while(true)
 {
   L(1,1);
   sleep(1);
   L(1,2);
   sleep(1);
   pthread_mutex_lock(&m1);
   L(1,3);
   sleep(1);
   pthread_mutex_unlock(&m1);
 }
}

void *trem2_function(void *arg){
while(true)
{
   pthread_mutex_lock(&m2);
   L(2,5);
   sleep(1);
   pthread_mutex_unlock(&m2);
   L(2,6);
   sleep(1);
   pthread_mutex_lock(&m1);
   L(2,7);
   sleep(1);
   pthread_mutex_unlock(&m1);
   L(2,8);
   sleep(1);
}
}

void *trem3_function(void *arg){
while(true)
{
   L(3,9);
   sleep(1);
   L(3,10);
   sleep(1);
   pthread_mutex_lock(&m2);
   L(3,11);
   sleep(1);
   pthread_mutex_unlock(&m2);
   L(3,12);
   sleep(1);
}
}

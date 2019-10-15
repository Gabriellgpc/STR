#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <ctime>
#include <string.h>

void L(int tremID, int trilho, int s);
void *trem1_function(void *arg);
void *trem2_function(void *arg);
pthread_mutex_t m1; /*Protecao para L */
pthread_mutex_t m2; 

int main() {
    pthread_t th_trem1, th_trem2;
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
	
    pthread_mutex_lock(&m2);

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


void L(int tremID, int trilho, int s){
   printf("Sou o trem %d e estou no trilho %d\n", tremID, trilho); 
   fflush(stdout);
   sleep(s);		
}

void *trem1_function(void *arg){
 while(true)
 {
   L(1,1,1);
   L(1,2, 1);
   pthread_mutex_lock(&m1);
   L(1,3,8);
   pthread_mutex_unlock(&m2);
   L(1,4,1);
 }
}


void *trem2_function(void *arg){
while(true)
{
   L(2,5,1);
   L(2,6,1);
   pthread_mutex_lock(&m2);
   L(2,7,1);
   pthread_mutex_unlock(&m1);
   L(2,8,1);
}
}

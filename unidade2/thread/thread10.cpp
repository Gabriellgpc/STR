//
//  thread10.cpp
//  
//
//  Created by Affonso on 24/10/17.
//

// #include "thread10.hpp"

// http:pubs.opengroup.org/onlinepubs/7908799/xsh/sem_post.html

// programa thread10.cpp
// Programa que sincroniza threads utilizando-se semáforos
// Para compilá-lo utilise: g++ -o thread10 thread10.cpp -lpthread

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <semaphore.h>

void *thread_function(void *arg);
sem_t bin_sem;

#define WORK_SIZE 1024
char work_area[WORK_SIZE];

int main() {
    int res;
    pthread_t a_thread;
    void *thread_result;
    
    res = sem_init(&bin_sem, 0, 0);
    if (res != 0) {
        perror("Semaphore initialization failed");
        exit(EXIT_FAILURE);
    }
    res = pthread_create(&a_thread, NULL, thread_function, NULL);
    if (res != 0) {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }
    printf("MAIN() --> Entre com texto. Digite 'fim' para terminar\n");
    while(strncmp("fim", work_area, 3) != 0) {
        fgets(work_area, WORK_SIZE, stdin);
        sem_post(&bin_sem);
    }
    printf("\nMAIN()--> Aguardando a THREAD terminar...\n");
    res = pthread_join(a_thread, &thread_result);
    if (res != 0) {
        perror("Thread join failed");
        exit(EXIT_FAILURE);
    }
    printf("MAIN() --> A THREAD terminou\n");
    sem_destroy(&bin_sem);
    exit(EXIT_SUCCESS);
}

void *thread_function(void *arg) {
    sem_wait(&bin_sem);
    while(strncmp("fim", work_area, 3) != 0) {
        printf("THREAD() --> Sua entrada tem  %lu caracteres\n", strlen(work_area) -1);
        sem_wait(&bin_sem);
    }
    printf("THREAD() --> THREAD terminando ..\n");
    pthread_exit(NULL);
}

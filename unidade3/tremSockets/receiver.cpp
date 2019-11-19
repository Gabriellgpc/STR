//
//  servidor_multicast.cpp
//  str
//
//  Created by Affonso on 18/05/16.
//  Copyright © 2016 Affonso. All rights reserved.
//

// #include "servidor_multicast.hpp"

// programa servidor_multicast.cpp - Servidor que lê e escreve em um vetor de caracter
// Protocolo UDP

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

#include <BlackGPIO.h>
#include <Adc.h>
#include <pthread.h>

#define MULTICAST_ADDR "225.0.0.37"
#define PORT 9734
float vec_float[4] = {0.0};


using namespace BlackLib;

BlackLib::BlackGPIO trilhos_gpios[] = {BlackGPIO(GPIO_67,output), BlackGPIO(GPIO_68 ,output),
                                       BlackGPIO(GPIO_44,output), BlackGPIO(GPIO_26 ,output),
                                       BlackGPIO(GPIO_46,output), BlackGPIO(GPIO_65 ,output),
                                       BlackGPIO(GPIO_61,output), BlackGPIO(GPIO_66 ,output),
                                       BlackGPIO(GPIO_69,output), BlackGPIO(GPIO_45 ,output),
                                       BlackGPIO(GPIO_47,output), BlackGPIO(GPIO_27 ,output),
                                       BlackGPIO(GPIO_49,output), BlackGPIO(GPIO_20,output)};

void MoveTrem(int tremID, int trilho);
void *trem1_function(void *arg);
void *trem2_function(void *arg);
void *trem3_function(void *arg);
void *trem4_function(void *arg);
pthread_mutex_t m[5];


int main( )
{
    int server_sockfd;
    size_t server_len;
    socklen_t client_len;
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;
    struct ip_mreq mreq;  // para endere�o multicast

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


    if ( (server_sockfd = socket(AF_INET, SOCK_DGRAM, 0) )  < 0  )  // cria um novo socket
    {
        printf(" Houve erro na ebertura do socket ");
        exit(1);
    }
    printf("%d\n",server_sockfd);
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(PORT);


    server_len = sizeof(server_address);

    if(  bind(server_sockfd, (struct sockaddr *) &server_address, server_len) < 0 )
    {
        perror("Houve error no Bind");
        exit(1);
    }

    mreq.imr_multiaddr.s_addr=inet_addr(MULTICAST_ADDR);
    mreq.imr_interface.s_addr=htonl(INADDR_ANY);
    int code;
    if (code = setsockopt(server_sockfd,IPPROTO_IP,IP_ADD_MEMBERSHIP,&mreq,sizeof(mreq)), code < 0) {
        perror("setsockopt");
	printf("codigo do erro = %d\n",code);
        exit(1);
    }
    printf(" IPPROTO_IP = %d\n", IPPROTO_IP);
    printf(" SOL_SOCKET = %d\n", SOL_SOCKET);
    printf(" IP_ADD_MEMBERSHIP = %d \n", IP_ADD_MEMBERSHIP);



    while(1){
        client_len = sizeof(client_address);
        if(recvfrom(server_sockfd, vec_float, 4*sizeof(float), 0,
                    (struct sockaddr *) &client_address, &client_len) < 0 )
        {
            perror(" erro no RECVFROM( )");
        }
    }

    return 0;
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
   usleep( ( 5000 - 5000*(vec_float[tremID-1]) + 200)*1000 ); //200ms to 5000ms
#else
   sleep(1);
#endif
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

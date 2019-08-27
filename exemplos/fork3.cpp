

// UFRN-CT-DCA
// Disciplina: Sistemas Operacionais
// Programa: fork2.c
// Objetivo: utilizar as funções getpid() e getppid()

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int main ()
{

// declaração de variáveis
  pid_t pid;          // definindo um identificador de processo - inteiro longo 
  pid_t pai = getpid();
  pid_t pid_filho;
  unsigned int sec = 0;
  unsigned int end = 10;  
 
  printf("Começando o programa fork3 ... \n");
  system("ps");  // tente ps -aux, ps -auf
  sleep(2);
  
	
  while(sec != end){
     
     if(sec == 5 && getpid() == pai){
        pid = fork();
        
        if(pid == 0){
	    end = sec+13;
            pid_filho = getpid();
        }
     }
    
    if(sec == 8 && getpid() == pai){
         pid = fork();
        
        if(pid == 0)
	    end = sec+7;
    }

    if(sec == 11 && getpid() == pid_filho) //aqui o pai de todos ja morreu!
    {
       pid = fork();
       if(pid == 0)
           end = sec+9;       
    }
    
      	
    printf("Sou o processo %d pid_filho de %d e tenho %d segundos de vida\n", getpid(), getppid(), sec);
    sleep(1);
    sec++;     	
  }

  printf("Sou o processo %d pid_filho de %d e tenho %d segundos de vida E agora vou morrer!!\n", getpid(), getppid(), sec); 	

  exit (0);

}

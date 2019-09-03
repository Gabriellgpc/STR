// UFRN-CT-DCA
// Disciplina: Sistemas Operacionais
// Programa matatdor.cpp
// Sinais sã eventos gerados pelo Unix em resposta a algumas condições, como:
//  erros, violação de memória, instrução ilegal, ...

#include <signal.h> // definição dos sinais de interrupções
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> // system()
#include <iostream>

using namespace std;

int  main()
{
  // o processo que vai matar

  int meu_pid;
  int pid_vitima;
  int opcao;

  meu_pid = getpid();
    
  
 printf( "Eu sou um programa matador de programa meu PID é %d\n", meu_pid );
  

 while(true) 
 {
 	system("clear");
	cout << "Opcoes\n";
	cout << "0 - Matar Processo\n";
	cout << "1 - Pausar Processo\n";
	cout << "2 - Continuar Processo\n";
    cin >> opcao;

	cout << "informe o PID do processo Alvo:";
	cin >> pid_vitima;


	switch(opcao){
		case 0://matar
			kill(pid_vitima, SIGKILL);
		break;
		case 1://pausar
			kill(pid_vitima, SIGSTOP);
		break;
		case 2://contiuar
			kill(pid_vitima, SIGCONT);
		break;
		defult:
		break;
	}

	
 }

 exit(0);
}


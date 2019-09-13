// UFRN-CT-DCA
// Disciplina: Sistemas de Tempo Real


#include <time.h>
#include <iostream> // para: cout
#include <stdio.h>
#include <unistd.h>  // para: sleep()
#include <stdlib.h>
#include <math.h>
#include <sys/resource.h>
#include <sched.h>  // sched_setaffinity

using namespace std;

// função para simular carregamento da CPU
void carga(int k)
{
  float f = 0.999999;
  for(int i=0; i<k; i++)
    {
      f = f*f*f*f*f;
      f = 1.56;
        for(int j=0; j<k; j++)
           {
	     f = sin(f)*sin(f)*f*f*f;

            }
    }

}


int main(int argc, char** argv){
     clock_t time_1, time_2;
     time_t  real_time_1, real_time_2, delta_real_time;
	 cpu_set_t mask;
    
     int saida;
     double saida2;

	 if(argc != 2){
		 std::cerr << "Passa a prioridade ai !!\n";
		 exit(-1);
	 }
	
	 CPU_ZERO(&mask);
	 CPU_SET(0, &mask);
	 nice( atoi(argv[1]));

	if(sched_setaffinity(0,sizeof(mask), &mask) != 0){
		std::cerr << "CPU set Affinity falhou!\n";
		exit(-1);
	}   

    //  Parte do código associada com uso intenso de CPU : início
    //
    //  --------------------------------------------------------------------------------
    
     time_1 = clock();
     real_time_1 = time(0);
     carga(10000);       // funcão de uso intenso de CPU
     real_time_2 = time(0);
     time_2 = clock();

    
    saida = (int) (time_2) - (time_1);  // tempo de CPU
    saida2 = (double) ((saida) / (double) CLOCKS_PER_SEC) ;
    delta_real_time = (real_time_2) - (real_time_1);
    
    printf("\n Tempo de uso da CPU em microsegundos: %d \n", saida);
    printf(" Tempo de uso da CPU em segundos: %f \n", saida2);
    printf(" Tempo Real decorrido em microsegundos: %d \n", (int) delta_real_time);
    cout << "\n\n  valor da prioridade do processo - final: " << getpriority(PRIO_PROCESS, 0 ) <<endl;
    
    // ---------------------------------------------------------------------------------
    //
    //  Parte do código associada com uso intenso de CPU : fim
    //
    //  --------------------------------------------------------------------------------
    
    
    exit(1);

}


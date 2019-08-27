
// UFRN-CT-DCA
// Disciplina: Sistemas de Tempo Real
// Programa: tempomicro.c

#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <sched.h>  // sched_setaffinity


int main(int argc, char** argv) {
    cpu_set_t mask;
    int i, j;
    struct timeval tempo_inicial, tempo_final;
    int tmili;

    CPU_ZERO(&mask);
	CPU_SET(atoi(argv[1]),&mask);
    
	if(sched_setaffinity(0,sizeof(mask), &mask) != 0){
       perror("Falhou!\n");
	}

    gettimeofday(&tempo_inicial, NULL);  // inicio é uma struct com dois campos:tv_sec e tv_usec.
    
     /* Substitua o for a seguir pelo trecho de código
       cujo tempo de execução deverá ser medido. */
    
    for (j = 0; j < 10; j ++)
        for (i = 0; i < 1387634300; i ++);
    
    gettimeofday(&tempo_final, NULL);
    tmili = (int) (1000 * (tempo_final.tv_sec - tempo_inicial.tv_sec) + (tempo_final.tv_usec - tempo_inicial.tv_usec) / 1000); // para transformar em milissegundos

    printf("tempo decorrido: %d milissegundos\n", tmili);
    return (0);
}

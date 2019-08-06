#include <iostream>
#include <cstdio>
#include <ctime>

#define CLOCKS_PER_MS (CLOCKS_PER_SEC/1000)

//Vetores usados pelos métodos de ordenação
int *vetorQuickSort;
int *vetorBubbleSort;
int tamanho;

//Função usada pelo qsort para comparar dois numeros
int compare_ints( const void* a, const void* b ) {
	int* arg1 = (int*) a;
	int* arg2 = (int*) b;
	if( *arg1 < *arg2 ) return -1;
	else if( *arg1 == *arg2 ) return 0;
	else return 1;
}

//Algoritmos de ordenação bubble sort
void bubbleSort(int *vetor, int tamanho) {
	int aux;
	for (int i = 0; i < tamanho-1; i++) {
		for (int j = 0; j < tamanho-1-i; j++) {
			if (vetor[j] > vetor[j+1]) {
				aux = vetor[j];
				vetor[j] = vetor[j+1];
				vetor[j+1] = aux;
			}
		}
	}
}


//Observe que os números são gerados aleatoriamente baseados
//em uma semente. Se for passado a mesma semente, os 
//números aleatórios serão os mesmos
void criarVetor(int tamanhoVetor, int semente){
	srand(semente);
	vetorQuickSort = new int[tamanhoVetor];
	vetorBubbleSort = new int[tamanhoVetor];
	for (int i=0;i<tamanhoVetor;i++){
		vetorQuickSort[i] =  rand()%100000;
        vetorBubbleSort[i] = vetorQuickSort[i]; // utilizar os mesmos valores
		//vetorBubbleSort[i] = rand()%100000;
	}
}

//|  N   | Bubble | QSort |
//|1000  |        |       |
//|5000  |        |       |
//|10000 |        |       |
//|50000 |        |       |
//|100000|        |       |

#define M 5
void mostraTabela(int n[],int tq[],int tb[]){
	printf("|   N   | Bubble | Qsort |\n");
	
	for(int i=0;i<M;i++){
		printf("| %d | %d | %d |\n",n[i],tb[i],tq[i]);
	}

}

int main(){
	int n[] = {1000,5000,10000,50000,100000};	  
	int tq[5];	
	int tb[5];	
	clock_t t,t2;	

	int sem = time(0);
	

	printf("|   N   | Bubble | Qsort |\n");
	for(int i=0;i<M;i++){
		criarVetor(n[i],sem); 

		t = clock();	
		bubbleSort(vetorBubbleSort,n[i]);			
		t2 = clock();
		tb[i] =	(t2 - t)/CLOCKS_PER_MS;

		t = clock();	
		qsort(vetorQuickSort,n[i],sizeof(int),compare_ints);			
		t2 = clock();
		tq[i] =	(t2 - t)/CLOCKS_PER_MS;
		printf("| %d | %d | %d |\n",n[i],tb[i],tq[i]);

	} 
	
	//tabela
	//mostraTabela(n,tq,tb);

	return 0;
}

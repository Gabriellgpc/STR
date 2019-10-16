#include <BlackGPIO.h>
#include <Adc.h>
#include <unistd.h> //sleep
#include <time.h>
#include <pthread.h>
#include <stdio.h>


using namespace BlackLib;

BlackLib::BlackGPIO trilhos_gpios[] = {BlackGPIO(GPIO_67,output), BlackGPIO(GPIO_68,output), BlackGPIO(GPIO_44,output), BlackGPIO(GPIO_26,output), BlackGPIO(GPIO_46,output), BlackGPIO(GPIO_65,output),
                                      BlackGPIO(GPIO_61,output), BlackGPIO(GPIO_66,output), BlackGPIO(GPIO_69,output), BlackGPIO(GPIO_45,output), BlackGPIO(GPIO_47,output), BlackGPIO(GPIO_27,output)};
ADC tremADC[] = {ADC(AINx::AIN1), ADC(AINx::AIN3), ADC(AINx::AIN5)};

void MoveTrem(int tremID, int trilho);
void *trem1_function(void *arg);
void *trem2_function(void *arg);
void *trem3_function(void *arg);
pthread_mutex_t m1; /*Protecao para L */
pthread_mutex_t m2;

unsigned usecs(unsigned vel){
	return 3000000 - 30000*vel;	
}
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

	//Monitorar ADC
	while(1){
		system("clear");
		printf("ADC Trem 1: %f -> sleep:%dms\n",tremADC[0].getPercentValue(),usecs(tremADC[0].getPercentValue())/1000);
		printf("ADC Trem 2: %f -> sleep:%dms\n",tremADC[1].getPercentValue(),usecs(tremADC[1].getPercentValue())/1000);
		printf("ADC Trem 3: %f -> sleep:%dms\n",tremADC[2].getPercentValue(),usecs(tremADC[2].getPercentValue())/1000);

	}

    printf("\nMAIN() --> Esperando a thread terminar...\n");
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
    printf("MAIN() --> Thread foi juntada com sucesso\n");
    pthread_mutex_destroy(&m1);
    exit(EXIT_SUCCESS);
}

void MoveTrem(int tremID, int trilho){
	//ascende led do trilho "trilho"
	int trilho_anterior;	

	if(trilho%4==0)	
		trilho_anterior = trilho + 3;
	else
		trilho_anterior = trilho - 1;
	
	trilhos_gpios[trilho_anterior].setValue(low);
	trilhos_gpios[trilho].setValue(high);
	usleep(usecs(tremADC[tremID].getPercentValue()));
	//trilhos_gpios[trilho-1].setValue(low);
}


void *trem1_function(void *arg){
 while(true)
 {
   MoveTrem(0,0);
   MoveTrem(0,1);
   pthread_mutex_lock(&m1);
   MoveTrem(0,2);
   pthread_mutex_unlock(&m1);
   MoveTrem(0,3);
 }
}

void *trem2_function(void *arg){
while(true)
{
   pthread_mutex_lock(&m1);
   MoveTrem(1,4);
   pthread_mutex_unlock(&m1);
   MoveTrem(1,5);
   pthread_mutex_lock(&m2);
   MoveTrem(1,6);
   pthread_mutex_unlock(&m2);
   MoveTrem(1,7);
}
}

void *trem3_function(void *arg){
while(true)
{
   pthread_mutex_lock(&m2);
   MoveTrem(2,8);
   pthread_mutex_unlock(&m2);
   MoveTrem(2,9);
   MoveTrem(2,10);
   MoveTrem(2,11);
}
}

#include <BlackGPIO.h>
#include <Adc.h>
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <math.h>

using namespace BlackLib;
using std::cout;

#define K 1000

void carga(){
	float f = 0.999999;
	for(int i = 0; i < K; i++)
	{
		f = f*f*f*f*f;
		for(int j = 0; j < K; j++)
		{
			f = sin(f)*sin(f)*f*f*f;
		}
	}
}

void led_ctrl(BlackGPIO &led){ 
	while(1){
		led.setValue(high);
		carga();
		led.setValue(low);
		carga();
	}
}

int main(){
	pid_t filhos[2]={1,1};
	pid_t pai = getpid();
	filhos[0] = fork();

	if(getpid() == pai){
		filhos[1] = fork();
	}
	if(filhos[0] == 0){
		BlackGPIO led = BlackGPIO(GPIO_26, output);
		led_ctrl(led);
	}
	else if(filhos[1] == 0){
		BlackGPIO led = BlackGPIO(GPIO_46, output);
		led_ctrl(led);
	}
	else{
		ADC adc0(AINx::AIN4);
		ADC adc1(AINx::AIN1);
		
		setpriority(PRIO_PROCESS, 0, -20);

		while(true){
			std::cout << "processo Pai : " << pai << "\n";
			std::cout << "processos filhos : " << filhos[0] << " e "  << filhos[1] << "\n";

			float a0 = adc0.getPercentValue();
			float a1 = adc1.getPercentValue();
				
			setpriority(PRIO_PROCESS, filhos[0], (int)(19*a0/100.0));
			setpriority(PRIO_PROCESS, filhos[1], (int)(19*a1/100.0));

			std::cout << "a0 = "  << a0 << std::endl;
			std::cout << "a1 = " << a1 << std::endl;
			sleep(1);
			system("clear");
			
		}
	}

		

	return 0;
}


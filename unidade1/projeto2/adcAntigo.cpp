#include <iostream>
#include <stdlib.h>
#include <Adc.h>

int main(){
	ADC adc0(AINx::AIN4);
	ADC adc1(AINx::AIN1);

	while(true){
		float a0 = adc0.getPercentValue();
		float a1 = adc1.getPercentValue();

		std::cout << "a0 = "  << a0 << std::endl;
		std::cout << "a1 = " << a1 << std::endl;
		system("clear");
	}
	return 0;
}

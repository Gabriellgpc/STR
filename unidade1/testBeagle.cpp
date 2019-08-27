#include <BlackGPIO.h>
#include <iostream>

using namespace BlackLib;
using namespace std;

int main(){
   BlackGPIO pin(GPIO_67,input);
   
   while(true){
     cout << "IN:" << pin.getNumericValue() << '\n';		

   }

	return 0;
}

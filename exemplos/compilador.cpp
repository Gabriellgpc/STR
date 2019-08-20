#include <stdlib.h>
#include <stdio.h>

int main (){
	system("g++ sistema2.cpp -o sistema2");
	system("./sistema2 &");
    system("ps");
    
	exit (0);
}



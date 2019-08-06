
#include <iostream> // para: cout
#include <time.h>   // para: time()
#include <unistd.h>
#include <stdlib.h>



using std::cout;
using std::cin;


int main ( )
{

  time_t t1,t2;
  
  int numero;
  int dTempo;	

  t1 = time( (time_t *) 0);  // apontando o ponteiro para null.
  
  // printf(" Com printf: %ld \n", tempo_real);
    for(int i=0; i< 1000000; i++)for(int k=0; k<1000;k++);
    
    
  t2 = time( (time_t *) 0);  // apontando o ponteiro para null.
    
  cout << "Delta T " << t2 - t1 << '\n';   

  exit(0);
}


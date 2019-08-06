
/////\// UFRN-CT-DCA
// Disciplina: Sistemas Operacionais
// Programa: sleep.c


#include <iostream> // para: cout
#include <stdio.h>
#include <unistd.h> // para: sleep()
#include <time.h>

using std::cout;

//using namespace std;


int main ( )
{

  double x = 1;
  time_t t1,t2;	
    
  //usleep(1000);
  sleep(1);
  cout << "passei. levou 2 segundos" << '\n';
  t1 = time((time_t*)0);
  for(int i=0; i<5; i++) {
    sleep(i);
    cout << "teste "  << i <<'\n';   
  }
  t2 = time((time_t*)0);

  cout << "Tempo gasto: " << t2-t1 << '\n';
  return(0);
}


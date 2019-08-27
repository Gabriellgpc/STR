#include <BlackGPIO.h>
#include <iostream>
// #include <time>
#include <sys/time.h>
#include <stdlib.h>     /* srand, rand */
#include <unistd.h>


#define LED0_PIN GPIO_67
#define LED1_PIN GPIO_68
#define BUTTON0_PIN GPIO_44
#define BUTTON1_PIN GPIO_26

#define TIME 30.0
#define N 2

using namespace BlackLib;
using std::cout;

double timer(void);

int main(){
  unsigned int hits = 0;
  unsigned int miss = 0;
  unsigned int mole;
  time_t start;
  time_t sec = 0;
  time_t ledsec_start = 0;
  BlackGPIO led[N] = {BlackGPIO(LED0_PIN, output),  BlackGPIO(LED1_PIN, output)};
  BlackGPIO button[N] = {BlackGPIO(BUTTON0_PIN, input),  BlackGPIO(BUTTON1_PIN, input)};

  cout << "ONLINE!\n";
  start = timer();

  srand(time(NULL));
  while(sec <= TIME){
    miss ++;
    mole = rand()%N;
    cout << "MOLE:" << mole << std::endl;
    led[mole].setValue(high);

    ledsec_start = timer();
    while(timer() - ledsec_start < 2.0){
      if(button[mole].getNumericValue() == 0){
        hits++;
        cout << "HIT!!\n";
        break;
      }
    }
    led[mole].setValue(low);
    sleep(1);

    sec = timer() - start;
    printf("Tempo:%d segundos Hits:%d\n", sec, hits);
  };

  cout << "ACABOU SEU TEMPO!\n";
  printf("Hits:%d, MISS:%d\n", hits, miss-hits);

  return 0;
}

double timer(void)
{
  static struct timeval tbase={-1,-1};
  struct timeval t;

  gettimeofday(&t,NULL);
  if (tbase.tv_sec==-1 && tbase.tv_usec==-1)
  {
    tbase = t;
  }
  return( t.tv_sec-tbase.tv_sec + (t.tv_usec-tbase.tv_usec)/1000000.0 );
}

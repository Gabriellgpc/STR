#include <BlackGPIO.h>
#include <iostream>
// #include <time>
#include <sys/time.h>
#include <stdlib.h>     /* srand, rand */
#include <unistd.h>

using namespace BlackLib;
using std::cout;

/* ======= DEFINES  ===== */

BlackLib::gpioName leds_gpios[] =    {GPIO_44,GPIO_67,GPIO_46,GPIO_61,GPIO_66,GPIO_45};
BlackLib::gpioName buttons_gpios[] = {GPIO_68,GPIO_26,GPIO_65,GPIO_69,GPIO_20,GPIO_60};

//#define TIME 30.0
#define N 6

double timer(void);

int main(int argc, char **argv){
  unsigned int hits = 0;
  unsigned int miss = 0;
  unsigned int mole;
  time_t t_game;
  time_t start;
  time_t sec = 0;
  time_t t_wait; 
  double ledsec_start = 0;
  double t_hold;
  
  if(argc != 4){
	  perror("PASSE US ARGUMETU\n");
	  exit(1);
 }
  t_hold = atof(argv[1]);
  t_wait = atoi(argv[2]);
  t_game = atoi(argv[3]);


  BlackGPIO led[] = 	{ BlackGPIO(leds_gpios[0], output),
						  BlackGPIO(leds_gpios[1], output),
						  BlackGPIO(leds_gpios[2], output),
						  BlackGPIO(leds_gpios[3], output),
						  BlackGPIO(leds_gpios[4], output),
						  BlackGPIO(leds_gpios[5], output)};

  BlackGPIO button[] = { BlackGPIO(buttons_gpios[0], input),
						  BlackGPIO(buttons_gpios[1], input),
						  BlackGPIO(buttons_gpios[2], input),
						  BlackGPIO(buttons_gpios[3], input),
						  BlackGPIO(buttons_gpios[4], input),
						  BlackGPIO(buttons_gpios[5], input)};

  cout << "ONLINE!\n";
  start = timer();

  srand(time(NULL));
  while(sec <= t_game){
    miss ++;
    mole = rand()%N;
    cout << "MOLE:" << mole << std::endl;
    led[mole].setValue(high);

    ledsec_start = timer();
    while(timer() - ledsec_start < t_hold){
      if(button[mole].getNumericValue() == 1){
        hits++;
        cout << "HIT!!\n";
        break;
      }
    }
    led[mole].setValue(low);
    usleep(t_wait * 1000); 
    //usleep(t_wait); 


    sec = timer() - start;
    printf("Tempo:%d segundos Hits:%d\n", sec, hits);
  };

  cout << "ACABOU SEU TEMPO!\n";
  printf("Hits:%d, MISS:%d\n", hits, miss-hits);

  return 0;
}

/* ======= FUNCOES   ===== */

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

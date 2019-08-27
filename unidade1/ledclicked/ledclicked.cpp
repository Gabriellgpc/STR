#include <BlackGPIO.h>
#include <iostream>
// #include <time>
#include <sys/time.h>
#include <stdlib.h>     /* srand, rand */
#include <unistd.h>

using namespace BlackLib;
using namespace std;

#define TIME 25

/* ======= DEFINES  ===== */

BlackLib::gpioName leds_gpios[] =    {GPIO_44,GPIO_67,GPIO_46,GPIO_61,GPIO_66,GPIO_45};
BlackLib::gpioName buttons_gpios[] = {GPIO_68,GPIO_26,GPIO_65,GPIO_69,GPIO_20,GPIO_60};

static BlackGPIO led[] = 	{ BlackGPIO(leds_gpios[0], output),
						  			  BlackGPIO(leds_gpios[1], output),
						  			  BlackGPIO(leds_gpios[2], output),
						  	 	      BlackGPIO(leds_gpios[3], output),
						  			  BlackGPIO(leds_gpios[4], output),
						  	 	      BlackGPIO(leds_gpios[5], output)};

static BlackGPIO button[] = { BlackGPIO(buttons_gpios[0], input),
						  			   BlackGPIO(buttons_gpios[1], input),
						  	  	 	   BlackGPIO(buttons_gpios[2], input),
						  		       BlackGPIO(buttons_gpios[3], input),
						  			   BlackGPIO(buttons_gpios[4], input),
						  			   BlackGPIO(buttons_gpios[5], input)};


double timer(void);
void menu();
void game(double t_hold, time_t t_wait, time_t t_game);

int main(int argc, char **argv){
  unsigned int k;  


  while(1){
    menu();
	cin >> k;
    
	switch(k){
    case 0: //facil
		game(2.0, 500, TIME);
    break;
	case 1: //medio
		game(1.0, 50, TIME);
    break;
	case 2: //dificil
		game(0.5, 50, TIME);
    break; 
	case 3: //insano
		game(0.3, 50, TIME);
    break;
	case 4: //aventura
		game(0.3, 50, TIME);
    break;
	case 5: //sair
		cout << "Vlw, flws!\n";
		exit(0);
	break;
	default:
	break;
	}

  }


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

void game(double t_hold, time_t t_wait, time_t t_game)
{
  #define N 6

  unsigned int hits = 0;
  unsigned int miss = 0;
  unsigned int mole;
  time_t start;
  time_t sec = 0;
  double ledsec_start = 0;
  
  start = timer();

  srand(time(NULL));
  while(sec <= t_game){
    miss ++;
    mole = rand()%N;
    led[mole].setValue(high);

    ledsec_start = timer();
    while(timer() - ledsec_start < t_hold){
      if(button[mole].getNumericValue() == 1){
        hits++;
        break;
      }
    }
    led[mole].setValue(low);
    usleep(t_wait * 1000);  

    sec = timer() - start;
  };
  printf("Hits:%d, MISS:%d\n", hits, miss-hits);
}

void menu(){
	cout << "LEDCLICKED ON\n";

    cout << "Escolha!:\n";
	cout << "0 - Modo Facil\n";
	cout << "1 - Modo Medio\n";
	cout << "2 - Modo Dificil\n";
	cout << "3 - Modo Insano\n";
	cout << "4 - Modo Aventura\n";
	cout << "5 - Sair\n";
}

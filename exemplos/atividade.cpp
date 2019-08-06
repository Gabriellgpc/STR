#include <iostream> //cout
#include <time.h>   //para: gmtime()
using namespace std;

int main ()
{
  time_t timer;
  struct tm data_nascimento, *data_atual;
  int seconds;
  data_nascimento.tm_hour = 7;   data_nascimento.tm_min = 30; data_nascimento.tm_sec = 0;
  data_nascimento.tm_year = 92; data_nascimento.tm_mon = 6; data_nascimento.tm_mday = 22;

  time(&timer);  
  data_atual = gmtime(&timer);

  seconds = difftime(timer,mktime(&data_nascimento));
  cout << "Se passaram " << seconds << " segundos desde :\n" ;
  cout << data_atual->tm_mday << "/" << data_atual->tm_mon+1 << "/" << data_atual->tm_year+1900 << "\t" << data_atual->tm_hour << ":" << data_atual->tm_min << ":" << data_atual->tm_sec << "\n";
  cout << "até \n";
  cout << data_nascimento.tm_mday << "/" << data_nascimento.tm_mon+1 << "/" << data_nascimento.tm_year+1900 << "\t" << data_nascimento.tm_hour << ":" << data_nascimento.tm_min << ":" << data_nascimento.tm_sec << "\n";  
  

  return 0;
}
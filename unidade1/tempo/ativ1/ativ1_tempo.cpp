#include <iostream> //cout, cerr
#include <ctime>   // para: time_t, struct tm, time, mktime
#include <cstring>   // std::string, std::stoi

using std::cout;
using std::stoi;

//Entrada no formato: DD MM AAAA HH MM SS
int main(int argc, char**argv)
{
  time_t currentTime, birthTime;
  struct tm tm_info;
  memset(&tm_info, 0, sizeof(tm_info)); //limpar a estrutura

  if(argc < 3){
    std::cerr << "Entrada Invalida" << '\n';
    return -1;
  }

  tm_info.tm_mday = stoi(argv[1]);
  tm_info.tm_mon  = stoi(argv[2]) - 1;
  tm_info.tm_year = stoi(argv[3]) - 1900;

  if(argc > 4){
    tm_info.tm_hour = stoi(argv[4]);
    tm_info.tm_min = stoi(argv[5]);
  }

  birthTime = mktime(&tm_info);
  time(&currentTime);

  std::cout <<"Tempo Decorrido:"<<currentTime - birthTime <<" s\n";

  return 0;
}

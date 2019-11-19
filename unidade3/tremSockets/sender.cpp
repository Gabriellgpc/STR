
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>


#define MULTICAST_ADDR "225.0.0.37"
#define PORT  9734
#define PERIODIC_TIME 1
//#define POT_MODE

// using namespace BlackLib;

#ifdef POT_MODE

#include <Adc.h>
ADC tremADC[] = {ADC(AINx::AIN0),
                 ADC(AINx::AIN1),
                 ADC(AINx::AIN2),
                 ADC(AINx::AIN3)};
#endif

void read_adcs(float *vec_float);
int POT_MODE = 1;

int main(int argc,char **argv)
{
    int sockfd;
    int len;
    struct sockaddr_in address;
    float vec_float[4] = {0.0};
    POT_MODE = 1;
    if(argc > 1){
	POT_MODE = 0;	
    }

    sockfd  = socket(AF_INET, SOCK_DGRAM,0);  // criacao do socket
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(MULTICAST_ADDR);
    address.sin_port = htons(PORT);

    len = sizeof(address);

    while(1){
      read_adcs(vec_float);
      sendto(sockfd, (uint8_t*)vec_float, 4*sizeof(float), 0, (struct sockaddr *) &address, len);
      sleep(PERIODIC_TIME);
    }

    close(sockfd);
    exit(0);
}


void read_adcs(float *vec_float)
{
  for(int i = 0; i < 4; i++)
    #ifdef POT_MODE
	vec_float[i] = tremADC[i].getPercentValue()/100.0;
    #else
	scanf("%f",&vec_float[i]);
    #endif
}

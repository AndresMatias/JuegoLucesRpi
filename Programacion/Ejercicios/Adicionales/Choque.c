#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include "easypio.h"

void secuenciaLuces();
//Varibles Globales
int Led[8]={23,24,25,12,16,20,21,26},i=0;

int main(int argc, char **argv)
{
	pioInit();
	for(i=0;i<8;i++)
	{
		pinMode(Led[i],OUTPUT);
	}	
	while(1)
	{
		for(i=0;i<3;i++)
		{
			secuenciaLuces();
		}	
		for(i=3;i>0;i--)
		{
			secuenciaLuces();
		}	
	} 
	return 0;
}

void secuenciaLuces()
{	
	digitalWrite(Led[i],1);
	digitalWrite(Led[7-i],1);		
	usleep(100000);
	digitalWrite(Led[i],0);
	digitalWrite(Led[7-i],0);	
}


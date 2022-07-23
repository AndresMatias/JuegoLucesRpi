#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include "kbhit.h" 
#include "easypio.h" 

void secuenciaLuces();
//Varibles Globales
int Led[8]={23,24,25,12,16,20,21,26},i=0;

int main(int argc, char **argv)
{
	nonblock(NB_ENABLE);
	pioInit();	
	while(!kbhit())
	{
		for(i=0;i<8;i++)
		{
			if(!kbhit())
			{
				secuenciaLuces();
			}
		}	
		for(i=6;i>0;i--)
		{
			if(!kbhit())
			{
				secuenciaLuces();
			}
		}	
	} 
	return 0;
}

void secuenciaLuces()
{
	pinMode(Led[i],OUTPUT);
	digitalWrite(Led[i],1);	
	delayMillis(50);
	digitalWrite(Led[i],0);
}

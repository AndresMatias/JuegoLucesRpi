#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "easypio.h"

int Led[8]={23,24,25,12,16,20,21,26},i=0,j=0,k=7;
int main(int argc, char **argv)
{
	pioInit();
	for(i=0;i<8;i++) //Configuracion de Pines de Salida
	{
		pinMode(Led[i],OUTPUT);
		digitalWrite(Led[i],0);
	}
	for(j=0;j<8;j++)
	{
		for(i=0;i<=k;i++)
		{
			digitalWrite(Led[i],1);	
			delayMillis(50);
			digitalWrite(Led[i],0);
			if(i==k)
			{
				i=0;
				while(i!=4)
				{
					delayMillis(100);
					digitalWrite(Led[k],0);	
					delayMillis(100);
					digitalWrite(Led[k],1);
					i++;
				}
				i=7;
			}
		}
		k--;
	}
	return 0;
}


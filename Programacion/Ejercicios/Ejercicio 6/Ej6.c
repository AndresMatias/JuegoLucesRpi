#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include "easypio.h"

int main(int argc, char **argv)
{
	pioInit();
	int leds[8]={23,24,25,12,16,20,21,26},i=0,j=0;
	int datos[16][8]={	{1,0,0,0,0,0,0,0},  //Matriz de Datos
						{1,0,0,0,0,0,0,0},
						{0,1,0,0,0,0,0,0},
						{0,1,0,0,0,0,0,0},
						{0,0,1,0,0,0,0,0},
						{0,0,1,0,0,0,0,0},
						{0,0,0,1,0,0,0,0},
						{0,0,0,1,0,0,0,0},
						{1,0,0,0,1,0,0,0},
						{0,1,0,0,1,0,0,0},
						{0,0,1,0,0,1,0,0},
						{0,0,0,1,0,1,0,0},
						{0,0,0,0,1,0,1,0},
						{0,0,0,0,0,1,1,0},
						{0,0,0,0,0,0,1,1},
						{0,0,0,0,0,0,0,1}};
	for(i=0;i<8;i++) //Configuracion de Pines de Salida
	{
		pinMode(leds[i],OUTPUT);
	}
	
	for(i = 0; i < 16; i++)  //Secuencia de luces
	{
		delayMillis(100);
		for(j = 0; j < 8; j++) 
		{
			digitalWrite(leds[j],datos[i][j]);
		}
	}

	return 0;
}


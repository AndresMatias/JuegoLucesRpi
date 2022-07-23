#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include "easypio.h" 
#define LED1 23 
#define LED2 24 
#define LED3 25 
#define LED4 12 
#define IN1 5 
#define IN2 6 
#define IN3 13 
#define IN4 19 

struct termios new,old;

void tecladoConfig()
{
	/* Obtenemos la configuración actual de la terminal */
        tcgetattr(0, &old);
        new=old;
	/* Le apagamos el bit "Echo" que es el eco para evitar que muestre tecla */
        new.c_lflag=0;
	/* Establecemos la nueva configuración de la terminal */
        tcsetattr(0, TCSANOW, &new);
}

void tecladoConfigInicial()
{
	tcsetattr(0, TCSANOW, &old);
}

int main(int argc, char **argv)
{
	char a;
	pioInit(); 
	pinMode(LED1,OUTPUT); 
	pinMode(LED2,OUTPUT); 
	pinMode(LED3,OUTPUT); 
	pinMode(LED4,OUTPUT); 
	pinMode(IN1,INPUT); 
	pinMode(IN2,INPUT); 
	pinMode(IN3,INPUT); 
	pinMode(IN4,INPUT); 
	tecladoConfig();
	printf("\nPalabra:");
	while(a!=27)
	{
		a=getchar();
	}
	printf("\nFin:");
	digitalWrite(LED1,digitalRead(IN1));//ESCRIBIMOS EN LAS SALIDAS LO QUE ESTE EN LAS ENTRADAS 
	digitalWrite(LED2,digitalRead(IN2)); 
	digitalWrite(LED3,digitalRead(IN3)); 
	digitalWrite(LED4,digitalRead(IN4));		
	printf("\n");
	tecladoConfigInicial();
	return 0;
}



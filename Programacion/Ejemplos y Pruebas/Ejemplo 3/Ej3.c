#include <stdlib.h> 
#include <stdio.h> 
#include <termios.h> 
#include <unistd.h> 
#include <wiringPi.h> 
#define LED1 4 
#define LED2 5 
#define LED3 6 
#define LED4 26 
#define IN1 21 
#define IN2 22 
#define IN3 23 
#define IN4 24 
int main() 
{ 
	wiringPiSetup(); 
	pinMode(LED1,OUTPUT); 
	pinMode(LED2,OUTPUT); 
	pinMode(LED3,OUTPUT); 
	pinMode(LED4,OUTPUT); 
	pinMode(IN1,INPUT); 
	pinMode(IN2,INPUT); 
	pinMode(IN3,INPUT); 
	pinMode(IN4,INPUT); 
	char aux=0; 
	struct termios old, new; 
	tcgetattr(0, &old); 
	new = old; new.c_cc[VMIN]=0; //CON ESTA CONFIGURACION LA LECTURA SE REALIZA INMEDIATAMENTE 
	new.c_cc[VTIME]=0; 
	new.c_lflag = 0; 
	tcsetattr(0, TCSANOW, &new); 
	system ("clear"); 
	do{ 
		read (0,&aux,1);//SI NO SE LEE NADA AL MOMENTO DE LA LECTURA, EL BUCLE CONTINUA EJECUTANDOSE 
	}
	while (aux != 27);//EL BUCLE FINALIZA PULSANDO ESC 
	tcsetattr(0, TCSANOW, &old); 
	digitalWrite(LED1,digitalRead(IN1));//ESCRIBIMOS EN LAS SALIDAS LO QUE ESTE EN LAS ENTRADAS 
	digitalWrite(LED2,digitalRead(IN2)); 
	digitalWrite(LED3,digitalRead(IN3)); 
	digitalWrite(LED4,digitalRead(IN4)); 
	printf("Transferencia completa"); 
	getchar(); 
}

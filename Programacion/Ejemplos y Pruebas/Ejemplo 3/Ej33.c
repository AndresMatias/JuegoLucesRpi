#include <stdlib.h> 
#include <stdio.h> 
#include <termios.h> 
#include <unistd.h> 
#include <wiringPi.h> 
#define LED1 4 
#define IN1 21 
int main() 
{ 
	wiringPiSetup(); 
	pinMode(LED1,OUTPUT); 
	pinMode(IN1,INPUT); 
	digitalWrite(LED1,digitalRead(IN1));//ESCRIBIMOS EN LAS SALIDAS LO QUE ESTE EN LAS ENTRADAS  
	printf("Transferencia completa"); 
	getchar(); 
}
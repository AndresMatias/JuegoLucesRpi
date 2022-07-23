#include "easypio.h"
#include <stdio.h>
#define MAX_STR_LEN 80

void getStrSerial(char *str){
	int i = 0;
	do{
		str[i] = getCharSerial();
	}while((str[i++] != '\r') && (i < MAX_STR_LEN));
	str[i-1] = 0;
}

void putStrSerial(char *str){
	int i = 0;
	while(str[i] != 0){
		putCharSerial(str[i++]);
	}
}


int main(void){
	char str[MAX_STR_LEN];
	pioInit();
	printf("Inicilizando UART...\n"); 
	uartInit(9600);
	printf("Done\n"); 
	putStrSerial("Probando 123\n");
	//putCharSerial('a');
	printf("Done\n"); 
}

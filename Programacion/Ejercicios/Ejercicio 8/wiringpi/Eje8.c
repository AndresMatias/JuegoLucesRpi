/*
	UART communication on Raspberry Pi using C (WiringPi Library)
*/
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <wiringPi.h>
#include <wiringSerial.h>

int main ()
{
	  int serial_port ;
	  char dat;
	  wiringPiSetup();
	  if ((serial_port = serialOpen ("/dev/ttyAMA0", 9600)) < 0)			/* abrir el puerto serie */
	  {
		fprintf (stderr, "Habilitar para abrir el dispositivo serial: %s\n", strerror (errno)) ;
		return 1 ;
	  }

	printf (" -------Comunicacion serie----\n") ;
	//dat = serialGetchar (serial_port);		/* retorna el siguiente caracter disponible en el dispositivo serial */	
	//printf ("%c", dat) ;
	serialPutchar(serial_port, 'r');		/* envia un unico byte por el puerto serie indicado*/
}

/*Comentarios Mucho Muy IMPORTANTES
 * modificar a termset para lectura no bloqueante*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <wiringPiI2C.h>
#include <wiringPi.h>
#include "easypio.h" //Desactive la funcion de analogwrite de esta biblioteca para que no interfiera con la de wiringpi
#include "password.h"
#include "teclado.h"
#include "kbhit.h"
#include "termset.h"
#define SIZE 10

//Varibles Globales
int Led[8]={23,24,25,12,16,20,21,26},i=0,j=0,cont=15,modo=0,intervalo[2]={5,40};
struct termios new,old;
char cadena[]="\n 1)Auto Fantastico \n 2)Choque \n 3)La Apilada \n 4)La Carrera \n 5)Secuencia 5 \n 6)Secuencia 6 \n 7)Secuencia 7 \n 8)Secuencia 8 \n 9)Salir \n Seleccione una opcion:";
char *cadena2[]={"\nSecuencia de luces: Auto Fantastico \n ""w"":Incremento de velocidad \n ""s"":Decremento de velocidad \n Para salir al menu presione la tecla escape\n",
				 "\nSecuencia de luces: Choque \n ""w"":Incremento de velocidad \n ""s"":Decremento de velocidad \n Para salir al menu presione la tecla escape o ingrese la letra 'q' si esta en modo remoto\n",
				 "\nSecuencia de luces: La Apilada  \n ""w"":Incremento de velocidad \n ""s"":Decremento de velocidad \n Para salir al menu presione la tecla escape o ingrese la letra 'q' si esta en modo remoto\n",
				 "\nSecuencia de luces: La Carrera \n ""w"":Incremento de velocidad \n ""s"":Decremento de velocidad \n Para salir al menu presione la tecla escape o ingrese la letra 'q' si esta en modo remoto\n",
				 "\nSecuencia de luces: Secuencia 5 \n ""w"":Incremento de velocidad \n ""s"":Decremento de velocidad \n Para salir al menu presione la tecla escape o ingrese la letra 'q' si esta en modo remoto\n",
				 "\nSecuencia de luces: Secuencia 6 \n ""w"":Incremento de velocidad \n ""s"":Decremento de velocidad \n Para salir al menu presione la tecla escape o ingrese la letra 'q' si esta en modo remoto\n",
				 "\nSecuencia de luces: Secuencia 7 \n ""w"":Incremento de velocidad \n ""s"":Decremento de velocidad \n Para salir al menu presione la tecla escape o ingrese la letra 'q' si esta en modo remoto\n",
				 "\nSecuencia de luces: Secuencia 7 \n ""w"":Incremento de velocidad \n ""s"":Decremento de velocidad \n Para salir al menu presione la tecla escape o ingrese la letra 'q' si esta en modo remoto\n"};
//Variables de Puerto Serial
int fd;

//Funciones
void Menu();
void SetVelocidadInicial(); //Setea velocidad inicial a travez de un adc
int Velocidad(); //Lee si se presiono una tecla cada 10 ms  
int AutoFantastico();
int Carrera(); 
int Choque();
int Apilada();
int Secuencia5();
int Secuencia6();
int Secuencia7();
int Secuencia8();
void Apagado(); //Apaga todos los leds
int EnviarUart(char *); //Envia datos por la uart
int RecibirUart(int); //Recibe datos por la uart si se ingresa un 0 en su argumento se queda en modo bloqueado esperando un caracter,sino entra en modo no canonico
int Comparacion(char);

int main(int argc, char **argv)
{
	char pass[]="cinco"; //Maximo de diez letras
	pioInit();
	for(i=0;i<8;i++) //Configuracion de Pines de Salida
	{
		pinMode(Led[i],OUTPUT);
		Apagado();
	}
	tecladoConfig(&new,&old); //Se Configura el teclado para ingresar contraseña
	if(Password(&pass[0])!=1) //Si se exede los intentos de contraseña el programa se termina
	{
		tecladoConfigInicial(&old); 
		return 0;
	}
	tecladoConfigInicial(&old);
	Menu();
	return 0;
}
void Menu()
{
	 int op=0,salir=0;
	  fflush(stdout);
	 while((modo!=1)&&(modo!=2))
	 {
		printf("\n 1)Modo Local \n 2)Modo Remoto \n Seleccione un modo:");
		scanf("%d",&modo);
	 }
	 if(modo==1)
	 {
		SetVelocidadInicial();
	 }	
	 op=0;
	 while(op!=9)
	 {
		 if(modo==1)
		 {
			printf("Modo: %d",modo);
			printf("%s",cadena);
			scanf("%d",&op);
			printf("\n");
			fflush(stdout);
		 }
		 if(modo==2)
		 {
			 intervalo[0]=1;
			 intervalo[1]=10;
			 cont=5;
			if(op!=9){EnviarUart(cadena);}
			while((op<1)||(op>9))
			{
				fflush(stdout);
				op=RecibirUart(0)-48;
			}
			printf("\n %d",op);
		 }
		 salir=0;
		 switch(op)  //Se escoje una secuencia de luz
		 {
			 case 1: //Auto Fantastico
				printf("%s",cadena2[0]);
				if(modo==2)
				{
					EnviarUart(cadena2[0]);
				}	
				tecladoConfig(&new,&old);
				while(salir!=27)
				{
					salir=AutoFantastico();	
				} 
				tecladoConfigInicial(&old);
				break;
			case 2: //Choque
				printf("%s",cadena2[1]);
				if(modo==2)
				{
					EnviarUart(cadena2[1]);
				}
				tecladoConfig(&new,&old);
				while(salir!=27)
				{
					salir=Choque();
				} 
				tecladoConfigInicial(&old);
				break;
			case 3: //Apilada
				printf("%s",cadena2[2]);
				if(modo==2)
				{
					EnviarUart(cadena2[2]);
				}
				tecladoConfig(&new,&old);
				while(salir!=27)
				{
					salir=Apilada();
				} 
				tecladoConfigInicial(&old);
				break;
			case 4 : //Carrera
				printf("%s",cadena2[3]);
				if(modo==2)
				{
					EnviarUart(cadena2[3]);
				}
				tecladoConfig(&new,&old);
				while(salir!=27)
				{
					salir=Carrera();
				} 
				tecladoConfigInicial(&old);
				break;
			case 5 : //Secuencia 5
				printf("%s",cadena2[4]);
				if(modo==2)
				{
					EnviarUart(cadena2[4]);
				}
				tecladoConfig(&new,&old);
				while(salir!=27)
				{
					salir=Secuencia5();
				} 
				tecladoConfigInicial(&old);
				break;
			case 6 : //Secuencia 6
				printf("%s",cadena2[5]);
				if(modo==2)
				{
					EnviarUart(cadena2[5]);
				}
				tecladoConfig(&new,&old);
				while(salir!=27)
				{
					salir=Secuencia6();
				} 
				tecladoConfigInicial(&old);
				break;
			case 7 : //Secuencia 7
				printf("%s",cadena2[6]);
				if(modo==2)
				{
					EnviarUart(cadena2[6]);
				}
				tecladoConfig(&new,&old);
				while(salir!=27)
				{
					salir=Secuencia7();
				}
				tecladoConfigInicial(&old); 
				break;
			case 8 : //Secuencia 8
				printf("%s",cadena2[7]);
				if(modo==2)
				{
					EnviarUart(cadena2[7]);
				}
				tecladoConfig(&new,&old);
				while(salir!=27)
				{
					salir=Secuencia8();
				}
				tecladoConfigInicial(&old); 
				break;
			case 9 : //Indicador de que se salio del Programa
			if(modo==2)
				{
					EnviarUart("\nHa salido del programa");
				}
				printf("\nHa salido del programa");
				
				break;
			default: //En caso de que se ingrese un numero distindo de los del menu 
				if(modo==2)
				{
					EnviarUart("\n Escoja una de las opciones \n");
				}
				printf("\nEscoja una de las opciones\n");
		}
		if(op!=9)
		{
			op=0;
		}
		Apagado(); //Se apagan todos los leds
		printf("\n");
	}
 }
/*-------------------------------Auto Fantastico-----------------------------------------------------------*/
int AutoFantastico()
{
	fflush(stdout); 
	int bandera;
	for(i=0;i<8;i++)
	{
		digitalWrite(Led[i],1);	
		bandera=Velocidad();
		digitalWrite(Led[i],0);
		if(bandera==27)
		{
			return bandera;
		}		
	}	
	for(i=6;i>0;i--)
	{
		digitalWrite(Led[i],1);	
		bandera=Velocidad();
		digitalWrite(Led[i],0);
		if(bandera==27)
		{
			return bandera;
		}
	}
	return(0);
}
/*-----------------------------------------Carrera--------------------------------------------------*/
int Carrera()
{
	fflush(stdout); 
	int bandera=0;
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
		for(i = 0; i < 16; i++)  //Secuencia de luces
		{
			bandera=Velocidad();
			if(bandera==27)
			{
				return bandera;
			}
			for(j = 0; j < 8; j++) 
			{
				digitalWrite(Led[j],datos[i][j]);
			}	
		}				
	return 0;
}
/*---------------------------------------Choque----------------------------------------------------*/
int Choque()
{
	fflush(stdout); 
	int bandera=0;
	for(i=0;i<3;i++)
	{
		digitalWrite(Led[i],1);
		digitalWrite(Led[7-i],1);		
		bandera=Velocidad();
		digitalWrite(Led[i],0);
		digitalWrite(Led[7-i],0);
		if(bandera==27)
		{
			return bandera;
		}
	}	
	for(i=3;i>0;i--)
	{
		digitalWrite(Led[i],1);
		digitalWrite(Led[7-i],1);		
		bandera=Velocidad();
		digitalWrite(Led[i],0);
		digitalWrite(Led[7-i],0);
		if(bandera==27)
		{
			return bandera;
		}
	}
	return 0;	
}
/*----------------------------------------Apilada---------------------------------------------------*/
int Apilada()
{
	fflush(stdout); 
	int k=7,bandera=0;
	for(j=0;j<8;j++)
	{
		for(i=0;i<=k;i++)
		{
			digitalWrite(Led[i],1);	
			bandera=Velocidad();
			digitalWrite(Led[i],0);
			if(bandera==27)
			{
				return bandera;
			}
			if(i==k)
			{
				i=0;
				while(i!=4)
				{
					delayMillis(50);
					digitalWrite(Led[k],0);	
					delayMillis(50);
					digitalWrite(Led[k],1);
					i++;
				}
				i=7;
			}
		}
		k--;
	}
	Apagado();
	return 0;
}
/*-------------------------------------------Secuencia5------------------------------------------------*/
int Secuencia5()
{
	fflush(stdout); 
	int bandera=0;
	j=0;
	for(i=0;i<2;i++)
	{
		digitalWrite(Led[(j=i)],1);	
		digitalWrite(Led[j=j+2],1);	
		digitalWrite(Led[j=j+2],1);	
		digitalWrite(Led[j=j+2],1);
		bandera=Velocidad();	
		digitalWrite(Led[(j=i)],0);	
		digitalWrite(Led[j=j+2],0);	
		digitalWrite(Led[j=j+2],0);	
		digitalWrite(Led[j=j+2],0);
		if(bandera==27)
		{
			Apagado();
			return bandera;
		}
	}
	return 0;
}
/*----------------------------------------------Secuencia6---------------------------------------------*/
int Secuencia6()
{
	fflush(stdout); 
	int bandera=0;
	j=0;
	for(i=0;i<8;i++)
	{
		digitalWrite(Led[(j=i)],1);	
		digitalWrite(Led[j=j+1],1);	
		bandera=Velocidad();
		digitalWrite(Led[(j=i)],0);
		digitalWrite(Led[j=j+1],0);		
		if(bandera==27)
		{
			Apagado();
			return bandera;
		}
	}
	return 0;
}
/*--------------------------------------------Secuencia7-----------------------------------------------*/
int Secuencia7()
{
	fflush(stdout); 
	int bandera=0;
	bandera=Velocidad();
	digitalWrite(Led[0],1);	
	digitalWrite(Led[1],1);
	digitalWrite(Led[2],1);	
	digitalWrite(Led[3],0);
	digitalWrite(Led[4],0);	
	digitalWrite(Led[5],1);
	digitalWrite(Led[6],1);	
	digitalWrite(Led[7],1);		
	bandera=Velocidad();
	if(bandera==27)
	{
		Apagado();
		return bandera;
	}
	digitalWrite(Led[0],0);	
	digitalWrite(Led[1],0);
	digitalWrite(Led[2],0);	
	digitalWrite(Led[3],1);
	digitalWrite(Led[4],1);	
	digitalWrite(Led[5],0);
	digitalWrite(Led[6],0);	
	digitalWrite(Led[7],0);		
	return 0;
}
/*---------------------------------------------Secuencia8----------------------------------------------*/
int Secuencia8()
{
	int bandera=0;
	fflush(stdout); 
	for(i=0;i<8;i++)
	{
		digitalWrite(Led[(j=i)],1);	
		digitalWrite(Led[j=j+2],1);	
		bandera=Velocidad();	
		digitalWrite(Led[j=i],0);
		digitalWrite(Led[j=j+2],0);	
		if(bandera==27)
		{
			Apagado();
			return bandera;
		}
	}
	return 0;
}
/*--------------------------------------------Apagado-----------------------------------------------*/
void Apagado()
{
	for(i=0;i<8;i++)
	{
		digitalWrite(Led[i],0);
	}
}
/*----------------------------------------------Velocidad---------------------------------------------*/
int Velocidad()
{
	int cont_aux=0;
	char dato;
	while(cont_aux!=cont)
	{
		nonblock(NB_ENABLE);
		if(modo==2)
		{
			Comparacion((dato=RecibirUart(2)));
			if(dato=='q')
			{
				return 27;
			}
		}
		if(kbhit())
		{
			dato=getchar();
			dato=Comparacion(dato);
			if(dato==27) //salir
			{	
				return dato;
			}
		}
		if(cont_aux!=cont)
		{
			cont_aux++;
			if(modo!=2)
			{
				delayMillis(10);
			}
			else
			{
				delayMillis(1);
			}
		}
	}
	return 0;
}
/*---------------------------------------------SetVelocidadInicial----------------------------------------------*/
void SetVelocidadInicial()
{
	const char PCF8591 = 0x48; // direccion base
	int fd, adcVal;	//declaracion de variables para acceder al adc
	int regla=0;
	char dato;
	wiringPiSetup();
	//if (wiringPiSetup () == -1) exit (1);	
	fd = wiringPiI2CSetup(PCF8591);		// configuracion del bus I2C, inicializa el sistema I2C con el ID del dispositivo.
	while (dato!=27)   
	{
		//read ADC0
		wiringPiI2CReadReg8(fd, PCF8591 + 0) ; //primer lectura 
		adcVal = wiringPiI2CReadReg8(fd, PCF8591 + 0) ;//segunda lectura valida
		regla=(adcVal*35)/255;
		cont=regla+5;	
		printf("\nVelocidad Inicial= %d ms \n Si desea salir presione esc sino cualquier otra tecla:",(cont*10));
		dato=getchar();	
		fflush(stdout);  	 
	}
}
/*--------------------------------------------EnviarUart-----------------------------------------------*/
int EnviarUart(char *cad)
{
	fd = open("/dev/ttyAMA0", O_WRONLY | O_RDONLY | O_NOCTTY | O_SYNC);
	if(fd < -1)
	{
		printf("ERROR: opening serial port\n");
		return -1;
	}
	if(termset(fd, 9600, &ttyold, &ttynew,0) == -1)
	{
		printf("ERROR: setting tty\n");
		return -1;
	}	
	write(fd, cad, strlen(cad)); //Puntero
	printf("\nEnviado\n");
	close(fd);
	return 0;
}
/*-------------------------------------------RecibirUart------------------------------------------------*/
int RecibirUart(int bandera)
{
	unsigned char buf[SIZE]; 
	//ssize_t n_read;
	fd = open("/dev/ttyAMA0", O_RDONLY | O_NOCTTY | O_SYNC);
	fflush(stdout);
	if(fd < -1)
	{
		printf("ERROR: opening serial port\n");
		return -1;
	}
	if(termset(fd, 9600, &ttyold, &ttynew,bandera) == -1)
	{
		printf("ERROR: setting tty\n");
		return -1;
	}
	read(fd, buf, SIZE);
	if((buf[0]=='s')||(buf[0]=='w'))
	{
		printf("%c ", buf[0]);
		printf("\n");
	}
	close(fd);
	return buf[0];
}
/*-------------------------------------------Comparacion------------------------------------------------*/
int Comparacion(char dato)
{	
	if((dato==119)&&(cont>intervalo[0])) //w
	{	
		cont--;
	}
	if((dato==115)&&(cont<intervalo[1])) //s
	{	
		cont++;
	}
	return dato;
}

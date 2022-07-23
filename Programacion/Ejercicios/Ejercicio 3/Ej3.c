/*
 * sin título.c
 * 
 * Copyright 2019 ltdi <ltdi@ltdi-G00>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

char c[6],aux,pass[6]="cinco";
int i,flag=0,intentos=3;

void InPassword()
{
	i=-1;
	aux=0;
	while((c[i]!=10)&&(aux!=10))
        {
			
		i++;
		if(i<=5)
		{
			c[i]=getchar();
			fflush(stdout);
			if((c[i]!=10)&&(c[i]!=127))
			{
				printf("*");
			}
		}
		else
		{
			i=i-1;
			aux=getchar();
			fflush(stdout);
		}
		if(((c[i]==127)||aux==127)&&(i!=0))
		{
			if(c[i]==127)
			{
				i=i-2;
			}
			if(aux==127)
			{
				i=i-1;
			}
			aux=32;//32
			printf("\b%c\b",aux);
			fflush(stdout);
		}
		if(c[0]==127)
		{
			i=-1;
		}
									
	}
	return;
}

void Comparar()
{
	i=0;
	while(i!=5)
	{
		if(c[i]==pass[i])
		{
			i++;
		}
		else
		{
			intentos--;
			printf("\nPassword No Valida");
			return;
		}		
	}		
	flag=1;	
	return;
}

void Resultado()
{
	if(flag==1)
	{
		printf("\nBienvenido al sistema");
	}     
	else
	{
		printf("\nSu sistema ha sido bloquedo 100 años");
	}
}

int main(int argc, char **argv)
{
        struct termios new,old;

	/* Obtenemos la configuración actual de la terminal */
        tcgetattr(0, &old);
        new=old;
	/* Le apagamos el bit "Echo" que es el eco para evitar que muestre tecla */
        new.c_lflag=0;
	/* Establecemos la nueva configuración de la terminal */
        tcsetattr(0, TCSANOW, &new);
       
        while((flag==0)&&(intentos!=0))
        {
			printf("\nIngrese Contraseña(Intentos %d): ",intentos);
			fflush(stdout);
			InPassword();	
			Comparar();
	}
		Resultado();
        /* ¡Ojo! ¡Si no dejamos todo como estaba le dejamos
         * al usuario la terminal rota!
         */
        tcsetattr(0, TCSANOW, &old);

        return 0;
}




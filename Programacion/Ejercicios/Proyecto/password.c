#include "password.h"

char c[6],aux,*pass;
int i,flag=0,intentos=3;

void InPassword()
{
	i=-1;
	aux=0;
	while((c[i]!=10)&&(aux!=10))
        {
			
		i++;
		if(i<=10)
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
	int aux=0;
	i=0;
	while(pass[i]!='\0') //Calculo el tamaño de la contraseña y se guarda en aux
	{
		i++;
		aux++;	
	}
	i=0;
	while(i!=aux)
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
		printf("\nBienvenido al sistema\n");
	}     
	else
	{
		printf("\nSu sistema ha sido bloquedo 100 años\n");
	}
}
int Password(char *Contra)
{      
		pass=Contra;
        while((flag==0)&&(intentos!=0))
        {
			printf("\nIngrese Contraseña(Intentos %d): ",intentos);
			fflush(stdout);
			InPassword();	
			Comparar();
		}
		Resultado();
        return flag;
}






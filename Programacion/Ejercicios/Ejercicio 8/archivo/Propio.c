#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "termset.h"
#define SIZE 10
int main(int argc, char **argv)
{
	FILE *fptr;
	ssize_t n_read;
	size_t len = 0;
	unsigned char buf[SIZE];
	char *line,*cadena="Digitales";
	int fd,i=0;
	
	fd = open("/dev/ttyAMA0", O_RDONLY | O_NOCTTY | O_SYNC);
	if(fd < -1)
	{
		printf("ERROR: opening serial port\n");
		return -1;
	}
	if(termset(fd, 9600, &ttyold, &ttynew) == -1)
	{
		printf("ERROR: setting tty\n");
		return -1;
	}
	
	printf("\n Primer bucle \n ");
	while(i!=-1)
	{
		n_read = read(fd, buf, SIZE);
		for(i = 0; i < n_read; i++)
		{
			printf("%c", buf[i]);		
		}
		if((buf[0]=='s')&&(buf[1]=='a')&&(buf[2]=='l')&&(buf[3]=='i')&&(buf[4]=='r'))	
		{
			i=-1;
		}		
	}
	close(fd);
	printf("\n Segundo bucle \n ");
	fflush(stdout);
	n_read=0;
	
	fptr = fopen("/dev/ttyAMA0", "r");
	  if(fptr == NULL)
	  {
		printf("ERROR: opening %s file\n", argv[1]);
		return -1;
	  }
	  fd = fileno(fptr);
	  if(termset(fd, 9600, &ttyold, &ttynew) == -1)
	  {
		printf("ERROR: setting tty\n");
		return -1;
	  }
	  i=0;
	while(i!= -1)
	{
		n_read = getline(&line, &len, fptr);
		if(n_read != -1)
		{
			printf("Line: %s", line);
		}	
		if((line[0]=='s')&&(line[1]=='a')&&(line[2]=='l')&&(line[3]=='i')&&(line[4]=='r'))
		{
			i=-1;
		}
	}
	fclose(fptr);
	fflush(stdout);
	
	printf("\n Tercer bucle \n ");
	
	fd = open("/dev/ttyAMA0", O_WRONLY | O_NOCTTY | O_SYNC);
	 if(fd < -1)
	 {
		printf("ERROR: opening serial port\n");
		return -1;
	 }
	if(termset(fd, 9600, &ttyold, &ttynew) == -1)
	{
		printf("ERROR: setting tty\n");
		return -1;
	}
	
	write(fd, cadena, 9);
	printf("\n Enviado\n");
	fflush(stdout);
	close(fd);	
	return 0;
}


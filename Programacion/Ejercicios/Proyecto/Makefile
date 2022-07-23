CC = gcc

OBJECTS = Principal.o kbhit.o teclado.o password.o termset.o
CABECERA = easypio.h password.h teclado.h kbhit.h termset.h

CFLAGS = -Wall -g  -c
ASFLAGS = -g 
LDFLAGS = -g 

Proyecto: $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o Proyecto -lwiringPi

password.o : password.c password.h
	$(CC) $(CFLAGS) password.c

teclado.o: teclado.c teclado.h
	$(CC) $(CFLAGS) teclado.c

kbhit.o: kbhit.c kbhit.h
	$(CC) $(CFLAGS) kbhit.c

termset.o: termset.c termset.h 
	$(CC) $(CFLAGS) termset.c

Principal.o: Principal.c $(CABECERA) 
	$(CC) $(CFLAGS) Principal.c

clean:
	rm *.o *.elf 
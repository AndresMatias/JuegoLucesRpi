# -----------------------------------------------------------------
# Makefile for suma.elf (main.c suma.s) 
# -----------------------------------------------------------------

AS = as
LD = ld
CC = gcc

OBJECTS = main.o suma.o

ASFLAGS = -g 
LDFLAGS = -g 
CFLAGS = -Wall -O1 -g  -c

suma.elf: $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o suma.elf

suma.o: suma.s 
	$(AS) $(ASFLAGS) suma.s -o suma.o

main.o: main.c
	$(CC) $(CFLAGS) main.c

clean:
	rm *.o *.elf 

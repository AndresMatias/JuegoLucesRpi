#ifndef EASYPIO_H
#define EASYPIO_H

#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>

#define BCM2835_PERI_BASE 0x3F000000
#define GPIO_BASE (BCM2835_PERI_BASE + 0x200000)
volatile unsigned int *gpio; //Pointer to base of gpio
#define GPLEV0 (* (volatile unsigned int *) (gpio + 13))
#define BLOCK_SIZE (4*1024)

#define GPFSEL ((volatile unsigned int *) (gpio + 0))
#define GPSET ((volatile unsigned int *) (gpio + 7))
#define GPCLR ((volatile unsigned int *) (gpio + 10))
#define GPLEV ((volatile unsigned int *) (gpio + 13))
#define INPUT 0
#define OUTPUT 1

void pioInit(void);
void pinMode(int , int );
void digitalWrite(int , int );
int digitalRead(int );

#endif


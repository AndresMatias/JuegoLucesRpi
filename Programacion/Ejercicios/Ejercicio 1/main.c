#include<stdio.h>
extern int suma(int a);
int main(void)
{
  int a = 1;
  int c; 
  c = suma(a);
  printf("\nResultado: %d\n",c);
  return 0;
} 

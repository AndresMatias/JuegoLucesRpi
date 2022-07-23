#include<stdio.h>
extern int suma(int a, int b);
int main(void)
{
  int a = 71;
  int b = 29;
  int c; 
  c = suma(a,b);
  printf("\nResultado: %d\n",c);
  return 0;
} 
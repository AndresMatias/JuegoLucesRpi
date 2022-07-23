#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include "kbhit.h"  

int main(int argc, char **argv)
{
	//char vector[4]={'^','[','[','D'};
	char vector_aux[4]={' ',' ',' ',' '};
	/*struct termios new,old;
        tcgetattr(0, &old);
        new=old;
        new.c_lflag=1;
        tcsetattr(0, TCSANOW, &new);*/
	nonblock(NB_ENABLE);
	while(1)
	{
		//if(kbhit())
			//{
				vector_aux[0]=getchar();
				printf("\n a:\n %d \n",vector_aux[0]);
				//printf("\n b: %c \n",vector_aux[1]);
				//printf("\n c: %c \n",vector_aux[2]);
				//printf("\n d: %c \n",vector_aux[3]);
				/*if(kbhit())
				{*/
					//printf("\n b: %d \n",getchar());
					//printf("\n c: %d \n",getchar());
				//}
			//}		
	} 
  //tcsetattr(0, TCSANOW, &old);
	return 0;
}


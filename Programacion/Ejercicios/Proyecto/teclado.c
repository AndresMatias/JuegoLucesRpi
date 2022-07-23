#include "teclado.h"

void tecladoConfig(struct termios *new,struct termios *old)
{
	/* Obtenemos la configuración actual de la terminal */
        tcgetattr(0, &(*old));
        *new=*old;
	/* Le apagamos el bit "Echo" que es el eco para evitar que muestre tecla */
        new->c_lflag=0;
	/* Establecemos la nueva configuración de la terminal */
        tcsetattr(0, TCSANOW, &(*new));
}

void tecladoConfigInicial(struct termios *old)
{
	tcsetattr(0, TCSANOW, &(*old));
}




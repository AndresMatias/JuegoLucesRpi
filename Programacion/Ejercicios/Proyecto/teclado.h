#ifndef _TECLADO_H_
#define _TECLADO_H_

#include <termios.h>
#include <unistd.h>
void tecladoConfig(struct termios *,struct termios *);
void tecladoConfigInicial(struct termios *);

#endif

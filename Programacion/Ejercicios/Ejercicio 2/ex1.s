.text
.arm
.global _start
_start:
        b reset
        b loop
        b loop
        b loop
        b loop
        nop
        b loop
        b loop

/* ==============================
*  CODIGO
*  ==============================
*/

reset:
	mov r0,#10
	bl retardo
	loop:   b loop
retardo:
  	otro:
	cmp r0,#0
	sub r0,#1 
	bne otro
	mov pc,lr    

/* ==============================
*  CONSTANTES
*  ==============================
*/
        .end

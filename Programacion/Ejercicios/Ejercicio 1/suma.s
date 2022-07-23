.text
.arm
.global suma
suma:
	mov r2,#0 
	cmp r0,#1 /*Case 1*/
	addeq r2,r2,#3
	beq bucle
	cmp r0,#2 /*Case 2*/
	addeq r2,r2,#4
	beq bucle
	cmp r0,#3 /*Case 3*/
	addeq r2,r2,#5
	beq bucle
bucle:	
	mov   r0, r2                    
  	mov   pc, lr  


//code pins and ports are edited for the pcb
ORG 100H
	
db 0C0H, 0F9H, 0A4H, 0B0H, 99H, 92H, 82H, 0F8H, 80H, 90H,0		;defining the values of 7 segments of each digit
	
RESET	EQU	P1.4 												;setting the 3 buttons of control
UP		EQU	P1.3
DOWN	EQU P1.2
	
ORG 0000H	
	
	AGAIN:														;setting pins as inputs
		SETB RESET 
		SETB UP
		SETB DOWN
	
	RESCHECK:													;checking the switches when they are pushed jumb to 
		JB RESET, UPCHECK										;the function of them		
		SJMP RESFUN
	
	UPCHECK:
		JB UP, DOWNCHECK
		SJMP UPFUN
	
	DOWNCHECK:
		JB DOWN, RESCHECK
		SJMP DOWNFUN
	
	RESFUN:														;reset function that reset values of DPTR	
		JNB RESET, RESFUN
		
		MOV DPTR, #100H
		MOV A, #00H
		SJMP READ
	
	UPFUN:														;next digit function by incrimenting DPTR 
		JNB UP, UPFUN
		INC DPTR   												;Make DPTR points to next value
		SJMP READ
	
	DOWNFUN:													;previous digit function by decrimenting DPTR
		JNB DOWN, DOWNFUN
		INC  DPL           								        ;inc / djnz as a jump-if != 0 without modifying yet
		DJNZ DPL, SkipDecDPH
		DEC  DPH                				      			;decrement high half if low half will wrap
	SkipDecDPH:
		DEC DPL
		SJMP READ
		
	READ:														;fuction that outputs the digit				  
		CLR A
		MOVC A, @A+DPTR
		MOV P0,A
		SJMP AGAIN
		END
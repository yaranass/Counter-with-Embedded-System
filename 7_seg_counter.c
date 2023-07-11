#include <REG51.H>                /* special function register declarations   */
#include <stdio.h>                /* prototype declarations for I/O functions */
int i=0;
void Setup_S52();

char segm[10]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90}; //look up table for digits from 0 to 9
char segdec[10]= {0x90,0x80,0xF8,0x82,0x92,0x99,0xB0,0xA4,0xF9,0xC0};

//unsigned int i;
//unsigned int x;

unsigned char ch;
void Count_down();
void Count_Up();
void Reset();
void Delay();


void main (void)
  {
  P0=0x00 ;
  Setup_S52();
	printf ("  Press R reset ,Press U to count up and press D to count down");   //Print a message to the terminal screen
		//serial communication
		while(1)
		{
		ch = getkey();		  // Get a character from the keyboard
			
		if(ch=='D' || ch=='d')
			{
			Count_down();
			}
		else if (ch=='U' || ch=='u')
			{
			Count_Up(); 
			}
		else if (ch=='R' || ch=='r') 
			{
			Reset();
			}		
}
}

void Setup_S52() 
{
    SCON  = 0x50;		        /* SCON: mode 1, 8-bit UART, enable rcvr      */
    TMOD |= 0x20;               /* TMOD: timer 1, mode 2, 8-bit reload        */
    TH1   = 250;                /* TH1:  reload value for 9600 baud @ 22.1184MHz   */
    TR1   = 1;                  /* TR1:  timer 1 run                          */
    TI    = 1;                  /* TI:   set TI to send first char of UART    */
}


void  Count_Up()
{
	i++;
	switch(i)
	{
    case 1:   P0=segm[1] ;
	            break;
		case 2:  	P0=segm[2] ;
              break;
		case 3:		P0=segm[3] ;
	            break;
		case 4:		P0=segm[4] ;
	            break;
		case 5:		P0=segm[5] ;
	            break;
		case 6:		P0=segm[6] ;
	            break;
		case 7:		P0=segm[7] ;
	            break;
		case 8:		P0=segm[8] ;
	            break;
		case 9:		P0=segm[9] ;i=9;printf ("  cannot count up anymore,press D to count down");
	            break;
  }
	Delay;
}

void  Count_down()
{
  i--;
	switch(i)
	{
		case 0:		P0=segm[0] ;printf ("  cannot count down anymore,press U to count up");
	            break;
    case 1:   P0=segm[1] ;
	            break;
		case 2:  	P0=segm[2] ;
              break;
		case 3:		P0=segm[3] ;
	            break;
		case 4:		P0=segm[4] ;
	            break;
		case 5:		P0=segm[5] ;
	            break;
		case 6:		P0=segm[6] ;
	            break;
		case 7:		P0=segm[7] ;
	            break;
		case 8:		P0=segm[8] ;
	            break;
		case 9:	 P0=segm[9] ;
	            break;
  }
	Delay;
}

void  Reset()
{
         P0=segm[0];
}

void Delay()
{
      for(i=0; i<40000; i++);   // Delay 2 Sec 
}


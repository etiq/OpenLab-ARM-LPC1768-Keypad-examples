#include <lpc17xx.h>
#include "delay.h"
#include "uart.h"

//PORT D in OpenLab is used as the default port for Keypad. i.e. PORT1[24:31]
//Note that the keypad won't work with PORTA in OpenLab as it contains the pins for UART0 communication.

#define KEYPAD_DATA_SET      	 LPC_GPIO1->FIOSET
#define KEYPAD_DATA_CLR    		 LPC_GPIO1->FIOCLR
#define KEYPAD_DATA_PIN				 LPC_GPIO1->FIOPIN

#define KEYPAD_DATA_DIR   LPC_GPIO1->FIODIR

#define KEYPAD_D0     24
#define KEYPAD_D1     25
#define KEYPAD_D2     26
#define KEYPAD_D3     27
#define KEYPAD_D4     28
#define KEYPAD_D5     29
#define KEYPAD_D6     30
#define KEYPAD_D7     31

#define KEYPAD_DATA_MASK   ((1<<KEYPAD_D0)|(1<<KEYPAD_D1)|(1<<KEYPAD_D2)|(1<<KEYPAD_D3))		//LSBs O/P & MSBs I/P

void sendbite(char bite)
{
    KEYPAD_DATA_CLR =	KEYPAD_DATA_MASK;
		KEYPAD_DATA_SET = (bite << KEYPAD_D0);	
}

int readbite(int column)
{
	switch(column)
	{
		case 3:	if((KEYPAD_DATA_PIN >> KEYPAD_D7) & 0x01)
							return 1;
						else
							return 0;
		case 2:	if((KEYPAD_DATA_PIN >> KEYPAD_D6) & 0x01)
							return 1;
						else
							return 0;
		case 1:	if((KEYPAD_DATA_PIN >> KEYPAD_D5) & 0x01)
							return 1;
						else
							return 0;
		case 0:	if((KEYPAD_DATA_PIN >> KEYPAD_D4) & 0x01)
							return 1;
						else
							return 0;
	}
}

void GetKey()
{
		while(1)
	{
	 /*1st row made low keeping other rows high and scan for which column reflects the software low*/
   sendbite(0XF7);      //F7	08          
	 if(readbite(3) == 0)
	 {
		 while(readbite(3)==0);
		 UART0_WriteString("1\r\n");																	  
		 break;
	 }
	 else if(readbite(2)==0)
	 {
		 while(readbite(2)==0);
		 UART0_WriteString("2\r\n");																	  
		 break;
	 }
	 else if(readbite(1)==0)
	 {
		 while(readbite(1)==0);
		 UART0_WriteString("3\r\n");																	  
		 break;
	 }
	 else if(readbite(0)==0)
	 {
		 while(readbite(0)==0);
		 UART0_WriteString("A\r\n");																	  
		 break;
	 }
	 delay_ms(10);

	 /*2nd row made low keeping other rows high and scan for which column reflects the software low*/
	 sendbite(0xFB);			//FB	04
	 if(readbite(3)==0)
	 {
		 while(readbite(3)==0);
		 UART0_WriteString("4\r\n");																	  
		 break;
	 }
	 else if(readbite(2)==0)
	 {
		 while(readbite(2)==0);
		 UART0_WriteString("5\r\n");																	  
		 break;
	 }
	 else if(readbite(1)==0)
	 {
		 while(readbite(1)==0);
		 UART0_WriteString("6\r\n");																	  
		 break;
	 }
	 else if(readbite(0)==0)
	 {
		 while(readbite(0)==0);
		 UART0_WriteString("B\r\n");																	  
		 break;
	 }
	 delay_ms(10);	 

	 /*3rd row made low keeping other rows high and scan for which column reflects the software low*/
	 sendbite(0xFD);			//FD	02
	 if(readbite(3)==0)
	 {
		 while(readbite(3)==0);
		 UART0_WriteString("7\r\n");																	  
		 break;
	 }
	 else if(readbite(2)==0)
	 {
		 while(readbite(2)==0);
		 UART0_WriteString("8\r\n");																	  
		 break;
	 }
	 else if(readbite(1)==0)
	 {
		 while(readbite(1)==0);
		 UART0_WriteString("9\r\n");																	  
		 break;
	 }
	 else if(readbite(0)==0)
	 {
		 while(readbite(0)==0);
		 UART0_WriteString("C\r\n");																	  
		 break;
	 }
	 delay_ms(10);

	 /*4th row made low keeping other rows high and scan for which column reflects the software low*/
	 sendbite(0xFE);				//FE	01
	 if(readbite(3)==0)
	 {
		 while(readbite(3)==0);
		 UART0_WriteString("*\r\n");																	  
		 break;
	 }
	 else if(readbite(2)==0)
	 {
		 while(readbite(2)==0);
		 UART0_WriteString("0\r\n");																	  
		 break;
	 }
	 else if(readbite(1)==0)
	 {
		 while(readbite(1)==0);
		 UART0_WriteString("#\r\n");																	  
		 break;
	 }
	 else if(readbite(0)==0)
	 {
		 while(readbite(0)==0);
		 UART0_WriteString("D\r\n");																	  
		 break;
	 }
	 delay_ms(10);
	}
}

int main (void)
{
  SystemInit();
	
	KEYPAD_DATA_DIR = KEYPAD_DATA_MASK;

  UART0_INIT();
  
  UART0_WriteString("KEYPAD\r\n");																	  
  
  while (1) 
  {
  UART0_WriteString("PRESS ANY KEY\r\n");																	  
	GetKey();
  }
}

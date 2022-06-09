/*(C) Umang Gajera - www.ocfreaks.com
More Embedded tutorials @ www.ocfreaks.com/cat/embedded/
LPC1343 UART Example 2 Source Code.
License : GPL.*/

#include <lpc13xx.h>

#define RDR         (1<<0) //Receiver Data Ready
#define THRE        (1<<5) //Transmit Holding Register Empty
#define MULVAL      1
#define DIVADDVAL   0
#define Ux_FIFO_EN  (1<<0)
#define Rx_FIFO_RST (1<<1)
#define Tx_FIFO_RST (1<<2)
#define DLAB_BIT    (1<<7)
#define LINE_FEED   0x0A //LF, For Linux, MAC and Windows Terminals
#define CARRIAGE_RETURN 0x0D //CR, For Windows Terminals (CR+LF).
#define ENTER       CARRIAGE_RETURN //Ascii value/code for Enter is 0x0D i.e. CR

void initUART(void);
void uartWrite(char data);
char uartRead(void);

int main(void)
{
	initUART();
	char data = 0;

	while(1)
	{
		data = uartRead(); //Read Data from Rx
		if(data == ENTER || data == LINE_FEED) //Check if user pressed Enter key
		{
			//Send NEW Line Character(s) i.e. "\n"
			uartWrite(CARRIAGE_RETURN); //Comment this for Linux or MacOS
			uartWrite(LINE_FEED); //Windows uses CR+LF for newline.
		}
		else
		{
			uartWrite(data); //Tx Read Data back
		}
	}
	//return 0; //Normally this won't execute
}

char uartRead(void)
{
	while(!(LPC_UART->LSR & RDR)); //wait until data arrives in Rx FIFO
	return LPC_UART->RBR;
}

void uartWrite(char txData)
{
	while(!(LPC_UART->LSR & THRE)); //wait until THR is empty
	//now we can write to Tx FIFO
	LPC_UART->THR = txData;
}

void initUART(void)
{
	/*Assuming CCLK=UART_PCLK=72Mhz!*/

	//UART CLOCK Enable Sequence Step 1 - Select TXD,RXD functions
	LPC_IOCON->PIO1_6 = 0x1; //Select RXD for PIO1_6
	LPC_IOCON->PIO1_7 = 0x1; //Select RXD for PIO2_6

	//UART CLOCK Enable Sequence Step 2 - Set Divider & Enable Clock
	LPC_SYSCON->UARTCLKDIV = 1; //Set Divider by 1, so UART_PCLK=CCLK
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<12);//Enable UART clock

	LPC_UART->LCR = 3 | DLAB_BIT ; /* 8 bits, no Parity, 1 Stop bit & DLAB set to 1  */
	LPC_UART->DLL = 39;
	LPC_UART->DLM = 0;

	LPC_UART->FCR |= Ux_FIFO_EN | Rx_FIFO_RST | Tx_FIFO_RST;
	LPC_UART->FDR = (MULVAL<<4) | DIVADDVAL; /* MULVAL=15(bits - 7:4) , DIVADDVAL=2(bits - 3:0)  */
	LPC_UART->LCR &= ~(DLAB_BIT);
	//Now since we have applied DLL and DLM we now lock or freeze those values by disabling DLAB i.e DLAB=0
	//Baud= ~115200. Now we can perform UART communication!
}
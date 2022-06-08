#include <lpc13xx.h>

#define THRE        (1<<5) 
#define MULVAL      1
#define DIVADDVAL   0
#define Ux_FIFO_EN  (1<<0)
#define Rx_FIFO_RST (1<<1)
#define Tx_FIFO_RST (1<<2)
#define DLAB_BIT    (1<<7)
#define LINE_FEED   0x0A 
#define CARRIAGE_RETURN 0x0D 

void initUART(void);
void uartWrite(char data);

int main(void)
{
	char msg[] = { 'H','e','l','l','o',' ','f','r','o','m',' ','L','P','C','1','3','4','3','\0' };
	int count=0;

	initUART();

	while(1)
	{
		while( msg[count]!='\0' )
		{
			uartWrite(msg[count]);
			count++;
		}
		
		uartWrite(CARRIAGE_RETURN); 
		uartWrite(LINE_FEED); 
		count=0; 
	}
	
}

void uartWrite(char txData)
{
	while(!(LPC_UART->LSR & THRE));
	LPC_UART->THR = txData;
}

void initUART(void)
{
	
	LPC_IOCON->PIO1_6 = 0x1; 
	LPC_IOCON->PIO1_7 = 0x1; 

	
	LPC_SYSCON->UARTCLKDIV = 1; 
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<12);

	LPC_UART->LCR = 3 | DLAB_BIT ;
	LPC_UART->DLL = 39;
	LPC_UART->DLM = 0;

	LPC_UART->FCR |= Ux_FIFO_EN | Rx_FIFO_RST | Tx_FIFO_RST;
	LPC_UART->FDR = (MULVAL<<4) | DIVADDVAL; 
	LPC_UART->LCR &= ~(DLAB_BIT);
	
}
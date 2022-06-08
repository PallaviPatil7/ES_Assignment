#include <lpc13xx.h>

int main(void)
{
	LPC_GPIO1->DIR &= ~((1<<5)) ; //config PIO1_5 as Input
	LPC_GPIO0->DIR |= (1<<7); //config PIO0_7 as Output

	LPC_GPIO0->DATA &= ~(1<<7); //drive PIO0_7 LOW initially

	while(1)
	{
		if( LPC_GPIO1->DATA & (1<<5) ) //Evaluates to True if PIO1_5 is HIGH
		{
			LPC_GPIO0->DATA |= (1<<7); 
		}
	}
	return 0; //this won't execute normally
}
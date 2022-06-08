#include <lpc13xx.h>
#define delay for(i=0;i<500000;i++);
//#define count 0x0000002;

int main()
{
	
	int i=0;
	LPC_GPIO2->DIR = 0xFFFF;
	 
	//LPC_GPIO2->DATA |= 0x0000000;

while(1){
	
 LPC_GPIO2->DATA |= 0x01;
	//delay;
	/*
	LPC_GPIO2->DATA |= 0x0000000;
	delay;
	LPC_GPIO2->DATA |= 0x0000002;
	delay;
	LPC_GPIO2->DATA |= 0x0000000;
	delay;
	LPC_GPIO2->DATA |= 0x0000003;
	delay;
	LPC_GPIO2->DATA |= 0x0000000;
	delay;
	LPC_GPIO2->DATA |= 0x0000004;
	delay;
	LPC_GPIO2->DATA |= 0x0000000;
	delay;
	LPC_GPIO2->DATA |= 0x0000005;
	delay;
	LPC_GPIO2->DATA |= 0x0000000;
	delay;
	LPC_GPIO2->DATA |= 0x0000006;
	delay;
	LPC_GPIO2->DATA |= 0x0000000;
	delay;
	LPC_GPIO2->DATA |= 0x0000007;
	delay;
	LPC_GPIO2->DATA |= 0x0000000;
	delay;
	LPC_GPIO2->DATA |= 0x0000008;
	delay;
	LPC_GPIO2->DATA |= 0x0000000;
	delay;
	LPC_GPIO2->DATA |= 0x0000009;
	delay;
	LPC_GPIO2->DATA |= 0x0000000;
	delay;
	*/
} 
}


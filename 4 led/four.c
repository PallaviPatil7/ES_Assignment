#include <lpc13xx.h>
#define delay for(i=0;i<30000;i++);

unsigned int i;

int main()
{

LPC_GPIO0->DIR = 0xFFFF;
LPC_GPIO3->DIR = 0xFFFF;
LPC_GPIO2->DIR = 0xFFFF;

while(1)
{

if( !(LPC_GPIO1->DATA & (1<<6)) )
{

LPC_GPIO2->DATA |= (1<<1);
delay;
LPC_GPIO2->DATA &= ~(1<<1);
delay;
LPC_GPIO2->DATA |= (1<<2);
delay;
LPC_GPIO2->DATA &= ~(1<<2);
delay;
LPC_GPIO2->DATA |= (1<<3);
delay;
LPC_GPIO2->DATA &= ~(1<<3);
delay;
LPC_GPIO2->DATA |= (1<<4);
delay;
LPC_GPIO2->DATA &= ~(1<<4);
delay;
}
if( !(LPC_GPIO1->DATA & (1<<5)) )
{

LPC_GPIO2->DATA |= (1<<4);
delay;
LPC_GPIO2->DATA &= ~(1<<4);
delay;
LPC_GPIO2->DATA |= (1<<3);
delay;
LPC_GPIO2->DATA &= ~(1<<3);
delay;
LPC_GPIO2->DATA |= (1<<2);
delay;
LPC_GPIO2->DATA &= ~(1<<2);
delay;
LPC_GPIO2->DATA |= (1<<1);
delay;
LPC_GPIO2->DATA &= ~(1<<1);
delay;
}
}
}

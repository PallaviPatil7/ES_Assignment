#include <lpc13xx.h>
#define delay for(i=0;i<3000;i++);
unsigned int i;
void lcd_int(void);
void dat(unsigned char);
void cmd(unsigned char);
void string(unsigned char *);
int main()
{

LPC_GPIO0->DIR = 0xFFFF;
LPC_GPIO3->DIR = 0xFFFF;
lcd_int();
cmd(0x8a);
string("Hello World");
while(1)
{
	if( !(LPC_GPIO1->DATA & (1<<2)) ){
cmd(0x1C);
delay;
	}
	else
		cmd(0x18);
	delay;
}
}
void lcd_int(void)
{
cmd(0x38);
cmd(0x0c);
cmd(0x06);
cmd(0x01);
cmd(0x80);
}
void cmd(unsigned char a)
{
LPC_GPIO0->DATA = 0x00;
LPC_GPIO0->DATA|=(a<<1);
LPC_GPIO3->DATA &= ~(1<<0);//rs=0
LPC_GPIO3->DATA &= ~(1<<1);//rw=0
LPC_GPIO3->DATA|=(1<<2);
delay;
LPC_GPIO3->DATA &= ~(1<<2);
}
void dat(unsigned char b)
{
LPC_GPIO0->DATA = 0x00;
LPC_GPIO0->DATA|=(b<<1);
LPC_GPIO3->DATA |= (1<<0);//rs=1
LPC_GPIO3->DATA &= ~(1<<1); //rw=0
LPC_GPIO3->DATA|=(1<<2); //en=1
delay;
LPC_GPIO3->DATA &= ~(1<<2);//en=0
}

void string(unsigned char *p)
{
while(*p!='\0') {
dat(*p++);
}
}
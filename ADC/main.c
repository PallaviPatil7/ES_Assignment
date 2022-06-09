/*(C) Umang Gajera - www.ocfreaks.com
LPC1343 ADC Example 1 Source Code using KEIL ARM for CooCox CoIDE
http://www.ocfreaks.com/lpc1343-adc-programming-tutorial/
More Embedded tutorials @ www.ocfreaks.com/cat/embedded/
License : GPL.*/
#include <string.h>
#include <lpc13xx.h>
#include <stdio.h>
//#include "ocf_lpc134x_lib.h" //contains code for UART and Timer.
#define delay for(i=0;i<5000;i++);


unsigned int i;

void lcd_int(void);
void dat(unsigned char);
void cmd(unsigned char);
void string(unsigned char *);


/* Check http://www.ocfreaks.com/retarget-printf-using-uart-coocox-coide/
 * on how to retarget printf() in coocox CoIDE*/

#define VREF       3.3 //Reference Voltage at VREFP pin, given VREFN = 0V(GND)
#define ADC_CLK_EN (1<<13) //Enable ADC Clock
#define SEL_AD0    (1<<0) //Select Channel AD0
#define CLKDIV     15 // ADC clock-divider (ADC_CLOCK=PCLK/CLKDIV+1), yields 4.5Mhz ADC clock
#define ADC_PWRUP  (~(1<<4)) //setting it to 0 will power it up
#define START_CNV  (1<<24) //001 for starting the conversion immediately
#define ADC_DONE   (1U<<31) //define it as unsigned value or compiler will throw warning
#define ADCR_SETUP_SCM (CLKDIV<<8)

int main(void)
{
	//SystemInit(); //Gets called by Startup code, sets CCLK=100Mhz, PCLK=25Mhz

	LPC_SYSCON->PDRUNCFG &= ADC_PWRUP; //Power-up ADC Block
	LPC_SYSCON->SYSAHBCLKCTRL |= ADC_CLK_EN; //Enable ADC clock
	LPC_ADC->CR = ADCR_SETUP_SCM | SEL_AD0; //Setup ADC Block

	/* Now select AD0 function and set ADMODE=0 PIO0_11(P0.11) */
	LPC_IOCON->R_PIO0_11 = 0x2; //Uncomment this if NOT using CoIDE, see tutorial for more.
//	LPC_IOCON->JTAG_TDI_PIO0_11 = 0x2; //comment this if NOT using CoIDE.

	unsigned int result = 0;
	float voltage = 0;
	unsigned char c;
	int mod,milivlt;
 int p;
int k=0;
	int num[4];
	LPC_GPIO0->DIR = 0xFFFF;
	LPC_GPIO3->DIR = 0xFFFF;
	LPC_GPIO0->DIR &= ~((1<<9));
	lcd_int();
	cmd(0xC0);
	while(1)
	{
		if((!(LPC_GPIO0->DATA & (1<<9)))){
		LPC_ADC->CR |= START_CNV; //Start new Conversion
		while((LPC_ADC->DR[0] & ADC_DONE) == 0); //Wait until conversion is finished
		result = (LPC_ADC->DR[0]>>6) & 0x3FF; //10 bit Mask to extract result
		voltage = ((float)result * VREF) / 1024;
		milivlt = (int)(voltage*1000);
		
		while(milivlt>0)
		{
			num[k]=milivlt%10;
			milivlt=milivlt/10;
			k++;
		}
		k--;
		cmd(0x01);
		for (p=k;p>=0;p--)
		{
			c=num[p]+48;
			dat(c);
			cmd(0x1C);
			delay;
		}
		delay; //Slowing down Updates to 2 Updates per second
		k=0;
	}
	else
	{
	string("Press the switch");
	cmd(0x1C);
	cmd(0x01);
	}
	}
	//return 0; //This won't execute
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


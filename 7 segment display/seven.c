#include <lpc13xx.h>
#define delay for(int i=0;i<300000;i++);

int main(){
		LPC_GPIO0->DIR = 0xFFFF;
 while(1) // Infinite loop
    {
LPC_GPIO0->DATA =0x0000007F; // display 0
delay ;
LPC_GPIO0->DATA =0x0000000C; // display 1
delay ;
LPC_GPIO0->DATA =0x000000B6; // display 2
delay ;
LPC_GPIO0->DATA =0x0000009F; // display 3
delay ;
LPC_GPIO0->DATA =0x000000CC; // display 4
delay ;
LPC_GPIO0->DATA =0x000000DA; // display 5
delay ;
LPC_GPIO0->DATA =0x000000FB; // display 6
delay ;
LPC_GPIO0->DATA =0x0000000F; // display 7
delay ;
LPC_GPIO0->DATA =0x000000FF; // display 8
delay ;
LPC_GPIO0->DATA =0x000000DF; // display 9
delay ;
/*LPC_GPIO0->DATA =0x00000008; // display a
delay ;
LPC_GPIO0->DATA =0x00000003; // display b
delay ;
LPC_GPIO0->DATA =0x00000046; // display c
delay ;
LPC_GPIO0->DATA =0x00000021; // display d
delay ;*/
}
}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	/*
	int i; 
	
	unsigned int a[]={0xf3,0x12,0x163,0x133,0x192,0x1b1,0x1f1,0x13,0x1f3,0x1b3}; //integer array with numbers for display

	int main(){
		
		LPC_GPIO0->DIR = 0xFFFF;
		
		while(1)

    {
        for(i=0;i<=9;i++)

        {
					LPC_GPIO0->DATA= LPC_GPIO0->DATA|a[i];           //sets corresponding pins HIGH

            delay ;                  //Calls delay function

           LPC_GPIO0->DATA =~ LPC_GPIO0->DATA|a[i];            //Sets corresponding pins LOW
					    delay ;       
				}
				 return 0;
		}

			}*/
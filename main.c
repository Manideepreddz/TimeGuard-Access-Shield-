#include"types.h"
#include"delay.h"
#include"defines.h"
#include"lcd_defines.h"
#include"pin_defines.h"
#include<lpc21xx.h>

#define EINT0_VIC_CHNO   14
#define EINT0_SWITCH_PIN 1
#define FUNC4            3
extern int password;
u32 entire;
u32 exits;
void eint0_virq_isr() __irq
{
	  u32 key;
	  while(1)
		{			
			CmdLCD(CLEAR_LCD);
			StrLCD("1.RTC 2.IN-OUT");
			CmdLCD(GOTO_LINE2);
			StrLCD("3.PSWD 4.DI 5.EXT");
			key=KeyScan()-48;
			if(key==5)
				break;
			switch(key)
			{
				case 1:Change_RTC();
				       break;
				case 2:Change_IN__Enter_Timings();
				       break;
				case 3:ChangePassword();
				       break;
				case 4:Display_Enter_Timings();
				       break;
			}
		}
	 EXTINT=1<<0;
	VICVectAddr=0;
}

int main()
{
	  u32 key;
	  IODIR0=1<<LED_SWITCH;
	  Init_RTC();
	  Init_KPM();
	  Init_LCD();
	  
	PINSEL0=(PINSEL0&~(3<<(EINT0_SWITCH_PIN*2)))|(FUNC4<<(EINT0_SWITCH_PIN*2));
	
	VICIntEnable=1<<EINT0_VIC_CHNO;
	VICVectCntl0=1<<5|EINT0_VIC_CHNO;
	VICVectAddr0=(u32)eint0_virq_isr;
	EXTMODE=1<<0;
	  CmdLCD(CLEAR_LCD);
	  StrLCD("WELCOME TO ARM");
	  CmdLCD(GOTO_LINE2);
	  StrLCD("VECTOR PROJECT");
	  delay_ms(500);
	while(1)
	{
		IOCLR0=1<<LED_SWITCH;
		Display_RTC();
		if(ColScan()==0)
		{
			key=KeyScan();
			if(key=='E')
			{
					Check_Password(entire,exits);	
			}
		}
	}
}
 


#include<lpc21xx.h>
#include"pin_defines.h"
#include"lcd_defines.h"
#include"delay.h"
#include"types.h"
#include"defines.h"
extern u32 entire;
extern u32 exits;
u8 KpmLUT[4][4]=
{
	{'0','1','2','3'},
	{'4','5','6','7'},
	{'8','9','B','E'},
	{'K','0','0','0'}
};

u32 password=1234;

void Init_KPM(void)
{
		IODIR1|=(0XF)<<ROW_4;
}
u32  ColScan(void)
{
		int status;
		status=(((IOPIN1>>COL_4)&0XF)<15)?0:1;
		return status;
}
u32  RowCheck(void)
{
	  u32 r;
	  for(r=0;r<=3;r++)
	  {
			IOPIN1=(IOPIN1&~(0XF<<ROW_4))|(~(1<<r)<<ROW_4);
			if(ColScan()==0)
				break;
		}
		IOCLR1=0XF<<ROW_4;
		return r;
}
u32  ColCheck(void)
{
		u32 c;
		for(c=0;c<=3;c++)
		{
			if(((IOPIN1>>(COL_4+c))&1)==0)
				break;
		}
		return c;
}
u8  KeyScan(void)
{
	  //Init_KPM();
		u32 r,c;
	  u8 key;
		while(ColScan());
		r=RowCheck();
		c=ColCheck();
	  key=KpmLUT[r][c];
		while(ColScan()==0);
	  return key;
}
	
void Check_Password(u32 entire,u32 exits)
{
	u32 count=0,num=0,attempt=3,value=HOUR;
	u8 key=0;
	CmdLCD(CLEAR_LCD);
	CmdLCD(GOTO_LINE1);
	StrLCD("Enter Password");
	CmdLCD(GOTO_LINE2);
	if(entire>value)
	{
		if(value<exits)
		{
			CmdLCD(CLEAR_LCD);
			CmdLCD(GOTO_LINE1);
			StrLCD("ENTER PWD IN LOGIN ");
			CmdLCD(GOTO_LINE2);
			StrLCD("TIMINGS FROM 5-8");
			delay_ms(500);
		}
	}
	else
	{
		while(1)
		{
				key=KeyScan();
			  if(key=='B')
        {
          CmdLCD(CLEAR_LCD);
					 CmdLCD(GOTO_LINE1);
					 StrLCD("Enter Password:");
					 num=num/10;
					 count--;
					 delete_space_password(count);
        }
				if(key>='0' && key<='9')
        {
					CharLCD('*');
					num=num*10+(key-48);
					delay_ms(10);
					count++;
				}
				if((count==4) &&(num!=password))
				{
						attempt--;
						CmdLCD(CLEAR_LCD);
						if(attempt>=1)
						{
									U32LCD(attempt);
									StrLCD(" attempt left");
									delay_ms(500);
									CmdLCD(CLEAR_LCD);
									 CmdLCD(GOTO_LINE1);
									 StrLCD("Enter Password:");
							     CmdLCD(GOTO_LINE2);
									count=0;
									num=0;
						}
						else
						{
									StrLCD("failed to open");
									delay_ms(500);
									
						}
				}
				if(count==4)
					break;
				delay_ms(1);
				while(ColScan()==0);
	  }
	}
	if(num==password)
	{
		CmdLCD(CLEAR_LCD);
		StrLCD("Success opened");
		IOSET0=1<<LED_SWITCH;
		delay_ms(500);
	}
}

void ChangePassword(void)
{
	s32 count=0,num=0;
	u8 key=0;
	CmdLCD(CLEAR_LCD);
	StrLCD("NEW PASSWORD");
	CmdLCD(GOTO_LINE2);
	while(1)
	{
			 key=KeyScan();
			  if(key=='B' && count<0)
        {
          CmdLCD(CLEAR_LCD);
					 CmdLCD(GOTO_LINE1);
					 StrLCD("NEW PASSWORD:");
					 num=num/10;
					 count--;
					 delete_space_password(count);
        }
				if(key>='0' && key<='9')
        {
					CharLCD('*');
					num=num*10+(key-48);
					delay_ms(10);
					count++;
				}
			if(count==4)
				break;
			while(ColScan()==0);
	}
	password=num;
}
void delete_space_password(u32 count)
{
	u32 i;
	CmdLCD(GOTO_LINE2);
	for(i=0;i<count;i++)
	   CharLCD('*');
}
void Display_Enter_Timings(void)
{
	CmdLCD(CLEAR_LCD);
	StrLCD("ENTIRE TIME:-");
	U32LCD(entire);
	CmdLCD(GOTO_LINE2);
	StrLCD("EXIT TIME:-");
	U32LCD(exits);
	delay_ms(500);
}
void Change_IN__Enter_Timings(void)
{
	u32 op,key,data;
	CmdLCD(CLEAR_LCD);
	StrLCD("CHANGE IN ENTIRE:");
	CmdLCD(GOTO_LINE2);
	StrLCD("1.YES 2.NO");
	op=KeyScan()-48;
	if(op==1)
	{
		data=0;
		CmdLCD(CLEAR_LCD);
     CmdLCD(GOTO_LINE1);
     StrLCD("NEW ENTIRE TIME:");
		CmdLCD(GOTO_LINE2);
		while(1)
		{
			key=KeyScan();
			if(key=='B')
			{
				CmdLCD(CLEAR_LCD);
        CmdLCD(GOTO_LINE1);
        StrLCD("NEW ENTIRE TIME:");
				data/=10;
				CmdLCD(GOTO_LINE2);
				U32LCD(data);
			}
			if(key=='K')
				break;
			if(key>='0' && key<='9')
			{
				U32LCD(key-48);
        data=(data*10)+(key-48);
			}
		}
		entire=data;
	}
	CmdLCD(CLEAR_LCD);
	StrLCD("CHANGE IN EXIT:");
	CmdLCD(GOTO_LINE2);
	StrLCD("1.YES 2.NO");
	op=KeyScan()-48;
	if(op==1)
	{
		data=0;
		CmdLCD(CLEAR_LCD);
     CmdLCD(GOTO_LINE1);
     StrLCD("NEW EXIT TIME:");
		CmdLCD(GOTO_LINE2);
		while(1)
		{
			key=KeyScan();
			if(key=='B')
			{
				CmdLCD(CLEAR_LCD);
        CmdLCD(GOTO_LINE1);
        StrLCD("NEW EXIT TIME:");
				data/=10;
				CmdLCD(GOTO_LINE2);
				U32LCD(data);
			}
			if(key=='K')
				break;
			if(key>='0' && key<='9')
			{
				U32LCD(key-48);
        data=(data*10)+(key-48);
			}
		}
		exits=data;
	}
}

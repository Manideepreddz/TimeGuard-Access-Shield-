#include<lpc21xx.h>
#include"types.h"
#include"delay.h"
#include"lcd_defines.h"
#include"pin_defines.h"

void WriteLCD(u8 Byte)
{
		IOCLR0=1<<LCD_RW;
		IOPIN0=(IOPIN0&~(0XFF<<LCD_DATA))|(Byte<<LCD_DATA);
		IOSET0=1<<LCD_EN;
		delay_us(1);
		IOCLR0=1<<LCD_EN;
	  delay_ms(2);
}
void CmdLCD(u8 cmdByte)
{
		IOCLR0=1<<LCD_RS;
		WriteLCD(cmdByte);
}
void Init_LCD()
{
		IODIR0|=((0XFF)<<LCD_DATA)|(1<<LCD_RS)|(1<<LCD_RW)|(1<<LCD_EN);
		delay_ms(15);
		CmdLCD(MODE_8BIT_LINE1);
	  delay_ms(4);
		delay_us(4100);
		CmdLCD(MODE_8BIT_LINE1);
		delay_us(100);
		CmdLCD(MODE_8BIT_LINE1);
		CmdLCD(MODE_8BIT_LINE2);
		CmdLCD(DSP_ON_CUR_ON);
		CmdLCD(CLEAR_LCD);
		CmdLCD(SHIFT_CUR_RIGHT);
}
void CharLCD(u8 ascii)
{
		IOSET0=1<<LCD_RS;
		WriteLCD(ascii);
}
void U32LCD(u32 data)
{
	  u8 arr[10];
	  s32 i=0;
		if(data==0)
			CharLCD('0');
		else
		{
		while(data)
		{
			arr[i++]=(data%10)+48;
			data=data/10;
		}
		for(--i;i>=0;i--)
			CharLCD(arr[i]);
	}
}
void S32LCD(s32 data)
{
		if(data<0)
		{
			CharLCD('-');
			data=-data;
		}
		U32LCD(data);
}
void StrLCD(u8 *str)
{
		while(*str)
			CharLCD(*str++);
}
void F32LCD(f32 fn,u32 Dp)
{
		u32 n,i;
		if(fn<0.0)
		{
			CharLCD('-');
			fn=-fn;
		}
		n=fn;
		U32LCD(n);
		CharLCD('.');
		for(i=0;i<Dp;i++)
		{
			fn=(fn-n)*10;
			n=fn;
			CharLCD(n+48);
		}
}
//void BuildCGRAM(u8* ptr,u8 nByte);

#include"types.h"
#include"delay.h"
#include"defines.h"
#include"lcd_defines.h"
#include"pin_defines.h"
#include<lpc21xx.h>
#include<stdlib.h>
#define FOSC 12000000
#define CCLK (5*FOSC)
#define PCLK (CCLK/4)

#define PREINT_VAL ((int)((PCLK / 32768) - 1))
#define PREFRAC_VAL (PCLK - ((PREINT_VAL+1)*32768))

s8 week[][4] = {"SUN","MON","TUE","WED","THU","FRI","SAT"}; 
void Init_RTC()
{
    CCR=1<<1;
    PREINT = PREINT_VAL;
    PREFRAC = PREFRAC_VAL;
    CCR=(1<<0);
}
void print_Menu()
{
    CmdLCD(CLEAR_LCD);
    StrLCD("1.H2.MI3.S4.DATE");
    CmdLCD(GOTO_LINE2);
    StrLCD("5.MO6.YE7.DY8.DI9.E");
}
void Change_RTC()
{
    u32 rtc;
    CmdLCD(CLEAR_LCD);
    while(1)
    {
        print_Menu();
        rtc=KeyScan()-48;
        if(rtc==9)
            break;
        switch(rtc)
        {
            case 1:Change_HOURS();
                   break;
            case 2:Change_MINS();
                     break;
            case 3:Change_SECS();
                     break;
            case 4:Change_DATES();
                     break;
            case 5:Change_MONTHS();
                     break;
            case 6:Change_YEARS();
                    break;
            case 7:Change_DAYS();
                    break;
            case 8:Display_RTC();
                     break;
     }
  }
}
void Display_RTC()
{
        CmdLCD(GOTO_LINE1);
        CmdLCD(CLEAR_LCD);
        CharLCD((HOUR/10)+48);
        CharLCD((HOUR%10)+48);
        CharLCD(':');
        CharLCD((MIN/10)+0x30);
        CharLCD((MIN%10)+0x30);
        CharLCD(':');
        CharLCD((SEC/10)+'0');
        CharLCD((SEC%10)+'0');
        CmdLCD(GOTO_LINE1+10);
        StrLCD(week[DOW]);
        
        CmdLCD(GOTO_LINE2);
        CharLCD((DOM/10)+48);
        CharLCD((DOM%10)+48);
        CharLCD('/');
        CharLCD((MONTH/10)+48);
        CharLCD((MONTH%10)+48);
        CharLCD('/');
        U32LCD(YEAR);
        delay_ms(500);
}

void Change_HOURS(void)
{
    u32 hour=0,count=0;
    u8 key;
    CmdLCD(CLEAR_LCD);
    CmdLCD(GOTO_LINE1);
    StrLCD("HOURS VALUE:");
    CmdLCD(GOTO_LINE2);
    while(1)
    {
        key=KeyScan();
        if(key=='K')
              break;
        if(key=='B')
        {
          CmdLCD(CLEAR_LCD);
       CmdLCD(GOTO_LINE1);
       StrLCD("HOURS VALUE:");
             hour=hour/10;
             delete_space(hour);
        }
        if(key>='0' && key<='9')
        {
         U32LCD(key-48);
            hour=(hour*10)+(key-48);
            count++;
        }
        if(hour>23)
      {
          Invalid_Input();
             hour=0;
             count=0;
            StrLCD("HOURS VALUE:");
        CmdLCD(GOTO_LINE2);
        }
        delay_ms(100);
        while(ColScan()==0);
    }
    HOUR=hour;
    
}
void Change_MINS(void)
{

    u32 min=0,count=0,key;
    CmdLCD(CLEAR_LCD);
    CmdLCD(GOTO_LINE1);
    StrLCD("MINUTES VALUE:");
    CmdLCD(GOTO_LINE2);
    while(1)
    {
            key=KeyScan();
        if(key=='K')
              break;
        if(key=='B')
        {
            CmdLCD(CLEAR_LCD);
       CmdLCD(GOTO_LINE1);
       StrLCD("MINUTES VALUE:");
             min=min/10;
             delete_space(min);
        }
        if(key>='0' && key<='9')
        {
            U32LCD(key-48);
            min=(min*10)+(key-48);
            count++;
        }
        if(min>59)
      {
          Invalid_Input();
            min=0;
            count=0;
            StrLCD("MINUTES VALUE:");
        CmdLCD(GOTO_LINE2);
        }
        delay_ms(100);
        while(ColScan()==0);
    }
    MIN=min;
    
}
void Change_SECS(void)
{
    u32 sec=0,count=0,key;
    CmdLCD(CLEAR_LCD);
    CmdLCD(GOTO_LINE1);
    StrLCD("SECONDS VALUE");
    CmdLCD(GOTO_LINE2);
    while(1)
    {
            key=KeyScan();
        if(key=='K')
              break;
        if(key=='B')
        {
            CmdLCD(CLEAR_LCD);
       CmdLCD(GOTO_LINE1);
       StrLCD("SECONDS VALUE:");
             sec=sec/10;
             delete_space(sec);
        }
        if(key>='0' && key<='9')
        {
            U32LCD(key-48);
            sec=(sec*10)+(key-48);
            count++;
        }
        if(sec>59)
      {
          Invalid_Input();
            sec=0;
            count=0;
            StrLCD("SECONDS VALUE");
        CmdLCD(GOTO_LINE2);
        }
        delay_ms(100);
        while(ColScan()==0);
    }
    SEC=sec;
    
}
void Change_DATES(void)
{
    u32 date=0,count=0,key;
    CmdLCD(CLEAR_LCD);
    CmdLCD(GOTO_LINE1);
    StrLCD("DATE VALUE");
    CmdLCD(GOTO_LINE2);
    while(1)
    {
        key=KeyScan();
        if(key=='K')
              break;
        if(key=='B')
        {
            CmdLCD(CLEAR_LCD);
       CmdLCD(GOTO_LINE1);
       StrLCD("DATE VALUE:");
             date=date/10;
             delete_space(date);
        }
        if(key>='0' && key<='9')
        {
            U32LCD(key-48);
            date=(date*10)+(key-48);
            count++;
        }
        if(date>31)
      {
          Invalid_Input();
            StrLCD("DATE VALUE");
        CmdLCD(GOTO_LINE2);
            date=0;
            count=0;
        }
            delay_ms(100);
        while(ColScan()==0);
    }
    DOM=date;
    
}
void Change_MONTHS(void)
{
    u32 months=0,count=0,key;
    CmdLCD(CLEAR_LCD);
    CmdLCD(GOTO_LINE1);
    StrLCD("MONTH VALUE");
    CmdLCD(GOTO_LINE2);
    delay_ms(500);
    while(1)
    {
        key=KeyScan();
        if(key=='K')
              break;
        if(key=='B')
        {
            CmdLCD(CLEAR_LCD);
       CmdLCD(GOTO_LINE1);
       StrLCD("MONTH VALUE:");
             months=months/10;
             delete_space(months);
        }
        if(key>='0' && key<='9')
        {
            U32LCD(key-48);
            months=(months*10)+(key-48);
            count++;
        }
        if(months>12)
      {
          Invalid_Input();
            StrLCD("MONTH VALUE");
      CmdLCD(GOTO_LINE2);
            months=0;
            count=0;
        }
        delay_ms(100);
        while(ColScan()==0);
    }
    MONTH=months;
    
}
void Change_YEARS(void)
{
    u32 year=0,count=0,key;
    CmdLCD(CLEAR_LCD);
    CmdLCD(GOTO_LINE1);
    StrLCD("YEAR VALUE");
    CmdLCD(GOTO_LINE2);
    while(1)
    {
     key=KeyScan();
        if(key=='K')
              break;
        if(key=='B')
        {
             CmdLCD(CLEAR_LCD);
       CmdLCD(GOTO_LINE1);
       StrLCD("YEAR VALUE:");
             year=year/10;
             delete_space(year);
        }
        if(key>='0' && key<='9')
        {
            U32LCD(key-48);
            year=(year*10)+(key-48);
            count++;
        }
        if(year>4096)
      {
          Invalid_Input();
            year=0;
            count=0;
            CmdLCD(GOTO_LINE1);
         StrLCD("YEAR VALUE");
            CmdLCD(GOTO_LINE2);
        }
        delay_ms(100);
        while(ColScan()==0);
    }
    YEAR=year;
    
}
void Change_DAYS(void)
{
    u32 day=0,count=0,key;
    CmdLCD(CLEAR_LCD);
    CmdLCD(GOTO_LINE1);
    StrLCD("DAYS VALUE");
    CmdLCD(GOTO_LINE2);
    while(1)
    {
        key=KeyScan();
        if(key=='K')
              break;
        if(key=='B')
        {
             CmdLCD(CLEAR_LCD);
       CmdLCD(GOTO_LINE1);
       StrLCD("DAYS VALUE:");
             day=day/10;
             delete_space(day);
        }
        if(key>='0' && key<='9')
        {
            U32LCD(key-48);
            day=(day*10)+(key-48);
            count++;
        }
        if(day>7)
      {
          Invalid_Input();
            day=0;
            count=0;
            CmdLCD(GOTO_LINE1);
          StrLCD("DAYS VALUE");
            CmdLCD(GOTO_LINE2);
        }
        delay_ms(100);
        while(ColScan()==0);
    }
    DOW=day;
}
void Invalid_Input()
{
            CmdLCD(CLEAR_LCD);
            CmdLCD(GOTO_LINE1);
             StrLCD("INVALID INPUT");
            CmdLCD(GOTO_LINE2);
            StrLCD("RE-ENTER AGAIN ");
            delay_ms(500);
            CmdLCD(CLEAR_LCD);
}
void delete_space(u32 value)
{
 CmdLCD(GOTO_LINE2);
    U32LCD(value);
}

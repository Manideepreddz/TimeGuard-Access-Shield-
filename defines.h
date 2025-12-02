#ifndef __DEFINES_H__
#define __DEFINES_H__

#include"types.h"

void Init_LCD(void);
void CmdLCD(u8 cmdbyte);
void WriteLCD(u8 Byte);
void U32LCD(u32 data);
void S32LCD(s32 data);
void CharLCD(u8 ascii);
void StrLCD(s8 *str);
void F32LCD(f32 fn,u32 Dp);
//void BuildCGRAM(u8* ptr,u8 nByte);

void Init_KPM(void);
u32  ColScan(void);
u32  RowCheck(void);
u32  ColCheck(void);
u8   KeyScan(void);
void  Check_Password(u32,u32);
void ChangePassword(void);
void delete_space_password(u32);

void Init_RTC(void);
void Change_RTC(void);
void Change_HOURS(void);
void Change_MINS(void);
void Change_SECS(void);
void Change_DATES(void);
void Change_MONTHS(void);
void Change_YEARS(void);
void Change_DAYS(void);
void Display_RTC(void);
void Invalid_Input(void);
void delete_space(u32);
void Display_Enter_Timings(void);
void Change_IN__Enter_Timings(void);

void eint0_virq_isr(void) __irq;

#endif

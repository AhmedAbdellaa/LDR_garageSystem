#ifndef CLCD_INTERFACE_H
#define CLCD_INTERFACE_H

#define CLCD_CLEAR_CMD 0X01
#define CLCD_RESETCURSOR_CMD 0X10


void CLCD_VoidSendCommand(uint8 copy_u8command);
void CLCD_VoidSendData(uint8 copy_u8Data);
void CLCD_VoidInit(void);

void CLCD_voidGoToXY(uint8 copy_u8xPos,uint8 copy_Ypos);
uint8 CLCD_u8WriteSpecialChar(uint8 copy_u8PatternNumber,uint8* copy_pu8PatternArr);

void CLCD_VoidPrintChars(const uint8* copy_u8charArray);
void CLCD_VoidPrintInt(sint32 copy_u32number);
void CLCD_VoidPrintFloat(sint32 copy_s32IntegerPart,uint32 copy_s32FloatingPart);

#endif

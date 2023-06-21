/***************************************************************************************************************************/
/***************************************************************************************************************************/
/************************************        @layer		: HAL                     ******************************************/
/************************************        @swc 		: CLCD_interface.h        ******************************************/
/************************************        @author	: Ahmed Gomaa             ******************************************/
/************************************        @version	: 1.0                     ******************************************/
/************************************        @date		:                         ******************************************/
/***************************************************************************************************************************/
/***************************************************************************************************************************/
#ifndef CLCD_INTERFACE_H
#define CLCD_INTERFACE_H



#define CLCD_u8_LINE_ONE  			 0
#define CLCD_u8_LINE_TWO   			 1

void  CLCD_voidSendCommand(uint8 copy_u8Command);
void  CLCD_voidSendData(uint8 copy_u8Data);
void  CLCD_voidInit(void);
uint8 CLCD_voidSendString(char* copy_pchString);
void  CLCD_voidWriteNumber(sint32 copy_u8Number);
void  CLCD_voidGoToXY(uint8 copy_u8Xpos,uint8 copy_u8Ypos);
uint8 CLCD_u8WriteSpecialCharacter(uint8 copy_u8PatternNumber,uint8 copy_pu8PatternArray[], uint8 copy_u8Xpos,uint8 copy_u8Ypos);
void  CLCD_voidSendNumber(sint8 Copy_u32Number);

#endif

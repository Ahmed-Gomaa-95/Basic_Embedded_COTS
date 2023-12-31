/***************************************************************************************************************************/
/***************************************************************************************************************************/
/************************************        @layer		: HAL                     ******************************************/
/************************************        @swc 		: CLCD_prv.h              ******************************************/
/************************************        @author	: Ahmed Gomaa             ******************************************/
/************************************        @version	: 1.0                     ******************************************/
/************************************        @date		:                         ******************************************/
/***************************************************************************************************************************/
/***************************************************************************************************************************/
#ifndef CLCD_PRV_H
#define CLCD_PRV_H




#define CLCD_LINE_TWO_OFFSET   0x40

#if CLCD_u8CONNECTION_MODE == FOUR_BIT
static void SetHalfDataPort(uint8 Copy_u8FourBitData);
#endif

void voidSendEnablePulse(void);

sint32 ReverseNumber(sint32 Number)
{
	sint32 ReversedNumber = 1;

	while(Number != 0)
	{
		ReversedNumber = (ReversedNumber*10) + (Number%10);
		Number /= 10;
	}


	return ReversedNumber;
}

#endif

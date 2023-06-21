
/***************************************************************************************************************************/
/***************************************************************************************************************************/
/************************************        @layer		: HAL                     ******************************************/
/************************************        @swc 		: CLCD_prog.c             ******************************************/
/************************************        @author	: Ahmed Gomaa             ******************************************/
/************************************        @version	: 1.0                     ******************************************/
/************************************        @date		:                         ******************************************/
/***************************************************************************************************************************/
/***************************************************************************************************************************/

#include "STD_TYPES.h"
#include <util/delay.h>
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "CLCD_interface.h"
#include "CLCD_cfg.h"
#include "CLCD_prv.h"
#include "ERROR_TYPES.h"


/**********************************************************************************************************************/
/**********************************************************************************************************************/
/*****                                                                                                            *****/
/***** @Function Name 		  : CLCD_voidSendCommand                                                              *****/
/***** @Function Description  : function sends command to lcd to configure it                                     *****/
/***** @Function Parameters   :  copy_u8Command : unsigned character number that contain command to send.         *****/
/***** @Function Return       :  void																	          *****/
/*****                                                                                                            *****/
/**********************************************************************************************************************/
/**********************************************************************************************************************/
void CLCD_voidSendCommand(uint8 copy_u8Command)
{
	/* 1 - Set RS pin to low for command  */
	DIO_u8SetPinValue(CLCD_u8CTRL_PORT,CLCD_u8RS_PIN,DIO_PIN_LOW);
	/* 2 - Set RW pin to low for write  */
#if CLCD_u8READ_OPERATION_ENABLE == ENABLED
	DIO_u8SetPinValue(CLCD_u8CTRL_PORT,CLCD_u8RW_PIN,DIO_PIN_LOW);
#endif

#if CLCD_u8CONNECTION_MODE == EIGHT_BIT
	/* 3 - Send the command  */
	DIO_u8SetPortValue(CLCD_u8DATA_PORT,copy_u8Command);
	/* 4 - Enable  */
	DIO_u8SetPinValue(CLCD_u8CTRL_PORT,CLCD_u8EN_PIN,DIO_PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(CLCD_u8CTRL_PORT,CLCD_u8EN_PIN,DIO_PIN_LOW);
#elif CLCD_u8CONNECTION_MODE == FOUR_BIT
	/*Send the higher 4 bits */
	SetHalfDataPort(copy_u8Command >> 4u);
	/* send enable pulse  */
	voidSendEnablePulse();
	/*Send the lower 4 bits of command  */
	SetHalfDataPort(copy_u8Command );
	/* send enable pulse  */
	voidSendEnablePulse();

#endif

}
/**********************************************************************************************************************/
/**********************************************************************************************************************/
/*****                                                                                                            *****/
/***** @Function Name 		  : CLCD_voidSendData                                                                 *****/
/***** @Function Description  :                             													  *****/
/***** @Function Parameters   :                                                                                   *****/
/***** 						   1- copy_Port   : enum called DIO_Port_t contains ports A,B, C and D                *****/
/***** 						   2- copy_PinNum : enum called DIO_Pin_t contains pins from 0 to 7                   *****/
/***** 						   3- copy_PinDir : enum called DIO_PinDir_t contains direction input and output      *****/
/***** @Function Return       :  function return an error state that can be OK or NOT_OK or NULL_POINTER          *****/
/*****                                                                                                            *****/
/**********************************************************************************************************************/
/**********************************************************************************************************************/
void CLCD_voidSendData(uint8 copy_u8Data)
{
	/* 1 - Set RS pin to low for data  */
	DIO_u8SetPinValue(CLCD_u8CTRL_PORT,CLCD_u8RS_PIN,DIO_PIN_HIGH);
	/* 2 - Set RW pin to low for write  */
#if CLCD_u8READ_OPERATION_ENABLE == ENABLED
	DIO_u8SetPinValue(CLCD_u8CTRL_PORT,CLCD_u8RW_PIN,DIO_PIN_LOW);
#endif

#if CLCD_u8CONNECTION_MODE == EIGHT_BIT
	/* 3 - Send the data */
	DIO_u8SetPortValue(CLCD_u8DATA_PORT,copy_u8Data);
	/* 4 - send the enable  */
	DIO_u8SetPinValue(CLCD_u8CTRL_PORT,CLCD_u8EN_PIN,DIO_PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(CLCD_u8CTRL_PORT,CLCD_u8EN_PIN,DIO_PIN_LOW);
#elif CLCD_u8CONNECTION_MODE == FOUR_BIT
	/*Send the higher 4 bits of the data */
	SetHalfDataPort(copy_u8Data >> 4u);
	/* send enable pulse  */
	voidSendEnablePulse();
	/*Send the lower 4 bits of the data  */
	SetHalfDataPort(copy_u8Data);
	/* send enable pulse  */
	voidSendEnablePulse();


#endif

}
/**********************************************************************************************************************/
/**********************************************************************************************************************/
/*****                                                                                                            *****/
/***** @Function Name 		  : CLCD_voidInit                                                             *****/
/***** @Function Description  :                             														 *****/
/***** @Function Parameters   :                                                                                   *****/
/***** 						   1- copy_Port   : enum called DIO_Port_t contains ports A,B, C and D                *****/
/***** 						   2- copy_PinNum : enum called DIO_Pin_t contains pins from 0 to 7                   *****/
/***** 						   3- copy_PinDir : enum called DIO_PinDir_t contains direction input and output      *****/
/***** @Function Return       :  function return an error state that can be OK or NOT_OK or NULL_POINTER          *****/
/*****                                                                                                            *****/
/**********************************************************************************************************************/
/**********************************************************************************************************************/
void CLCD_voidInit(void)
{
	/* 1- wait for more than 30 ms after power on */
	_delay_ms(40);

	/* 2- Function set : 2 lines , font size 5x7 */
#if CLCD_u8CONNECTION_MODE == EIGHT_BIT
	CLCD_voidSendCommand(0b00111000);
#elif CLCD_u8CONNECTION_MODE ==  FOUR_BIT
	SetHalfDataPort(0b0010);
	voidSendEnablePulse();
	SetHalfDataPort(0b0010);
	voidSendEnablePulse();
	SetHalfDataPort(0b1000);
	voidSendEnablePulse();
#endif
	/* 3- Display ON/OFF Control : Display on , cursor off , blink cursor off */
	CLCD_voidSendCommand(0b00001100);
	/* 4- Display Clear */
	CLCD_voidSendCommand(1);

}
/**********************************************************************************************************************/
/**********************************************************************************************************************/
/*****                                                                                                            *****/
/***** @Function Name 		  :  CLCD_voidSendString                                                              *****/
/***** @Function Description  :  function display string on lcd                       							  *****/
/***** @Function Parameters   :  copy_pchString   : pointer to character that contain the sting to display        *****/
/***** @Function Return       :  function return an error state that can be OK or NOT_OK or NULL_POINTER          *****/
/*****                                                                                                            *****/
/**********************************************************************************************************************/
/**********************************************************************************************************************/
uint8 CLCD_voidSendString(char* copy_pchString)
{
	uint8 Local_u8ErrorState = OK;
	/* check if the pointer to string is null or not */
	if(copy_pchString == NULL)
	{
		Local_u8ErrorState = NULL_POINTER;  /* assign state error with null pointer */
	}
	else
	{
		/* loop over string till it reach null character */
		while(*copy_pchString != '\0')
		{
			/* Send character by character  */
			CLCD_voidSendData(*copy_pchString);
			copy_pchString++;

		}
	}
	return Local_u8ErrorState;

}
/**********************************************************************************************************************/
/**********************************************************************************************************************/
/*****                                                                                                            *****/
/***** @Function Name 		  : CLCD_voidWriteNumber                                                              *****/
/***** @Function Description  :                             													  *****/
/***** @Function Parameters   : copy_u8Number   : signed integer number to display on screen               		  *****/
/***** @Function Return		  : void                                                                              *****/
/*****                                                                                                            *****/
/**********************************************************************************************************************/
/**********************************************************************************************************************/
void CLCD_voidWriteNumber(sint32 copy_u8Number)
{
	char Local_chNumber[32];
	uint8 Local_u8RightDigit;
	uint8 Local_u8Counter = 0;
	if(copy_u8Number == 0)
	{
		CLCD_voidSendData('0');
		return;
	}
	else
	{
		if(copy_u8Number < 0)
		{
			CLCD_voidSendData('-');
			copy_u8Number *= -1;
		}

		while(copy_u8Number != 0)
		{
			Local_u8RightDigit = copy_u8Number % 10 + '0';
			Local_chNumber[Local_u8Counter] = Local_u8RightDigit;
			copy_u8Number /= 10;
			Local_u8Counter++;
		}
		while(Local_u8Counter >= 1 )
		{
			CLCD_voidSendData(Local_chNumber[Local_u8Counter - 1 ]);
			Local_u8Counter--;
		}
	}



}


/**********************************************************************************************************************/
/**********************************************************************************************************************/
/*****                                                                                                            *****/
/***** @Function Name 		  : CLCD_voidGoToXY                                                                   *****/
/***** @Function Description  :  function to go to position that user want to go                          		  *****/
/***** @Function Parameters   :                                                                                   *****/
/***** 						   1- copy_u8Xpos   : unsigned character X position to go				              *****/
/***** 						   2- copy_u8Ypos   : unsigned character Y position to go                			  *****/
/***** @Function Return		  : void                                                                              *****/
/*****                                                                                                            *****/
/**********************************************************************************************************************/
/**********************************************************************************************************************/
void CLCD_voidGoToXY(uint8 copy_u8Xpos,uint8 copy_u8Ypos)
{

	uint8 Local_u8DDRamAddress = copy_u8Ypos * CLCD_LINE_TWO_OFFSET + copy_u8Xpos;

	/* or
	if(copy_u8Ypos == CLCD_u8_LINE_ONE)
	{
		Local_u8DDRamAddress = copy_u8Xpos;
	}
	else if(copy_u8Ypos == CLCD_u8_LINE_TWO)
	{
		Local_u8DDRamAddress = CLCD_LINE_TWO_OFFSET * copy_u8Ypos + copy_u8Xpos;
	}
	 */

	/* Set bit 7 for setting DDRam address */
	SET_BIT(Local_u8DDRamAddress,7);

	CLCD_voidSendCommand(Local_u8DDRamAddress);

}

/**********************************************************************************************************************/
/**********************************************************************************************************************/
/*****                                                                                                            *****/
/***** @Function Name 		  : SetHalfDataPort                                                                   *****/
/***** @Function Description  : Set the half port bits to the data port                            				  *****/
/***** @Function Parameters   : Copy_u8FourBitData : unsigned character variable contain half port bits           *****/
/***** @Function Return		  : void                                                                              *****/
/*****                                                                                                            *****/
/**********************************************************************************************************************/
/**********************************************************************************************************************/
#if CLCD_u8CONNECTION_MODE == FOUR_BIT
static void SetHalfDataPort(uint8 Copy_u8FourBitData)
{
	DIO_u8SetPinValue(CLCD_u8DATA_PORT,CLCD_u8D4_PIN,GET_BIT(Copy_u8FourBitData,0));
	DIO_u8SetPinValue(CLCD_u8DATA_PORT,CLCD_u8D5_PIN,GET_BIT(Copy_u8FourBitData,1));
	DIO_u8SetPinValue(CLCD_u8DATA_PORT,CLCD_u8D6_PIN,GET_BIT(Copy_u8FourBitData,2));
	DIO_u8SetPinValue(CLCD_u8DATA_PORT,CLCD_u8D7_PIN,GET_BIT(Copy_u8FourBitData,3));
}
#endif

/**********************************************************************************************************************/
/**********************************************************************************************************************/
/*****                                                                                                            *****/
/***** @Function Name 		  : voidSendEnablePulse                                                               *****/
/***** @Function Description  : function to enable LCD to receive data                            				  *****/
/***** @Function Parameters   : void																	          *****/
/***** @Function Return		  : void                                                                              *****/
/*****                                                                                                            *****/
/**********************************************************************************************************************/
/**********************************************************************************************************************/
void voidSendEnablePulse(void)
{
	DIO_u8SetPinValue(CLCD_u8CTRL_PORT,CLCD_u8EN_PIN,DIO_PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(CLCD_u8CTRL_PORT,CLCD_u8EN_PIN,DIO_PIN_LOW);
}

/**********************************************************************************************************************/
/**********************************************************************************************************************/
/*****                                                                                                            *****/
/***** @Function Name 		  : CLCD_u8WriteSpecialCharacter                                                      *****/
/***** @Function Description  : function to write a special pattern on LCD                            			  *****/
/***** @Function Parameters   :																					  *****/
/*****	 	 	 	 	 	 	1- copy_u8PatternNumber : unsigned character location to save the pattern in it   *****/
/*****                          2- copy_pu8PatternArray : unsigned character array contain pattern                *****/
/***** 						    3- copy_u8Xpos   : unsigned character X position to go				              *****/
/***** 						    4- copy_u8Ypos   : unsigned character Y position to go                			  *****/
/***** @Function Return		  : Local_u8ErrorState: unsigned character error state                                *****/
/*****                                                                                                            *****/
/**********************************************************************************************************************/
/**********************************************************************************************************************/
uint8 CLCD_u8WriteSpecialCharacter(uint8 copy_u8PatternNumber,uint8 copy_pu8PatternArray[], uint8 copy_u8Xpos,uint8 copy_u8Ypos)
{
	uint8 Local_u8ErrorState = OK;

	if(copy_pu8PatternArray != NULL)
	{
		uint8 Local_u8CGRamAddress = copy_u8PatternNumber * 8u;
		uint8 Local_u8Itrator;
		/* Set Bit 6 and clear Bit 7 for setting CGRAM address command */
		SET_BIT(Local_u8CGRamAddress,6u);

		/*Set CGRAM Address*/
		CLCD_voidSendCommand(Local_u8CGRamAddress);
		/*write the pattern inside the CGRAM*/
		for(Local_u8Itrator = 0u ; Local_u8Itrator < 8u ; Local_u8Itrator++)
		{
			CLCD_voidSendData(copy_pu8PatternArray[Local_u8Itrator]);
		}

		/* Set DDRAM Address */
		CLCD_voidGoToXY(copy_u8Xpos,copy_u8Ypos);

		/*write the corresponding pattern number to display from CGRAM*/
		CLCD_voidSendData(copy_u8PatternNumber);
	}
	else
	{
		Local_u8ErrorState = NULL_POINTER;
	}
	return Local_u8ErrorState;
}


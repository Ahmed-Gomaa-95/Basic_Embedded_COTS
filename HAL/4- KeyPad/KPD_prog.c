/***************************************************************************************************************************/
/***************************************************************************************************************************/
/************************************        @layer		: HAL                     ******************************************/
/************************************        @swc 		: KPD_prog.h              ******************************************/
/************************************        @author	: Ahmed Gomaa             ******************************************/
/************************************        @version	: 1.0                     ******************************************/
/************************************        @date		:                         ******************************************/
/***************************************************************************************************************************/
/***************************************************************************************************************************/
#include "STD_TYPES.h"
#include "ERROR_TYPES.h"
#include "DIO_interface.h"
#include "KPD_interface.h"
#include "KPD_cfg.h"
#include "KPD_prv.h"

/**********************************************************************************************************************/
/**********************************************************************************************************************/
/*****                                                                                                            *****/
/***** @Function Name 		  : KPD_u8GetPressedKey                                                               *****/
/***** @Function Description  : function to get keypad pressed key.                            			          *****/
/***** @Function Parameters   :	void																		      *****/
/***** @Function Return		  : Local_u8PressedKey: unsigned character contain the pressed key value              *****/
/*****                                                                                                            *****/
/**********************************************************************************************************************/
/**********************************************************************************************************************/
uint8 KPD_u8GetPressedKey(void)
{
	uint8 Local_u8RowCounter , Local_u8ColCounter , Local_u8KeyState , Local_u8PressedKey = KPD_u8NO_PRESSED_KEY_VAL;
	static uint8 Local_u8KPDArr[ROW_NUM][COL_NUM] = KPD_u8BUTTON_ARRAY;
	static uint8 Local_u8ColArr[COL_NUM] = KPD_u8COL_ARRAY;
	static uint8 Local_u8RowArr[ROW_NUM] = KPD_u8ROW_ARRAY;


	/* Activate the column pins */
	for(Local_u8ColCounter = 0u ; Local_u8ColCounter < COL_NUM ; Local_u8ColCounter++)
	{
		/* Activate the current column */
		DIO_u8SetPinValue(KPD_u8COL_PORT,Local_u8ColArr[Local_u8ColCounter],DIO_PIN_LOW);

		/* Read the row pins */
		for(Local_u8RowCounter = 0u ; Local_u8RowCounter < ROW_NUM ; Local_u8RowCounter++)
		{
			/* Read the current row */
			DIO_u8GetPinValue(KPD_u8ROW_PORT,Local_u8RowArr[Local_u8RowCounter],&Local_u8KeyState);

			/*Check if the key is pressed or not*/
			if( Local_u8KeyState == DIO_PIN_LOW )
			{
				Local_u8PressedKey = Local_u8KPDArr[Local_u8RowCounter][Local_u8ColCounter];

				/* Wait until key is released ( pooling with blocking on pin reading ) */
				while( Local_u8KeyState == DIO_PIN_LOW )
				{
					DIO_u8GetPinValue(KPD_u8ROW_PORT,Local_u8RowArr[Local_u8RowCounter],&Local_u8KeyState);
				}
			}
		}

		/* Deactivate the current column */
		DIO_u8SetPinValue(KPD_u8COL_PORT,Local_u8ColArr[Local_u8ColCounter],DIO_PIN_HIGH);
	}
	return Local_u8PressedKey;
}

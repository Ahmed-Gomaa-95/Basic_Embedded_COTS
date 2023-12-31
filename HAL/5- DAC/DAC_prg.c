/**********************************************************************************************************************/
/**********************************************************************************************************************/
/************************************        @layer: HAL                    *******************************************/
/************************************        @swc : DAC_prg.c               *******************************************/
/************************************        @author: Ahmed Gomaa           *******************************************/
/************************************        @version: 1.0                  *******************************************/
/************************************        @date: 13/6/2023               *******************************************/
/**********************************************************************************************************************/
/**********************************************************************************************************************/


#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ERROR_TYPES.h"
#include "DIO_interface.h"
#include "DAC_cfg.h"
#include "DAC_interface.h"


/**********************************************************************************************************************/
/**********************************************************************************************************************/
/*****                                                                                                            *****/
/***** @Function Name 		  : DAC_voidSetAnalogVolt                                                             *****/
/***** @Function Description  : function set analog volt to DAC 					                              *****/
/***** @Function Parameters   :  copy_u16VoltMS : unsigned short integer that take volt in milli second           *****/
/***** @Function Return       :  void																	          *****/
/*****                                                                                                            *****/
/**********************************************************************************************************************/
/**********************************************************************************************************************/
uint8 DAC_voidSetAnalogVolt(uint16 copy_u16VoltMS)
{
	uint8 Local_u8ErrorStat = OK;
	uint8 Local_u8Digital = ( ( (uint32)copy_u16VoltMS  *  DAC_u8Levels ) / DAC_u16Refernce_Voltage ); /*Digital = analog / step*/
	if(copy_u16VoltMS <= DAC_u16Refernce_Voltage)
	{
		DIO_u8SetPortValue(DAC_u8PORT,Local_u8Digital - 1u);
	}
	else
	{
		Local_u8ErrorStat = NOT_OK;
	}
	return Local_u8ErrorStat;

}

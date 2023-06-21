/**********************************************************************************************************************/
/**********************************************************************************************************************/
/************************************        @layer: MCAL                   *******************************************/
/************************************        @swc : DIO_prog.c              *******************************************/
/************************************        @author: Ahmed Gomaa           *******************************************/
/************************************        @version: 1.0                  *******************************************/
/************************************        @date: 29/4/2023               *******************************************/
/**********************************************************************************************************************/
/**********************************************************************************************************************/


#include "STD_TYPES.h"

#include "BIT_MATH.h"
#include "ERROR_TYPES.h"

#include "DIO_reg.h"
#include "DIO_interface.h"


/**********************************************************************************************************************/
/**********************************************************************************************************************/
/*****                                                                                                            *****/
/***** @Function Name 		  : DIO_u8SetPinDirection                                                             *****/
/***** @Function Description  : function make the pin direction as an input or output                             *****/
/***** @Function Parameters   :                                                                                   *****/
/***** 						   1- copy_Port   : enum called DIO_Port_t contains ports A,B, C and D                *****/
/***** 						   2- copy_PinNum : enum called DIO_Pin_t contains pins from 0 to 7                   *****/
/***** 						   3- copy_PinDir : enum called DIO_PinDir_t contains direction input and output      *****/
/***** @Function Return       :  function return an error state that can be OK or NOT_OK or NULL_POINTER          *****/
/*****                                                                                                            *****/
/**********************************************************************************************************************/
/**********************************************************************************************************************/
uint8 DIO_u8SetPinDirection(DIO_Port_t copy_Port, DIO_Pin_t copy_PinNum, DIO_PinDir_t copy_PinDir )
{
	uint8 Local_u8ErrorState = OK;

	if( ( copy_PinNum >= DIO_PIN0 ) &&  ( copy_PinNum <= DIO_PIN7 ) )
	{
		if( copy_PinDir == DIO_PIN_INPUT )
		{
			switch(copy_Port)
			{
			case DIO_PORTA: CLR_BIT(DDRA,copy_PinNum); break;
			case DIO_PORTB: CLR_BIT(DDRB,copy_PinNum); break;
			case DIO_PORTC: CLR_BIT(DDRC,copy_PinNum); break;
			case DIO_PORTD: CLR_BIT(DDRD,copy_PinNum); break;
			default: Local_u8ErrorState = NOT_OK;
			}

		}
		else if(copy_PinDir == DIO_PIN_OUTPUT)
		{
			switch(copy_Port)
			{
			case DIO_PORTA: SET_BIT(DDRA,copy_PinNum); break;
			case DIO_PORTB: SET_BIT(DDRB,copy_PinNum); break;
			case DIO_PORTC: SET_BIT(DDRC,copy_PinNum); break;
			case DIO_PORTD: SET_BIT(DDRD,copy_PinNum); break;
			default: Local_u8ErrorState = NOT_OK;
			}
		}
		else
		{
			Local_u8ErrorState = NOT_OK;
		}
	}
	else
	{
		Local_u8ErrorState = NOT_OK;
	}



	return Local_u8ErrorState;

}

/**********************************************************************************************************************/
/**********************************************************************************************************************/
/*****                                                                                                            *****/
/***** @Function Name 		: DIO_u8SetPortDirection                                                              *****/
/***** @Function Parameters :                                                                                     *****/
/***** 						  1- copy_Port      : enum called DIO_Port_t contains ports A,B, C and D              *****/
/***** 						  2- copy_u8PortDir : unsigned character value taken from user to set port direction  *****/
/***** @Function Return     : function return an error state that can be OK or NOT_OK or NULL_POINTER             *****/
/*****                                                                                                            *****/
/**********************************************************************************************************************/
/**********************************************************************************************************************/
uint8 DIO_u8SetPortDirection(DIO_Port_t copy_Port,  uint8 copy_u8PortDir )
{
	uint8 Local_u8ErrorState = OK;

	switch(copy_Port)
	{
	case DIO_PORTA: DDRA = copy_u8PortDir ; break;
	case DIO_PORTB: DDRB = copy_u8PortDir ; break;
	case DIO_PORTC: DDRC = copy_u8PortDir ; break;
	case DIO_PORTD: DDRD = copy_u8PortDir ; break;
	default: Local_u8ErrorState = NOT_OK;

	}

	return Local_u8ErrorState;
}

/*********************************************************************************************************************/
/*********************************************************************************************************************/
/*****                                                                                                           *****/
/***** @Function Name 		  : DIO_u8SetPinValue                                                                *****/
/***** @Function Description  : function set the pin value  ( high or low value)                                 *****/
/***** @Function Parameters   :                                                                                  *****/
/***** 						   1- copy_Port   : enum called DIO_Port_t contains ports A,B, C and D               *****/
/***** 						   2- copy_PinNum : enum called DIO_Pin_t contains pins from 0 to 7                  *****/
/***** 						   3- copy_PinVal : enum called DIO_PinVal_t contains value if pin (High or Low)     *****/
/***** @Function Return       :  function return an error state that can be OK or NOT_OK or NULL_POINTER         *****/
/*****                                                                                                           *****/
/*********************************************************************************************************************/
/*********************************************************************************************************************/
uint8 DIO_u8SetPinValue(DIO_Port_t copy_Port, DIO_Pin_t copy_PinNum , DIO_PinVal_t copy_PinVal )
{
	uint8 Local_u8ErrorState = OK;

	if( ( copy_PinNum >= DIO_PIN0 ) &&  ( copy_PinNum <= DIO_PIN7 ) )
	{
		if(copy_PinVal == DIO_PIN_HIGH)
		{
			switch(copy_Port)
			{
			case DIO_PORTA: SET_BIT(PORTA,copy_PinNum); break;
			case DIO_PORTB: SET_BIT(PORTB,copy_PinNum); break;
			case DIO_PORTC: SET_BIT(PORTC,copy_PinNum); break;
			case DIO_PORTD: SET_BIT(PORTD,copy_PinNum); break;
			default: Local_u8ErrorState = NOT_OK;
			}
		}
		else if(copy_PinVal == DIO_PIN_LOW)
		{
			switch(copy_Port)
			{
			case DIO_PORTA: CLR_BIT(PORTA,copy_PinNum); break;
			case DIO_PORTB: CLR_BIT(PORTB,copy_PinNum); break;
			case DIO_PORTC: CLR_BIT(PORTC,copy_PinNum); break;
			case DIO_PORTD: CLR_BIT(PORTD,copy_PinNum); break;
			default: Local_u8ErrorState = NOT_OK;
			}
		}

	}
	else
	{
		Local_u8ErrorState = NOT_OK;
	}



	return Local_u8ErrorState;
}

/*********************************************************************************************************************/
/*********************************************************************************************************************/
/*****                                                                                                           *****/
/***** @Function Name 		  : DIO_u8SetPortValue                                                               *****/
/***** @Function Description  : function set the port value taken from user.                                     *****/
/***** @Function Parameters   :                                                                                  *****/
/***** 						   1- copy_Port      : enum called DIO_Port_t contains ports A,B, C and D            *****/
/***** 						   2- copy_u8PortVaL : unsigned character value taken from user                      *****/
/***** @Function Return       :  function return an error state that can be OK or NOT_OK or NULL_POINTER         *****/
/*****                                                                                                           *****/
/*********************************************************************************************************************/
/*********************************************************************************************************************/
uint8 DIO_u8SetPortValue(DIO_Port_t copy_Port, uint8 copy_u8PortVaL )
{
	uint8 Local_u8ErrorState = OK;
	switch(copy_Port)
	{
	case DIO_PORTA: PORTA = copy_u8PortVaL; break;
	case DIO_PORTB: PORTB = copy_u8PortVaL; break;
	case DIO_PORTC: PORTC = copy_u8PortVaL; break;
	case DIO_PORTD: PORTD = copy_u8PortVaL; break;
	default: Local_u8ErrorState = NOT_OK;
	}


	return Local_u8ErrorState;
}

/*********************************************************************************************************************/
/*********************************************************************************************************************/
/*****                                                                                                           *****/
/***** @Function Name 		  : DIO_u8GetPinValue                                                                *****/
/***** @Function Description  : function get the pin value  ( high or low value)                                 *****/
/***** @Function Parameters   :                                                                                  *****/
/***** 						   1- copy_Port   : enum called DIO_Port_t contains ports A,B, C and D               *****/
/***** 						   2- copy_PinNum : enum called DIO_Pin_t contains pins from 0 to 7                  *****/
/***** 						   3- copy_pVal   : pointr to enum called DIO_PinVal_t to store value of pin         *****/
/***** @Function Return       :  function return an error state that can be OK or NOT_OK or NULL_POINTER         *****/
/*****                                                                                                           *****/
/*********************************************************************************************************************/
/*********************************************************************************************************************/
uint8 DIO_u8GetPinValue(DIO_Port_t copy_Port,  DIO_Pin_t copy_PinNum ,  DIO_PinVal_t* copy_pVal )
{
	uint8 Local_u8ErrorState = OK;

	if(copy_pVal != NULL)
	{
		if( ( copy_PinNum >= DIO_PIN0 ) &&  ( copy_PinNum <= DIO_PIN7 ) )
		{
			switch(copy_Port)
			{
			case DIO_PORTA: *copy_pVal = GET_BIT(PINA , copy_PinNum); break;
			case DIO_PORTB: *copy_pVal = GET_BIT(PINB , copy_PinNum); break;
			case DIO_PORTC: *copy_pVal = GET_BIT(PINC , copy_PinNum); break;
			case DIO_PORTD: *copy_pVal = GET_BIT(PIND , copy_PinNum); break;
			default: Local_u8ErrorState = NOT_OK;
			}
		}
		else
		{
			Local_u8ErrorState = NOT_OK;
		}
	}
	else
	{
		Local_u8ErrorState = NULL_POINTER;
	}



	return Local_u8ErrorState;
}

/*********************************************************************************************************************/
/*********************************************************************************************************************/
/*****                                                                                                           *****/
/***** @Function Name 		  : DIO_u8TogglePinValue                                                             *****/
/***** @Function Description  : function toggle the pin value                                                    *****/
/***** @Function Parameters   :                                                                                  *****/
/***** 						   1- copy_Port   : enum called DIO_Port_t contains ports A,B, C and D               *****/
/***** 						   2- copy_PinNum : enum called DIO_Pin_t contains pins from 0 to 7                  *****/
/***** @Function Return       :  function return an error state that can be OK or NOT_OK or NULL_POINTER         *****/
/*****                                                                                                           *****/
/*********************************************************************************************************************/
/*********************************************************************************************************************/
uint8 DIO_u8TogglePinValue(DIO_Port_t copy_Port, DIO_Pin_t copy_PinNum)
{
	uint8 Local_u8ErrorState = OK;

	if( ( copy_PinNum >= DIO_PIN0 ) &&  ( copy_PinNum <= DIO_PIN7 ) )
	{
		switch(copy_Port)
		{
		case DIO_PORTA: TOG_BIT(PORTA , copy_PinNum); break;
		case DIO_PORTB: TOG_BIT(PORTB , copy_PinNum); break;
		case DIO_PORTC: TOG_BIT(PORTC , copy_PinNum); break;
		case DIO_PORTD: TOG_BIT(PORTD , copy_PinNum); break;
		default: Local_u8ErrorState = NOT_OK;
		}
	}
	else
	{
		Local_u8ErrorState = NOT_OK;
	}



	return Local_u8ErrorState;
}

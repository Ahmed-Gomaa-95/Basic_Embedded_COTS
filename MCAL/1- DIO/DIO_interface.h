/**********************************************************************************************************************/
/**********************************************************************************************************************/
/************************************        @layer: MCAL                   *******************************************/
/************************************        @swc : DIO_interface.h         *******************************************/
/************************************        @author: Ahmed Gomaa           *******************************************/
/************************************        @version: 1.0                  *******************************************/
/************************************        @date: 29/4/2023               *******************************************/
/**********************************************************************************************************************/
/**********************************************************************************************************************/

#ifndef DIO_INTERFACE_h
#define DIO_INTERFACE_h
typedef enum
{
	DIO_PORTA, 
	DIO_PORTB, 
	DIO_PORTC, 
	DIO_PORTD
	
}DIO_Port_t;

typedef enum
{
	DIO_PIN0,
	DIO_PIN1,
	DIO_PIN2,
	DIO_PIN3,
	DIO_PIN4,
	DIO_PIN5,
	DIO_PIN6,
	DIO_PIN7
}DIO_Pin_t;

typedef enum
{
	DIO_PIN_INPUT,
	DIO_PIN_OUTPUT
}DIO_PinDir_t;

typedef enum
{
	DIO_PIN_LOW,
	DIO_PIN_HIGH
}DIO_PinVal_t;

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
uint8 DIO_u8SetPinDirection(DIO_Port_t copy_Port, DIO_Pin_t copy_PinNum, DIO_PinDir_t copy_PinDir );

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
uint8 DIO_u8SetPortDirection(DIO_Port_t copy_Port,  uint8 copy_u8PortDir );

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
uint8 DIO_u8SetPinValue(DIO_Port_t copy_Port, DIO_Pin_t copy_PinNum , DIO_PinVal_t copy_PinVal );

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
uint8 DIO_u8SetPortValue(DIO_Port_t copy_Port, uint8 copy_u8PortVaL );

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
uint8 DIO_u8GetPinValue(DIO_Port_t copy_Port,  DIO_Pin_t copy_PinNum ,  DIO_PinVal_t* copy_pVal );

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
uint8 DIO_u8TogglePinValue(DIO_Port_t copy_Port, DIO_Pin_t copy_PinNum);


#endif

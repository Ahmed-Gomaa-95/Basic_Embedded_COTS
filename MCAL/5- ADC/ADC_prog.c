/***************************************************************************************************************************/
/***************************************************************************************************************************/
/************************************        @layer		: MCAL                    ******************************************/
/************************************        @swc 		: ADC_prog.c              ******************************************/
/************************************        @author	: Ahmed Gomaa             ******************************************/
/************************************        @version	: 1.0                     ******************************************/
/************************************        @date		:                         ******************************************/
/***************************************************************************************************************************/
/***************************************************************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ERROR_TYPES.h"
#include "ADC_prv.h"
#include "ADC_cfg.h"
#include "ADC_reg.h"
#include "ADC_interface.h"


static uint16* ADC_pu16ConversionResult = NULL;

static void (*ADC_pvNotificationFunc)(void) = NULL;

static uint8 ADC_u8BusyFlag = IDLE ;

static uint8* ADC_pu8ChannelArr = NULL;
static uint8 ADC_u8ChainSize = 0;
static uint8 ADC_u8ChannelIndex = 0;

static uint8 ADC_u8ISRState ;

/**********************************************************************************************************************/
/**********************************************************************************************************************/
/*****                                                                                                            *****/
/***** @Function Name 		  : ADC_voidInit                                                                      *****/
/***** @Function Description  : function initialize the ADC peripheral                        				      *****/
/***** @Function Parameters   : void                                                                              *****/
/***** @Function Return       : void 																	          *****/
/*****                                                                                                            *****/
/**********************************************************************************************************************/
/**********************************************************************************************************************/
void ADC_voidInit(void)
{
	/*1- Reference selection : AVCC with external capacitor at AREF pin*/
	SET_BIT(ADMUX,ADMUX_REFS0);
	CLR_BIT(ADMUX,ADMUX_REFS1);
#if ADC_u8RESOLUTION == EIGHT_BITS
	/*2- Activate left adjust for 8-bit  */
	SET_BIT(ADMUX,ADMUX_ADLAR);
#elif ADC_u8RESOLUTION == TEN_BITS
	CLR_BIT(ADMUX,ADMUX_ADLAR);
#else
#error wrong ADC_u8RESOLUTION configuration value
#endif
	/*3- check on prescalar configuration setting*/
	ADCSRA &= PRESCALAR_MASK; /*clear the prescalar bits*/
	ADCSRA |= ADC_u8PRESCALAR;
	/*4- ADC Enable*/
	SET_BIT(ADCSRA,ADCSRA_ADEN);

}

/**********************************************************************************************************************/
/**********************************************************************************************************************/
/*****                                                                                                            *****/
/***** @Function Name 		  : ADC_u8StartSingleConversionSynch                                                  *****/
/***** @Function Description  : function do synchronous single conversion in adc                                  *****/
/***** @Function Parameters   :                                                                                   *****/
/***** 						   1- copy_u8Channel  : enum called ADC_channel_t contains possible channels in ADC   *****/
/***** 						   2- copy_pu16DigResult : pointer to short integer to contain result of conversion   *****/
/***** @Function Return       : Local_u8ErrorState : unsigned character variable return error state               *****/
/*****                                                                                                            *****/
/**********************************************************************************************************************/
/**********************************************************************************************************************/
uint8 ADC_u8StartSingleConversionSynch(ADC_channel_t copy_u8Channel , uint16* copy_pu16DigResult)
{
	uint8 Local_u8ErrorState = OK;
	if(copy_pu16DigResult != NULL)
	{
		if(ADC_u8BusyFlag == IDLE)
		{
			uint32 Local_u32Counter = 0u;

			/* ADC is busy now */
			ADC_u8BusyFlag = BUSY;

			/*ISR state shall be equal to Single conversion synchronous*/
			ADC_u8ISRState = SINGLE_CONVERSION;


			/* Set the channel */
			ADMUX &= CHALNNEL_SELECTION_MASK; /* clear channel selection bits*/
			ADMUX |= copy_u8Channel;


			/* start conversion  */
			SET_BIT(ADCSRA,ADCSRA_ADSC);

			/* wait (block) until conversion is completed or the time out has not passed yet */
			while(  ( GET_BIT(ADCSRA,ADCSRA_ADIF) == 0 ) && ( Local_u32Counter < ADC_u32TIMEOUT_COUNT ) )
			{
				Local_u32Counter++;
			}
			if(Local_u32Counter == ADC_u32TIMEOUT_COUNT)
			{
				/* Loop is broken because time out has passed */
				Local_u8ErrorState = TIMEOUT_ERR;
			}
			else /* Loop broken because flag raised */
			{
				/*Clear ADC conversion complete flag*/
				SET_BIT(ADCSRA,ADCSRA_ADIF);

				/* Return the reading */
#if ADC_u8RESOLUTION == EIGHT_BITS
				return (uint16)ADCH;
#elif ADC_u8RESOLUTION == TEN_BITS
				return ADC;
#endif
				/* Task is done , ADC is IDLE now */
				ADC_u8BusyFlag = IDLE;
			}
		}
		else
		{
			Local_u8ErrorState = BUSY_ERR;
		}
	}
	else
	{
		Local_u8ErrorState = NULL_POINTER;
	}


	return Local_u8ErrorState;

}

/**********************************************************************************************************************/
/**********************************************************************************************************************/
/*****                                                                                                            *****/
/***** @Function Name 		  : ADC_u8StartSingleConversionAsynch                                                 *****/
/***** @Function Description  : function do Asynchronous single conversion in adc                                 *****/
/***** @Function Parameters   :                                                                                   *****/
/***** 						   1- copy_u8Channel  : enum called ADC_channel_t contains possible channels in ADC   *****/
/***** 						   2- copy_pu16DigResult : pointer to short integer to contain result of conversion   *****/
/***** 						   3- copy_pvNotificationFunc : pointer to a notification function                    *****/
/***** @Function Return       : Local_u8ErrorState : unsigned character variable return error state               *****/
/*****                                                                                                            *****/
/**********************************************************************************************************************/
/**********************************************************************************************************************/
uint8 ADC_u8StartSingleConversionAsynch(ADC_channel_t copy_u8Channel , uint16* copy_pu16DigResult , void (*copy_pvNotificationFunc)(void))
{
	uint8 Local_u8ErrorState = OK;
	if( ( copy_pu16DigResult != NULL ) && ( copy_pvNotificationFunc != NULL) )
	{
		if(ADC_u8BusyFlag == IDLE)
		{
			/*ADC is busy now*/
			ADC_u8BusyFlag = BUSY;

			/*ISR state shall be equal to Single conversion asynchronous*/
			ADC_u8ISRState = SINGLE_CONVERSION;

			/* convert the digital result and notification function local variables into global  */
			ADC_pu16ConversionResult = copy_pu16DigResult ;

			ADC_pvNotificationFunc = copy_pvNotificationFunc;

			/* Set the channel */
			ADMUX &= CHALNNEL_SELECTION_MASK; /* clear channel selection bits*/
			ADMUX |= copy_u8Channel;


			/* Start the conversion  */
			SET_BIT(ADCSRA,ADCSRA_ADSC);

			/*Enable ADC conversion  complete interrupt */
			SET_BIT(ADCSRA,ADCSRA_ADIE);
		}
		else
		{
			Local_u8ErrorState = BUSY_ERR;
		}
	}
	else
	{
		Local_u8ErrorState = NULL_POINTER;
	}



	return Local_u8ErrorState;
}

/**********************************************************************************************************************/
/**********************************************************************************************************************/
/*****                                                                                                            *****/
/***** @Function Name 		  : ADC_u8StartChainConversionAsynch                                                  *****/
/***** @Function Description  : function do Asynchronous chain conversion in ADC                                  *****/
/***** @Function Parameters   :                                                                                   *****/
/***** 						   1- copy_Chain  : enum called ADC_ChainConfig_t contains configuration ADC   *****/
/***** 						   2- copy_pu16DigResult : pointer to short integer to contain result of conversion   *****/
/***** 						   3- copy_pvNotificationFunc : pointer to a notification function                    *****/
/***** @Function Return       : Local_u8ErrorState : unsigned character variable return error state               *****/
/*****                                                                                                            *****/
/**********************************************************************************************************************/
/**********************************************************************************************************************/
uint8 ADC_u8StartChainConversionAsynch(ADC_ChainConfig_t* copy_Chain)
{
	uint8 Local_u8ErrorState = OK;

	if(copy_Chain != NULL)
	{
		if( ( copy_Chain->ArrayOfResult != NULL ) && ( copy_Chain->ChannelArray != NULL ) && (copy_Chain->NotificationFunc != NULL) )
		{
			/* Check if ADC is available or not */
			if(ADC_u8BusyFlag == IDLE)
			{
				/* ADC is now busy */
				ADC_u8BusyFlag = BUSY;

				/*ISR state shall be equal to chain conversion asynchronous*/
				ADC_u8ISRState = CHAIN_CONVERSION;

				/*Initialize the chain data globally*/
				ADC_pu8ChannelArr = copy_Chain->ChannelArray;
				ADC_pu16ConversionResult = copy_Chain->ArrayOfResult;
				ADC_u8ChainSize   =  copy_Chain->NumOfConversions;
				ADC_pvNotificationFunc = copy_Chain->NotificationFunc;
				ADC_u8ChannelIndex = 0;

				/*Set first channel conversion*/
				ADMUX &= CHALNNEL_SELECTION_MASK;
				ADMUX |= ADC_pu8ChannelArr[0];

				/* Start the conversion  */
				SET_BIT(ADCSRA,ADCSRA_ADSC);

				/*Enable ADC conversion  complete interrupt */
				SET_BIT(ADCSRA,ADCSRA_ADIE);
			}
			else
			{

				Local_u8ErrorState = BUSY_ERR;
			}
		}
		else
		{
			Local_u8ErrorState = NULL_POINTER;
		}
	}
	else
	{
		Local_u8ErrorState = NULL_POINTER;
	}
	return Local_u8ErrorState;
}

/*ADC conversion complete ISR*/
void __vector_16 (void)		__attribute__((signal));
void __vector_16 (void)
{
	/*Check the source of the ISR whether it comes from single conversion or chain conversion*/
	if(ADC_u8ISRState == SINGLE_CONVERSION )
	{
		/*ISR comes from single conversion asynchronous*/

		/*Disable ADC conversion complete interrupt*/
		CLR_BIT(ADCSRA , ADCSRA_ADIE);

		/* ADC is IDLE now */
		ADC_u8BusyFlag = IDLE;
		/* Read the conversion result  */
#if ADC_u8RESOLUTION == EIGHT_BITS
		*ADC_pu16ConversionResult = (uint16)ADCH;
#elif ADC_u8RESOLUTION == TEN_BITS
		*ADC_pu16ConversionResult = ADC;
#endif
		/* Invoke the callback notification function */
		if(ADC_pvNotificationFunc != NULL)
		{
			/* Notification function calling */
			ADC_pvNotificationFunc();
		}
		else
		{

			/* Do nothing */
		}
	}
	else
	{
		/*ISR comes from chain conversion asynchronous*/

		/*Read the current conversion result*/
#if ADC_u8RESOLUTION == EIGHT_BITS
		ADC_pu16ConversionResult[ADC_u8ChannelIndex] = (uint16)ADCH;
#elif ADC_u8RESOLUTION == TEN_BITS
		ADC_pu16ConversionResult[ADC_u8ChannelIndex] = ADC;
#endif
		/*Increment the current conversion index*/
		ADC_u8ChannelIndex++;

		/*Check if the chain is finished*/
		if(ADC_u8ChannelIndex == ADC_u8ChainSize)
		{
			/* Chain is finished*/

			/*ADC is now IDLE */
			ADC_u8BusyFlag = IDLE;

			/*Disable ADC conversion complete interrupt*/
			CLR_BIT(ADCSRA , ADCSRA_ADIE);

			/* Invoke the callback notification function */
			if(ADC_pvNotificationFunc != NULL)
			{
				/* Notification function calling */
				ADC_pvNotificationFunc();
			}
			else
			{

				/* Do nothing */
			}

		}
		else
		{
			/*Chain is not finished , set the next channel*/
			ADMUX &= CHALNNEL_SELECTION_MASK ;
			ADMUX |= ADC_pu8ChannelArr[ADC_u8ChannelIndex];

			/*Start conversion*/
			SET_BIT(ADCSRA,ADCSRA_ADSC);
		}

	}

}

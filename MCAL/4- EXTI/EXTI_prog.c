/***************************************************************************************************************************/
/***************************************************************************************************************************/
/************************************        @layer		: MCAL                    ******************************************/
/************************************        @swc 		: EXTI_prog.h             ******************************************/
/************************************        @author	: Ahmed Gomaa             ******************************************/
/************************************        @version	: 1.0                     ******************************************/
/************************************        @date		:                         ******************************************/
/***************************************************************************************************************************/
/***************************************************************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ERROR_TYPES.h"
#include "GIE_interface.h"
#include "EXTI_reg.h"
#include "EXTI_cfg.h"
#include "EXTI_prv.h"
#include "EXTI_interface.h"


/**********************************************************************************************************************/
/**********************************************************************************************************************/
/*****                                                                                                            *****/
/***** @Function Name 		  : EXTI_voidInit                                                                     *****/
/***** @Function Description  : pre-build function that configure external interrupt               			      *****/
/***** @Function Parameters   : void                                                                              *****/
/***** @Function Return       : void																	          *****/
/*****                                                                                                            *****/
/**********************************************************************************************************************/
/**********************************************************************************************************************/
void EXTI_voidInit(void)
{
#if EXTI_u8INT0_STATUS == ENABLED
	SET_BIT(GICR , GICR_INT0);
#if	  EXTI_u8INT0_TRIG == FALLING_EDGE
	CLR_BIT(MCUCR,MCUCR_ISC00);
	SET_BIT(MCUCR,MCUCR_ISC01);
#elif EXTI_u8INT0_TRIG == RISING_EDGE
	SET_BIT(MCUCR,MCUCR_ISC00);
	SET_BIT(MCUCR,MCUCR_ISC01);
#elif EXTI_u8INT0_TRIG == ON_CHANGE
	SET_BIT(MCUCR,MCUCR_ISC00)
	CLR_BIT(MCUCR,MCUCR_ISC01);
#elif EXTI_u8INT0_TRIG == LOW_LEVEL
	CLR_BIT(MCUCR,MCUCR_ISC00);
	CLR_BIT(MCUCR,MCUCR_ISC01);
#else
#error " Wrong Triggering option ";
#endif

#endif

#if EXTI_u8INT1_STATUS == ENABLED
	SET_BIT(GICR , GICR_INT1);
#if	  EXTI_u8INT0_TRIG == FALLING_EDGE
	CLR_BIT(MCUCR,MCUCR_ISC10);
	SET_BIT(MCUCR,MCUCR_ISC11);
#elif EXTI_u8INT0_TRIG == RISING_EDGE
	SET_BIT(MCUCR,MCUCR_ISC10);
	SET_BIT(MCUCR,MCUCR_ISC11);
#elif EXTI_u8INT0_TRIG == ON_CHANGE
	SET_BIT(MCUCR,MCUCR_ISC10)
	CLR_BIT(MCUCR,MCUCR_ISC11);
#elif EXTI_u8INT0_TRIG == LOW_LEVEL
	CLR_BIT(MCUCR,MCUCR_ISC10);
	CLR_BIT(MCUCR,MCUCR_ISC11);
#else
#error " Wrong Triggering option ";
#endif

#endif

#if EXTI_u8INT2_STATUS == ENABLED
	SET_BIT(GICR , GICR_INT2);
#if	  EXTI_u8INT0_TRIG == FALLING_EDGE
	CLR_BIT(MCUCSR,MCUCSR_ISC2);
#elif EXTI_u8INT0_TRIG == RISING_EDGE
	SET_BIT(MCUCSR,MCUCSR_ISC2);
#else
#error " Wrong Triggering option ";
#endif

#endif


}




/**********************************************************************************************************************/
/**********************************************************************************************************************/
/*****                                                                                                            *****/
/***** @Function Name 		  : EXTI_voidEnable                                                                   *****/
/***** @Function Description  : function that enable external interrupt                						      *****/
/***** @Function Parameters   : copy_u8IntNum : unsigned character contain interrupt number                       *****/
/***** @Function Return       : Local_u8ErrorState : unsigned character return error state 						  *****/
/*****                                                                                                            *****/
/**********************************************************************************************************************/
/**********************************************************************************************************************/
uint8 EXTI_voidEnable(uint8 copy_u8IntNum)
{
	uint8 Local_u8ErrorState = OK;
	if( (copy_u8IntNum <= EXTI_u8_INT2) && (copy_u8IntNum >= EXTI_u8_INT0) )
	{
		switch(copy_u8IntNum)
		{
		case EXTI_u8_INT0: SET_BIT(GICR,GICR_INT0); break;
		case EXTI_u8_INT1: SET_BIT(GICR,GICR_INT1); break;
		case EXTI_u8_INT2: SET_BIT(GICR,GICR_INT2); break;
		default: Local_u8ErrorState = NOT_OK ; break;
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
/***** @Function Name 		  : EXTI_voidDisable                                                                  *****/
/***** @Function Description  : function that disable external interrupt               						      *****/
/***** @Function Parameters   : copy_u8IntNum : unsigned character contain interrupt number                       *****/
/***** @Function Return       : Local_u8ErrorState : unsigned character return error state 						  *****/
/*****                                                                                                            *****/
/**********************************************************************************************************************/
/**********************************************************************************************************************/
uint8 EXTI_voidDisable(uint8 copy_u8IntNum)
{
	uint8 Local_u8ErrorState = OK;
	if( (copy_u8IntNum <= EXTI_u8_INT2) && (copy_u8IntNum >= EXTI_u8_INT0) )
	{
		switch(copy_u8IntNum)
		{
		case EXTI_u8_INT0: CLR_BIT(GICR,GICR_INT0); break;
		case EXTI_u8_INT1: CLR_BIT(GICR,GICR_INT1); break;
		case EXTI_u8_INT2: CLR_BIT(GICR,GICR_INT2); break;
		default: Local_u8ErrorState = NOT_OK ; break;
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
/***** @Function Name 		  : EXTI_voidSetSenseCtrl                                                             *****/
/***** @Function Description  : function that trigger the external interrupt           						      *****/
/***** @Function Parameters   : 1- copy_u8IntNum : unsigned character contain interrupt number                    *****/
/***** 							2- copy_u8Trig   : unsigned character contain triggering option                   *****/
/***** @Function Return       : Local_u8ErrorState : unsigned character return error state 						  *****/
/*****                                                                                                            *****/
/**********************************************************************************************************************/
/**********************************************************************************************************************/
uint8 EXTI_voidSetSenseCtrl(uint8 copy_u8IntNum , uint8 copy_u8Trig)
{

	uint8 Local_u8ErrorState = OK;
	/*check the  number of interrupt */
	if( (copy_u8IntNum <= EXTI_u8_INT2) && (copy_u8IntNum >= EXTI_u8_INT0) )
	{
		switch(copy_u8IntNum)
		{
		case EXTI_u8_INT0:
			if(copy_u8Trig == EXTI_u8_FALLING_EDGE)
			{
				/* for falling edge triggering : ISC00 = 0 & ISC01 = 1 */
				CLR_BIT(MCUCR,MCUCR_ISC00);
				SET_BIT(MCUCR,MCUCR_ISC01);
			}
			else if(copy_u8Trig == EXTI_u8_RISING_EDGE)
			{
				/* for rising edge triggering : ISC00 = 1 & ISC01 = 1 */
				SET_BIT(MCUCR,MCUCR_ISC00);
				SET_BIT(MCUCR,MCUCR_ISC01);
			}
			else if(copy_u8Trig == EXTI_u8_ON_CHANGE)
			{
				/* for on change triggering : ISC00 = 1 & ISC01 = 0 */
				SET_BIT(MCUCR,MCUCR_ISC00);
				CLR_BIT(MCUCR,MCUCR_ISC01);
			}
			else if(copy_u8Trig == EXTI_u8_LOW_LEVEL)
			{
				/* for low level  triggering : ISC00 = 0 & ISC01 = 0 */
				CLR_BIT(MCUCR,MCUCR_ISC00);
				CLR_BIT(MCUCR,MCUCR_ISC01);
			}
			else
			{
				Local_u8ErrorState = NOT_OK;
			}
			break;
		case EXTI_u8_INT1:
			if(copy_u8Trig == EXTI_u8_FALLING_EDGE)
			{
				/* for falling edge triggering : ISC10 = 0 & ISC11 = 1 */
				CLR_BIT(MCUCR,MCUCR_ISC10);
				SET_BIT(MCUCR,MCUCR_ISC11);
			}
			else if(copy_u8Trig == EXTI_u8_RISING_EDGE)
			{
				/* for rising edge triggering : ISC10 = 1 & ISC11 = 1 */
				SET_BIT(MCUCR,MCUCR_ISC10);
				SET_BIT(MCUCR,MCUCR_ISC11);
			}
			else if(copy_u8Trig == EXTI_u8_ON_CHANGE)
			{
				/* for on change triggering : ISC10 = 1 & ISC11 = 0 */
				SET_BIT(MCUCR,MCUCR_ISC10);
				CLR_BIT(MCUCR,MCUCR_ISC11);
			}
			else if(copy_u8Trig == EXTI_u8_LOW_LEVEL)
			{
				/* for low level  triggering : ISC10 = 0 & ISC11 = 0 */
				CLR_BIT(MCUCR,MCUCR_ISC10);
				CLR_BIT(MCUCR,MCUCR_ISC11);
			}
			else
			{
				Local_u8ErrorState = NOT_OK;
			}
			break;
		case EXTI_u8_INT2:
			if(copy_u8Trig == EXTI_u8_FALLING_EDGE)
			{
				/* for falling edge triggering : ISC2 = 0*/
				CLR_BIT(MCUCSR,MCUCSR_ISC2);
			}
			else if(copy_u8Trig == EXTI_u8_RISING_EDGE)
			{
				/* for rising edge triggering : ISC2 = 1*/
				SET_BIT(MCUCSR,MCUCSR_ISC2);
			}
			else
			{
				Local_u8ErrorState = NOT_OK;
			}
			break;
		default: Local_u8ErrorState = NOT_OK ; break;
		}
	}
	else
	{
		Local_u8ErrorState = NOT_OK;
	}



	return Local_u8ErrorState;
}




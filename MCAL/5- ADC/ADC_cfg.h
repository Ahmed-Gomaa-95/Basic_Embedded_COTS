/***************************************************************************************************************************/
/***************************************************************************************************************************/
/************************************        @layer		: MCAL                    ******************************************/
/************************************        @swc 		: ADC_cfg.h               ******************************************/
/************************************        @author	: Ahmed Gomaa             ******************************************/
/************************************        @version	: 1.0                     ******************************************/
/************************************        @date		:                         ******************************************/
/***************************************************************************************************************************/
/***************************************************************************************************************************/
#ifndef ADC_CFG_H_
#define ADC_CFG_H_


/* Configure ADC Prescalar division factor : 1- DIVISON_BY_2
 * 											 2- DIVISON_BY_4
 * 											 3- DIVISON_BY_8
 * 											 4- DIVISON_BY_16
 * 											 5- DIVISON_BY_32
 * 											 6- DIVISON_BY_64
 * 											 7- DIVISON_BY_128
 **/
#define ADC_u8PRESCALAR			DIVISON_BY_128

/*configure ADC resolution : 1- EIGHT_BITS
 * 							 2- TEN_BITS
 **/
#define ADC_u8RESOLUTION		TEN_BITS

#define ADC_u32TIMEOUT_COUNT	5000u

#endif /* ADC_CFG_H_ */

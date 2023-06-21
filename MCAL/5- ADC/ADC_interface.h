/***************************************************************************************************************************/
/***************************************************************************************************************************/
/************************************        @layer		: MCAL                    ******************************************/
/************************************        @swc 		: ADC_interface.h         ******************************************/
/************************************        @author	: Ahmed Gomaa             ******************************************/
/************************************        @version	: 1.0                     ******************************************/
/************************************        @date		:                         ******************************************/
/***************************************************************************************************************************/
/***************************************************************************************************************************/

#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

typedef struct
{
	uint8   NumOfConversions;
	uint8*  ChannelArray;
	uint16* ArrayOfResult;
	void (*NotificationFunc)(void);

}ADC_ChainConfig_t;

typedef enum
{
	ADC0_SINGLE_ENDED,
	ADC1_SINGLE_ENDED,
	ADC2_SINGLE_ENDED,
	ADC3_SINGLE_ENDED,
	ADC4_SINGLE_ENDED,
	ADC5_SINGLE_ENDED,
	ADC6_SINGLE_ENDED,
	ADC7_SINGLE_ENDED,
	ADC0_POS_ADC0_NEG_10x_GAIN,
	ADC1_POS_ADC0_NEG_10x_GAIN,
	ADC0_POS_ADC0_NEG_200x_GAIN,
	ADC1_POS_ADC0_NEG_200x_GAIN,
	ADC2_POS_ADC2_NEG_10x_GAIN,
	ADC3_POS_ADC2_NEG_10x_GAIN,
	ADC2_POS_ADC2_NEG_200x_GAIN,
	ADC3_POS_ADC2_NEG_200x_GAIN,
	ADC0_POS_ADC1_NEG_1x_GAIN,
	ADC1_POS_ADC1_NEG_1x_GAIN,
	ADC2_POS_ADC1_NEG_1x_GAIN,
	ADC3_POS_ADC1_NEG_1x_GAIN,
	ADC4_POS_ADC1_NEG_1x_GAIN,
	ADC5_POS_ADC1_NEG_1x_GAIN,
	ADC6_POS_ADC1_NEG_1x_GAIN,
	ADC7_POS_ADC1_NEG_1x_GAIN,
	ADC0_POS_ADC2_NEG_1x_GAIN,
	ADC1_POS_ADC2_NEG_1x_GAIN,
	ADC2_POS_ADC2_NEG_1x_GAIN,
	ADC3_POS_ADC2_NEG_1x_GAIN,
	ADC4_POS_ADC2_NEG_1x_GAIN,


}ADC_channel_t;

void ADC_voidInit(void);
uint8 ADC_u8StartSingleConversionSynch(ADC_channel_t copy_u8Channel , uint16* copy_pu16DigResult);
uint8 ADC_u8StartSingleConversionAsynch(ADC_channel_t copy_u8Channel , uint16* copy_pu16DigResult , void (*copy_pvNotificationFunc)(void));

uint8 ADC_u8StartChainConversionAsynch(ADC_ChainConfig_t* copy_Chain);


#endif /* ADC_INTERFACE_H_ */

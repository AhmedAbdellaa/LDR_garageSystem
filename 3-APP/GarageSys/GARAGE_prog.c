#include "util/delay.h"

#include "../../libraries/STD_TYPES_H.h"
#include "../../libraries/ErrType.h"

#include "../../0-MCAL/1-DIO/DIO_interface.h"
#include "../../0-MCAL/2-Port/PORT_interface.h"
#include "../../0-MCAL/4-GIE/GIE_interface.h"
#include "../../0-MCAL/5-ADC/ADC_interface.h"


#include "../../1-HAL/LDR/LDR_interface.h"
#include "../../1-HAL/LED/LED_interface.h"
#include "../../1-HAL/CLCD/CLCD_interface.h"
#include "GARAGE_interface.h"

ADC_CHAIN_config_t Global_ADC_Chain_devicses[];
static GASY_CONFIG_t* Global_GASY;

// cars numbers
static sint16 Global_u8GarageSpace = 150u;
static sint16 Global_u8CarsCount = 149u;

// flags
uint8 Global_u8CarInFlag = 0u;	// car go into in the garage
uint8 Global_u8CarOutFlag = 0u; // car go out from the garage

// ADC Notification Callback
void ADC0CallBack(void)
{
	// measure light level
	LDR_u8GetLLFromDigSignal(&Global_GASY->GA_LDR_INPoint);
	if (Global_GASY->GA_LDR_INPoint.LightLevel < GASY_CUTON_LIGHT_LEVE)
	{
		Global_u8CarInFlag = 1u;
	}
	else
	{
		/*do nothing*/
	}
}
void ADC7CallBack(void)
{
	// measure light level
	LDR_u8GetLLFromDigSignal(&Global_GASY->GA_LDR_OutPoint);
	if (Global_GASY->GA_LDR_OutPoint.LightLevel < GASY_CUTON_LIGHT_LEVE)
	{
		Global_u8CarOutFlag = 1u;
	}
	else
	{
		/*do nothing*/
	}
}
////
uint8 GASY_u8init(GASY_CONFIG_t *referance_GASY)
{
	uint8 Local_u8ErrorState = OK;
	if (referance_GASY != NULL)
	{

		Global_GASY = referance_GASY;
		// init enter point
		Global_ADC_Chain_devicses[0].ConversionChannel = (ADC_channel_t)Global_GASY->GA_LDR_INPoint.AnalogChannel_DigitalSignal;
		Global_ADC_Chain_devicses[0].pvnotificationFunction = &ADC0CallBack;
		Global_ADC_Chain_devicses[0].result = &(Global_GASY->GA_LDR_INPoint.AnalogChannel_DigitalSignal);
		// init out point
		Global_ADC_Chain_devicses[1].ConversionChannel = (ADC_channel_t)Global_GASY->GA_LDR_OutPoint.AnalogChannel_DigitalSignal;
		Global_ADC_Chain_devicses[1].pvnotificationFunction = &ADC7CallBack;
		Global_ADC_Chain_devicses[1].result = &(Global_GASY->GA_LDR_OutPoint.AnalogChannel_DigitalSignal);

		// display on screen
		CLCD_VoidSendCommand(CLCD_CLEAR_CMD);
		CLCD_VoidPrintChars("Available: ");
		CLCD_VoidPrintInt((sint32)(Global_u8GarageSpace - Global_u8CarsCount));
		CLCD_voidGoToXY(0,1);
		CLCD_VoidPrintChars("in use: ");
		CLCD_VoidPrintInt((sint32)Global_u8CarsCount);
		// init leds notification
		LED_u8SetON(&referance_GASY->GA_LED_cont);
		LED_u8SetOFF(&referance_GASY->GA_LED_STOP);
	}
	else
	{
		Local_u8ErrorState = NULL_PTR;
	}
	return Local_u8ErrorState;
}

void GASY_voidUpdateAfterLeave()
{

	// display on screen
	CLCD_VoidSendCommand(CLCD_CLEAR_CMD);
	CLCD_VoidPrintChars("Available: ");
	CLCD_VoidPrintInt((sint32)(Global_u8GarageSpace - Global_u8CarsCount));
	CLCD_voidGoToXY(0,1);
	CLCD_VoidPrintChars("in use: ");
	CLCD_VoidPrintInt((sint32)Global_u8CarsCount);
	// init leds notification
	LED_u8SetON(&Global_GASY->GA_LED_cont);
	LED_u8SetOFF(&Global_GASY->GA_LED_STOP);
	// reset flags
	Global_u8CarInFlag = 0u;
	Global_u8CarOutFlag = 0u;
}
void GASY_voidMainLoop()
{

	while (1)
	{

		// read all LDR light level
		ADC_u8StartChainConverstionAsync(Global_ADC_Chain_devicses, 2u);
		_delay_ms(50);
		// car enter the garage
		if (Global_u8CarInFlag == 1)
		{
			// led notification for stop car while the other one out
			LED_u8SetOFF(&Global_GASY->GA_LED_cont);
			LED_u8SetON(&Global_GASY->GA_LED_STOP);
			//if there is a free parking slot
			if((Global_u8GarageSpace - Global_u8CarsCount)>0){
				//wait for second flag
				while (Global_u8CarOutFlag != 1)
				{
					ADC_u8StartConverstionAsync(Global_ADC_Chain_devicses[1].ConversionChannel,
							Global_ADC_Chain_devicses[1].result, Global_ADC_Chain_devicses[1].pvnotificationFunction);
					

					_delay_ms(50);
				}
				// waiting for car to leave
				while (Global_GASY->GA_LDR_OutPoint.LightLevel < GASY_CUTON_LIGHT_LEVE)
				{
					ADC_u8StartConverstionAsync(Global_ADC_Chain_devicses[1].ConversionChannel,
							Global_ADC_Chain_devicses[1].result, Global_ADC_Chain_devicses[1].pvnotificationFunction);
					

					_delay_ms(50);
				}
				//increase count of cars inside the garage
				Global_u8CarsCount += 1;
				//if there is a no parking slot
			}else{
				//reset flag
				Global_u8CarInFlag = 0;

				CLCD_VoidSendCommand(CLCD_CLEAR_CMD);
				CLCD_VoidPrintChars("no parking available");
				//wait for car to leave
				while (Global_u8CarInFlag != 1)
				{
					ADC_u8StartConverstionAsync(Global_ADC_Chain_devicses[0].ConversionChannel,
							Global_ADC_Chain_devicses[0].result, Global_ADC_Chain_devicses[0].pvnotificationFunction);
					

					_delay_ms(50);
				}

				while (Global_GASY->GA_LDR_INPoint.LightLevel < GASY_CUTON_LIGHT_LEVE)
				{
					ADC_u8StartConverstionAsync(Global_ADC_Chain_devicses[0].ConversionChannel,
							Global_ADC_Chain_devicses[0].result, Global_ADC_Chain_devicses[0].pvnotificationFunction);
					

					_delay_ms(50);
				}
			}
			GASY_voidUpdateAfterLeave();
		} // car out of  the garage
		else if (Global_u8CarOutFlag == 1)
		{

			// led notification for stop car while the other one out
			LED_u8SetOFF(&Global_GASY->GA_LED_cont);
			LED_u8SetON(&Global_GASY->GA_LED_STOP);
			//wait for second flag
			while (Global_u8CarInFlag != 1)
			{
				ADC_u8StartConverstionAsync(Global_ADC_Chain_devicses[0].ConversionChannel,
						Global_ADC_Chain_devicses[0].result, Global_ADC_Chain_devicses[0].pvnotificationFunction);
				

				_delay_ms(50);
			}
			// waiting for car to leave
			while (Global_GASY->GA_LDR_INPoint.LightLevel < GASY_CUTON_LIGHT_LEVE)
			{
				ADC_u8StartConverstionAsync(Global_ADC_Chain_devicses[0].ConversionChannel,
						Global_ADC_Chain_devicses[0].result, Global_ADC_Chain_devicses[0].pvnotificationFunction);
				

				_delay_ms(50);
			}
			Global_u8CarsCount -= 1;
			GASY_voidUpdateAfterLeave();
			//if there is a no parking slot


		}
		else
		{
			/*do nothing*/
		}
	}
}

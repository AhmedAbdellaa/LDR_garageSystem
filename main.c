/*
 * main.c
 *
 *  Created on: Jun 4, 2023
 *      Author: ahmed
 */


#include <util/delay.h>

#include "libraries/STD_TYPES_H.h"
#include "0-MCAL/1-DIO/DIO_interface.h"
#include "0-MCAL/2-Port/PORT_interface.h"
#include "0-MCAL/5-ADC/ADC_interface.h"
#include "0-MCAL/4-GIE/GIE_interface.h"

#include "1-HAL/CLCD/CLCD_interface.h"
#include "1-HAL/LDR/LDR_interface.h"
#include "1-HAL/LED/LED_interface.h"
#include "3-APP/GarageSys/GARAGE_interface.h"



void main()
{
	/*Initialize*/
	Port_voidInit();
	ADC_voidInit();
	GIE_voidEnableGlobal();

	CLCD_VoidInit();


	GASY_CONFIG_t Local_GASY = {{ADC0_SINGLE_ENDED,5000ul,9u},
			{ADC7_SINGLE_ENDED,5000ul,9u},
			{LED_ACTIVE_HIGH,DIO_PORTC,DIO_PIN0},
			 {LED_ACTIVE_HIGH,DIO_PORTC,DIO_PIN1}};

	GASY_u8init(&Local_GASY);
	GASY_voidMainLoop();
//	while(1){}

}

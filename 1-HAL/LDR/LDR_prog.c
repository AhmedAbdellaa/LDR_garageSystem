
#include "../../libraries/STD_TYPES_H.h"
#include "../../libraries/ErrType.h"
#include "../../libraries/MAP.h"
#include "../../0-MCAL/1-DIO/DIO_interface.h"
#include "../../0-MCAL/5-ADC/ADC_interface.h"
#include "LDR_interface.h"

uint8 LDR_u8GetLighlevel(LDR_Config_t* refrance_LDR){
	uint8 Local_u8ErrorState = OK;
	if(refrance_LDR != NULL ){
		uint16 Local_u16Reading ;
		ADC_u8StartConverstionSync(refrance_LDR->AnalogChannel_DigitalSignal,&Local_u16Reading);
		uint16 Local_u16VoltageReading = (uint16)MAP(0u,1023ul,0u,refrance_LDR->max_volt,(sint32)Local_u16Reading);

		refrance_LDR->LightLevel = (Local_u16VoltageReading/1850.0)*100;

	}else{
		Local_u8ErrorState = NULL_PTR;
	}
	return Local_u8ErrorState;
}

uint8 LDR_u8GetLLFromDigSignal(LDR_Config_t* refrance_LDR){
	uint8 Local_u8ErrorState = OK;
	if(refrance_LDR != NULL ){

		uint16 Local_u16VoltageReading = (uint16)MAP(0u,1023ul,0u,refrance_LDR->max_volt,(sint32)refrance_LDR->AnalogChannel_DigitalSignal);

		refrance_LDR->LightLevel = (Local_u16VoltageReading/1850.0)*100;

	}else{
		Local_u8ErrorState = NULL_PTR;
	}
	return Local_u8ErrorState;
}

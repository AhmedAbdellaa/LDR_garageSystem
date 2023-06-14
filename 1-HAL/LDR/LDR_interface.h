#ifndef LDR_INTERFACE_H
#define LDR_INTERFACE_H


typedef struct LDR_Config_t
{
	uint16 AnalogChannel_DigitalSignal;
	uint16 max_volt;
    uint16 LightLevel;
}LDR_Config_t;

uint8 LDR_u8GetLighlevel(LDR_Config_t* refrance_LDR);
uint8 LDR_u8GetLLFromDigSignal(LDR_Config_t* refrance_LDR);
#endif

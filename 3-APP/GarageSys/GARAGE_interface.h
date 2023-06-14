//GARAGE SYSTEM : GASY
#ifndef GASY_INTERFACE_H 
#define GASY_INTERFACE_H

#define GASY_CUTON_LIGHT_LEVE 3u
typedef struct GASY_CONFIG_t{
    LDR_Config_t GA_LDR_INPoint;
    LDR_Config_t GA_LDR_OutPoint;
    LED_Config_t GA_LED_STOP;
    LED_Config_t GA_LED_cont;

}GASY_CONFIG_t;

void ADC0CallBack(void);
void ADC7CallBack(void);
uint8 GASY_u8init(GASY_CONFIG_t *referance_GASY);
void GASY_voidUpdateAfterLeave();
void GASY_voidMainLoop();

#endif

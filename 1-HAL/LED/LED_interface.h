#ifndef GARAGE_INTERFACE_H
#define GARAGE_INTERFACE_H

typedef enum LED_Activitype_t{
    LED_ACTIVE_HIGH,LED_ACTIVE_LOW
}LED_Activitype_t;

typedef struct LED_Config_t
{
    LED_Activitype_t Activitype;
    DIO_port_t port;
    DIO_pin_t Pin;
}LED_Config_t;



uint8 LED_u8SetON(const LED_Config_t* copy_LED_Object);
uint8 LED_u8SetOFF(const LED_Config_t* copy_LED_Object);
uint8 LED_u8Toggle(const LED_Config_t* copy_LED_Object);
#endif

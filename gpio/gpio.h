#ifndef _GPIO_H__
#define _GPIO_H__

// Configurer Broche de Port en mode Output Push-Pull
char Port_IO_Init_General_Output(GPIO_TypeDef * Port, u8 Broche);

// Configurer Broche de Port en mode Output Alternative Push-Pull
char Port_IO_Init_Alternative_Output(GPIO_TypeDef * Port, u8 Broche);

// Configurer Broche de Port en mode Input Floating
char Port_IO_Init_Input(GPIO_TypeDef * Port, u8 Broche);

// Configurer Broche de Port en mode Input Analog
char Port_IO_Init_Input_Analog(GPIO_TypeDef * Port, u8 Broche);

// Configurer Broche de Port en mode Input Pull-up
char Port_IO_Init_Input_Pullup(GPIO_TypeDef * Port, u8 Broche);

// Mettre 1 dans la sortie du Port d'une Broche
void Port_IO_Set(GPIO_TypeDef * Port, u8 Broche);

// Mettre 0 dans la sortie du Port d'une Broche
void Port_IO_Reset(GPIO_TypeDef * Port, u8 Broche);

// Lire l'état du Port d'une Broche
unsigned int Port_IO_Read(GPIO_TypeDef * Port, u8 Broche);

// Inverser l'état du Port d'une Broche
void Port_IO_Blink(GPIO_TypeDef * Port, u8 Broche);

#endif /* _GPIO_H__ */

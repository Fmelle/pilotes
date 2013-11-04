#include "stm32f10x.h"
#include "gpio.h"

// Validation des horloges des périphériques GPIO
void Init_Ports_IO(void) {
	(RCC->APB2ENR)|= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN | RCC_APB2ENR_IOPCEN | RCC_APB2ENR_IOPDEN;
}

// Configurer Broche de Port en mode Output General Push-Pull
char Port_IO_Init_General_Output(GPIO_TypeDef * Port, u8 Broche) {
	if(!Port || Broche > 15 || Broche < 0){
		return -1;
	}
	
	if (Broche < 8) {
		// Mode Output 10Hz
		Port->CRL |= (0x01 << Broche * 4);
		// CNF en General Push-Pull
		Port->CRL &= ~(0x01 << (Broche * 4 + 2));
	} else {
		// Mode Output 10Hz
		Port->CRH |= (0x01 << (Broche - 8) * 4);
		// CNF en General Push-Pull
		Port->CRH &= ~(0x01 << ((Broche - 8) * 4 + 2));
	}
	
	return 0;
}

// Configurer Broche de Port en mode Output Alternative Push-Pull
char Port_IO_Init_Alternative_Output(GPIO_TypeDef * Port, u8 Broche) {
	if(!Port || Broche > 15 || Broche < 0){
		return -1;
	}

	if(Broche < 8) {
		// Mode Output 10Hz
		Port->CRL |= (0x01 << Broche * 4);
		// CNF en Alternative Push-Pull
		Port->CRL &= ~(0x01 << (Broche * 4 + 2));
		Port->CRL |= (0x01 << (Broche * 4 + 3));
	} else {
		// Mode Output 10Hz
		Port->CRH |= (0x01 << (Broche - 8) * 4);
		// CNF en Alternative Push-Pull
		Port->CRH &= ~(0x01 << ((Broche - 8) * 4 + 2));
		Port->CRH |= (0x01 << ((Broche - 8) * 4 + 3));
	}

	return 0;
}

// Configurer Broche de Port en mode Input Floating
char Port_IO_Init_Input(GPIO_TypeDef * Port, u8 Broche) {
	if(!Port || Broche > 15 || Broche < 0) {
		return -1;
	}
	
	if (Broche < 8) {
		Port->CRL |= (0x01 << (Broche * 4 + 2));
	} else {
		Port->CRH |= (0x01 << ((Broche - 8) * 4 + 2));
	}
	
	return 0;
}

// Configurer Broche de Port en mode Input Analog
char Port_IO_Init_Input_Analog(GPIO_TypeDef * Port, u8 Broche) {
	if(!Port || Broche > 15 || Broche < 0) {
		return -1;
	}

	if (Broche < 8) {
		Port->CRL &= ~(0x01 << (Broche * 4));
	} else {
		Port->CRH &= ~(0x01 << ((Broche - 8) * 4));
	}

	return 0;
}

// Configurer Broche de Port en mode Input Pull-up
char Port_IO_Init_Input_Pullup(GPIO_TypeDef * Port, u8 Broche) {
	if(!Port || Broche > 15 || Broche < 0) {
		return -1;
	}

	if (Broche < 8) {
		Port->CRL &= ~(0x01 << (Broche * 4));
		Port->CRL |= (0x8 << (Broche * 4));
	} else {
		Port->CRH &= ~(0x01 << ((Broche - 8) * 4));
		Port->CRL |= (0x8 << ((Broche - 8) * 4));
	}

	return 0;
}

// Mettre 1 dans la sortie du Port d'une Broche
void Port_IO_Set(GPIO_TypeDef * Port, u8 Broche) {
	Port->ODR |= (0x01 << Broche);
}

// Mettre 0 dans la sortie du Port d'une Broche
void Port_IO_Reset(GPIO_TypeDef * Port, u8 Broche) {
	Port->ODR &= ~(0x01 << Broche);
}

// Lire l'état du Port d'une Broche
unsigned int Port_IO_Read(GPIO_TypeDef * Port, u8 Broche) {
	return (Port->IDR & ( 1 << Broche )) >> Broche;
}

// Inverser l'état du Port d'une Broche
void Port_IO_Blink(GPIO_TypeDef * Port, u8 Broche) {
	unsigned int etat = (Port->ODR & ( 1 << Broche )) >> Broche;
	
	if (etat == 0) {
		Port_IO_Set(Port, Broche);
	} else {
		Port_IO_Reset(Port, Broche);
	}
}
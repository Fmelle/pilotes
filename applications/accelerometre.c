#include "stm32f10x.h"
#include "../gpio/gpio.h"
#include "../ADC/adc.h"
#include "accelerometre.h"

void Init_Accelerometre(void) {
	// Init GPIO ports and ADC
	Port_IO_Init_Input_Analog(GPIOC, 0);
	Port_IO_Init_Input_Analog(GPIOC, 1);
	Init_ADC_Converter(ADC2);

	// Configure ADC
	Set_Cycles_ADC(ADC2, 7.5);
}

int Get_Valeur_X(void) {
	// Start conversion
	Start_ADC_Single_Conv(ADC2, 10);
	// Return converted value of direction X
	return ADC_Single_Conv_Get_Value(ADC2);
}

int Get_Valeur_Y(void) {
	// Start conversion
	Start_ADC_Single_Conv(ADC2, 11);
}
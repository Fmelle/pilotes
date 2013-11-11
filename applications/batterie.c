#include "stm32f10x.h"
#include "../gpio/gpio.h"
#include "../ADC/adc.h"
#include "batterie.h"

void Init_Batterie(void) {
	// Configure PC.2 en analog input
	Port_IO_Init_Input_Analog(GPIOC, 2);

	// Enable ADC1
	Init_ADC_Converter(ADC1);

	// Set Cycles for ADC1
	Set_Cycles_ADC(ADC1, 7.5);
}

int Get_Batterie_Charge(void) {
	// Commence conversion sur Channel 12
	Start_ADC_Single_Conv(ADC1, 12);

	return (ADC_Single_Conv_Get_Value(ADC1));
}

u8 Check_Batterie_Below_Level(float Seuil_Batterie, float Tension_Alim, float Pont_Div, float Resolution_ADC) {
	// init variables
	u8 Flag = 0;
	int Tension_Batterie = 0;
	float Tension_Batterie_Faible = 0.0;

	// fill variables
	Tension_Batterie = Get_Batterie_Charge();
	Tension_Batterie_Faible = Seuil_Batterie * Tension_Alim * Pont_Div * Resolution_ADC;

	// Tension Batterie < XX %
	if ((float)Tension_Batterie < Tension_Batterie_Faible) {
		Flag = 1;
	}

	return Flag;
}
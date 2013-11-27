#include "stm32f10x.h"
#include "../gpio/gpio.h"
#include "../adc/adc.h"
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

	return ADC_Single_Conv_Get_Value(ADC1);
}

// Fonction a tourner tous les cycles pour regarder si le batterie tient ou pas avec FLAG
u8 Check_Batterie_Below_Level(float Seuil_Batterie, float Tension_Alim, float Pont_Div, float Resolution_ADC) {
	// init variables
	u8 Flag = 0;
	int Tension_Batterie = 0;
	float Tension_Batterie_Faible = 0.0;

	// Fill variables
	Tension_Batterie = Get_Batterie_Charge();
	Tension_Batterie_Faible = Seuil_Batterie * Tension_Alim * Pont_Div * Resolution_ADC;

	// Tension Batterie < XX %
	if ((float)Tension_Batterie < Tension_Batterie_Faible) {
		Flag = 1;
	}

	return Flag;
}

u8 Check_Boat_Batterie_Below_80_percent(void) {
	const float Seuil_Batterie=0.80;
	const float alim = 12.0;
	const float pont_div = 1./13.;
	const float resolution_ADC = 4096./3.3;
	// Return actual batterie alert value
	return (Check_Batterie_Below_Level(Seuil_Batterie, alim, pont_div, resolution_ADC));
}
#include "stm32f10x.h"
#include "../gpio/gpio.h"
#include "../adc/adc.h"
#include "accelerometre.h"
#include "math.h"

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
	// Return converted value of direction Y
	return ADC_Single_Conv_Get_Value(ADC2);
}

u32 Calcul_Accelerometre_Offset(void) {
	// Init vars calculation offset
	u32 ACCUM = 0;
	u8 i = 0;
	
	//// Calcul de OFFSET
	// On calcule l'OFFSET sur 100 mesures de l'axe X
	// - 100 parce que c'est la valeur delta des variations de valeurs
	// - L'axe X represente l'OFFSET de l'accéléromètre du position initiale
	// 	 --> Au position initiale: l'axe X est égale à 0
	while (i < 100) {
		ACCUM += Get_Valeur_X();
		i++;
	}
	// Ceci nous rends l'offset de l'accéléromètre en prenant la moyenne
	return (u32)(ACCUM / 100);
}

u8 Check_Angle_Tangage(u32 OFFSET) {
	// Valeurs lit par l'ADC de l'accelerometre
	int Valeur_X = 0;
	int Valeur_Y = 0;	
	// Flag pour inclinaison du bateau de > 45 degres
	// Init : 0 (< 45 degrees)
	u8 Flag_45 = 0;

	// Get Valeurs lis par les ADC
	Valeur_X = Get_Valeur_X();
	Valeur_Y = Get_Valeur_Y();

	// Substraction de l'offset
	Valeur_X = Valeur_X - OFFSET;
	Valeur_Y = Valeur_Y - OFFSET;
	
	// La valeur en X peut prendre des valeurs négatifs:
	// Valeur absolue pour regarder les deux sens d'inclinaison
	if(Valeur_X < 0) {
		Valeur_X = -Valeur_X;
	}

	// Si l'angle roulis dépasse 45° on lâche les voiles
	// Marge de 70
	if((Valeur_X + 70) > Valeur_Y){
		Flag_45 = 1;
	}
	
	return Flag_45;
}


int Return_Angle_Accelerometre(void) {
	float Ygo = 2300.0, Ymax = 1760.0 ;
	float Y = 0.0;
	int angle=0;
	
	Y = Get_Valeur_Y();
	angle = (acos((Y-Ymax)/(Ygo-Ymax)))*(180/M_PI);
	
	return angle;
}
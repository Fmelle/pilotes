#include "stm32f10x.h"

float Calcule_Percentage_Angle(float Angle_Vent) {
	float Perc = 0.0;
	
	// Angle valid
	if(Angle_Vent >= 180) {
		Angle_Vent = Angle_Vent - 180;
		if(Angle_Vent >= 135) {
			Perc = 0.00 + 0.05;
		} else {
			// Valeur corr. à 1ms/135 * angle [1->135] = 0->1 ms
			Perc = ((180 - Angle_Vent - 45.00) / 135.0) * 0.05 + 0.05;
		}
	} else if(Angle_Vent <= 45) {
		Perc = 0.00 + 0.05;
	} else {
		// Valeur corr. à 1ms/135 * angle [1->135] = 0->1 ms
		Perc = ((Angle_Vent - 45.0) / 135.0) * 0.05 + 0.05;
	}
	
	return Perc;
}

unsigned int Recuperer_Direction_Generale_Du_Vent(float Angle_Vent) {
	unsigned int tribord = 0;
	if(Angle_Vent >= 180) {
		tribord = 1;
	}
	return tribord;
}
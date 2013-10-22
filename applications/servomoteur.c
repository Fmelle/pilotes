#include "stm32f10x.h"

#include "stm32f10x.h"

float Calcule_Percentage_Angle(float Angle_Vent) {
	float Perc = 0.0, tribord = 0.0, babord = 0.0;
	
	if(Angle_Vent > 360.0 || Angle_Vent < 0.0) {
		return -1;
	}
	
	/*
	// Angle divisé entre 
	// 0 deg -> 360 deg
	// (1ms  -> 2ms)
	// 0.05  -> 0.10

	if(Angle_Vent >= 315.0 || Angle_Vent <= 45.0) {
		Perc = 0.05;
		return (1.0 - Perc);
	} 
	if(Angle_Vent < 315.0 && Angle_Vent > 46.0) {
		Angle_Vent = Angle_Vent - 45.0;

		// 46 deg -> 1ms -- 314 deg -> 2ms
		Perc = (Angle_Vent / 269.0) * 0.05 + 0.05;
		return (1.0 - Perc);
	}
	*/

	// Angle divise entre 
	// 0 deg -> 180 deg
	// (1ms  -> 2ms)
	// 0.05  -> 0.10
	// 		et 
	// 180 deg -> 360 deg
	// (1ms    -> 2ms)
	// 0.05    -> 0.10

	if(Angle_Vent <= 360.0 && Angle_Vent > 180.0) {
		tribord = Angle_Vent - 180.0;

		if(tribord >= 135.0) {
			Perc = 0.05;
			return (1.0 - Perc);
		} else {
			tribord = 135.0 - tribord;
			// Valeur corr. à 1ms/135 * angle [1->135] = 0->1 ms
			Perc = (tribord / 134.0) * 0.05 + 0.05;
			return (1.0 - Perc);
		}
	}

	if(Angle_Vent <= 180.0 && Angle_Vent >= 0.0) {
		babord = Angle_Vent;

		if(babord <= 45.0) {
			Perc = 0.05;
			return (1.0 - Perc);
		} else {
			babord = babord - 45.0;
			// Valeur corr. à 1ms/135 * angle [1->135] = 0->1 ms
			Perc = (babord / 135.0) * 0.05 + 0.05;
			return (1.0 - Perc);
		}
	}
}

unsigned int Recuperer_Direction_Generale_Du_Vent(float Angle_Vent) {
	unsigned int tribord = 0;
	if(Angle_Vent >= 180.0) {
		tribord = 1;
	}
	return tribord;
}
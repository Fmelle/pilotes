#include "stm32f10x.h"
#include "servomoteur.h"

float Calcule_Percentage_Angle(float Angle_Vent) {
	float Perc = 0.95;
	
	if (Angle_Vent > 360.0 || Angle_Vent < 0.0) {
		return 1.00;
	}
	
	if (Angle_Vent <= 45.0 || Angle_Vent >= 315.0)  {		
		Perc = 0.90;
	}
	
	if (Angle_Vent > 45.0 && Angle_Vent <= 180.0) {
		Perc = ((0.05/135.0)*Angle_Vent)+0.883333333;
	}
	
	if (Angle_Vent > 180.0 && Angle_Vent < 315.0) {
		Perc = ((-0.05/135.0)*Angle_Vent)+1.016666667;
	}
	
	return (1 - Perc);
}

unsigned int Recuperer_Direction_Generale_Du_Vent(float Angle_Vent) {
	unsigned int tribord = 0;
	if(Angle_Vent >= 180.0) {
		tribord = 1;
	}
	return tribord;
}
#ifndef _SERVO_H__
#define _SERVO_H__

/**
* Transformer une angle de vent en percentage pour PWM
* @param Angle de vent en flottant
* @return Perc en flottant
**/
float Calcule_Percentage_Angle(float Angle_Vent);

/**
* Récupérer si le vent vient de tribord ou babord
* @param Angle de vent flottant
* @return Tribord boolean
**/
unsigned int Recuperer_Direction_Generale_Du_Vent(float Angle_Vent);

#endif /* _SERVO_H__ */
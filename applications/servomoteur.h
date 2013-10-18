#ifndef _SERVO_H__
#define _SERVO_H__

/**
* Transformer une angle de vent pour le servomoteur en percentage
* @param Angle de vent en flottant
* @return Tribord
**/
float Calcule_Percentage_Angle_Servomoteur(float Angle_Vent);

/**
* Récupérer si le vent vient de tribord ou babord
* @param Angle de vent flottant
* @return Perc en flottant
**/
unsigned int Recuperer_direction_generale_du_vent(float Angle_Vent);

#endif /* _SERVO_H__ */
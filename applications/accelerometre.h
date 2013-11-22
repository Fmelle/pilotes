#ifndef _ACCELEROMETRE_H__
#define _ACCELEROMETRE_H__

/**
* Init accelerometre
* @param void
* @return void
**/
void Init_Accelerometre(void);

/**
* Get X direction value
* @param void
* @return void
**/
int Get_Valeur_X(void);

/**
* Get Y direction value
* @param void
* @return void
**/
int Get_Valeur_Y(void);

/**
* Get offset accelerometre
* @param void
* @return offset
**/
u32 Calcul_Accelerometre_Offset(void);

/**
* Check boat inclination and
* return flag (1 - demands interruption, 0 - within boundaries)
* @param offset
* @return flag
**/
u8 Check_Angle_Tangage(u32 OFFSET);

/**
* Get angle tangage de bateau
* @param void
* @return angle
**/
int Return_Angle_Accelero(void);

#endif /* _ACCELEROMETRE_H__ */
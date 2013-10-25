#ifndef _GIROUETTE_H__
#define _GIROUETTE_H__

//Intialise la girouette
void Init_Girouette(void);

// Start Timer
void Timer_Incremental_Start(TIM_TypeDef * Timer);

//Retourne l'angle de al girouette(pour le PWM du servomoteur)
float Return_Angle_Girouette(void);

#endif //_GIROUETTE_H__//

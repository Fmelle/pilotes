#include "stm32f10x.h"
#include "../clock/clock.h"
#include "../timer/timer.h"
#include "../gpio/gpio.h"
#include "../services/servomoteur.h"
#include "../services/girouette.h"
#include "../services/emetteur.h"
#include "commandevoiles.h"

// Initialisation de toutes les fonctions necessaire à la commande des voiles
void Init_Commande_Voiles(void) {
	float Period_Set;
	//Initialisation girouette
	Init_Girouette();
	Port_IO_Init_Alternative_Output(GPIOA, 8);
	//Initialisation du TIM1 en PWM
	Period_Set = Timer_PWM_Init(TIM1, 20000, 1);
}

// Commande des voiles en fonction du vent mesuré
void Update_Commande_Voiles(void) {
	float Perc_Cycle, Period_PWM;
	// Commande voiles
	Perc_Cycle = Calcule_Percentage_Angle(Return_Angle_Girouette());
	Period_PWM = Timer_PWM_Set_Duration(TIM1, Perc_Cycle, 1);
}

// Fonction qui nous permet depuis le couche main de border les voiles
void Release_Voiles(void) {
	float Period_PWM; 
	Period_PWM = Timer_PWM_Set_Duration(TIM1, 0.05, 1);
}

// Fonction qui mets en évidence pour l'utilisateur le vent mesuré
void Send_Angle_Vent(void) {
	char IntroAngleVent[]="\n\rAngle de vent: ";
	// Emission de l'angle du vent
	Send_Chaine(IntroAngleVent);
	Send_Number((int)Return_Angle_Girouette());
}
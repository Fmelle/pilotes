#include "stm32f10x.h"
#include "../clock/clock.h"
#include "../timer/timer.h"
#include "../gpio/gpio.h"
#include "../services/servomoteur.h"
#include "../services/girouette.h"
#include "../services/emetteur.h"
#include "commandevoiles.h"

// Fonction qui initialise toutes les fonctions necessaire a la commande des voiles
void Init_Commande_Voiles(void) {
	float Period_Set;
	//Initialisation girouette
	Init_Girouette();
	Port_IO_Init_Alternative_Output(GPIOA, 8);
	//Initialisation du TIM1 en PWM
	Period_Set = Timer_PWM_Init(TIM1, 20000, 1);
}

//Fonction qui lance la commande des voiles
void Update_Commande_Voiles(void) {
	float Perc_Cycle, Period_PWM, Angle_Vent;
	char IntroAngleVent[]="\n\rAngle de vent: ";
	// Récupération angle vent
	Angle_Vent = Return_Angle_Girouette();
	// Commande voiles
	Perc_Cycle = Calcule_Percentage_Angle(Angle_Vent);
	Period_PWM = Timer_PWM_Set_Duration(TIM1, Perc_Cycle, 1);
	// Emission de l'angle du vent
	Send_Chaine(IntroAngleVent);
	Send_Number((int)Angle_Vent);
}

// Fonction qui nous permet depuis le couche main de border les voiles
void Release_Voiles(void) {
	float Period_PWM; 
	Period_PWM = Timer_PWM_Set_Duration(TIM1, 0.05, 1);
}
#include "stm32f10x.h"
#include "../clock/clock.h"
#include "../timer/timer.h"
#include "../gpio/gpio.h"
#include "../applications/servomoteur.h"
#include "../applications/girouette.h"
#include "commandevoiles.h"

//Fonction qui initialise toutes les fonctions necessaire a la commande des voiles
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
	float Perc_Cycle, Period_PWM;
	//Lancement du programme de commande de voile
	Perc_Cycle = Calcule_Percentage_Angle(Return_Angle_Girouette());
	Period_PWM = Timer_PWM_Set_Duration(TIM1, Perc_Cycle, 1);
}
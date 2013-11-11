#include "stm32f10x.h"
#include "../clock/clock.h"
#include "../timer/timer.h"
#include "../gpio/gpio.h"
#include "../applications/servomoteur.h"
#include "../applications/girouette.h"

//Fonction qui initialise toutes les fonctions necessaire a la commande des voiles
void Init_Commandevoiles( void ) {
	
	//Initialisation girouette
	Init_Girouette();
	Port_IO_Init_Alternative_Output(GPIOB, 8);
	
	float Period_Set, Period_PWM, Perc_Cycle;
	
	//Initialisation du TIM1 en PWM
	Period_Set = Timer_PWM_Init(TIM1, 20000, 1);
	
	//Mise a 1 du bit MOE
	TIM1->BDTR |= 0x8000;
	
}

//Fonction qui lance la commande des voiles
void Deb_Commande_Voiles (void){
	
//Lancement du programme de commande de voile
	while (1) {
		
	Perc_Cycle = Calcule_Percentage_Angle(Return_Angle_Girouette());
	Period_PWM = Timer_PWM_Set_Duration(TIM1, Perc_Cycle, 1);
	
	}
	
	
	
}
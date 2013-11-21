#include "stm32f10x.h"
#include "../clock/clock.h"
#include "../timer/timer.h"
#include "../gpio/gpio.h"
#include "../applications/moteur_cc.h"
#include "commandeplateau.h"

void Init_Commande_Plateau(void) {
	// Init Moteur CC
	Init_Moteur_CC();
}

void Update_Commande_Plateau(void) {
	// Surveille commande Moteur CC
	float Duty, Period_PWM;
	// Recuperer commande
	Duty = Duty_Cycle_Moteur_CC();
	// Set commande
	Period_PWM = Timer_PWM_Set_Duration(TIM2, Duty, 2);
}
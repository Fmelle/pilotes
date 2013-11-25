#include "stm32f10x.h"
#include "../services/moteur_cc.h"
#include "commandeplateau.h"

void Init_Commande_Plateau(void) {
	// Init Moteur CC
	Init_Moteur_CC();
}

void Update_Commande_Plateau(void) {
	// Surveille commande Moteur CC
	float Duty;
	// Recuperer commande
	Duty = Duty_Cycle_Moteur_CC();
	// Set commande
	Set_Commande_Moteur_CC(Duty);
}
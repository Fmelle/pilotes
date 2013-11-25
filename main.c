//__________________________________________________________
// BINOME :
// ETAT : 
//__________________________________________________________

//____ registres de périphériques du stm_32
#include "stm32f10x.h"
#include "../clock/clock.h"
#include "../timer_systick/timer_systick.h"
#include "../Applications/commandevoiles.h"
#include "../Applications/commandeplateau.h"
#include "../Applications/surveillealerte.h"

// Set Systick handler
void Cycle (void) {
	u8 FlagAccelero = Controle_Inclinaison_Bateau();
	u8 FlagBatterie = Controle_Batterie_Faible();
	
	// Surveille commande voiles
	if(FlagAccelero == 0) {
		Update_Commande_Voiles();
	} else {
		Close_Voiles();
	}
	
	// Surveille commande plateau
	Update_Commande_Plateau();
}

int main (void) {
	float Duree_Systick;
	
	// Configure clocks
	CLOCK_Configure();
	// Init surveille du bateau
	Init_Surveille_Alerte();
	// Init commande des voiles
	Init_Commande_Voiles();
	// Init commande du plateau
	Init_Commande_Plateau();

	// SYSTICK Init and config (Period: 100ms ; Priority: 2)
	Duree_Systick = Duree Systick_Period(100000);
	Systick_Prio_IT(2, Cycle);
	SysTick_On;
	SysTick_Enable_IT;

	return 0;
}


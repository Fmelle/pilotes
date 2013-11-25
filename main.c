//__________________________________________________________
// BINOME :
// ETAT : 
//__________________________________________________________

//____ registres de périphériques du stm_32
#include "stm32f10x.h"
#include "../clock/clock.h"
#include "../timer/timer.h"
#include "../gpio/gpio.h"
#include "../adc/adc.h"
#include "../applications/servomoteur.h"
#include "../applications/girouette.h"
#include "../applications/accelerometre.h"
#include "../applications/batterie.h"
#include "../APP/commandevoiles.h"
#include "../APP/commandeplateau.h"
#include "../APP/surveillealerte.h"
#include "../timer_systick/Timer_Systick.h"

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
	
	// Init periphs
	CLOCK_Configure();
	Init_Ports_IO();
	Init_Timers_1234();
	
	// Init surveille bateau
	Init_Surveille_Alerte();
	// Init commande voiles
	Init_Commande_Voiles();
	// Init commande plateau
	Init_Commande_Plateau();

	// SYSTICK
	Duree_Systick = Duree Systick_Period(100000);
	Systick_Prio_IT(5, Cycle);
	SysTick_On;
	SysTick_Enable_IT;

	return 0;
}


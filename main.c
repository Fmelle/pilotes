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

int main (void)
{
	// Vars globales
	u8 FlagBatterie = 0;
	u8 FlagAccelero = 0;
	
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
	
	while(1) {
		FlagBatterie = Controle_Inclinaison_Bateau();
		FlagAccelero = Controle_Batterie_Faible();
		// Surveille commande voiles
		Update_Commande_Voiles();
		// Surveille commande plateau
		Update_Commande_Plateau();
	}

	return 0;
}


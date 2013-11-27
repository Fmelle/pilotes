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

// Variable globale de compteur
int Compteur_Systick = 0;

// Set Systick handler
void Cycle (void) {
 	Compteur_Systick++;
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

	// SYSTICK Init and config (Period: 33ms ; Priority: 2)
	Duree_Systick = Systick_Period(33000);
	Systick_Prio_IT(2, Cycle);
	SysTick_On;
	SysTick_Enable_IT;
	
	// Surveille bateau
	while(1) {
		
		if (Compteur_Systick % 3 == 1) {
			// Surveille inclinaison
			u8 FlagAccelero = Controle_Inclinaison_Bateau();
			// Surveille commande voiles
			if(FlagAccelero == 1) {
				Release_Voiles();
			} else {
				Update_Commande_Voiles();
			}
		}
				
		if (Compteur_Systick % 9 == 0) {
			// Surveille commande plateau
			Update_Commande_Plateau();	
		}
			
		if (Compteur_Systick % 303 == 0){
			// Surveille batterie
			Controle_Batterie_Faible();
			// Re-init du compteur systick
			Compteur_Systick = 0 ;
		}
		
	}
	
	return 0;
}


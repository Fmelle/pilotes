#include "stm32f10x.h"
#include "../services/accelerometre.h"
#include "../services/emetteur.h"
#include "../services/batterie.h"
#include "surveillealerte.h"

// Offset accéléro globale constant à calculer
u32 OFFSET = 0;

void Init_Surveille_Alerte(void) {
	Init_Accelerometre();
	Init_Emetteur();
	Init_Batterie();
	
	OFFSET = Calcul_Accelerometre_Offset();
}

u8 Controle_Batterie_Faible(void) {
	u8 flag=0;
	
	// Definition des messages d'alerte pour la batterie
	char Chaine1[]="\n\r*Batterie faible*\n\r";
	
	// Appel de la fonction CheckBatterie qui envoie 1 si la batterie 
	// a perdu 20 % de sa tension continue initiale
	flag = Check_Boat_Batterie_Below_80_percent();
	
	// if batterie faible envoie message d'alerte
	if (flag == 1) {
		Send_Chaine(Chaine1);
	}
	
	return flag;
}

u8 Controle_Inclinaison_Bateau(void) {
	u8 flag=0;
	
	// Definition des messages d'alerte pour l'inclinaison du bateau
	char Chaine1[]="\n\r*Angle > 45*\n\r";

	// Appel de la fonction CheckInclinaison qui envoie 1 si l'inclinasion du
	// bateau est plus grande de 45 degres, 0 sinon
	flag = Check_Angle_Tangage(OFFSET);
	
	// If inclinaison bateau > 45° envoie message d'alerte
	if(flag == 1) {
		Send_Chaine(Chaine1);
	}
	
	return flag;
}

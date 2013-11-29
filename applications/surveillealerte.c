#include "stm32f10x.h"
#include "../services/accelerometre.h"
#include "../services/emetteur.h"
#include "../services/batterie.h"
#include "surveillealerte.h"

// Offset accéléro globale constant à calculer
u32 OFFSET = 0;

void Init_Surveille_Alerte(void) {
	
	char Introduction1[]="/////////////////////////\n\r";
	char Introduction2[]="// * PROJECT VOILIER * //\n\r";
	char Introduction3[]="/////////////////////////\n\r";
	char Introduction4[]="// Par:                //\n\r";
	char Introduction5[]="//      CID Ludovic    //\n\r";
	char Introduction6[]="//      DELBECQ Scott  //\n\r";
	char Introduction7[]="//      MELLE Fridtjof //\n\r";
	char Introduction8[]="//      NEROME Nelson  //\n\r";
	char Introduction9[]="//                     //\n\r";
	char IntroductionA[]="/////////////////////////\n\r";
	char IntroductionB[]="//   4 AE IS           //\n\r";
	char IntroductionC[]="//   INSA Toulouse     //\n\r";
	char IntroductionD[]="//                     //\n\r";
	char IntroductionE[]="//................2013 //\n\r";
	
	Init_Accelerometre();
	Init_Emetteur();
	Init_Batterie();

	Send_Chaine(Introduction1);
	Send_Chaine(Introduction2);
	Send_Chaine(Introduction3);
	Send_Chaine(Introduction4);
	Send_Chaine(Introduction5);
	Send_Chaine(Introduction6);
	Send_Chaine(Introduction7);
	Send_Chaine(Introduction8);
	Send_Chaine(Introduction9);
	Send_Chaine(IntroductionA);
	Send_Chaine(IntroductionB);
	Send_Chaine(IntroductionC);
	Send_Chaine(IntroductionD);
	Send_Chaine(IntroductionE);

	// Introduction finie

	char Initialisation1[]="//////////////////////////\n\r";
	char Initialisation2[]="//* Init accelerometre *//\n\r";
	char Initialisation3[]="//////////////////////////\n\r";
	char Initialisation4[]="//* Tournez girouette  *//\n\r";
	
	OFFSET = Calcul_Accelerometre_Offset();

	Send_Chaine(Initialisation1);
	Send_Chaine(Initialisation2);
	Send_Chaine(Initialisation3);
	Send_Chaine(Initialisation4);
}

u8 Controle_Batterie_Faible(void) {
	u8 flag=0;
	
	// Definition des messages d'alerte pour la batterie
	char BatterieFaible[]="\n\r* Batterie faible *\n\r";
	
	// Appel de la fonction CheckBatterie qui envoie 1 si la batterie 
	// a perdu 20 % de sa tension continue initiale
	flag = Check_Boat_Batterie_Below_80_percent();
	
	// If batterie faible envoie message d'alerte
	if (flag == 1) {
		Send_Chaine(BatterieFaible);
	}
		
	return flag;
}

u8 Controle_Inclinaison_Bateau(void) {
	u8 flag=0;
	
	// Definition des messages d'alerte pour l'inclinaison du bateau
	char Chaine1[]="\n\r* Angle roulis > 45 *\n\r";

	// Appel de la fonction CheckInclinaison qui envoie 1 si l'inclinasion du
	// bateau est plus grande de 45 degres, 0 sinon
	flag = Check_Angle_Tangage(OFFSET);
	
	// If inclinaison bateau > 45° envoie message d'alerte
	if(flag == 1) {
		Send_Chaine(Chaine1);
	}
	
	return flag;
}

void Send_Perc_Tension_Batterie(void) {
	char PercBatterie[]="\n\rPerc batterie restant: ";
	// Cahier des charges pour l'alimentation
	const float Alim = 12.0;
	const float Pont_Diviseur = 1./13.;
	const float Resolution_ADC = 4096./3.3;
	// Calcul de tension de la batterie en percentage
	float Tension_Batterie = (float)(Get_Batterie_Charge());
	float Tension_Max = (float)(Alim * Pont_Diviseur * Resolution_ADC);
	int Percentage_Restant = (int)(Tension_Batterie/Tension_Max * 100.0);
	
	Send_Chaine(PercBatterie);
	Send_Number(Percentage);
}
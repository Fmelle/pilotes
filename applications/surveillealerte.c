#include "stm32f10x.h"
#include "../services/accelerometre.h"
#include "../services/emetteur.h"
#include "../services/batterie.h"
#include "surveillealerte.h"

// Offset accéléro globale constant à calculer
u32 OFFSET = 0;

void Init_Surveille_Alerte(void) {
	
	char Introduction1[]="\n\r/////////////////////////\n\r";
	char Introduction2[]="\n\r// * PROJECT VOILIER * //\n\r";
	char Introduction3[]="\n\r/////////////////////////\n\r";
	char Introduction4[]="\n\r// Par:                //\n\r";
	char Introduction5[]="\n\r//      CID Ludovic    //\n\r";
	char Introduction6[]="\n\r//      DELBECQ Scott  //\n\r";
	char Introduction7[]="\n\r//      MELLE Fridtjof //\n\r";
	char Introduction8[]="\n\r//      NEROME Nelson  //\n\r";
	char Introduction9[]="\n\r//                     //\n\r";
	char IntroductionA[]="\n\r/////////////////////////\n\r";
	char IntroductionB[]="\n\r//   4 AE IS           //\n\r";
	char IntroductionC[]="\n\r//   INSA Toulouse     //\n\r";
	char IntroductionD[]="\n\r//                     //\n\r";
	char IntroductionE[]="\n\r//				2013 //\n\r";
	char IntroductionF[]="\n\r/////////////////////////\n\r";
	char IntroductionG[]="\n\r//\n\r";
	char IntroductionH[]="\n\r//\n\r";
	
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
	Send_Chaine(IntroductionF);
	Send_Chaine(IntroductionG);
	Send_Chaine(IntroductionH);

	// Introduction finie

	char Initialisation1[]="\n\r// // // // // // // // // // // // ///\n\r";
	char Initialisation2[]="\n\r// *   Accelerometre initialisee   * //\n\r";
	char Initialisation3[]="\n\r// // // // // // // // // // // // ///\n\r";
	char Initialisation4[]="\n\r// * Veuillez tourner la girouette * //\n\n\n\r";
	
	OFFSET = Calcul_Accelerometre_Offset();

	Send_Chaine(Initialisation1);
	Send_Chaine(Initialisation2);
	Send_Chaine(Initialisation3);
}

u8 Controle_Batterie_Faible(void) {
	u8 flag=0;
	
	// Definition des messages d'alerte pour la batterie
	char Chaine1[]="\n\r * Batterie faible * \n\r";
	
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
	char Chaine1[]="\n\r * Angle tangage du bateau > 45 * \n\r";

	// Appel de la fonction CheckInclinaison qui envoie 1 si l'inclinasion du
	// bateau est plus grande de 45 degres, 0 sinon
	flag = Check_Angle_Tangage(OFFSET);
	
	// If inclinaison bateau > 45° envoie message d'alerte
	if(flag == 1) {
		Send_Chaine(Chaine1);
	}
	
	return flag;
}

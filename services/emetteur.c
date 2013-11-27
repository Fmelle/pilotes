#include "stm32f10x.h"
#include "../usart/usart.h"
#include "../gpio/gpio.h"

// Initialise l'emmetteur
void Init_Emetteur (void) {
	//on initialise l'USART avec un baud de 9600 (cf cahier des charges)	
	Init_Transm_USART(USART1, 9600);
	//On active le port A11 pour la sortie de l'emmeteur
	Port_IO_Init_General_Output(GPIOA,11);
	
	// Mettez le emetteur en transmission en permanence
	Port_IO_Set(GPIOA,11);
	// pour éviter d'observer l'effet du bruit
}

// Envoyer une chaine de caractere
void Send_Chaine(char * Chaine) {
	
	int i;
	char * Caractere;
	Caractere=Chaine;
	
	// Mise a 1 de TX pour demarrer la transmission
	// Port_IO_Set(GPIOA,11); --> voir remarque
	
	while ((*Caractere)!='\0') {
		Transm_USART(USART1,Caractere);	
		// Pour pas remplir le buffer du recepteur (Connecté à l'ordinateur)
		for (i=0 ; i < 100000 ; i++);
		Caractere++;
	}
	
	// Mise a 0 de TX pour terminer la transmission
	// Port_IO_Reset(GPIOA,11); --> voir remarque
	
	// Remarque:
	// Tant que le programme tourne ; on reste en transmission
}

// Envoyer un nombre integer
void Send_Number(int nb) {
	Transm_Nb_USART(USART1, nb);
	// Pour pas remplir le buffer du recepteur (Connecté à l'ordinateur)
	for (i=0 ; i < 100000 ; i++);
}
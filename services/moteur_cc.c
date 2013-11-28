#include "stm32f10x.h"
#include "../../pilotes/GPIO/GPIO.h"
#include "../../pilotes/timer/timer.h"
#include "moteur_cc.h"


void Init_Moteur_CC(void) {
	// Le moteur est rélié (physiquement) à PA1, PA2  - sur TIM2 Channel 2 et 3
	float duree_cycle;

	// Initialisation du recepteur de la telecommande
	duree_cycle = Timer_Basic_Init(TIM4, 30000);
	Init_PWM_Input_Voie_1_et_2(TIM4);
	Port_IO_Init_Input(GPIOB, 6);

	// Initialisation du Moteur CC
	Port_IO_Init_General_Output(GPIOA, 2);
	Port_IO_Init_Alternative_Output(GPIOA, 1);

	// On veut une frequence de 50Hz -> T = 20ms
	Timer_PWM_Init(TIM2, 20000, 2);
	Timer_PWM_Init(TIM2, 20000, 3);
}

float Duty_Cycle_Moteur_CC(void) {
	// Init duty a envoyer
	float duty = 0.0;	

	// Récupération du rapport entre Channel 1 et Channel 2
	// du Timer 4 pour determiner l'impulsion recu
	// -> Sens et vitesse
	float rapport_impulsion;
	u16 duty_TIM4_1, duty_TIM4_2;
	
	duty_TIM4_1 = Get_Timer_CCR(TIM4, 1);
	duty_TIM4_2 = Get_Timer_CCR(TIM4, 2);

	// Rapport de Channel 2 (polarisé) Channel 1 (non-polarisé)
	// pour en déduire direction souhaité à partir de tout
	// télécommande
	rapport_impulsion = ((float)duty_TIM4_2/(float)duty_TIM4_1);

	// Determination du sens et vitesse
	///////////////////////////////////
	//
	// Problème de maitrîser la translation
	// de l'info recu par le Recepteur
	// qui plaît bien le Moteur CC	
	//
	//	TODO1:
	//			Trouver une système X afin
	//			que le Moteur comprend bien 
	//			les info recu par la télécommande
	//
	if (rapport_impulsion >= X && rapport_impulsion <= X) {
		 // État de repos
		 duty = 0.0;
	}	
	
	// Sens babord légère
	if (rapport_impulsion >= X && rapport_impulsion < X) {
		 // Sens babord
		 Port_IO_Reset(GPIOA, 2);
		 // Vitesse
		 duty = 0.33;
	}
	
	// Sens babord max		
	if (rapport_impulsion > X && rapport_impulsion < X) {
		 // Sens babord
		 Port_IO_Reset(GPIOA, 2);
		 // Vitesse
		 duty = 0.66;
	}

	// Sens tribord légère	
	if (rapport_impulsion > X && rapport_impulsion <= X) {
		 // Sens tribord
		 Port_IO_Set(GPIOA, 2); 
		 // Vitesse
		 duty = 0.33;
	}

	// Sens tribord max	
	if (rapport_impulsion > X && rapport_impulsion < X) {
		 // Sens tribord
		 Port_IO_Set(GPIOA, 2); 
		 // Vitesse
		 duty = 0.66;
	}
	///////////////////////////////////

	return duty;
}
	
void Set_Commande_Moteur_CC(float Duty) {
	float Period_PWM;
	// Set Timer output with new duty cycle to affect command
	// of Moteur CC
	Period_PWM = Timer_PWM_Set_Duration(TIM2, Duty, 2);
}
	
#include "stm32f10x.h"
#include "../../pilotes/GPIO/GPIO.h"
#include "../../pilotes/timer/timer.h"
#include "moteur_cc.h"


void Init_Moteur_CC(void) {
	// Le moteur est rélié (physiquement) à PA1 ,PA2 sur TIM2 Channel 2 et 3
	
	Port_IO_Init_General_Output(GPIOA,2);
	Port_IO_Init_Alternative_Output(GPIOA,1);
	Port_IO_Init_Input(GPIOB, 6);
	
	// On initialise le recepteur de la telecommande
	Timer_Basic_Init(TIM4, 30000);
	Init_PWM_Input(TIM4);
	
	// On veut une frequence de 50Hz -> T=20ms
	Timer_PWM_Init(TIM2, 20000, 2);
	Timer_PWM_Init(TIM2, 20000, 3);
}

float Duty_Cycle_Moteur_CC(void) {
	
	float duty = 0.0;
	float duty_telecommande = (float)TIM4->CCR2;
	
	// Valeur reel telecommande [G=2752 : N=3277 : D=3828]
	if (duty_telecommande > 3260.0 && duty_telecommande < 3290.0) {
		 duty = 0.0 ;
	}	
			
	if (duty_telecommande <= 3260.0) {
		 // Sens = 0 -> babord
		 Port_IO_Reset(GPIOA, 2);
		 // Loi linéaire y=-(1.0/527)x+(3277*(1.0/527))
		 duty = (-(1.0/527.0) * duty_telecommande) + (3285*(1.0/527.0)) ;	
	}
	
	
	if (duty_telecommande >= 3290.0) {
		 // Sens = 1 -> tribord
		 Port_IO_Set(GPIOA, 2); 
		 // Loi linéaire y=(1/549)x-(3277*(1/549))
		 duty = ((1.0/549.0) * duty_telecommande) - (3285.0*(1.0/549.0));
	}
	
	return duty;
}
	
void Set_Commande_Moteur_CC(float Duty) {
	float Period_PWM;
	// Set Timer output with new duty cycle to affect command
	// of Moteur CC
	Period_PWM = Timer_PWM_Set_Duration(TIM2, Duty, 2);
}
	
//_________________________________________________________
// BINOME :
// ETAT : 
//__________________________________________________________

//____ registres de p�riph�riques du stm_32
#include "stm32f10x.h"
#include "../pilotes/clock/clock.h"
#include "../pilotes/timer/timer.h"
#include "../pilotes/gpio/gpio.h"
#include "girouette.h"



void Init_Girouette (void) {


	// la girouette est r�lier (physiquement) � PA5 ,PA6 et PA7
	// PA6= TIM3_CH1 et PA7=TIM3_CH2 donc les voie A et B du codeur sont bien reli�s au timer
	//Reste a configur� les PA5,6,7 en INPUT FLOATING
	
	//parametrage des ports d'entr�e du gpio pour le timer incremental
	Port_IO_Init_Input(GPIOA,5);
	Port_IO_Init_Input(GPIOA,6);
	Port_IO_Init_Input(GPIOA,7);
	
	//configuration du timer incremental
	
	Timer_Incremental_Init(TIM3,720);//360 p�riodes sur 1 tour sur chaque voie
	
	Timer_Incremental_Start(TIM3);
	
	//configuration de l'IT sur le PA5
	(EXTI->IMR) = 0x01<<5 ;
	
		//configuration du type d'evenement : IT sur front montant
		(EXTI->RTSR)|=(0x01<<5);
		(EXTI->FTSR) &= ~(0x01 <<5);
	
	//configuration du l'IT sur le M3
	NVIC->ISER[0] |= NVIC_ISER_SETENA_23;
	
	// Priorit� it NVIC
	NVIC->IP[23]=4;
		
	
}

int Return_Angle_Girouette(void){
	
	int angle_girouette;
	angle_girouette=(int)TIM3->CNT;
	angle_girouette=angle_girouette/2;
	return (angle_girouette);
}

void EXTI9_5_IRQHandler (void){
	
	TIM3->CNT=0x0;
	EXTI->PR |= 0x1 <<5;
	
	
}
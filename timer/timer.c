#include "stm32f10x.h"
#include "clock.h"
#include "timer.h"
#include "../gpio/gpio.h"

// Timer Handler fonctions
// For configuration of interruption handlers
static void (* ptfcTim1) (void);
static void (* ptfcTim2) (void);

/////////////////						  /////////////////
// 					  UTILITARIES						 //
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

// Get Timer Frequence
u32 Get_Tim_Freq(TIM_TypeDef * Timer) {
	return CLOCK_GetTIMCLK(Timer);
}

/////////////////						  /////////////////
// 					  INIT TIMERS						 //
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

// INIT
void Init_Timers_1234(void) {
	// Init Timer 1
	(RCC->APB2ENR)|= RCC_APB2ENR_TIM1EN;
	// Init Timer 2, 3, 4
	(RCC->APB1ENR)|= RCC_APB1ENR_TIM2EN | RCC_APB1ENR_TIM3EN | RCC_APB1ENR_TIM4EN;
}

// Set Basic Timer (TIM2, TIM3, TIM4)
float Timer_Basic_Init(TIM_TypeDef * Timer, float Duree_us) {
	u32 frequence_timer = Get_Tim_Freq(Timer);
	float Duree_hz = 1000000.0 / Duree_us;
	
	// Rapport SYSTICK / Frequence Choisi
	float rapport_freq = (float)frequence_timer / Duree_hz;

	// Configuration de Prescaler
	Timer->PSC = (u16)(rapport_freq / 65535.0);
	float PSC = (float)Timer->PSC;
	// Configuration de Auto-Reload
	Timer->ARR = (u16)(rapport_freq / (PSC + 1.0));
	float ARR = (float)Timer->ARR;
	// Enable Timer
	Timer->CR1 |= (0x01 << 0);
	
	// Verification of the timer's given frequence
	return ((PSC + 1.0) * (ARR + 1.0)) / frequence_timer * 1000000.0;
}

// Set Advanced Timer PWM (TIM1, TIM8)
float Timer_PWM_Init(TIM_TypeDef * Timer, float Duree_us, u8 Channel) {
	u32 frequence_timer = Get_Tim_Freq(Timer);
	float Duree_hz = 1000000.0 / Duree_us;
	
	// Rapport SYSTICK / Frequence Choisi
	float rapport_freq = (float)frequence_timer / Duree_hz;

	// Configuration de Prescaler
	Timer->PSC = (u16)(rapport_freq / 65535.0);
	float PSC = (float)Timer->PSC;
	// Configuration de Auto-Reload
	Timer->ARR = (u16)(rapport_freq / (PSC + 1.0));
	float ARR = (float)Timer->ARR;
	
	// Configuration de durée de cycle pour le PWM (init 100 % = 1 / 10 Periode de Timer)
	switch (Channel) {
		case 1:
			Timer->CCR1 |= (u16)(ARR / 10.0);
			// Configuration en mode PWM Mode 1
			Timer->CCMR1 |= (0x110 << ((Channel - 1) * 8 + 4));
			break;
		case 2:
			Timer->CCR2 |= (u16)(ARR / 10.0);
			// Configuration en mode PWM Mode 1
			Timer->CCMR1 |= (0x110 << ((Channel - 1) * 8 + 4));
			break;
		case 3:
			Timer->CCR3 |= (u16)(ARR / 10.0);
			// Configuration en mode PWM Mode 1
			Timer->CCMR2 |= (0x110 << ((Channel - 1) * 8 + 4));
			break;
		case 4:
			Timer->CCR4 |= (u16)(ARR / 10.0);
			// Configuration en mode PWM Mode 1
			Timer->CCMR2 |= (0x110 << ((Channel - 1) * 8 + 4));
			break;
		default:
			Timer->CCR1 |= (u16)(ARR / 10.0);
			// Configuration en mode PWM Mode 1
			Timer->CCMR1 |= (0x110 << ((Channel - 1) * 8 + 4));
			break;
	}

	// Enable PWM
	Timer->CCER |= (0x01 << (Channel - 1) * 4);
	
	// Enable Timer
	Timer->CR1 |= (0x01 << 0);
	
	// Verification of the timer's given frequence
	return ((PSC + 1.0) * (ARR + 1.0)) / frequence_timer * 1000000.0;
}

float Timer_PWM_Set_Duration(TIM_TypeDef * Timer, float Duree_us, u8 Channel) {
	float CCR;
	u32 frequence_timer = Get_Tim_Freq(Timer);

	// Configuration de durée de cycle pour le PWM
	switch (Channel) {
		case 1:
			Timer->CCR1 |= (u16)();
			CCR = (float)Timer->CCR1;
			break;
		case 2:
			Timer->CCR2 |= (u16)();
			CCR = (float)Timer->CCR2;
			break;
		case 3:
			Timer->CCR3 |= (u16)();
			CCR = (float)Timer->CCR3;
			break;
		case 4:
			Timer->CCR4 |= (u16)();
			CCR = (float)Timer->CCR4;
			break;
		default:
			Timer->CCR1 |= (u16)();
			CCR = (float)Timer->CCR1;
			break;
	}

	return (((float)Timer->PSC + 1.0) * (CCR + 1.0)) / frequence_timer * 1000000.0;
}

// Set Basic Timer Incremental Mode (TIM2, TIM3, TIM4)
void Timer_Incremental_Init(TIM_TypeDef * Timer, int Overflow) {

	
// En-dessous: Code trouvé dans le main de projet lié au pilote girouette
/*
	Init_Ports_IO();
	Init_Timers();
	// la girouette est rélier (physiquement) à PA5 ,PA6 et PA7
	// PA6= TIM3_CH1 et PA7=TIM3_CH2 donc les voie A et B du codeur sont bien reliés au timer
	//Reste a configuré les PA5,6,7 en INPUT FLOATING
	
	//parametrage des ports d'entrée du gpio pour le timer incremental
	Port_IO_Init_Input(GPIOA,5);
	Port_IO_Init_Input(GPIOA,6);
	Port_IO_Init_Input(GPIOA,7);
	
	//configuration du timer incremental
	
	Timer_1234_Encoder(TIM3,360);
	
	while(!(GPIOA->ODR & (0x01 << 5)){} // On attent de passer par la position 0 ( la voie index passe a 1 à cette endroit)

	// Enable Timer
	Timer->CR1 |= (0x01 << 0);
*/
	
	//Activation du mode encoder sur les 2 voies
	Timer->SMCR |= 0x11;
	
	//Configuration de a valeur de l'autoreload
	Timer->ARR = (u16) Overflow;
	
	
}

// Start incremental timer
void Timer_Incremental_Start(TIM_TypeDef * Timer){

	// On attend de passer a la position reference
	while (Port_IO_Read(GPIOA,5) == 0) ;
		
	//Le comptage demarre
	Timer->CR1 |= (0x01 << 0);	

}

/////////////////						  /////////////////
// 					  INTERRUPTIONS						 //
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//// Example on interruption handler to define in main.c :
//
/* 	// Define handler
*  	void Interruption_Handler (void);
* 	// Set handler
*  	void Interruption_Handler (void) {
*		Port_IO_Blink(GPIOB, 9);
*	}
*/
///////////////////////////////////////////////////////////

void TIM1_Activate_IT_UP(TIM_TypeDef * Timer, u8 Priority, void (*IT_function) (void)) {
	// Activer l'it dans le timer
	Timer->DIER |= TIM_DIER_UIE;
	// Enable IT de TIM1 au niv u-ctrl
	NVIC->ISER[0] |= NVIC_ISER_SETENA_25;
	// priorité it NVIC
	NVIC->IP[25] = Priority;
	// configurer fonction
	ptfcTim1 = IT_function;
}

void TIM2_Activate_IT(TIM_TypeDef * Timer, u8 Priority, void (*IT_function) (void)) {
	// Activer l'it dans le timer
	Timer->DIER |= TIM_DIER_UIE;
	// Mettre en jeu l'interruption de TIM2 au niv u-ctrl
	(NVIC->ISER[0]) |= NVIC_ISER_SETENA_28;
	// Priorité it NVIC
	NVIC->IP[28]=Priority;
	// configurer fonction
	ptfcTim2 = IT_function;
}

// Interruption Handler TIM1 Update Event
void TIM1_UP_IRQHandler (void) {
	// Interruption registered //
	// Reset interruption flag
	TIM1->SR &= ~(0x01 << 0);
	// Call interrupt routine
	ptfcTim1();
}

// Interruption Handler TIM2 Global Event
void TIM2_IRQHandler (void) {
	// Interruption registered //
	// Reset interruption flag
	TIM2->SR &= ~(0x01 << 0);
	// Call interrupt routine
	ptfcTim2();
}
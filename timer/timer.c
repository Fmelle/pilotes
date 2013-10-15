#include "stm32f10x.h"
#include "clock.h"
#include "timer.h"

// Timer Handler fonctions
// For configuration
static void (* ptfcTim1) (void);
static void (* ptfcTim2) (void);

// INIT
void Init_Timers_1234(void) {
	// Init Timer 1
	(RCC->APB2ENR)|= RCC_APB2ENR_TIM1EN;
	// Init Timer 2, 3, 4
	(RCC->APB1ENR)|= RCC_APB1ENR_TIM2EN | RCC_APB1ENR_TIM3EN | RCC_APB1ENR_TIM4EN;
}

// Set Basic Timer (TIM2, TIM3, TIM4)
float Timer_Basic_Init(TIM_TypeDef * Timer, float Duree_us) {
	u32 frequence_timer = CLOCK_GetTIMCLK(Timer);
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

// Set Advanced Timer PWM (TIM1, TIM2)
float Timer_PWM_Init(TIM_TypeDef * Timer, float Duree_us, u8 Channel) {
	u32 frequence_timer = CLOCK_GetTIMCLK(Timer);
	float Duree_hz = 1000000.0 / Duree_us;
	
	// Set channel pour configuration
	Channel--;
	
	// Rapport SYSTICK / Frequence Choisi
	float rapport_freq = (float)frequence_timer / Duree_hz;

	// Configuration de Prescaler
	Timer->PSC = (u16)(rapport_freq / 65535.0);
	float PSC = (float)Timer->PSC;
	// Configuration de Auto-Reload
	Timer->ARR = (u16)(rapport_freq / (PSC + 1.0));
	float ARR = (float)Timer->ARR;
	
	// Configuration de durée de cycle pour le PWM (init 100 %)
	
	
	// Configuration en PWM Mode 1
	if (Channel < 2) {
		Timer->CCMR1 |= (0x110 << (Channel * 8 + 4));
	} else {
		Timer->CCMR2 |= (0x110 << (Channel * 8 + 4));
	}
	// Enable PWM
	Timer->CCER |= (0x01 << Channel * 4);
	
	// Enable Timer
	Timer->CR1 |= (0x01 << 0);
	
	// Verification of the timer's given frequence
	return ((PSC + 1.0) * (ARR + 1.0)) / frequence_timer * 1000000.0;
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
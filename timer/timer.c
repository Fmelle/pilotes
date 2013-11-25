#include "stm32f10x.h"
#include "../clock/clock.h"
#include "timer.h"

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

// Set Advanced Timer PWM (TIM1, TIM8) Input
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
	
	// Configuration de durée de sortie pour le PWM (init 100 % = 1 / 10 Periode de Timer)
	// APPLICATION: Init en bordage des voiles
	switch (Channel) {
		case 1:
			Timer->CCR1 = (u16)(ARR * 0.1);
			// Configuration en mode PWM Mode 1
			Timer->CCMR1 &= ~(0x1 << ((Channel - 1) * 8 + 4));
			Timer->CCMR1 |= (0x1 << ((Channel - 1) * 8 + 5));
			Timer->CCMR1 |= (0x1 << ((Channel - 1) * 8 + 6));
			break;
		case 2:
			Timer->CCR2 = (u16)(ARR * 0.1);
			// Configuration en mode PWM Mode 1
			Timer->CCMR1 &= ~(0x1 << ((Channel - 1) * 8 + 4));
			Timer->CCMR1 |= (0x1 << ((Channel - 1) * 8 + 5));
			Timer->CCMR1 |= (0x1 << ((Channel - 1) * 8 + 6));
			break;
		case 3:
			Timer->CCR3 = (u16)(ARR * 0.1);
			// Configuration en mode PWM Mode 1
			Timer->CCMR1 &= ~(0x1 << ((Channel - 1) * 8 + 4));
			Timer->CCMR1 |= (0x1 << ((Channel - 1) * 8 + 5));
			Timer->CCMR1 |= (0x1 << ((Channel - 1) * 8 + 6));
			break;
		case 4:
			Timer->CCR4 = (u16)(ARR * 0.1);
			// Configuration en mode PWM Mode 1
			Timer->CCMR1 &= ~(0x1 << ((Channel - 1) * 8 + 4));
			Timer->CCMR1 |= (0x1 << ((Channel - 1) * 8 + 5));
			Timer->CCMR1 |= (0x1 << ((Channel - 1) * 8 + 6));
			break;
		default:
			Timer->CCR1 = (u16)(ARR * 0.1);
			// Configuration en mode PWM Mode 1
			Timer->CCMR1 &= ~(0x1 << ((Channel - 1) * 8 + 4));
			Timer->CCMR1 |= (0x1 << ((Channel - 1) * 8 + 5));
			Timer->CCMR1 |= (0x1 << ((Channel - 1) * 8 + 6));
			break;
	}

	// Enable PWM
	Timer->CCER |= (0x01 << (Channel - 1) * 4);
	
	// Enable bit MOE si Timer 1
	if (Timer == TIM1) {
		Timer->BDTR |= (0x1 << 15);
	}
	
	// Enable Timer
	Timer->CR1 |= (0x01 << 0);
	
	// Verification of the timer's given frequence
	return ((PSC + 1.0) * (ARR + 1.0)) / frequence_timer * 1000000.0;
}

float Timer_PWM_Set_Duration(TIM_TypeDef * Timer, float Perc_Arr, u8 Channel) {
	float CCR, ARR = (float)Timer->ARR;
	u32 frequence_timer = Get_Tim_Freq(Timer);

	// Configuration de durée de cycle pour le PWM
	switch (Channel) {
		case 1:
			Timer->CCR1 = (u16)(ARR * Perc_Arr);
			CCR = (float)Timer->CCR1;
			break;
		case 2:
			Timer->CCR2 = (u16)(ARR * Perc_Arr);
			CCR = (float)Timer->CCR2;
			break;
		case 3:
			Timer->CCR3 = (u16)(ARR * Perc_Arr);
			CCR = (float)Timer->CCR3;
			break;
		case 4:
			Timer->CCR4 = (u16)(ARR * Perc_Arr);
			CCR = (float)Timer->CCR4;
			break;
		default:
			Timer->CCR1 = (u16)(ARR * Perc_Arr);
			CCR = (float)Timer->CCR1;
			break;
	}
	
	return (((float)Timer->PSC + 1.0) * (CCR + 1.0)) / frequence_timer * 1000000.0;
}

// Set Basic Timer Incremental Mode (TIM2, TIM3, TIM4)
void Timer_Incremental_Init(TIM_TypeDef * Timer, int Overflow) {
	//Activation du mode encoder sur les 2 voies
	Timer->SMCR |= 0x11;
	
	//Configuration de a valeur de l'autoreload
	Timer->ARR = (u16) Overflow;
}

// Start incremental timer
void Timer_Start(TIM_TypeDef * Timer) {
	Timer->CR1 |= (0x01 << 0);
}

// Set Advanced Timer PWM (TIM1, TIM8) Input
void Init_PWM_Input(TIM_TypeDef * Timer) {
	//For example, you can measure the period (in TIMx_CCR1 register) and the duty cycle (in
	//TIMx_CCR2 register) of the PWM applied on TI1 using the following procedure (depending
	//on CK_INT frequency and prescaler value):
	
	//● Select the active input for TIMx_CCR1: write the CC1S bits to 01 in the TIMx_CCMR1
	//register (TI1 selected).
	Timer->CCMR1 |= TIM_CCMR1_CC1S_0 ;
	Timer->CCMR1 &= ~(TIM_CCMR1_CC1S_1);
  
	//● Select the active polarity for TI1FP1 (used both for capture in TIMx_CCR1 and counter
	// clear): write the CC1P bit to ‘0’  in the TIMx_CCER(active on rising edge).
  	Timer->CCER &= ~(TIM_CCER_CC1P);
	
	//● Select the active input for TIMx_CCR2: write the CC2S bits to 10 in the TIMx_CCMR1
	//register (TI1 selected).
	
	Timer->CCMR1|= TIM_CCMR1_CC2S_1 ;
	Timer->CCMR1 &= ~(TIM_CCMR1_CC2S_0);
	
	//● Select the active polarity for TI1FP2 (used for capture in TIMx_CCR2): write the CC2P
	//bit to ‘1’ in the TIMx_CCER(active on falling edge).

  	Timer->CCER |= (TIM_CCER_CC2P );
	
	//● Select the valid trigger input: write the TS bits to 101 in the TIMx_SMCR register
	//(TI1FP1 selected).
 	Timer->SMCR |= TIM_SMCR_TS_0 | TIM_SMCR_TS_2;
 	Timer->SMCR &= ~(TIM_SMCR_TS_1);
 
	//● Configure the slave mode controller in reset mode: write the SMS bits to 100 in the
	//TIMx_SMCR register.
	Timer->SMCR |= TIM_SMCR_SMS_2;
 	Timer->SMCR &= ~(TIM_SMCR_SMS_1);
 	Timer->SMCR &= ~(TIM_SMCR_SMS_0);

	//● Enable the captures: write the CC1E and CC2E bits to ‘1’ in the TIMx_CCER register
	Timer->CCER |= TIM_CCER_CC2E | TIM_CCER_CC1E ;
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
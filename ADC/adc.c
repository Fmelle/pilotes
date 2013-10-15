#include "stm32f10x.h"
#include "clock.h"
#include "adc.h"

void Init_AD_CONVERTERS_12(void) { 
	(RCC->APB2ENR)|= RCC_APB2ENR_ADC1EN | RCC_APB2ENR_ADC2EN;
}

float Init_ADC_Single_Conv_Tech_Max(ADC_TypeDef * ADC) {
	// Obtenir le freq d'entrée du ADC
	u32 ADC_CLK_FREQ = CLOCK_GetPCLK2();
	// En temps
	float ADC_CLK_PERIODE = (1.0/(float)ADC_CLK_FREQ);
	
	// Enable ADC en Single Mode Conversion With Interruption //
	
	// // Reglage générale
	// Set Interruption trigger ON
	ADC->CR1 |= (0x01 << 5);
	// Single
	ADC->CR2 &= ~(0x01 << 1);
	
	// // Reglage de conversion
	// 1 Conversion
	ADC->SQR1 &= ~(0x0001 << 20);
	// Sur voie 1
	ADC->SQR3 &= ~(0x00001 << 0);
	// Temps d'échantillonnage (Sampling time) au max
	ADC->SMPR2 |= (0x111 << 0);
	// ADC -> ON
	ADC->CR2 |= (0x01 << 0);
	
	return ADC_CLK_PERIODE * 252.0 * 1000000.0;
}

void Execute_ADC_Single_Conv(ADC_TypeDef * ADC) {
	// ADC -> START
	ADC->CR2 |= (0x01 << 0);
}
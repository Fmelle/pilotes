#include "stm32f10x.h"
#include "../clock/clock.h"
#include "adc.h"

void Init_ADC_Converter(ADC_TypeDef * ADC) {

	if (ADC == ADC1) {
		(RCC->APB2ENR)|= RCC_APB2ENR_ADC1EN;

		// ADC -> ON
		ADC1->CR2 |= (0x01 << 0);
	}
	if (ADC == ADC2) {
		(RCC->APB2ENR)|= RCC_APB2ENR_ADC2EN;
		
		// ADC -> ON
		ADC2->CR2 |= (0x01 << 0);
	}
	
}

void Set_Cycles_ADC(ADC_TypeDef * ADC, float nb_cycles) {
	int champ=0,num_bit=0;

	if (nb_cycles == 1.5){
		// 000 : 1.5 cycles
		ADC->SMPR1 = 0;
  	    ADC->SMPR2 = 0;
	}
	
	if (nb_cycles == 7.5){	
		// 001: 7.5 cycles
		while (champ < 10) {
			ADC->SMPR1 |= (0x01 << num_bit);
			ADC->SMPR2 |= (0x01 << num_bit);
			champ++;
			num_bit += 3;
		}
	}
	
	if (nb_cycles == 13.5) {
		// 010: 13.5 cycles
		while (champ < 10) {
			ADC->SMPR1 |= (0x01 << (num_bit+1));
			ADC->SMPR2 |= (0x01 << (num_bit+1));
			champ++;
			num_bit += 3;
		}
	}
	
	if (nb_cycles == 28.5) {
		// 011: 28.5 cycles
		while (champ < 10) {
			ADC->SMPR1 = ADC->SMPR1 | (0x01 << num_bit) | (0x01 <<  (num_bit+1));
			ADC->SMPR2 = ADC->SMPR2 | (0x01 << num_bit) | (0x01 <<  (num_bit+1));
			champ++;
			num_bit += 3;
		}
	 }
	
	if (nb_cycles == 41.5) {
		// 	100: 41.5 cycles
		while (champ < 10) {
			ADC->SMPR1 |= (0x01 << (num_bit+2));
			ADC->SMPR2 |= (0x01 << (num_bit+2));
			champ++;
			num_bit += 3;
		}
	}

	if (nb_cycles == 55.5) {
		// 	101: 55.5 cycles
		while (champ < 10) {
			ADC->SMPR1 = ADC->SMPR1 | (0x01 << num_bit) | (0x01 <<  (num_bit+2));
			ADC->SMPR2 = ADC->SMPR2 | (0x01 << num_bit) | (0x01 <<  (num_bit+2));
			champ++;
			num_bit += 3;
		}
	}
	
	if (nb_cycles == 71.5) {
		// 110: 71.5 cycles
		while (champ < 10) {
			ADC->SMPR1 = ADC->SMPR1 | (0x01 << (num_bit+1)) | (0x01 << (num_bit+2));
			ADC->SMPR2 = ADC->SMPR2 | (0x01 << (num_bit+1)) | (0x01 << (num_bit+2));
			champ++;
			num_bit += 3;
		}
	}					   

	if (nb_cycles == 239.5) {
		 ADC->SMPR1 = 0xFFFFFFFF;
		 ADC->SMPR2 = 0xFFFFFFFF;
	}
}

float Init_ADC_Single_Conv(ADC_TypeDef * ADC, u16 Temps_Conv_Total_us) {
	float nb_cycles, nb_cycles_calcule;
	// Obtenir le freq d'entrée du ADC
	u32 ADC_CLK_FREQ = CLOCK_GetADCCLK();
	// En temps
	float ADC_CLK_PERIODE = (1.0/(float)ADC_CLK_FREQ);
	
	// Single Conversion Mode
	ADC->CR2 &= ~(0x01 << 1);

	// Nb de cycles souhaite
	nb_cycles_calcule = (float)Temps_Conv_Total_us * (float)ADC_CLK_FREQ - 12.5;

	if(1.5 > nb_cycles_calcule) {
		nb_cycles = 1.5;
		Set_Cycles_ADC(ADC, nb_cycles);
	}
	
	if((1.5 <= nb_cycles_calcule) && (nb_cycles_calcule <= 7.5)) {
		if((nb_cycles_calcule - 1.5) >= (7.5 - nb_cycles_calcule)) {
			nb_cycles = 7.5;
			Set_Cycles_ADC(ADC, nb_cycles);
		} else {
			nb_cycles = 1.5;
			Set_Cycles_ADC(ADC, nb_cycles);
		}
	}
	
	if((7.5 < nb_cycles_calcule) && (nb_cycles_calcule <= 13.5)) {
		if( (nb_cycles_calcule - 7.5) >= (13.5 - nb_cycles_calcule)) {
			nb_cycles = 13.5;
			Set_Cycles_ADC(ADC, nb_cycles);
		} else {
			nb_cycles = 7.5;
			Set_Cycles_ADC(ADC, nb_cycles);
		}
	}
	
	if((13.5 < nb_cycles_calcule) && (nb_cycles_calcule <= 28.5)) {
		if( (nb_cycles_calcule - 13.5) >= (28.5 - nb_cycles_calcule)) {
			nb_cycles = 28.5;
			Set_Cycles_ADC(ADC,nb_cycles);
		} else {
			nb_cycles = 13.5;
			Set_Cycles_ADC(ADC,nb_cycles);
		}
	}
	
	if((28.5 < nb_cycles_calcule) && (nb_cycles_calcule <= 41.5)) {
		if( (nb_cycles_calcule - 28.5) >= (41.5 - nb_cycles_calcule)) {																		
			nb_cycles = 41.5;
			Set_Cycles_ADC(ADC,nb_cycles);
		} else {
			nb_cycles = 28.5;
			Set_Cycles_ADC(ADC,nb_cycles);
		}
	}
	
	if((41.5 < nb_cycles_calcule) && (nb_cycles_calcule <= 55.5)) {
		if( (nb_cycles_calcule - 41.5) >= (55.5 - nb_cycles_calcule)) {
			nb_cycles = 55.5;
			Set_Cycles_ADC(ADC,nb_cycles);
		} else {
			nb_cycles = 41.5;
			Set_Cycles_ADC(ADC,nb_cycles);
		}
	}
	
	if((55.5 < nb_cycles_calcule) && (nb_cycles_calcule <= 71.5)) {
		if((nb_cycles_calcule - 55.5) >= (71.5 - nb_cycles_calcule)) {
			nb_cycles = 71.5;
			Set_Cycles_ADC(ADC,nb_cycles);
		} else {
			nb_cycles = 55.5;
			Set_Cycles_ADC(ADC,nb_cycles);
		}
	}
	
	if((71.5 <= nb_cycles_calcule) && (nb_cycles_calcule <= 239.5)) {
		if( (nb_cycles_calcule - 71.5) >= (239.5 - nb_cycles_calcule)) {
			nb_cycles = 239.5;
			Set_Cycles_ADC(ADC, nb_cycles);
		} else {
			nb_cycles = 71.5;
			Set_Cycles_ADC(ADC, nb_cycles);
		}
	}
	
	if(239.5 < nb_cycles_calcule) {
		nb_cycles = 239.5;
		Set_Cycles_ADC(ADC, nb_cycles);
	}
	
	// Temps de conversion en us
	return ADC_CLK_PERIODE * (nb_cycles + 12.5) * 1000000.0;
}

void Start_ADC_Single_Conv(ADC_TypeDef * ADC, u8 Channel) {
	// Init EOC register
	ADC->SR &= ~(0x01 << 1);
	
	// Init voies d'enregistrement
	ADC->SQR1 &= ~(0x01 << 0);
	ADC->SQR2 &= ~(0x01 << 0);
	ADC->SQR3 &= ~(0x01 << 0);
	
	// 1 Conversion
	ADC->SQR1 &= ~(0xF << 20);
	// Channel to read
	ADC->SQR3 |= Channel;

	// ADC -> START
	ADC->CR2 |= (0x01 << 0);
}

int ADC_Single_Conv_Get_Value(ADC_TypeDef * ADC) {
	// Wait for interruption End of Conversion
	while ((ADC->SR & (0x01 << 1)) == 0);
	
	return (ADC->DR);
}
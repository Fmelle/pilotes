#include "stm32f10x.h"
#include "usart.h"
#include "../gpio/gpio.h"
#include "../clock/clock.h"

//Initialisation de l'USART en transmission
void Init_Transm_USART (USART_TypeDef *USART, int Baud) {
	
	
	// On definit les variables qui vont servir au calcul
	
	float Usart_DIV=0;
	unsigned int USARTDIV_Mantisse=0;
	
	u32 frequence_PCLK=0;
	
	// Activation des horloges de peripheriques USART
	if (USART == USART1)
	{
		(RCC->APB2ENR)=(RCC->APB2ENR) | RCC_APB2ENR_USART1EN;
		
		
		// Configuration de USART1_TX (broche PA9)
		Port_IO_Init_Alternative_Output(GPIOA,9);
		
		
		// Lecture de la frequence de PCLK2
		frequence_PCLK = CLOCK_GetPCLK2();		
	}
	if (USART == USART2)
	{
		(RCC->APB1ENR)=(RCC->APB1ENR) | RCC_APB1ENR_USART2EN;
		
		// Configuration de USART2_TX (broche PA2)
		Port_IO_Init_Alternative_Output(GPIOA,2);
		
		// Lecture de la frequence de PCLK2
		frequence_PCLK = CLOCK_GetPCLK1();
	}
	if (USART == USART3)
	{
		(RCC->APB1ENR)=(RCC->APB1ENR) | RCC_APB1ENR_USART3EN;
		
		// Configuration de USART2_TX (broche PB10)
		Port_IO_Init_Alternative_Output(GPIOB,10);
		
		// Lecture de la frequence de PCLK2
		frequence_PCLK = CLOCK_GetPCLK1();
	}
		
	// Enable the USART by writing the UE bit in USART_CR1 register to 1 (bit 13)
	USART->CR1 |= (1 << 13);

	// Program the M bit in USART_CR1 to define the word length= 8 bits (bit 12);
	USART->CR1 &= ~(1 << 12);

	// Program the number of stop bits in USART_CR2 (bit 13:12)
	// 00 = 1 stop;				10 = 2 stops
	USART->CR2 &= ~(3 << 12);

	// Select baut rate USART_BRR register
	
	// horloge PCLK2 pour USART1 (72 MHz max)
	// horloge PCLK1 pour USART2,3,4 (36 MHz max)
	
	// Lecture de USART_DIV
	Usart_DIV = (float) frequence_PCLK/(16*Baud);
	
	// Recuperation de la Mantisse 
	USARTDIV_Mantisse = (int) Usart_DIV;
	
	// Ecriture de la mantisse dans le registre BRR bits [4:15]
	USART->BRR = (USARTDIV_Mantisse << 4);
	
	// Calcul de la fraction dans la meme variable
	Usart_DIV = Usart_DIV - (float)USARTDIV_Mantisse;
	Usart_DIV *= 16;
	
	// Ecriture de la fraction dans le registre BRR
	USART->BRR |= ((u8)Usart_DIV);


	// Clear TC bit (transmission non fini)
	USART->SR &= ~(1 << 6);
}

// Envoie un caractere via l'USART
void Transm_USART(USART_TypeDef * USART, char *caractere) {
		
	//On active la transmission en mettant el bit TE de USART_CR1 a 1
	USART->CR1 |= (1 << 3);
		
	//Ecriture du caractere a envoyer dans USART_DR
	USART->DR= (*caractere);	
}

// Envoie un nombre via l'USART
void Transm_Nb_USART(USART_TypeDef * USART, int nb) {
		
	//On active la transmission en mettant el bit TE de USART_CR1 a 1
	USART->CR1 |= (1 << 3);
		
	// Ecriture du nombre a envoyer dans USART_DR
	USART->DR = nb;
}
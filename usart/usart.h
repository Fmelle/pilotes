#include "stm32f10x.h"


//Initialisation de l'USART en transmission
void Init_Transm_USART (USART_TypeDef *USART, int Baud);

//Fonction qui envoie un caractere via l'USART
void Transm_USART(USART_TypeDef *USART, char *caractere);
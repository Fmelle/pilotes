#ifndef _USART_H__
#define _USART_H__

// Initialisation de l'USART en transmission
void Init_Transm_USART (USART_TypeDef * USART, int Baud);

// Envoyer un caractere via l'USART
void Transm_USART(USART_TypeDef * USART, char *caractere);

// Envoyer un nombre via l'USART
void Transm_Nb_USART(USART_TypeDef * USART, int nb);

#endif /* _USART_H__ */
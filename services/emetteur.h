#include "stm32f10x.h"
#include "../usart/usart.h"
#include "../gpio/gpio.h"

//Initialise l'emmetteur
void Init_Emetteur (void);

//Envoie une chaine de caractere
void Send_Chaine(char * Chaine);
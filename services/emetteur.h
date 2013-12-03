#ifndef _EMETTEUR_H__
#define _EMETTEUR_H__

// Initialise l'emetteur
void Init_Emetteur(void);

// Envoyer une chaine de caractere
void Send_Chaine(char * Chaine);

// Envoyer une nombre integer
void Send_Number(unsigned int nb);

#endif /* _EMETTEUR_H__ */
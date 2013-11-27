#ifndef _EMETTEUR_H__
#define _EMETTEUR_H__

//Initialise l'emmetteur
void Init_Emetteur (void);

// Envoyer une chaine de caractere
void Send_Chaine(char * Chaine);

// Envoyer une nombre integer
void Send_Number(int nb);

#endif /* _EMETTEUR_H__ */
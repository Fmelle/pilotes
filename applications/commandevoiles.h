#ifndef _COMMANDE_VOILES_H__
#define _COMMANDE_VOILES_H__

// Fonction qui initialise toutes les fonctions necessaire a la commande des voiles
void Init_Commande_Voiles(void);

// Fonction qui surveille la commande des voiles
void Update_Commande_Voiles(void);

// Fonction qui nous permet depuis le couche main de border les voiles
void Release_Voiles(void);

// Fonction qui mets en �vidence pour l'utilisateur le vent mesur�
void Send_Angle_Vent(void);

#endif /* _COMMANDE_VOILES_H__ */
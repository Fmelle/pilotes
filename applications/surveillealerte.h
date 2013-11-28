#ifndef _SURVEILLE_ALERTE_H__
#define _SURVEILLE_ALERTE_H__

void Init_Surveille_Alerte(void);

u8 Controle_Batterie_Faible(void);

u8 Controle_Inclinaison_Bateau(void);

void Send_Perc_Tension_Batterie(void);

#endif /* _SURVEILLE_ALERTE_H__ */
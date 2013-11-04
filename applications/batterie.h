#ifndef _BATTERIE_H__
#define _BATTERIE_H__

/**
* Configure tous les ADC et Broches 
* pour le service batterie (ADC1, PC.2)
* @param void
* @return void
**/
void Init_Batterie(void);

/**
* Récupérer la valeur convertie par ADC1 sur
* voie 12 (en lancant un noveau conversion
* et renvoiant la valeur)
* @param void
* @return Valeur du registre ADC1->DR
**/
int Get_Batterie_Charge(void);

#endif /* _BATTERIE_H__ */
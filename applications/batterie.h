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

/**
* Regarder si le batterie a perdu du tension
* jusqu'à une seuil donné en renvoyant une flag
* @param Seuil à comparer avec le tension de la batterie
* @param Tension de l'Alimentation (12V normalement)
* @param Valeur correspondant au pont diviseur que
* on peut faire pour exprimer le valeur de l'alimentation
* Tension_Batterie = Vcc / 13 (Vcc = Tension_Alim)
* @param Resolution de l'ADC que on utilise pour lire la tension
* de la batterie
* @return 
* - Flag = 1 si le tension est au-dessous de limite critique.
* - Flag = 0 sinon.
**/
u8 Check_Batterie_Below_Level(float Seuil_Batterie, float Tension_Alim, float Pont_Div, float Resolution_ADC);

/**
* Regarder alerte batterie voilier spécifique
* @param void
* @return 
* - Flag = 1 si le tension est au-dessous de limite critique.
* - Flag = 0 sinon.
**/
u8 Check_Boat_Batterie_Below_80_percent(void);

#endif /* _BATTERIE_H__ */
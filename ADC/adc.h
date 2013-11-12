#ifndef _ADC_H__
#define _ADC_H__

/**
* Activate ADC 1 and ADC 2
* @param ADC Pointeur vers le jeu de registres (de type ADC_TypeDef) du
* ADC considéré
* @return void
**/
void Init_ADC_Converter(ADC_TypeDef * ADC);

/**
* Set conversion cycle settings for ADC
* @param ADC Pointeur vers le jeu de registres (de type ADC_TypeDef) du
* ADC considéré
* @param Number of cycles adapted for ADC
* @return void
**/
void Set_Cycles_ADC(ADC_TypeDef * ADC, float nb_cycles);

/**
* Configure un ADC en Single Mode Conversion
* @param ADC Pointeur vers le jeu de registres (de type ADC_TypeDef ) du
* ADC considéré
* @param Duree de conversion totale souhaite adaptée au signal d'entrée
* de Analog-Digital Converter
* @return Le durée de conversion totale en us
**/
float Init_ADC_Single_Conv(ADC_TypeDef * ADC, u16 Temps_Conv_Total_us);

/**
* Executer une conversion sur un ADC
* @param ADC Pointeur vers le jeu de registres (de type ADC_TypeDef ) du
* ADC considéré
* @return void
**/
void Start_ADC_Single_Conv(ADC_TypeDef * ADC, u8 Channel);

/**
* Récupérer résultat de la conversion (quand prêt)
* @param ADC Pointeur vers le jeu de registres (de type ADC_TypeDef ) du
* ADC considéré
* @return void
**/
int ADC_Single_Conv_Get_Value(ADC_TypeDef * ADC);

#endif /* _ADC_H__ */
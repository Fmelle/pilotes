#ifndef _ADC_H__
#define _ADC_H__

/**
* Activate ADC 1 and ADC 2
* @param void
* @return void
**/
void Init_AD_CONVERTERS_12(void);

/**
* Configure un ADC en Single Mode Conversion
* @param ADC Pointeur vers le jeu de registres (de type ADC_TypeDef ) du
* ADC considéré
* @param Duree_Ech_us souhaite adaptée au signal d'entrée
* de Analog-Digital Converter
* @return Le durée de conversion totale en us
**/
float Init_ADC_Single_Conv_Tech_Max(ADC_TypeDef * ADC);

/**
* Executer une conversion sur un ADC
* @param ADC Pointeur vers le jeu de registres (de type ADC_TypeDef ) du
* ADC considéré
**/
void Execute_ADC_Single_Conv(ADC_TypeDef * ADC);

#endif /* _ADC_H__ */
#ifndef _TIMER_H__
#define _TIMER_H__

/**
* Récupérer frequence d'horloge
* @param Timer Pointeur vers le jeu de registres (de type TIM_TypeDef) du
* timer considéré
* @return Le fréquence d'horloge (de type u32)
**/
u32 Get_Tim_Freq(TIM_TypeDef * Timer);

/**
* Activer Timers 1, 2, 3, 4
* @param Void
* @return Void
**/
void Init_Timers_1234(void);

/**
* Configure un Timer Simple
* @param Timer Pointeur vers le jeu de registres (de type TIM_TypeDef ) du
* timer considéré
* @param Duree_us Intervalle de temps exprimé en μs entre
* deux débordements successifs
* @return Le durée véritable qui a été configurée
**/
float Timer_Basic_Init(TIM_TypeDef * Timer, float Duree_us);

/**
* Configure un Timer en PWM
* @param Timer Pointeur vers le jeu de registres (de type TIM_TypeDef ) du
* timer considéré
* @param Duree_us Intervalle de temps exprimé en μs entre
* deux débordements successifs
* @param Channel Le valeur du channel que on souhaite
* configurer en PWM
* @return Le durée véritable qui a été configurée
**/
float Timer_PWM_Init(TIM_TypeDef * Timer, float Duree_us, u8 Channel);


/**
* Set durée du cycle
* @param Timer Pointeur vers le jeu de registres (de type TIM_TypeDef ) du
* timer considéré
* @param Perc_Arr Percentage de la période de Timer
* souhaité pour le duree de sortie du PWM
* @param Channel Le valeur du channel que on souhaite
* configurer en PWM
* @return Le durée véritable qui a été configurée
**/
float Timer_PWM_Set_Duration(TIM_TypeDef * Timer, float Perc_Arr, u8 Channel);

/**
* Configure un Timer en Incremental
* @param Timer Pointeur vers le jeu de registres (de type TIM_TypeDef ) du
* timer considéré
* @param Overflow Somme de incrementation qui déclenche une interruption
**/
void Timer_Incremental_Init(TIM_TypeDef * Timer, int Overflow);

/**
* Demarre un Timer Incremental
* @param Timer Pointeur vers le jeu de registres (de type TIM_TypeDef ) du
* timer considéré
* @return void
**/
void Timer_Start(TIM_TypeDef * Timer);

/**
* Demarre un Timer Avancé (TIM1 ou TIM8)
* @param Timer Pointeur vers le jeu de registres (de type TIM_TypeDef ) du
* timer considéré
* @return void
**/
void Init_PWM_Input(TIM_TypeDef * Timer);

/**
* Configure la routine d'interruption de TIM1 en mode UPDATE (débordement de timer)
* @param Timer Pointeur vers le jeu de registres (de type TIM_TypeDef ) du
* timer considéré
* @param Priority Niveau de priorité de l'interruption
* @param IT_function Pointeur sur la fonction qui sera exécutée dans le routine
d'interruption
**/
void TIM1_Activate_IT_UP(TIM_TypeDef * Timer, u8 Priority, void (*IT_function) (void));

/**
* Configure la routine d'interruption de TIM2
* @param Timer Pointeur vers le jeu de registres (de type TIM_TypeDef ) du
* timer considéré
* @param Priority Niveau de priorité de l'interruption
* @param IT_function Pointeur sur la fonction qui sera exécutée dans le routine
d'interruption
**/
void TIM2_Activate_IT(TIM_TypeDef * Timer, u8 Priority, void (*IT_function) (void));

#endif /* _TIMER_H__ */

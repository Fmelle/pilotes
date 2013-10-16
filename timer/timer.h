#ifndef _TIMER_H__
#define _TIMER_H__

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
* Configure un Timer en Incremental
* @param Timer Pointeur vers le jeu de registres (de type TIM_TypeDef ) du
* timer considéré
* @param ?????
* @return ?????
**/
void Timer_Incremental_Init(TIM_TypeDef * Timer, int Overflow);

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


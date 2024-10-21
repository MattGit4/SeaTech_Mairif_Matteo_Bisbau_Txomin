/* 
 * File:   timer.h
 * Author: TP-EO-5
 *
 * Created on 2 octobre 2024, 10:34
 */

#ifndef TIMER_H
#define TIMER_H
void InitTimer23(void);
void InitTimer1(void);
void InitTimer4(void);
void SetFreqTimer1(float);

extern unsigned long timestamp;


#endif /* TIMER_H */

#define MOTEUR_DROIT 0
#define MOTEUR_GAUCHE 1